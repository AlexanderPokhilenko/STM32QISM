#ifndef DOTINFO_H
#define DOTINFO_H


class DotInfo
{
public:
    DotInfo(int fadingT = 60000);
    ~DotInfo();
    double x;
    double y;
    double height;
    double velocity;
    int index;
    int fadingTime;
    int timeToFade;
};

#endif // DOTINFO_H
