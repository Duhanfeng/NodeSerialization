#include "variant_geometry.h"

namespace qv
{
    inline GeometryComplex::GeometryComplex() noexcept :
        type(rv::GeometryType::None),
        x(0),
        y(0),
        w(0),
        h(0),
        angle(0),
        x2(0),
        y2(0)
    {
    }

    template<typename _Tp>
    inline GeometryComplex::GeometryComplex(const rv::Point<_Tp>& value) noexcept :
        type(rv::GeometryType::Point),
        x(value.x),
        y(value.y),
        w(0),
        h(0),
        angle(0),
        x2(0),
        y2(0)
    {

    }

    template<typename _Tp>
    inline GeometryComplex::GeometryComplex(const rv::Line<_Tp>& value) noexcept :
        type(rv::GeometryType::Line),
        x(value.p1.x),
        y(value.p1.y),
        w(0),
        h(0),
        angle(value.angle()),
        x2(value.p2.x),
        y2(value.p2.y)
    {
        //angle = value.angle();
    }

    template<typename _Tp>
    inline GeometryComplex::GeometryComplex(const rv::Pose<_Tp>& value) noexcept :
        type(rv::GeometryType::Pose),
        x(value.center.x),
        y(value.center.y),
        w(0),
        h(0),
        angle(value.angle),
        x2(0),
        y2(0)
    {
    }

    template<typename _Tp>
    inline GeometryComplex::GeometryComplex(const rv::Circle<_Tp>& value) noexcept :
        type(rv::GeometryType::Circle),
        x(value.center.x),
        y(value.center.y),
        w(value.radius * 2),    //w,h代表直径
        h(value.radius * 2),
        angle(0),
        x2(0),
        y2(0)
    {

    }

    template<typename _Tp>
    inline GeometryComplex::GeometryComplex(const rv::RotatedRect<_Tp>& value) noexcept :
        type(rv::GeometryType::RotatedRect),
        x(value.center.x),
        y(value.center.y),
        w(value.size.width),
        h(value.size.height),
        angle(value.angle),
        x2(0),
        y2(0)
    {
    }

    inline bool GeometryComplex::supportPoint() const
    {
        return true;
    }

    inline bool GeometryComplex::supportPoint2() const
    {
        return type == rv::GeometryType::Line;
    }

    inline bool GeometryComplex::supportAngle() const
    {
        return (type == rv::GeometryType::Line) || (type == rv::GeometryType::Pose) || (type == rv::GeometryType::RotatedRect);
    }

    inline bool GeometryComplex::supportSize() const
    {
        return (type == rv::GeometryType::Circle) || (type == rv::GeometryType::RotatedRect);
    }

    inline bool GeometryComplex::supportPose() const
    {
        return (type == rv::GeometryType::Line) || (type == rv::GeometryType::Pose) || (type == rv::GeometryType::RotatedRect);
    }

    inline rv::Point<double> GeometryComplex::getPoint() const
    {
        return rv::Point<double>(x, y);
    }

    inline rv::Point<double> GeometryComplex::getPoint2() const
    {
        return rv::Point<double>(x2, y2);
    }

    inline double GeometryComplex::getAngle() const
    {
        return angle;
    }

    inline double GeometryComplex::getWidth() const
    {
        return w;
    }

    inline double GeometryComplex::getHeight() const
    {
        return h;
    }

    inline rv::Size<double> GeometryComplex::getSize() const
    {
        return rv::Size<double>(w, h);
    }

    inline rv::Line<double> GeometryComplex::getLine() const
    {
        return rv::Line<double>(x, y, x2, y2);
    }

    inline rv::Pose<double> GeometryComplex::getPose() const
    {
        return rv::Pose<double>(x, y, angle);
    }

    inline rv::Circle<double> GeometryComplex::getCircle() const
    {
        return rv::Circle<double>(x, y, w / 2);
    }

    inline rv::RotatedRect<double> GeometryComplex::getRect() const
    {
        return rv::RotatedRect<double>(x, y, w, h, angle);
    }

    template<typename _Tp>
    inline bool GeometryComplex::tryGetPoint(rv::Point<_Tp>& value) const
    {
        if (supportPoint())
        {
            value = getPoint();
            return true;
        }

        return false;
    }

    template<typename _Tp>
    inline bool GeometryComplex::tryGetPoint2(rv::Point<_Tp>& value) const
    {
        if (supportPoint2())
        {
            value = getPoint2();
            return true;
        }

        return false;
    }

    template<typename _Tp>
    inline bool GeometryComplex::tryGetAngle(_Tp& value) const
    {
        if (supportAngle())
        {
            value = _Tp(angle);
            return true;
        }

        return false;
    }

    template<typename _Tp>
    inline bool GeometryComplex::tryGetWidth(_Tp& value) const
    {
        if (supportSize())
        {
            value = _Tp(w);
            return true;
        }

        return false;
    }

    template<typename _Tp>
    inline bool GeometryComplex::tryGetHeight(_Tp& value) const
    {
        if (supportSize())
        {
            value = _Tp(h);
            return true;
        }

        return false;
    }

    template<typename _Tp>
    inline bool GeometryComplex::tryGetSize(rv::Size<_Tp>& value) const
    {
        if (supportSize())
        {
            value = rv::Size(_Tp(w), _Tp(h));
            return true;
        }

        return false;
    }

    template<typename _Tp>
    inline bool GeometryComplex::tryGetLine(rv::Line<_Tp>& value) const
    {
        if (supportPoint2())
        {
            value = rv::Line<_Tp>((_Tp)x, (_Tp)y, (_Tp)x2, (_Tp)y2);
            return true;
        }

        return false;
    }

    template<typename _Tp>
    inline bool GeometryComplex::tryGetPose(rv::Pose<_Tp>& value) const
    {
        if (supportPose())
        {
            value = rv::Pose<_Tp>((_Tp)x, (_Tp)y, angle);
            return true;
        }

        return false;
    }

    template<typename _Tp>
    inline bool GeometryComplex::tryGetCircle(rv::Circle<_Tp>& value) const
    {
        if (supportPoint() && supportSize())
        {
            value = rv::Circle<_Tp>((_Tp)x, (_Tp)y, _Tp(w / 2));
            return true;
        }

        return false;
    }

    template<typename _Tp>
    inline bool GeometryComplex::tryGetRect(rv::RotatedRect<_Tp>& value) const
    {
        if (supportPoint() && supportSize())
        {
            value = rv::RotatedRect<_Tp>((_Tp)x, (_Tp)y, (_Tp)w, (_Tp)h, angle);
            return true;
        }

        return false;
    }

}

