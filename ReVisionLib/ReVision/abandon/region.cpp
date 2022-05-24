#include "region.h"
#include "rmath.h"

namespace rv
{
    rv::Region::Region()
    {

    }

    rv::Region::Region(const Region& r, bool copyData)
    {
        clear();
        regionType = r.regionType;

        if (!copyData)
        {
            switch (regionType)
            {
            case rv::RegionType::Shape:
                shapeRegion = r.shapeRegion;
                break;
            case rv::RegionType::Contour:
                contour = r.contour;
                break;
            case rv::RegionType::Runs:
                runs = r.runs;
#if ENABLE_HCORE
                m_hregion = r.m_hregion;
#endif
                break;
            default:
                break;
            }
        }
        else
        {
            switch (regionType)
            {
            case rv::RegionType::Shape:
                shapeRegion = std::make_shared<ShapeRegion>();
                if (r.shapeRegion != nullptr)
                {
                    shapeRegion->isFillup = r.shapeRegion->isFillup;
                    shapeRegion->type = r.shapeRegion->type;
                    shapeRegion->shape = r.shapeRegion->shape;
                }
                break;
            case rv::RegionType::Contour:
                contour = std::make_shared<Contour>();
                if (r.contour != nullptr)
                {
                    contour->contour = r.contour->contour;
                    contour->isHoleFirst = r.contour->isHoleFirst;
                }
                break;
            case rv::RegionType::Runs:
                runs = std::make_shared<Runs>();
                if (r.runs != nullptr)
                {
                    runs->r = r.runs->r;
                    runs->cb = r.runs->cb;
                    runs->ce = r.runs->ce;
#if ENABLE_HCORE
                    m_hregion = r.m_hregion.Clone();
#endif
                }
                break;
            default:
                break;
            }
        }

    }

    rv::Region::Region(const cv::RotatedRect& rect)
    {
        clear();
        regionType = RegionType::Shape;

        shapeRegion = std::make_shared<ShapeRegion>();
        shapeRegion->type = ShapeType::RotatedRect;
        shapeRegion->shape.rotateRect.center.x = rect.center.x;
        shapeRegion->shape.rotateRect.center.y = rect.center.y;
        shapeRegion->shape.rotateRect.size.width = rect.size.width;
        shapeRegion->shape.rotateRect.size.height = rect.size.height;
        shapeRegion->shape.rotateRect.angle = deg2rad(rect.angle);

    }

    Region::Region(const std::shared_ptr<Runs>& runs)
    {
        clear();
        regionType = RegionType::Runs;
        this->runs = runs;
    }

    Region::Region(cv::InputArray mask)
    {
        clear();
        regionType = RegionType::Runs;
        this->runs = convertToRuns(mask);
        
    }

    Region Region::clone() const
    {
        Region region(*this, true);

        return region;
    }

    bool Region::empty() const
    {

        return (regionType == RegionType::None);
    }

    void Region::clear()
    {
        shapeRegion = std::shared_ptr<ShapeRegion>();
        contour = std::shared_ptr<Contour>();
        runs = std::shared_ptr<Runs>();
        regionType = RegionType::None;

#if ENABLE_HCORE
        m_hregion = HRegion();
#endif 

    }

    std::shared_ptr<Runs> Region::convertToRuns(cv::InputArray mask)
    {
        if (mask.empty())
        {
            return std::shared_ptr<rv::Runs>();
        }

        cv::Mat cvMask = mask.getMat();

        //游程编码
        std::shared_ptr<rv::Runs> runs = std::make_shared<Runs>();
        for (int r = 0; r < cvMask.rows; r++)
        {
            uchar* data = cvMask.ptr(r);
            bool isStart = false;
            for (int c = 0; c < cvMask.cols; c++)
            {
                if (!isStart)
                {
                    if (*data != 0)
                    {
                        isStart = true;
                        runs->r.push_back(r);
                        runs->cb.push_back(c);
                    }
                }
                else
                {
                    //如果已经开始,而当前为0,则认为已经结束
                    if (*data == 0)
                    {
                        isStart = false;
                        runs->ce.push_back(c - 1);
                    }
                }

                data++;
            }

            //如果查找到末尾,则保存末尾
            if (isStart)
            {
                runs->ce.push_back(cvMask.cols);
            }
        }

        return runs;
    }

