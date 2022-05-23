#include "adapted_cv.hpp"

template <typename _Tp>
inline constexpr cv::Size converToCvSize(const rv::Size<_Tp>& size) noexcept
{
    return cv::Size((int)size.width, (int)size.height);
}

template <typename _Tp>
inline constexpr cv::Size2f converToCvSizeF(const rv::Size<_Tp>& size) noexcept
{
    return cv::Size2f((float)size.width, (float)size.height);
}

template <typename _Tp>
inline constexpr cv::Point converToCvPoint(const rv::Point<_Tp>& point) noexcept
{
    return cv::Point((int)point.x, (int)point.y);
}

template <typename _Tp>
inline constexpr cv::Point2f converToCvPointF(const rv::Point<_Tp>& point) noexcept
{
    return cv::Point2f((float)point.x, (float)point.y);
}

template <typename _Tp>
inline constexpr cv::Rect converToCvRect(const rv::Rectangle<_Tp>& rect) noexcept
{
    return cv::Rect(converToCvPoint(rect.topLeft()), converToCvSize(rect.size));
}

template <typename _Tp>
inline constexpr cv::Rect2f converToCvRectF(const rv::Rectangle<_Tp>& rect) noexcept
{
    return cv::Rect2f(converToCvPointF(rect.topLeft()), converToCvSizeF(rect.size));
}

template <typename _Tp>
inline constexpr cv::RotatedRect converToCvRotatedRect(const rv::Rectangle<_Tp>& rect) noexcept
{
    return cv::RotatedRect(converToCvPoint(rect.center), converToCvSize(rect.size), 0);
}

template <typename _Tp>
inline constexpr cv::RotatedRect converToCvRotatedRect(const rv::RotatedRect<_Tp>& rect) noexcept
{
    return cv::RotatedRect(converToCvPoint(rect.center), converToCvSize(rect.size), (float)rv::rad2deg(rect.angle));
}


/* ----------------------- cv转rv ----------------------- */


template <typename _Tp>
inline constexpr rv::Size<int> converToSize(const cv::Size_<_Tp>& size) noexcept
{
    return rv::Size<int>((int)size.width, (int)size.height);
}

template <typename _Tp>
inline constexpr rv::Size<double> converToSizeF(const cv::Size_<_Tp>& size) noexcept
{
    return rv::Size<double>((double)size.width, (double)size.height);
}

template <typename _Tp>
inline constexpr rv::Point<int> converToPoint(const cv::Point_<_Tp>& point) noexcept
{
    return rv::Point<int>((int)point.x, (int)point.y);
}

template <typename _Tp>
inline constexpr rv::Point<double> converToPointF(const cv::Point_<_Tp>& point) noexcept
{
    return rv::Point<double>((double)point.x, (double)point.y);
}

template <typename _Tp>
inline constexpr rv::Rectangle<int> converToRect(const cv::Rect_<_Tp>& rect) noexcept
{
    //opencv中的rect类型,x和y表示的是左上角的坐标
    rv::Point<int> center(int(rect.x + rect.width / 2), int(rect.y + rect.height / 2));

    return rv::Rectangle<int>(center, converToSize(rect.size()));
}

template <typename _Tp>
inline constexpr rv::Rectangle<double> converToRectF(const cv::Rect_<_Tp>& rect) noexcept
{
    //opencv中的rect类型,x和y表示的是左上角的坐标
    rv::Point<double> center(rect.x + rect.width / 2, rect.y + rect.height / 2);

    return rv::Rectangle<double>(center, converToSizeF(rect.size()));
}

template <typename _Tp>
inline constexpr rv::RotatedRect<int> converToRotatedRect(const cv::Rect_<_Tp>& rect) noexcept
{
    //opencv中的rect类型,x和y表示的是左上角的坐标
    rv::Point<int> center(rect.x + rect.width / 2, rect.y + rect.height / 2);

    return rv::RotatedRect<int>(center, converToSize(rect.size()), 0);
}

template <typename _Tp>
inline constexpr rv::RotatedRect<double> converToRotatedRectF(const cv::Rect_<_Tp>& rect) noexcept
{
    //opencv中的rect类型,x和y表示的是左上角的坐标
    rv::Point<double> center(rect.x + rect.width / 2, rect.y + rect.height / 2);

    return rv::RotatedRect<double>(center, converToSizeF(rect.size()), 0);
}

inline rv::RotatedRect<int> converToRotatedRect(const cv::RotatedRect& rect) noexcept
{
    return rv::RotatedRect<int>(converToPoint(rect.center), converToSize(rect.size), rv::deg2rad(rect.angle));
}

inline rv::RotatedRect<double> converToRotatedRectF(const cv::RotatedRect& rect) noexcept
{
    return rv::RotatedRect<int>(converToPointF(rect.center), converToSizeF(rect.size), rv::deg2rad(rect.angle));
}
