#ifndef RADARWINDOW_H
#define RADARWINDOW_H
#include "dotinfo.h"
#include "rasterwindow.h"
#include <ctime>
#include <QtGui>
#include <QSerialPort>


///Описывает единственное окно 
class RadarWindow : public RasterWindow
{
    Q_OBJECT
public:
    RadarWindow(QSerialPort *serialPort);

protected:
    //Отрисовка всей сцены
    void render(QPainter *p) override;
    void wheelEvent(QWheelEvent *ev) override;

private slots:
    void handleReadyRead();
    void handleTimeout();
    void handleError(QSerialPort::SerialPortError error);

private:
    void addDot(int dist);
    QSerialPort *m_serialPort;
    QByteArray m_readData;
    QTimer m_timer;
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
    std::chrono::time_point<std::chrono::high_resolution_clock> prevFrameTime;
    std::list<DotInfo> dots;
    double scale;
    int steps;
    const int maxRadius;
    const int maxSteps;
    const double deltaAngle;
    const double deltaScale;

};

#endif // RADARWINDOW_H
