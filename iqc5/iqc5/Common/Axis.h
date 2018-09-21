#ifndef AXIS_H
#define AXIS_H

template<typename T>
class Axis  //坐标的模板类
{
public:
    Axis()
        :x(0),y(0)
    {

    }

    Axis(T axisX, T axisY)
        :x(axisX),y(axisY)
    {

    }

    void set(T axisX, T axisY)
    {
        x = axisX;
        y = axisY;
    }

public:
    T x;
    T y;
};

#endif // AXIS_H
