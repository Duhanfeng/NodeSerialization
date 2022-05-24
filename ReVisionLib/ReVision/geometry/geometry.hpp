#pragma once

#include "geometries/size.hpp"
#include "geometries/point.hpp"
#include "geometries/line.hpp"
#include "geometries/rectangle.hpp"
#include "geometries/rotatedRect.hpp"
#include "geometries/circle.hpp"
#include "geometries/arc.hpp"
#include "geometries/annulus.hpp"
#include "geometries/ray.hpp"
#include "geometries/pose.hpp"
#include "geometries/polygon.hpp"
#include "geometries/contours.hpp"
#include "geometries/runs.hpp"

#include "adapted/adapted_cv.hpp"

/*
0.尺寸,Size
1.点,Point
2.直线,Line
3.矩形,Rectangle
4.旋转矩形,RotatedRect
5.圆,Circle
6.圆弧,Arc
7.圆环,Annulus
8.射线,Ray
9.位置,Pose
10.多边形,Polygon
11.点集(离散),PointSet
12.轮廓,Contours
13.游程编码/行程编码

备注:Polygon和PointSet的数据结构都是一样的,但是应用上,Polygon常用于描述三角形,四边形,
或其他不规则的多边形,数据量比较少;
而PointSet用于描述多个离散的点位组,数据量级在几百上千上万这个级别;
而在处理上,Polygon多用值类型传递即可;而PointSet多配合智能指针进行传递;
*/

namespace rv
{
    enum class GeometryType
    {
        None = 0,
        Point,
        Line,
        Rectangle,
        RotatedRect,
        Circle,
        Arc,
        Annulus,
        Ray,
        Pose,
        Polygon,
        PointSet,
        Contours,
        Runs,
    };

}
