#include "region.h"
#include <geometry/geometry.hpp>

namespace rv
{
    inline Region::Region(const cv::RotatedRect& rect) noexcept
    {
        regionType = RegionType::Geometry;
        shapeRegion = std::make_shared<GeometryRegion>(); 

        shapeRegion->type = GeometryType::RotatedRect;
        shapeRegion->rotateRect = converToRotatedRect(rect);
    }

    template<typename _Tp1, typename _Tp2>
    inline Region::Region(const cv::Point_<_Tp1>& p1, const cv::Point_<_Tp2>& p2) noexcept
    {
        regionType = RegionType::Geometry;
        shapeRegion = std::make_shared<GeometryRegion>(); 

        shapeRegion->type = GeometryType::Line;
        shapeRegion->line = Line<double>(converToPointF(p1), converToPointF(p2));
    }

    template<typename _Tp>
    inline Region::Region(const cv::Point_<_Tp>& center, double radius) noexcept
    {
        regionType = RegionType::Geometry;
        shapeRegion = std::make_shared<GeometryRegion>(); 

        shapeRegion->type = GeometryType::Circle;
        shapeRegion->circle = Circle<double>(converToPointF(center), radius);
    }

    template<typename _Tp>
    inline Region::Region(const cv::Rect_<_Tp>& rect) noexcept
    {
        regionType = RegionType::Geometry;
        shapeRegion = std::make_shared<GeometryRegion>(); 

        shapeRegion->type = GeometryType::RotatedRect;
        shapeRegion->rotateRect = converToRotatedRectF(rect);
    }

    template<typename _Tp>
    inline Region::Region(const cv::Rect_<_Tp>& rect, double angle) noexcept
    {
        regionType = RegionType::Geometry;
        shapeRegion = std::make_shared<GeometryRegion>(); 

        shapeRegion->type = GeometryType::RotatedRect;
        shapeRegion->rotateRect = converToRotatedRectF(rect);
        shapeRegion->rotateRect.angle = angle;
    }

    template<typename _Tp>
    inline Region::Region(const Line<_Tp>& line) noexcept
    {
        regionType = RegionType::Geometry;
        shapeRegion = std::make_shared<GeometryRegion>(); 

        shapeRegion->type = GeometryType::Line;
        shapeRegion->line = line;
    }

    template<typename _Tp>
    inline Region::Region(const Circle<_Tp>& circle) noexcept
    {
        regionType = RegionType::Geometry;
        shapeRegion = std::make_shared<GeometryRegion>(); 

        shapeRegion->type = GeometryType::Circle;
        shapeRegion->circle = circle;
    }

    template<typename _Tp>
    inline Region::Region(const Rectangle<_Tp>& rect) noexcept
    {
        regionType = RegionType::Geometry;
        shapeRegion = std::make_shared<GeometryRegion>(); 

        shapeRegion->type = GeometryType::RotatedRect;
        shapeRegion->rotateRect = RotatedRect<double>(rect, 0);
    }

    template<typename _Tp>
    inline Region::Region(const RotatedRect<_Tp>& rect) noexcept
    {
        regionType = RegionType::Geometry;
        shapeRegion = std::make_shared<GeometryRegion>(); 

        shapeRegion->type = GeometryType::RotatedRect;
        shapeRegion->rotateRect = rect;
    }

}

