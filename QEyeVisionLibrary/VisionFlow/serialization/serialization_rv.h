#pragma once

#include <iostream>
#include <fstream>
#include <boost/archive/binary_iarchive.hpp>    //二进制序列化
#include <boost/archive/binary_oarchive.hpp>    //二进制序列化
#include <boost/serialization/vector.hpp>       //序列化STL容器要导入
#include <boost/serialization/map.hpp>          //序列化STL容器要导入
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/shared_ptr_helper.hpp>
#include <opencv2/opencv.hpp>
#include <ReVisionLib/revision.hpp>

BOOST_SERIALIZATION_SPLIT_FREE(::rv::ReMat)

namespace boost 
{
    namespace serialization 
    {
#pragma region Geometry

        template<class Archive>
        void save(Archive& ar, const ::rv::ReMat& m, const unsigned int version)
        {
            cv::Mat image = m.getMat();
            ar& BOOST_SERIALIZATION_NVP(image);
        }

        template <class Archive>
        void load(Archive& ar, ::rv::ReMat& m, const unsigned int version)
        {
            cv::Mat image;
            ar& BOOST_SERIALIZATION_NVP(image);
            m = ::rv::ReMat(image);
        }

        template <class Archive, typename _Tp>
        void serialize(Archive& ar, ::rv::Size<_Tp>& size, const unsigned int version)
        {
            ar& BOOST_SERIALIZATION_NVP(size.width);
            ar& BOOST_SERIALIZATION_NVP(size.height);
        }

        template <class Archive, typename _Tp>
        void serialize(Archive& ar, ::rv::Point<_Tp>& point, const unsigned int version)
        {
            ar& BOOST_SERIALIZATION_NVP(point.x);
            ar& BOOST_SERIALIZATION_NVP(point.y);
        }

        template <class Archive, typename _Tp>
        void serialize(Archive& ar, ::rv::Line<_Tp>& line, const unsigned int version)
        {
            ar& BOOST_SERIALIZATION_NVP(line.p1);
            ar& BOOST_SERIALIZATION_NVP(line.p2);
        }

        template <class Archive, typename _Tp>
        void serialize(Archive& ar, ::rv::Rectangle<_Tp>& rect, const unsigned int version)
        {
            ar& BOOST_SERIALIZATION_NVP(rect.center);
            ar& BOOST_SERIALIZATION_NVP(rect.size);
        }

        template <class Archive, typename _Tp>
        void serialize(Archive& ar, ::rv::RotatedRect<_Tp>& rect, const unsigned int version)
        {
            ar& BOOST_SERIALIZATION_NVP(rect.center);
            ar& BOOST_SERIALIZATION_NVP(rect.size);
            ar& BOOST_SERIALIZATION_NVP(rect.angle);
        }

        template <class Archive, typename _Tp>
        void serialize(Archive& ar, ::rv::Circle<_Tp>& circle, const unsigned int version)
        {
            ar& BOOST_SERIALIZATION_NVP(circle.center);
            ar& BOOST_SERIALIZATION_NVP(circle.radius);
        }

        template <class Archive, typename _Tp>
        void serialize(Archive& ar, ::rv::Arc<_Tp>& arc, const unsigned int version)
        {
            ar& BOOST_SERIALIZATION_NVP(arc.center);
            ar& BOOST_SERIALIZATION_NVP(arc.radius);
            ar& BOOST_SERIALIZATION_NVP(arc.angleStart);
            ar& BOOST_SERIALIZATION_NVP(arc.angleEnd);
        }

        template <class Archive, typename _Tp>
        void serialize(Archive& ar, ::rv::Annulus<_Tp>& annulus, const unsigned int version)
        {
            ar& BOOST_SERIALIZATION_NVP(annulus.center);
            ar& BOOST_SERIALIZATION_NVP(annulus.radius1);
            ar& BOOST_SERIALIZATION_NVP(annulus.radius2);
            ar& BOOST_SERIALIZATION_NVP(annulus.angleStart);
            ar& BOOST_SERIALIZATION_NVP(annulus.angleEnd);
        }

