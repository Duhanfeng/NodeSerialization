#pragma once

namespace qv
{
    class Point2D
    {
    public:
        double x = 0;
        double y = 0;

        Point2D()
        {

        }

        Point2D(double _x, double _y)
        {
            x = _x;
            y = _y;
        }

        static double distance(Point2D p1, Point2D p2)
        {

            return std::sqrt(std::pow((p1.y - p2.y), 2) + std::pow((p1.x - p2.x), 2));
        }
    };

    class Pose2D
    {
    public:
        Point2D point;
        double theta = 0;   //弧度

        Pose2D()
        {

        }

        Pose2D(double _x, double _y, double _theta)
        {
            point.x = _x;
            point.y = _y;
            theta = _theta;
        }

        Pose2D(Point2D point, double _theta)
        {
            point = point;
            theta = _theta;
        }
    };

    class Line2D
    {
    public:
        Point2D p1;
        Point2D p2;

        Line2D()
        {

        }

        Line2D(Point2D _p1, Point2D _p2)
        {
            p1 = _p1;
            p2 = _p2;

        }
    };

    class Circle2D
    {
    public:
        Point2D center;
        double radius = 0.0;    //半径

        Circle2D()
        {

        }

        Circle2D(Point2D _center, double _radius)
        {
            center = _center;
            radius = _radius;

        }
    };

    class Rect2D
    {
    public:
        Point2D center;
        double width = 0.0;     //宽
        double height = 0.0;    //高
        double angle = 0.0;     //角度

        Rect2D()
        {

        }

        Rect2D(Point2D _center, double _width, double _height, double _angle)
        {
            center = _center;
            width = _width;
            height = _height;
            angle = _angle;

        }

    };

}