    rv::Region Region::mask2Region(cv::InputArray mask)
    {
        
        return rv::Region(convertToRuns(mask));
    }

    cv::Mat Region::getRegionMask(int rows, int cols) const
    {
        cv::Mat mask = cv::Mat::zeros(rows, cols, CV_8UC1);

        if (isShapeRetatedRect())
        {
            cv::RotatedRect maskRect = converToCvRotatedRect();
            cv::Point2f pts[4];
            maskRect.points(pts);
            cv::Point pts2[4];
            for (size_t i = 0; i < 4; i++)
            {
                pts2[i] = pts[i];
            }
            cv::fillConvexPoly(mask, pts2, 4, { 255, 255, 255 });
        }

        return mask;
    }

    bool Region::isShapeRetatedRect() const
    {

        return ((regionType == RegionType::Shape) && (shapeRegion != nullptr) && ((shapeRegion->type == ShapeType::RotatedRect) || (shapeRegion->type == ShapeType::Rect)));
    }

    cv::RotatedRect Region::converToCvRotatedRect() const
    {
        if ((regionType == RegionType::Shape) && (shapeRegion != nullptr))
        {
            if (shapeRegion->type == ShapeType::RotatedRect)
            {
                return cv::RotatedRect(cv::Point2f((float)shapeRegion->shape.rotateRect.center.x, (float)shapeRegion->shape.rotateRect.center.y),
                    cv::Size2f((float)shapeRegion->shape.rotateRect.size.width, (float)shapeRegion->shape.rotateRect.size.height), (float)rad2deg(shapeRegion->shape.rotateRect.angle));
            }
            else if (shapeRegion->type == ShapeType::Rect)
            {
                return cv::RotatedRect(cv::Point2f((float)shapeRegion->shape.rect.center.x, (float)shapeRegion->shape.rect.center.y),
                    cv::Size2f((float)shapeRegion->shape.rect.size.width, (float)shapeRegion->shape.rect.size.height), 0);
            }
        }

        return cv::RotatedRect();
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
        case rv::RegionType::Shape:
            if (shapeRegion == nullptr)
            {
                return hregion;
            }
            switch (shapeRegion->type)
            {
            case ShapeType::Circle:
                hregion.GenCircle(shapeRegion->shape.circle.center.y, shapeRegion->shape.circle.center.x, shapeRegion->shape.circle.radius);
                break;
            case ShapeType::Rect:
                hregion.GenRectangle2(shapeRegion->shape.rect.center.y, shapeRegion->shape.rect.center.x, 0,
                    shapeRegion->shape.rect.size.width / 2, shapeRegion->shape.rect.size.height / 2);
                break;
            case ShapeType::RotatedRect:
                hregion.GenRectangle2(shapeRegion->shape.rotateRect.center.y, shapeRegion->shape.rotateRect.center.x, -shapeRegion->shape.rotateRect.angle,
                    shapeRegion->shape.rotateRect.size.width / 2, shapeRegion->shape.rotateRect.size.height / 2);
                break;
            default:
                break;
            }
            break;
        case rv::RegionType::Contour:
            break;
        case rv::RegionType::Runs:
            if (m_hregion.IsInitialized() && (m_hregion.CountObj() > 0))
            {
                return m_hregion;
            }
            else
            {
                const_cast<HRegion&>(m_hregion) = convertToHMat(runs);
                return m_hregion;
            }
            break;
        case rv::RegionType::HRegion:
            return m_hregion;
        }

        return hregion;
    }

    bool Region::checkValid(const HRegion& region)
    {
        return region.IsInitialized() && (region.CountObj() > 0);
    }

    std::shared_ptr<Runs> Region::convertToRuns(const HRegion& hregion)
    {
        using namespace HalconCpp;
        HTuple row;
        HTuple columnBegin;
        HTuple columnEnd;
        hregion.GetRegionRuns(&row, &columnBegin, &columnEnd);

        if (row.Length() == 0)
        {
            return std::shared_ptr<Runs>();
        }

        std::shared_ptr<rv::Runs> runs = std::make_shared<Runs>();

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

    HRegion Region::convertToHMat(const std::shared_ptr<Runs>& runs)
    {
        using namespace HalconCpp;
        if ((runs == nullptr) || runs->empty())
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