        template <class Archive, typename _Tp>
        void serialize(Archive& ar, ::rv::Ray<_Tp>& ray, const unsigned int version)
        {
            ar& BOOST_SERIALIZATION_NVP(ray.center);
            ar& BOOST_SERIALIZATION_NVP(ray.angle);
        }

        template <class Archive, typename _Tp>
        void serialize(Archive& ar, ::rv::Pose<_Tp>& poses, const unsigned int version)
        {
            ar& BOOST_SERIALIZATION_NVP(poses.center);
            ar& BOOST_SERIALIZATION_NVP(poses.angle);
        }

        template <class Archive, typename _Tp>
        void serialize(Archive& ar, ::rv::Polygon<_Tp>& polygon, const unsigned int version)
        {
            ar& BOOST_SERIALIZATION_NVP(polygon);
        }

        template <class Archive, typename _Tp>
        void serialize(Archive& ar, ::rv::Contours<_Tp>& contours, const unsigned int version)
        {
            ar& BOOST_SERIALIZATION_NVP(contours);
        }

        template <class Archive, typename _Tp>
        void serialize(Archive& ar, ::rv::Runs<_Tp>& runs, const unsigned int version)
        {
            ar& BOOST_SERIALIZATION_NVP(runs.r);
            ar& BOOST_SERIALIZATION_NVP(runs.cb);
            ar& BOOST_SERIALIZATION_NVP(runs.ce);
        }

#pragma endregion

        template <class Archive>
        void serialize(Archive& ar, ::rv::GeometryRegion& geometryRegion, const unsigned int version)
        {
            ar& BOOST_SERIALIZATION_NVP(geometryRegion.type);
            ar& BOOST_SERIALIZATION_NVP(geometryRegion.circle);
            ar& BOOST_SERIALIZATION_NVP(geometryRegion.line);
            ar& BOOST_SERIALIZATION_NVP(geometryRegion.rotateRect);
            ar& BOOST_SERIALIZATION_NVP(geometryRegion.polygon);
        }


        template<class Archive>
        void serialize(Archive& ar, ::rv::Region& region, const unsigned int version)
        {
            ar& BOOST_SERIALIZATION_NVP(region.regionType);
            ar& BOOST_SERIALIZATION_NVP(region.shapeRegion);
            ar& BOOST_SERIALIZATION_NVP(region.contours);
            ar& BOOST_SERIALIZATION_NVP(region.pointSet);
            ar& BOOST_SERIALIZATION_NVP(region.runs);
        }

        template <class Archive>
        void serialize(Archive& ar, ::rv::IsotropicScaling& scaling, const unsigned int version)
        {
            ar& BOOST_SERIALIZATION_NVP(scaling.max);
            ar& BOOST_SERIALIZATION_NVP(scaling.min);
        }

        template <class Archive>
        void serialize(Archive& ar, ::rv::AnisotropicScaling& scaling, const unsigned int version)
        {
            ar& BOOST_SERIALIZATION_NVP(scaling.rowMax);
            ar& BOOST_SERIALIZATION_NVP(scaling.rowMin);
            ar& BOOST_SERIALIZATION_NVP(scaling.colMax);
            ar& BOOST_SERIALIZATION_NVP(scaling.colMin);
        }

        template <class Archive>
        void serialize(Archive& ar, ::rv::RectMix& rectMix, const unsigned int version)
        {
            ar& BOOST_SERIALIZATION_NVP(rectMix.rotateRect);
            ar& BOOST_SERIALIZATION_NVP(rectMix.caliperGap);
            ar& BOOST_SERIALIZATION_NVP(rectMix.findLine);
            ar& BOOST_SERIALIZATION_NVP(rectMix.edgeGap);
            ar& BOOST_SERIALIZATION_NVP(rectMix.caliperLength);
            ar& BOOST_SERIALIZATION_NVP(rectMix.caliperWidth);
        }

        template <class Archive>
        void serialize(Archive& ar, ::rv::CircleMix& circleMix, const unsigned int version)
        {
            ar& BOOST_SERIALIZATION_NVP(circleMix.annulus);
            ar& BOOST_SERIALIZATION_NVP(circleMix.caliperGap);
            ar& BOOST_SERIALIZATION_NVP(circleMix.caliperWidth);
        }

    } // namespace serialization
} // namespace boost
