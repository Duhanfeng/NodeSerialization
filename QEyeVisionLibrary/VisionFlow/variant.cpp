#include "variant.h"

namespace qv
{

#pragma region 构造

    Variant::Variant()
    {
        //构建类型映射表,牺牲构造时间换取运行时的时间
        m_typeMap.clear();
        m_typeMap[typeid(int).hash_code()] = VariantType::Int;
        m_typeMap[typeid(std::vector<int>).hash_code()] = VariantType::Int;
        m_typeMap[typeid(double).hash_code()] = VariantType::Double;
        m_typeMap[typeid(std::vector<double>).hash_code()] = VariantType::Double;
        m_typeMap[typeid(std::string).hash_code()] = VariantType::String;
        m_typeMap[typeid(std::vector<std::string>).hash_code()] = VariantType::String;
        m_typeMap[typeid(rv::ReMat).hash_code()] = VariantType::Image;
        m_typeMap[typeid(std::vector<rv::ReMat>).hash_code()] = VariantType::Image;
        m_typeMap[typeid(Point2D).hash_code()] = VariantType::Point;
        m_typeMap[typeid(std::vector<Point2D>).hash_code()] = VariantType::Point;
        m_typeMap[typeid(Pose2D).hash_code()] = VariantType::Pose;
        m_typeMap[typeid(std::vector<Pose2D>).hash_code()] = VariantType::Pose;
        m_typeMap[typeid(Line2D).hash_code()] = VariantType::Line;
        m_typeMap[typeid(std::vector<Line2D>).hash_code()] = VariantType::Line;
        m_typeMap[typeid(Circle2D).hash_code()] = VariantType::Circle;
        m_typeMap[typeid(std::vector<Circle2D>).hash_code()] = VariantType::Circle;
        m_typeMap[typeid(Rect2D).hash_code()] = VariantType::Rect;
        m_typeMap[typeid(std::vector<Rect2D>).hash_code()] = VariantType::Rect;

    }

    Variant::Variant(const Variant& value) : Variant()
    {
        m_type = value.m_type;

        m_intValue = value.m_intValue;
        m_doubleValue = value.m_doubleValue;
        m_stringValue = value.m_stringValue;
        m_imageValue = value.m_imageValue;

        m_pointValue = value.m_pointValue;
        m_poseValue = value.m_poseValue;
        m_lineValue = value.m_lineValue;
        m_circleValue = value.m_circleValue;
        m_rectValue = value.m_rectValue;
    }

    Variant::Variant(int value) : Variant()
    {
        setValue(value);
    }

    Variant::Variant(const std::vector<int>& values) : Variant()
    {
        setValue(values);
    }

    Variant::Variant(double value) : Variant()
    {
        setValue(value);
    }

    Variant::Variant(const std::vector<double>& values) : Variant()
    {
        setValue(values);
    }

    Variant::Variant(const std::string& value) : Variant()
    {
        setValue(value);
    }

    Variant::Variant(const std::vector<std::string>& values) : Variant()
    {
        setValue(values);
    }

    Variant::Variant(const rv::ReMat& value) : Variant()
    {
        setValue(value);
    }

    Variant::Variant(const std::vector<rv::ReMat>& values) : Variant()
    {
        setValue(values);
    }

    Variant::Variant(const Point2D& value) : Variant()
    {
        setValue(value);
    }

    Variant::Variant(const std::vector<Point2D>& values) : Variant()
    {
        setValue(values);
    }

    Variant::Variant(const Pose2D& value) : Variant()
    {
        setValue(value);
    }

    Variant::Variant(const std::vector<Pose2D>& values) : Variant()
    {
        setValue(values);
    }

    Variant::Variant(const Line2D& value) : Variant()
    {
        setValue(value);
    }

    Variant::Variant(const std::vector<Line2D>& values) : Variant()
    {
        setValue(values);
    }

    Variant::Variant(const Circle2D& value) : Variant()
    {
        setValue(value);
    }

    Variant::Variant(const std::vector<Circle2D>& values) : Variant()
    {
        setValue(values);
    }

    Variant::Variant(const Rect2D& value) : Variant()
    {
        setValue(value);
    }

    Variant::Variant(const std::vector<Rect2D>& values) : Variant()
    {
        setValue(values);
    }

    void Variant::setType(VariantType type)
    {
        if (m_type != type)
        {
            clear();
            m_type = type;
        }
    }

    Variant::VariantType Variant::type() const
    {
        return m_type;
    }



#pragma endregion


    void Variant::clear()
    {
        m_intValue.clear();
        m_doubleValue.clear();
        m_stringValue.clear();
        m_imageValue.clear();

        m_pointValue.clear();
        m_poseValue.clear();
        m_lineValue.clear();
        m_circleValue.clear();
        m_rectValue.clear();

        m_type = VariantType::Empty;
    }

    size_t Variant::length() const
    {
        switch (m_type)
        {
        case qv::Variant::VariantType::Int:
            return m_intValue.length();
        case qv::Variant::VariantType::Double:
            return m_doubleValue.length();
        case qv::Variant::VariantType::String:
            return m_stringValue.length();
        case qv::Variant::VariantType::Image:
            return m_imageValue.length();
        case qv::Variant::VariantType::Point:
            return m_pointValue.length();
        case qv::Variant::VariantType::Pose:
            return m_poseValue.length();
        case qv::Variant::VariantType::Line:
            return m_lineValue.length();
        case qv::Variant::VariantType::Circle:
            return m_circleValue.length();
        case qv::Variant::VariantType::Rect:
            return m_rectValue.length();
        default:
            return size_t();
        }
    }

#pragma region 设置

    void Variant::setValue(int value)
    {
        clear();
        m_type = getType<int>();
        m_intValue.setValue(value);
    }

