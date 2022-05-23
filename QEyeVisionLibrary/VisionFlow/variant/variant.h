#pragma once

#include <vector>
#include <map>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/export.hpp>
#include <ReVisionLib/revision.hpp>
#include "variant_base.h"
#include "variant_geometry.h"

namespace qv
{
    class Variant
    {
    public:
        enum class VariantType
        {
            Empty = 0,
            Int,
            Double,
            String,
            Image,
            Point,
            Pose,       //Point + 角度
            Line,       //Point + Point
            Circle,     //Point + 半径
            Rect,       //Point + 宽 + 高 + 角度
        };

    public:

        //构造
        Variant() noexcept;
        Variant(const Variant& value) noexcept;

        Variant(int value) noexcept;
        Variant(double value) noexcept;
        Variant(const std::string& value) noexcept;
        Variant(const rv::ReMat& value) noexcept;
        Variant(const rv::Point<double>& value) noexcept;
        Variant(const rv::Pose<double>& value) noexcept;
        Variant(const rv::Line<double>& value) noexcept;
        Variant(const rv::Circle<double>& value) noexcept;
        Variant(const rv::RotatedRect<double>& value) noexcept;
        Variant(const GeometryComplex& value) noexcept;

        Variant(const std::vector<int>& value) noexcept;
        Variant(const std::vector<double>& value) noexcept;
        Variant(const std::vector<std::string>& value) noexcept;
        Variant(const std::vector<rv::Point<double>>& value) noexcept;
        Variant(const std::vector<rv::Pose<double>>& value) noexcept;
        Variant(const std::vector<rv::Line<double>>& value) noexcept;
        Variant(const std::vector<rv::Circle<double>>& value) noexcept;
        Variant(const std::vector<rv::RotatedRect<double>>& value) noexcept;
        Variant(const std::vector<GeometryComplex>& value) noexcept;

        //设置
        void setValue(const Variant& value) noexcept;
        void setValue(int value) noexcept;
        void setValue(double value) noexcept;
        void setValue(const std::string& value) noexcept;
        void setValue(const rv::ReMat& value) noexcept;
        void setValue(const rv::Point<double>& value) noexcept;
        void setValue(const rv::Pose<double>& value) noexcept;
        void setValue(const rv::Line<double>& value) noexcept;
        void setValue(const rv::Circle<double>& value) noexcept;
        void setValue(const rv::RotatedRect<double>& value) noexcept;
        void setValue(const GeometryComplex& value) noexcept;

        void setValue(const std::vector<int>& value) noexcept;
        void setValue(const std::vector<double>& value) noexcept;
        void setValue(const std::vector<std::string>& value) noexcept;
        void setValue(const std::vector<rv::Point<double>>& value) noexcept;
        void setValue(const std::vector<rv::Pose<double>>& value) noexcept;
        void setValue(const std::vector<rv::Line<double>>& value) noexcept;
        void setValue(const std::vector<rv::Circle<double>>& value) noexcept;
        void setValue(const std::vector<rv::RotatedRect<double>>& value) noexcept;
        void setValue(const std::vector<GeometryComplex>& value) noexcept;

        //校验
        bool supportInt() const;
        bool supportDouble() const;
        bool supportString() const;
        bool supportReMat() const;

        bool supportGeometry() const;
        bool supportPoint() const;
        bool supportPose() const;
        bool supportLine() const;
        bool supportCircle() const;
        bool supportRect() const;

        //获取
        int getInt() const;
        double getDouble() const;
        std::string getString() const;
        rv::ReMat getReMat() const;
        rv::ReMat getImage() const;
        rv::Point<double> getPoint() const;
        rv::Pose<double> getPose() const;
        rv::Line<double> getLine() const;
        rv::Circle<double> getCircle() const;
        rv::RotatedRect<double> getRect() const;

        std::vector<int> getIntArray() const;
        std::vector<double> getDoubleArray() const;
        std::vector<std::string> getStringArray() const;
        std::vector<rv::Point<double>> getPointArray() const;
        std::vector<rv::Pose<double>> getPoseArray() const;
        std::vector<rv::Line<double>> getLineArray() const;
        std::vector<rv::Circle<double>> getCircleArray() const;
        std::vector<rv::RotatedRect<double>> getRectArray() const;

        //功能函数
        void clear();
        void setType(VariantType type);
        VariantType type() const;
        size_t length() const;

    private:
        VariantType m_type{ VariantType::Empty };

        VariantBase<int> m_intValue;
        VariantBase<double> m_doubleValue;
        VariantBase<std::string> m_stringValue;
        VariantBase<GeometryComplex> m_geometryValue;
        rv::ReMat m_imageValue;

    private:
        friend class boost::serialization::access;

        template <typename Archive>
        void serialize(Archive& ar, const unsigned int version)
        {
            ar& BOOST_SERIALIZATION_NVP(m_type);
            ar& BOOST_SERIALIZATION_NVP(m_intValue);
            ar& BOOST_SERIALIZATION_NVP(m_doubleValue);
            ar& BOOST_SERIALIZATION_NVP(m_stringValue);
            ar& BOOST_SERIALIZATION_NVP(m_geometryValue);
            ar& BOOST_SERIALIZATION_NVP(m_imageValue);
        }

    };

}
