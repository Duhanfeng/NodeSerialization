#pragma once

#include <iostream>
#include <fstream>
#include <boost/archive/binary_iarchive.hpp>    //二进制序列化
#include <boost/archive/binary_oarchive.hpp>    //二进制序列化
#include <boost/serialization/vector.hpp>       //序列化STL容器要导入
#include <boost/serialization/map.hpp>          //序列化STL容器要导入
#include <opencv2/opencv.hpp>

BOOST_SERIALIZATION_SPLIT_FREE(cv::Mat)

namespace boost {
    namespace serialization {

        template<class Archive>
        void save(Archive& ar, const cv::Mat& m, const unsigned int version)
        {
            int cols = m.cols;
            int rows = m.rows;
            size_t elem_size = m.elemSize();
            size_t elem_type = m.type();

            ar& BOOST_SERIALIZATION_NVP(cols);
            ar& BOOST_SERIALIZATION_NVP(rows);
            ar& BOOST_SERIALIZATION_NVP(elem_size);
            ar& BOOST_SERIALIZATION_NVP(elem_type);

            const size_t data_size = m.cols * m.rows * elem_size;
            ar& boost::serialization::make_array(m.ptr(), data_size);
        }

        template <class Archive>
        void load(Archive& ar, cv::Mat& m, const unsigned int version)
        {
            int cols = 0;
            int rows = 0;
            size_t elem_size = 0;
            size_t elem_type = 0;

            ar& BOOST_SERIALIZATION_NVP(cols);
            ar& BOOST_SERIALIZATION_NVP(rows);
            ar& BOOST_SERIALIZATION_NVP(elem_size);
            ar& BOOST_SERIALIZATION_NVP(elem_type);

            m.create(rows, cols, elem_type);

            size_t data_size = m.cols * m.rows * elem_size;
            ar& boost::serialization::make_array(m.ptr(), data_size);
        }

        template <class Archive, typename _Tp>
        void serialize(Archive& ar, cv::Point_<_Tp>& point, const unsigned int version)
        {
            ar& BOOST_SERIALIZATION_NVP(point.x);
            ar& BOOST_SERIALIZATION_NVP(point.y);
        }

        template <class Archive, typename _Tp>
        void serialize(Archive& ar, cv::Point3_<_Tp>& point, const unsigned int version)
        {
            ar& BOOST_SERIALIZATION_NVP(point.x);
            ar& BOOST_SERIALIZATION_NVP(point.y);
            ar& BOOST_SERIALIZATION_NVP(point.z);
        }

        template <class Archive, typename _Tp>
        void serialize(Archive& ar, cv::Size_<_Tp>& size, const unsigned int version)
        {
            ar& BOOST_SERIALIZATION_NVP(size.width);
            ar& BOOST_SERIALIZATION_NVP(size.height);
        }

        template <class Archive>
        void serialize(Archive& ar, cv::RotatedRect& rect, const unsigned int version)
        {
            ar& BOOST_SERIALIZATION_NVP(rect.center);
            ar& BOOST_SERIALIZATION_NVP(rect.size);
            ar& BOOST_SERIALIZATION_NVP(rect.angle);
        }

        template<class Archive, typename _Tp>
        inline void serialize(Archive& ar, cv::Ptr<_Tp>& t, const unsigned int file_version)
        {
            split_free(ar, t, file_version);
        }

        template <class Archive, typename _Tp>
        void save(Archive& ar, const cv::Ptr<_Tp>& ptr, const unsigned int version)
        {
            ar& BOOST_SERIALIZATION_NVP((_Tp*)ptr.get());
        }

        template <class Archive, typename _Tp>
        void load(Archive& ar, cv::Ptr<_Tp>& ptr, const unsigned int version)
        {
            _Tp* newPtr;
            ar& BOOST_SERIALIZATION_NVP(newPtr);
            ptr = cv::Ptr<_Tp>(newPtr);
        }

    } // namespace serialization
} // namespace boost
