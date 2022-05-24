#include "region.h"
#include <memory>

namespace rv
{
    Region::Region() noexcept
    {

    }

    Region::Region(const Region& r, bool copyData) noexcept
    {
        regionType = r.regionType;

        if (!copyData)
        {
            switch (r.regionType)
            {
            case rv::RegionType::Geometry:
                shapeRegion = r.shapeRegion;
                break;
            case rv::RegionType::Contours:
                contours = r.contours;
                break;
            case rv::RegionType::PointSet:
                pointSet = r.pointSet;
                break;
            case rv::RegionType::Runs:
                runs = r.runs;
                break;
            default:
                break;
            }
        }
        else
        {
            switch (r.regionType)
            {
            case rv::RegionType::Geometry:
                shapeRegion = std::make_shared<GeometryRegion>(); 
                *shapeRegion = *r.shapeRegion;
                break;
            case rv::RegionType::Contours:
                contours = std::make_shared<Contours<double>>(*r.contours); 
                break;
            case rv::RegionType::PointSet:
                pointSet = std::make_shared<PointSet<double>>(*r.pointSet); 
                break;
            case rv::RegionType::Runs:
                runs = std::make_shared<Runs<int>>(*r.runs); 
                break;
            default:
                break;
            }
        }

    }

    Region::Region(const std::shared_ptr<Contours<double>>& contours) noexcept
    {
        regionType = RegionType::Contours;
        this->contours = contours;
    }

    Region::Region(const std::shared_ptr<PointSet<double>>& pointSet) noexcept
    {
        regionType = RegionType::PointSet;
        this->pointSet = pointSet;
    }

    Region::Region(const std::shared_ptr<Runs<int>>& runs) noexcept
    {
        regionType = RegionType::Runs;
        this->runs = runs;
    }

    Region::Region(cv::InputArray mask) noexcept
    {
        regionType = RegionType::Runs;
        this->runs = convertToRuns(mask);
    }

    Region Region::clone() const
    {
        return Region(*this, true);
    }

    bool Region::empty() const
    {
        return (regionType == RegionType::None);
    }

    void Region::clear()
    {
        shapeRegion = std::shared_ptr<GeometryRegion>();
        contours = std::shared_ptr<Contours<double>>();
        pointSet = std::shared_ptr<PointSet<double>>();
        runs = std::shared_ptr<Runs<int>>();
        regionType = RegionType::None;
    }

    cv::Mat Region::getRegionMask(int rows, int cols) const
    {
        cv::Mat mask;
        
        switch (regionType)
        {
        case rv::RegionType::Geometry:
            if (shapeRegion == nullptr)
            {
                return cv::Mat();
            }
            switch (shapeRegion->type)
            {
            case GeometryType::Line:
                mask = cv::Mat::zeros(rows, cols, CV_8UC1);
                cv::line(mask, converToCvPoint(shapeRegion->line.p1), converToCvPoint(shapeRegion->line.p2), { 255, 255, 255 }, 1, 8);
                break;
            case GeometryType::Circle:
                mask = cv::Mat::zeros(rows, cols, CV_8UC1);
                cv::circle(mask, converToCvPoint(shapeRegion->circle.center), (int)shapeRegion->circle.radius, { 255, 255, 255 }, cv::FILLED, 8);
                break;
            case GeometryType::RotatedRect:
            {
                cv::Point2f pts[4];
                converToCvRotatedRect(shapeRegion->rotateRect).points(pts);
                cv::Point pts2[4];
                for (size_t i = 0; i < 4; i++)
                {
                    pts2[i] = pts[i];
                }
                mask = cv::Mat::zeros(rows, cols, CV_8UC1);
                cv::fillConvexPoly(mask, pts2, 4, { 255, 255, 255 });
                break;
            }
            case GeometryType::Polygon:

                break;
            default:
                break;
            }
            break;
        case rv::RegionType::Contours:
            if (contours == nullptr)
            {
                return cv::Mat();
            }
            break;
        case rv::RegionType::PointSet:
            if (pointSet == nullptr)
            {
                return cv::Mat();
            }
            break;
        case rv::RegionType::Runs:
            if (runs == nullptr)
            {
                return cv::Mat();
            }
            return drawRuns(runs, rows, cols);
        default:
            return cv::Mat();
        }

        return mask;
    }

    bool Region::isShapeRetatedRect() const
    {

        return ((regionType == RegionType::Geometry) && (shapeRegion != nullptr) && (shapeRegion->type == GeometryType::RotatedRect));
    }

