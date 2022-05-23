#pragma once

#include <vector>
#include <opencv2/opencv.hpp>
#include "revisonDef.h"

namespace rv
{
    enum class RegionType
    {
        None,
        Shape,      //形状描述法
        Contour,    //轮廓集法
        Runs,       //游程编码法

#if ENABLE_HCORE
        HRegion,
#endif
    };

    //形状区域
    template<typename _Tp> class ShapeRegionUnion
    {
    public:
        Point<_Tp> point;
        Line<_Tp> line;
        Circle<_Tp> circle;
        Rect<_Tp> rect;
        RotatedRect<_Tp> rotateRect;
    };

    //游程组
    class Runs
    {
    public:
        std::vector<int> r;     //当前row
        std::vector<int> cb;    //行程开始col坐标
        std::vector<int> ce;    //行程结束col坐标

        Runs()
        {
            r.clear();
            cb.clear();
            ce.clear();
        }

        bool empty() const { return r.empty(); }
    };

    class ShapeRegion
    {
    public:
        ShapeRegionUnion<double> shape;
        bool isFillup = true;
        ShapeType type = ShapeType::None;
    };

    class Contour
    {
    public:
        std::vector<PointSet<int>> contour;
        bool isHoleFirst = false;       //第一层定义为孔洞标志
    };

    class Region
    {
    public:
        Region();
        Region(const Region& r, bool copyData = false);
        Region(const cv::RotatedRect& rect);
        template<typename _Tp> Region(const cv::Point_<_Tp>& center, double radius);
        template<typename _Tp> Region(const Circle<_Tp>& circle);
        template<typename _Tp> Region(const Rect<_Tp>& rect);
        template<typename _Tp> Region(const RotatedRect<_Tp>& rect);
        Region(const std::shared_ptr<Runs>& runs);
        Region(cv::InputArray mask);
        Region clone() const;

        //功能函数
        bool empty() const;
        void clear();
        static std::shared_ptr<Runs> convertToRuns(cv::InputArray mask);
        static rv::Region mask2Region(cv::InputArray mask);
        cv::Mat getRegionMask(int rows, int cols) const;    //暂时只支持旋转矩形

        bool isShapeRetatedRect() const;                //判断是否是以几何描述的矩形
        cv::RotatedRect converToCvRotatedRect() const;  //以cvRotatedRect的形式获取其region(仅isShapeRetatedRect 有效的情况下可用)

        std::shared_ptr<ShapeRegion> shapeRegion;
        std::shared_ptr<Contour> contour;
        std::shared_ptr<Runs> runs;
        RegionType regionType = RegionType::None;       //决定region使用哪种解析方式

        //HRegion兼容
#if ENABLE_HCORE
    public:
        Region(const HRegion& hregion);
        HRegion toHMat() const;
        static bool checkValid(const HRegion& region);
    private:
        HRegion m_hregion;
        static std::shared_ptr<Runs> convertToRuns(const HRegion& hregion);
        static HRegion convertToHMat(const std::shared_ptr<Runs>& runs);
#endif

    };

    typedef const Region& InputRegion;

    template<typename _Tp>
    Region::Region(const cv::Point_<_Tp>& center, double radius)
    {
        clear();
        regionType = RegionType::Shape;

        ShapeRegion* shape = new ShapeRegion();
        shape->type = ShapeType::Circle;
        shape->shape.circle.center.x = double(center.x);
        shape->shape.circle.center.y = double(center.y);
        shape->shape.circle.radius = double(radius);

        shapeRegion = std::shared_ptr<ShapeRegion>(shape);

    }

    template<typename _Tp>
    Region::Region(const Circle<_Tp>& circle)
    {
        clear();
        regionType = RegionType::Shape;

        ShapeRegion* shape = new ShapeRegion();
        shape->type = ShapeType::Circle;
        shape->shape.circle.center.x = double(circle.center.x);
        shape->shape.circle.center.y = double(circle.center.y);
        shape->shape.circle.radius = double(circle.radius);

        shapeRegion = std::shared_ptr<ShapeRegion>(shape);

    }

    template<typename _Tp>
    Region::Region(const Rect<_Tp>& rect)
    {
        clear();
        regionType = RegionType::Shape;

        ShapeRegion* shape = new ShapeRegion();
        shape->type = ShapeType::Rect;
        shape->shape.rect.center.x = double(rect.center.x);
        shape->shape.rect.center.y = double(rect.center.y);
        shape->shape.rect.size.width = double(rect.size.width);
        shape->shape.rect.size.height = double(rect.size.height);

        shapeRegion = std::shared_ptr<ShapeRegion>(shape);

    }

    template<typename _Tp>
    Region::Region(const RotatedRect<_Tp>& rect)
    {
        clear();
        regionType = RegionType::Shape;

        ShapeRegion* shape = new ShapeRegion();
        shape->type = ShapeType::RotatedRect;
        shape->shape.rotateRect.center.x = double(rect.center.x);
        shape->shape.rotateRect.center.y = double(rect.center.y);
        shape->shape.rotateRect.size.width = double(rect.size.width);
        shape->shape.rotateRect.size.height = double(rect.size.height);
        shape->shape.rotateRect.angle = double(rect.angle);

        shapeRegion = std::shared_ptr<ShapeRegion>(shape);

    }

}
