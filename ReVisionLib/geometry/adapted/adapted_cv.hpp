#pragma once

#include <opencv2/opencv.hpp>
#include "../geometries/size.hpp"
#include "../geometries/point.hpp"
#include "../geometries/line.hpp"
#include "../geometries/rectangle.hpp"
#include "../geometries/rotatedRect.hpp"
#include "../geometries/circle.hpp"
#include "../geometries/arc.hpp"
#include "../geometries/annulus.hpp"
#include "../geometries/ray.hpp"
#include "../geometries/pose.hpp"
#include "../geometries/polygon.hpp"
#include "../geometries/contours.hpp"
#include "../geometries/runs.hpp"

/* ----------------------- rv转cv ----------------------- */

template <typename _Tp>
inline constexpr cv::Size converToCvSize(const rv::Size<_Tp>& size) noexcept;

template <typename _Tp>
inline constexpr cv::Size2f converToCvSizeF(const rv::Size<_Tp>& size) noexcept;

template <typename _Tp>
inline constexpr cv::Point converToCvPoint(const rv::Point<_Tp>& point) noexcept;

template <typename _Tp>
inline constexpr cv::Point2f converToCvPointF(const rv::Point<_Tp>& point) noexcept;

template <typename _Tp>
inline constexpr cv::Rect converToCvRect(const rv::Rectangle<_Tp>& rect) noexcept;

template <typename _Tp>
inline constexpr cv::Rect2f converToCvRectF(const rv::Rectangle<_Tp>& rect) noexcept;

template <typename _Tp>
inline constexpr cv::RotatedRect converToCvRotatedRect(const rv::Rectangle<_Tp>& rect) noexcept;

template <typename _Tp>
inline constexpr cv::RotatedRect converToCvRotatedRect(const rv::RotatedRect<_Tp>& rect) noexcept;


/* ----------------------- cv转rv ----------------------- */
template <typename _Tp>
inline constexpr rv::Size<int> converToSize(const cv::Size_<_Tp>& size) noexcept;

template <typename _Tp>
inline constexpr rv::Size<double> converToSizeF(const cv::Size_<_Tp>& size) noexcept;

template <typename _Tp>
inline constexpr rv::Point<int> converToPoint(const cv::Point_<_Tp>& point) noexcept;

template <typename _Tp>
inline constexpr rv::Point<double> converToPointF(const cv::Point_<_Tp>& point) noexcept;

template <typename _Tp>
inline constexpr rv::Rectangle<int> converToRect(const cv::Rect_<_Tp>& rect) noexcept;

template <typename _Tp>
inline constexpr rv::Rectangle<double> converToRectF(const cv::Rect_<_Tp>& rect) noexcept;

template <typename _Tp>
inline constexpr rv::RotatedRect<int> converToRotatedRect(const cv::Rect_<_Tp>& rect) noexcept;

template <typename _Tp>
inline constexpr rv::RotatedRect<double> converToRotatedRectF(const cv::Rect_<_Tp>& rect) noexcept;

inline rv::RotatedRect<int> converToRotatedRect(const cv::RotatedRect& rect) noexcept;
inline rv::RotatedRect<double> converToRotatedRectF(const cv::RotatedRect& rect) noexcept;

#include "adapted_cv.inl"