#pragma once

#include "remat.h"
#include "region.h"

#include <opencv2/opencv.hpp>
#include <vector>

namespace rv
{
    class IsotropicScaling
    {
    public:
        double max{ 1.0 };
        double min{ 1.0 };
    };

    class AnisotropicScaling
    {
    public:
        double rowMax{ 1.0 };
        double rowMin{ 1.0 };
        double colMax{ 1.0 };
        double colMin{ 1.0 };
    };

    enum class ScalingMode
    {
        None= 0,
        Isotropic,
        Anisotropic,
    };

    //匹配参数,在创建模板后修改有效
    class IMatchParam
    {
    public:

        //角度
        virtual double angleStart() const = 0;
        virtual void setAngleStart(double value) = 0;   //弧度制
        virtual double angleEnd() const = 0;
        virtual void setAngleEnd(double value) = 0;     //弧度制

        //匹配分数
        virtual double minScore() const = 0;
        virtual void setMinScore(double value) = 0;     //[0-1]

        //查找数量
        virtual int numMatches() const = 0;
        virtual void setNumMatches(int value) = 0;      //0代表不限制

        //最大重叠度
        virtual double maxOverlap() const = 0;
        virtual void setMaxOverlap(double value) = 0;   //[0-1]

        //原点偏移
        virtual void getOrigin(cv::Point2d& originOffset, double& angle) const = 0;     //弧度制
        virtual void setOrigin(const cv::Point2d& originOffset, double angle) = 0;

    };

    class MatchResult
    {
    public:
        MatchResult() {}
        MatchResult(double _x, double _y, double _angle, double _score, double _scaleCol, double _scaleRow, std::string _modelIdentifier)
            : x(_x), y(_y), angle(_angle), score(_score),
            scaleCol(_scaleCol), scaleRow(_scaleRow),
            modelIdentifier(_modelIdentifier) {}

        double x{ 0 };
        double y{ 0 };
        double angle{ 0 };          //角度,弧度制,顺时针为正角度
        double score{ 0 };
        double scaleCol{ 1.0 };
        double scaleRow{ 1.0 };
        std::string modelIdentifier;
    };

    class IModel : public IMatchParam
    {
    public:
        //创建/释放
        virtual bool create(InputReMat image, InputRegion region) = 0;
        virtual bool create(InputReMat image, InputRegion region, const IsotropicScaling& scaling) = 0;
        virtual bool create(InputReMat image, InputRegion region, const AnisotropicScaling& scaling) = 0;
        virtual void clear() = 0;

        //查找
        virtual bool find(InputReMat image, InputRegion region, std::vector<MatchResult>& results) const = 0;

    public:
        virtual bool isCreated() const = 0;
        virtual ScalingMode scalingMode() const = 0;
        virtual IsotropicScaling isotropicScaling() const = 0;
        virtual AnisotropicScaling anisotropicScaling() const = 0;
        virtual ReMat templImage() const = 0;
        virtual Region templRegion() const = 0;

    };

    class IShapeModel : public IModel
    {
    public:
        //轮廓
        virtual void getContour(std::vector<cv::Point2d>& points) const = 0;
    };

    class INccModel : public IModel
    {
    public:
    };

    class IColorModel : public IModel
    {
    public:
    };

    class MatchInterface
    {
    public:
        //创建模板
        virtual cv::Ptr<IShapeModel> createShapeModel() = 0;
        virtual cv::Ptr<INccModel> createNccModel() = 0;
        virtual cv::Ptr<IColorModel> createColorModel() = 0;

        //查找
        virtual bool find(InputReMat image, InputRegion region, const IModel& model, std::vector<MatchResult>& results) const = 0;
        virtual bool find(InputReMat image, InputRegion region, const std::vector<IModel>& models, std::vector<MatchResult>& results) = 0;

    public:
        static cv::Ptr<MatchInterface> create(bool useHCore = true);

    };

}

