#pragma once

#include <vector>
#include "ReVision/remat.h"

namespace rv
{
    class IContour
    {
    public:
        virtual double area() = 0;
        virtual double row() = 0;
        virtual double column() = 0;
        virtual double width() = 0;
        virtual double height() = 0;

        virtual double compactness() = 0;   //精密度, L=轮廓长度,F=面积. max(1, L^2/(2F*pi))
        virtual double contlength() = 0;    //周长

        virtual double convexity() = 0;     //凸性,凸包的面积/原始面积
        virtual double rectangularity() = 0;//矩形度
        virtual double circularity() = 0;   //圆度, min(1, area/(max^2*pi)) max=质心到边缘的最大距离

        //连接性
        virtual double connectNum() = 0;    //连接数量
        virtual int holesNum() = 0;         //孔洞数量
        virtual double holesArea() = 0;     //孔洞面积
        virtual int eulerNum() = 0;         //欧拉数量,连接部件数与孔数之差

        //等价椭圆
        virtual double ellipseMajor() = 0;  //等价椭圆主轴,Ra
        virtual double ellipseMinor() = 0;  //等价椭圆副轴,Rb
        virtual double ellipseRatio() = 0;  //椭圆比率,Rb/Ra
        virtual double ellipseAngle() = 0;  //椭圆角度
        virtual double anisometry() = 0;    //等距,Ra/Rb, >=1
        virtual double bulkiness() = 0;     //蓬松性,pi*Ra*Rb/A
        virtual double structureFactor() = 0;   //结构因子,anisometry*bulkiness-1

        //最小外接矩形
        virtual double smallestRectWidth() = 0;
        virtual double smallestRectHeight() = 0;
        virtual double smallestRectRow() = 0;
        virtual double smallestRectCol() = 0;
        virtual double smallestRectAngle() = 0;

        //圆
        virtual double outerRadius() = 0;   //最小外接圆半径
        virtual double innerRadius() = 0;   //最大内接圆半径

        //距
        virtual void moments(std::vector<double>& m) = 0;

    };

}