    cv::RotatedRect Region::toCvRotatedRect() const
    {
        if (isShapeRetatedRect())
        {
            return converToCvRotatedRect<double>(shapeRegion->rotateRect);
        }

        return cv::RotatedRect();
    }

    std::shared_ptr<Runs<int>> Region::convertToRuns(cv::InputArray mask)
    {
        cv::Mat cvMask = mask.getMat();
        if (!cvMask.empty() && cvMask.isContinuous() && (cvMask.channels() == 1))
        {
            std::shared_ptr<Runs<int>> runs = std::make_shared<Runs<int>>();
            runs->readFormImage(cvMask.data, cvMask.cols, cvMask.rows);
            return runs;
        }

        return std::shared_ptr<rv::Runs<int>>();
    }

    rv::Region Region::mask2Region(cv::InputArray mask)
    {
        
        return rv::Region(convertToRuns(mask));
    }

    cv::Mat Region::drawRuns(std::shared_ptr<Runs<int>> runs, int rows, int cols)
    {
        cv::Mat mask = cv::Mat::zeros(rows, cols, CV_8UC1);

        if (runs == nullptr)
        {
            mask;
        }

        size_t _size = runs->size();
        for (size_t i = 0; i < _size; i++)
        {
            cv::line(mask, { runs->r[i], runs->cb[i] }, { runs->r[i], runs->ce[i] }, { 255, 255, 255 });
        }

        return mask;
    }

#if ENABLE_HCORE

    Region::Region(const HRegion& hregion)
    {
        clear();

        //获取其游程编码
        runs = convertToRuns(hregion);
        //缓存其hregion
        m_hregion = hregion;

        regionType = RegionType::Runs;
    }

    HRegion Region::toHMat() const
    {
        HRegion hregion;
        switch (regionType)
        {
        case rv::RegionType::Geometry:
            if (shapeRegion == nullptr)
            {
                return hregion;
            }
            switch (shapeRegion->type)
            {
            case GeometryType::Circle:
                hregion.GenCircle(shapeRegion->circle.center.y, shapeRegion->circle.center.x, shapeRegion->circle.radius);
                break;
            case GeometryType::RotatedRect:
                hregion.GenRectangle2(shapeRegion->rotateRect.center.y, shapeRegion->rotateRect.center.x, -shapeRegion->rotateRect.angle,
                    shapeRegion->rotateRect.size.width / 2, shapeRegion->rotateRect.size.height / 2);
                break;
            default:
                break;
            }
            break;
        case rv::RegionType::Contours:
            break;
        case rv::RegionType::Runs:
            if (m_hregion.IsInitialized() && (m_hregion.CountObj() > 0))
            {
                return m_hregion;
            }
            else
            {
                const_cast<Region*>(this)->m_hregion = convertToHMat(runs);
                return m_hregion;
            }
            break;
        }

        return hregion;
    }

    bool Region::checkValid(const HRegion& region)
    {
        return region.IsInitialized() && (region.CountObj() > 0);
    }

    std::shared_ptr<Runs<int>> Region::convertToRuns(const HRegion& hregion)
    {
        using namespace HalconCpp;
        HTuple row;
        HTuple columnBegin;
        HTuple columnEnd;
        hregion.GetRegionRuns(&row, &columnBegin, &columnEnd);

        if (row.Length() == 0)
        {
            return std::shared_ptr<Runs<int>>();
        }

        std::shared_ptr<Runs<int>> runs = std::make_shared<Runs<int>>();

        runs->r.resize(row.Length());
        runs->cb.resize(row.Length());
        runs->ce.resize(row.Length());
        for (Hlong i = 0; i < row.Length(); i++)
        {
            runs->r[i] = row[i].I();
            runs->cb[i] = columnBegin[i].I();
            runs->ce[i] = columnEnd[i].I();
        }

        return runs;
    }

    HRegion Region::convertToHMat(const std::shared_ptr<Runs<int>>& runs)
    {
        using namespace HalconCpp;
        if ((runs == nullptr) || (runs->size() == 0))
        {
            return HRegion();
        }

        HTuple row(runs->r.data(), runs->r.size());
        HTuple columnBegin(runs->cb.data(), runs->cb.size());
        HTuple columnEnd(runs->ce.data(), runs->ce.size());

        HRegion region;
        region.GenRegionRuns(row, columnBegin, columnEnd);

        return region;
    }

#endif

}
