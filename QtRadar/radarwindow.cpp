#include "radarwindow.h"
#include <ctime>
#include <QWidget>
#include <math.h>
#include <iostream>

const int fps = 20;

RadarWindow::RadarWindow(QSerialPort *serialPort) : m_serialPort(serialPort), scale(1.0), steps(0), maxRadius(4000), maxSteps(200), deltaAngle(360.0 / maxSteps), deltaScale(0.01)
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
    if (m_readData.isEmpty())
    {
        QTextStream(stdout) << QObject::tr("No data was currently available for reading from port %1") .arg(m_serialPort->portName()) << endl;
    }
    else
    {
        QTextStream(stdout) << QObject::tr("Data successfully received from port %1") .arg(m_serialPort->portName()) << endl;
        //QTextStream(stdout) << m_readData << endl;

        const std::string str = m_readData.toStdString();

        std::size_t current, previous = 0;
        current = str.find('\n');
        while (current != std::string::npos)
        {
            std::string sub = str.substr(previous, current - previous);
            std::cout << sub << std::endl;
            int dist = std::stoi(sub);
            addDot(dist);

            previous = current + 1;
            current = str.find('\n', previous);
        }

        int dist = std::stoi(str.substr(previous, current - previous));
        addDot(dist);

        m_readData.clear();
    }

    renderLater();
}

void RadarWindow::addDot(int dist)
{
    double angle = deltaAngle * steps;

    qreal x = sin(angle) * 100.0 * dist / maxRadius;
    qreal y = cos(angle) * 100.0 * dist / maxRadius;

    DotInfo info;

    info.x = x;
    info.y = -y;

    dots.push_back(info);

    steps++;
    if(steps >= maxSteps) steps = 0;
}

void RadarWindow::handleError(QSerialPort::SerialPortError serialPortError)
{
    if (serialPortError == QSerialPort::ReadError) {
        QTextStream(stdout) << QObject::tr("An I/O error occurred while reading "
                                        "the data from port %1, error: %2")
                            .arg(m_serialPort->portName())
                            .arg(m_serialPort->errorString())
                         << endl;
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
    p->setBrush(Qt::black);
    p->drawRect(-100, -100, 200, 200);

    p->save();
    p->setPen(QPen(QColor(0, 255, 0, 150), 1));
    p->setBrush(Qt::NoBrush);
    p->drawEllipse(-100, -100, 200, 200);
    p->drawEllipse(-50, -50, 100, 100);
    for(int i = 0; i < 360; i+= 30){
        p->drawLine(0, 0, 0, 100);
        p->rotate(30);
    }
    p->restore();

    //Вычисление времени
    auto now = std::chrono::high_resolution_clock::now();
    long long renderDelta = std::chrono::duration_cast<std::chrono::milliseconds>(now-prevFrameTime).count();
    prevFrameTime = now;

    //от 0 до 1
    double angle = deltaAngle * steps;
    p->save();
    p->rotate(-90);
    p->rotate(angle);

    QConicalGradient conicalGrad(0, 0, 0);
    conicalGrad.setColorAt(0, Qt::green);
    conicalGrad.setColorAt(0.001, QColor(0, 255, 0, 100));
    conicalGrad.setColorAt(7.5 / 360, Qt::transparent);
    conicalGrad.setColorAt(1.0 - 7.5 / 360, Qt::transparent);
    conicalGrad.setColorAt(1.0 - 0.001, QColor(0, 255, 0, 100));
    conicalGrad.setColorAt(1, Qt::green);
    p->setBrush(QBrush(conicalGrad));
    //p->setPen(QPen(Qt::green, 0.1));
    p->drawPie(-100, -100, 200, 200, -120, 120*2); //full circle = 360 * 16; [-120; 120] = 15 deg
    p->restore();

    p->setPen(QPen(Qt::green, 1));
    QFont font = p->font();
    font.setPointSize(3);
    p->setFont(font);
    p->drawText(0, 100, QString::number(maxRadius / scale));
    p->drawText(0, 50, QString::number(maxRadius / scale / 2.0));

    p->scale(scale, scale);

    for(DotInfo &dot : dots)
    {
        if(abs(dot.x) * scale <= 100 && abs(dot.y) * scale <= 100)
        {
            int transparency = (255 * dot.timeToFade) / dot.fadingTime;
            auto color = QColor(0, 255, 0, transparency);
            p->setPen(QPen(color, 1));
            p->drawPoint(QPointF(dot.x, dot.y));
        }
        dot.timeToFade -= renderDelta;
        if(dot.timeToFade <= 0)
        {
            dots.pop_front();
        }
    }
/*
    if(reader.HasValue())
    {
        PlaneInfo* planeInfo = reader.GetCurrent();

        long long deltaT = planeInfo->timeMs - duration / 1000000;

        while(planeInfo != nullptr && deltaT <= 0)
        {
            if(deltaT > -500)
            {
                double planeAngle = 2 * M_PI * planeInfo->timeMs / 1000 / period;
                //qInfo()<< planeAngle;
                qreal x = planeInfo->radius / maxRadius * sin(planeAngle) * 100;
                qreal y = planeInfo->radius / maxRadius * cos(planeAngle) * 100;
                //qInfo()<< "X: " << x << " Y: " << y;
                reader.MoveNext();

                DotInfo info;
                info.x = x;
                info.y = -y;
                info.timeToFade += deltaT;

                dots.push_back(info);
            }
            else
            {
                qInfo() << "Был пропущен самолёт.";
                reader.MoveNext();
            }

            if(!reader.HasValue()) break;

            planeInfo = reader.GetCurrent();
            deltaT = planeInfo->timeMs - duration / 1000000;
        }
    }
    else
    {
        qInfo() << "Отсутствует текущее значение.";
    }
*/
    p->end();
}

void RadarWindow::wheelEvent(QWheelEvent *ev)
{
    scale += ev->delta() / 120.0 * deltaScale;
    if(scale < deltaScale){
        scale = deltaScale;
    }
}

