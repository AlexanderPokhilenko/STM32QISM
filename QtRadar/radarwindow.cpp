#include "radarwindow.h"
#include <ctime>
#include <QWidget>
#include <math.h>

const int fps = 20;

RadarWindow::RadarWindow(QSerialPort *serialPort) : m_serialPort(serialPort), scale(1.0), steps(0), maxRadius(4000), maxSteps(200), deltaAngle(360.0 / maxSteps), deltaScale(0.1)
{
    setTitle("Radar");
    resize(500, 500);

    connect(m_serialPort, &QSerialPort::readyRead, this, &RadarWindow::handleReadyRead);
    connect(m_serialPort, &QSerialPort::errorOccurred, this, &RadarWindow::handleError);
    connect(&m_timer, &QTimer::timeout, this, &RadarWindow::handleTimeout);

    m_timer.start(1000 / fps);

    startTime = std::chrono::high_resolution_clock::now();
    prevFrameTime = startTime;
}

void RadarWindow::handleReadyRead()
{
    m_readData.append(m_serialPort->readAll());

    if (!m_timer.isActive()) m_timer.start(1000 / fps);
}

void RadarWindow::handleTimeout()
{
    if (!m_readData.isEmpty())
    {
        int l = m_readData.length();

        if(l % 2 == 1) l--;

        for(int i = 0; i < l; i += 2)
        {
            ushort dist;
            memcpy(&dist, m_readData.mid(i, 2), sizeof(ushort));
            addDot(dist);
        }

        m_readData.remove(0, l);
    }

    renderLater();
}

void RadarWindow::addDot(ushort dist)
{
    double angle = (360.0 - deltaAngle * steps) * M_PI / 180.0;

    qreal x = sin(angle) * dist * 100.0 / maxRadius;
    qreal y = cos(angle) * dist * 100.0 / maxRadius;

    DotInfo info;

    info.x = x;
    info.y = -y;

    dots.push_back(info);

    steps++;
    if(steps >= maxSteps) steps = 0;
}

void RadarWindow::handleError(QSerialPort::SerialPortError serialPortError)
{
    if (serialPortError == QSerialPort::ReadError)
    {
        QTextStream(stdout) << QObject::tr("An I/O error occurred while reading the data from port %1, error: %2").arg(m_serialPort->portName()).arg(m_serialPort->errorString()) << endl;
        QCoreApplication::exit(1);
    }
}

void RadarWindow::render(QPainter *p)
{
    p->translate(width() / 2, height() / 2);

    int side = qMin(width(), height());
    p->scale(side / 200.0, side / 200.0);

    //Сглаживание
    p->setRenderHint(QPainter::Antialiasing);

    p->setPen(Qt::NoPen);
    p->setBrush(Qt::gray);
    p->drawRect(-100, -100, 200, 200);

    p->save();
    p->setPen(QPen(Qt::lightGray, 1));
    p->setBrush(Qt::NoBrush);
    p->drawEllipse(-100, -100, 200, 200);
    p->restore();

    //Вычисление времени
    auto now = std::chrono::high_resolution_clock::now();
    long long renderDelta = std::chrono::duration_cast<std::chrono::milliseconds>(now-prevFrameTime).count();
    prevFrameTime = now;
    p->setPen(QPen(Qt::black, 1));
    QFont font = p->font();
    font.setPointSize(3);
    p->setFont(font);
    p->drawText(0, 100, QString::number(maxRadius / scale));

    p->scale(scale, scale);

    for(DotInfo &dot : dots)
    {
        if(abs(dot.x) * scale <= 100 && abs(dot.y) * scale <= 100)
        {
            int transparency = (255 * dot.timeToFade) / dot.fadingTime;
            auto color = QColor(0, 0, 0, transparency);
            p->setPen(QPen(color, 1));
            p->drawPoint(QPointF(dot.x, dot.y));
        }
        dot.timeToFade -= renderDelta;
        if(dot.timeToFade <= 0) dots.pop_front();
    }

    p->end();
}

void RadarWindow::keyPressEvent(QKeyEvent *event)
{
    char c = static_cast<char>(event->key());
    QByteArray byteArr;
    byteArr.append(c);
    m_serialPort->write(byteArr);
}

void RadarWindow::wheelEvent(QWheelEvent *ev)
{
    scale += ev->delta() / 120.0 * deltaScale;
    if(scale < deltaScale){
        scale = deltaScale;
    }
}