    void Variant::setValue(const std::vector<int>& values)
    {
        clear();
        m_type = getType<std::vector<int>>();
        m_intValue.setValue(values);
    }

    void Variant::setValue(double value)
    {
        clear();
        m_type = getType<double>();
        m_doubleValue.setValue(value);
    }

    void Variant::setValue(const std::vector<double>& values)
    {
        clear();
        m_type = getType<std::vector<double>>();
        m_doubleValue.setValue(values);
    }

    void Variant::setValue(const std::string& value)
    {
        clear();
        m_type = getType<std::string>();
        m_stringValue.setValue(value);
    }

    void Variant::setValue(const std::vector<std::string>& values)
    {
        clear();
        m_type = getType<std::vector<std::string>>();
        m_stringValue.setValue(values);
    }

    void Variant::setValue(const rv::ReMat& value)
    {
        clear();
        m_type = getType<rv::ReMat>();
        m_imageValue.setValue(value);
    }

    void Variant::setValue(const std::vector<rv::ReMat>& values)
    {
        clear();
        m_type = getType<std::vector<rv::ReMat>>();
        m_imageValue.setValue(values);
    }

    void Variant::setValue(const Point2D& value)
    {
        clear();
        m_type = getType<Point2D>();
        m_pointValue.setValue(value);
    }

    void Variant::setValue(const std::vector<Point2D>& values)
    {
        clear();
        m_type = getType<std::vector<Point2D>>();
        m_pointValue.setValue(values);
    }

    void Variant::setValue(const Pose2D& value)
    {
        clear();
        m_type = getType<Pose2D>();
        m_poseValue.setValue(value);
    }

    void Variant::setValue(const std::vector<Pose2D>& values)
    {
        clear();
        m_type = getType<std::vector<Pose2D>>();
        m_poseValue.setValue(values);
    }

    void Variant::setValue(const Line2D& value)
    {
        clear();
        m_type = getType<Line2D>();
        m_lineValue.setValue(value);
    }

    void Variant::setValue(const std::vector<Line2D>& values)
    {
        clear();
        m_type = getType<std::vector<Line2D>>();
        m_lineValue.setValue(values);
    }

    void Variant::setValue(const Circle2D& value)
    {
        clear();
        m_type = getType<Circle2D>();
        m_circleValue.setValue(value);
    }

    void Variant::setValue(const std::vector<Circle2D>& values)
    {
        clear();
        m_type = getType<std::vector<Circle2D>>();
        m_circleValue.setValue(values);
    }

    void Variant::setValue(const Rect2D& value)
    {
        clear();
        m_type = getType<Rect2D>();
        m_rectValue.setValue(value);
    }

    void Variant::setValue(const std::vector<Rect2D>& values)
    {
        clear();
        m_type = getType<std::vector<Rect2D>>();
        m_rectValue.setValue(values);
    }

#pragma endregion

#pragma region 获取

    int Variant::getInt() const
    {
        if (m_type == VariantType::Int)
        {
            return m_intValue.getValue();
        }
        else
        {
            return 0;
        }
    }

    double Variant::getDouble() const
    {
        if (m_type == VariantType::Int)
        {
            return (double)m_intValue.getValue();
        }
        else if (m_type == VariantType::Double)
        {
            return m_doubleValue.getValue();
        }
        else
        {
            return 0;
        }
    }

    std::string Variant::getString() const
    {
        if (m_type == VariantType::String)
        {
            return m_stringValue.getValue();
        }
        else
        {
            return std::string();
        }
    }

    rv::ReMat Variant::getReMat() const
    {
        if (m_type == VariantType::Image)
        {
            return m_imageValue.getValue();
        }
        else
        {
            return rv::ReMat();
        }
    }

    rv::ReMat Variant::getImage() const
    {

        return getReMat();
    }

    Point2D Variant::getPoint() const
    {
        if (m_type == VariantType::Point)
        {
            return m_pointValue.getValue();
        }
        else
        {
            return Point2D();
        }
    }

    Pose2D Variant::getPose() const
    {
        if (m_type == VariantType::Pose)
        {
            return m_poseValue.getValue();
        }
        else
        {
            return Pose2D();
        }
    }

    Line2D Variant::getLine() const
    {
        if (m_type == VariantType::Line)
        {
            return m_lineValue.getValue();
        }
        else
        {
            return Line2D();
        }
    }

    Circle2D Variant::getCircle() const
    {
        if (m_type == VariantType::Circle)
        {
            return m_circleValue.getValue();
        }
        else
        {
            return Circle2D();
        }
    }

    Rect2D Variant::getRect() const
    {
        if (m_type == VariantType::Rect)
        {
            return m_rectValue.getValue();
        }
        else
        {
            return Rect2D();
        }
    }

    const std::vector<int>& Variant::getIntArray() const
    {
        return m_intValue.getValues();
    }

    const std::vector<double>& Variant::getDoubleArray() const
    {
        return m_doubleValue.getValues();
    }

    const std::vector<std::string>& Variant::getStringArray() const
    {
        return m_stringValue.getValues();
    }

    const std::vector<rv::ReMat>& Variant::getReMatArray() const
    {
        return m_imageValue.getValues();
    }

    const std::vector<Point2D>& Variant::getPointArray() const
    {
        return m_pointValue.getValues();
    }

    const std::vector<Pose2D>& Variant::getPoseArray() const
    {
        return m_poseValue.getValues();
    }

    const std::vector<Line2D>& Variant::getLineArray() const
    {
        return m_lineValue.getValues();
    }

    const std::vector<Circle2D>& Variant::getCircleArray() const
    {
        return m_circleValue.getValues();
    }

    const std::vector<Rect2D>& Variant::getRectArray() const
    {
        return m_rectValue.getValues();
    }

#pragma endregion

}
