#pragma once
#include <vector>
#include <map>
#include <ReVisionLib/revision.hpp>
#include "variant_geometry.h"

namespace qv
{
    template<typename _Tp>
    class VariantBase
    {
    public:

        VariantBase()
        {
            m_values.clear();
        }

        VariantBase(const VariantBase& variant)
        {
            m_values.clear();
            m_values = variant.m_values;
        }

        void clear() 
        {
            m_values.clear();
        }

        void setValue(const _Tp& value)
        {
            m_values.clear();
            m_values.push_back(value);
        }

        void setValue(const std::vector<_Tp>& values)
        {
            m_values.clear();
            m_values = values;
        }

        _Tp getValue() const
        {
            if (empty())
            {
                return _Tp();
            }

            return m_values[0];
        }

        const std::vector<_Tp>& getValues() const
        {
            return m_values;
        }

        bool empty() const
        {
            return m_values.size() == 0;
        }

        size_t length() const
        {
            return m_values.size();
        }

        VariantBase& operator = (const VariantBase& var)
        {
            m_values = var.m_values;

            return *this;
        }

    protected:
        std::vector<_Tp> m_values;

    };

    //备注: 
    //下一步改进: 用所有的几何形状用一个class来描述,方便传递
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
        Variant();
        Variant(const Variant& value);
        Variant(int value);
        Variant(const std::vector<int>& values);
        Variant(double value);
        Variant(const std::vector<double>& values);
        Variant(const std::string& value);
        Variant(const std::vector<std::string>& values);
        Variant(const rv::ReMat& value);
        Variant(const std::vector<rv::ReMat>& values);
        Variant(const Point2D& value);
        Variant(const std::vector<Point2D>& values);
        Variant(const Pose2D& value);
        Variant(const std::vector<Pose2D>& values);
        Variant(const Line2D& value);
        Variant(const std::vector<Line2D>& values);
        Variant(const Circle2D& value);
        Variant(const std::vector<Circle2D>& values);
        Variant(const Rect2D& value);
        Variant(const std::vector<Rect2D>& values);

        void setType(VariantType type);
        VariantType type() const;
        void clear();
        size_t length() const;

        //设置
        void setValue(int value);
        void setValue(const std::vector<int>& values);
        void setValue(double value);
        void setValue(const std::vector<double>& values);
        void setValue(const std::string& value);
        void setValue(const std::vector<std::string>& values);
        void setValue(const rv::ReMat& value);
        void setValue(const std::vector<rv::ReMat>& values);
        void setValue(const Point2D& value);
        void setValue(const std::vector<Point2D>& values);
        void setValue(const Pose2D& value);
        void setValue(const std::vector<Pose2D>& values);
        void setValue(const Line2D& value);
        void setValue(const std::vector<Line2D>& values);
        void setValue(const Circle2D& value);
        void setValue(const std::vector<Circle2D>& values);
        void setValue(const Rect2D& value);
        void setValue(const std::vector<Rect2D>& values);

        //获取
        int getInt() const;
        double getDouble() const;
        std::string getString() const;
        rv::ReMat getReMat() const;
        rv::ReMat getImage() const;
        Point2D getPoint() const;
        Pose2D getPose() const;
        Line2D getLine() const;
        Circle2D getCircle() const;
        Rect2D getRect() const;

        const std::vector<int>& getIntArray() const;
        const std::vector<double>& getDoubleArray() const;
        const std::vector<std::string>& getStringArray() const;
        const std::vector<rv::ReMat>& getReMatArray() const;
        const std::vector<Point2D>& getPointArray() const;
        const std::vector<Pose2D>& getPoseArray() const;
        const std::vector<Line2D>& getLineArray() const;
        const std::vector<Circle2D>& getCircleArray() const;
        const std::vector<Rect2D>& getRectArray() const;

    protected:
        VariantType m_type{ VariantType::Empty };

        VariantBase<int> m_intValue;
        VariantBase<double> m_doubleValue;
        VariantBase<std::string> m_stringValue;
        VariantBase<rv::ReMat> m_imageValue;

        VariantBase<Point2D> m_pointValue;
        VariantBase<Pose2D> m_poseValue;
        VariantBase<Line2D> m_lineValue;
        VariantBase<Circle2D> m_circleValue;
        VariantBase<Rect2D> m_rectValue;

    private:
        template<typename _Tp> VariantType getType();
        std::map<size_t, VariantType> m_typeMap;

    };

    template<typename _Tp>
    inline Variant::VariantType Variant::getType()
    {
        size_t id = typeid(_Tp).hash_code();

        if (m_typeMap.find(id) != m_typeMap.end())
        {
            return m_typeMap[id];
        }

        return VariantType::Empty;
    }

}
