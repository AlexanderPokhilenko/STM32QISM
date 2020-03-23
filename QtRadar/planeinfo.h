#ifndef PLANEINFO_H
#define PLANEINFO_H


class PlaneInfo
{
public:
    PlaneInfo();
    ~PlaneInfo();
    long long timeMs;
    double radius;
    double height;
    double velocity;
    int index;
};

#endif // PLANEINFO_H
