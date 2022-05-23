#pragma once

#include <opencv2/opencv.hpp>
#include <vector>
#include "remat.h"
#include <geometry/geometry.hpp>

namespace rv
{
    //卡尺极性
    enum class CaliperTransition
    {
        Positive,   //从黑到白
        Negative,   //从白到黑
        All,        //以上两种都可
    };

    //卡尺目标
    enum class CaliperResultSelection
    {
        First,      //第一个点
        Second,     //第二个点
        Last,       //最后一个点
        Max,        //最优点
        All,        //所有点
    };

    class FindEdgeParams
    {
    public:
        double sigma = 1.0;     //滤波系数
        double threshold = 20;  //查找阈值系数

        CaliperTransition transition = CaliperTransition::Positive;         //卡尺极性(颜色变化)
        CaliperResultSelection selection = CaliperResultSelection::Max;     //卡尺目标

    };

    class FitParams
    {
    public:
        int iterations = 5;     //迭代次数,数值越高,效果越好,耗时越长

    };

    class FitLineParams : public FitParams
    {
    public:
        
    };

    enum class FitCircleType
    {
        Circle, //圆
        Arc,    //圆弧
    };

    class FitCircleParams : public FitParams
    {
    public:
        FitCircleType type;

    };

    class FitRectParams : public FitParams
    {
    public:

    };

    class IEdgeFinder
    {
    public:

        //查找边缘
        virtual bool findEdge(rv::InputReMat image, const rv::RotatedRect<double>& region, rv::Point<double>& edge, const FindEdgeParams& params) = 0;
        virtual bool findEdge(rv::InputReMat image, const rv::RotatedRect<double>& region, std::vector<rv::Point<double>>& edges, const FindEdgeParams& params) = 0;

    };

    class IGeometryFitter
    {
    public:
        virtual bool fitLine(const std::vector<rv::Point<double>>& points, rv::Line<double>& line, const FitLineParams& params) = 0;
        virtual bool fitCircle(const std::vector<rv::Point<double>>& points, rv::Circle<double>& circle, const FitCircleParams& params) = 0;
        virtual bool fitRotatedRect(const std::vector<rv::Point<double>>& points, rv::RotatedRect<double>& rect, const FitRectParams& params) = 0;
    };

}
