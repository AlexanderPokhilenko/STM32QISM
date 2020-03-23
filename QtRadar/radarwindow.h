#ifndef RADARWINDOW_H
#define RADARWINDOW_H
#include "dotinfo.h"
#include "rasterwindow.h"
#include "readeriterator.h"
#include <ctime>
#include <QtGui>


///Описывает единственное окно 
class RadarWindow : public RasterWindow
{
    Q_OBJECT
public:
    RadarWindow(const std::string filepath = "data.txt");

protected:
    void timerEvent(QTimerEvent *) override;
    //Отрисовка всей сцены
    void render(QPainter *p) override;
    void mousePressEvent(QMouseEvent *ev) override;
    void wheelEvent(QWheelEvent *ev) override;
    double getCurrentAngle(long long time);

private:
    int m_timerId;
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
    std::chrono::time_point<std::chrono::high_resolution_clock> prevFrameTime;
    //Пересоздаёт таймер
    int myStartTimer();
    ReaderIterator reader;
    std::list<DotInfo> dots;
    QSet<int> neededTables;
    double scale;
    const int period;
    const int maxRadius;
    const double deltaScale;

};

#endif // RADARWINDOW_H
