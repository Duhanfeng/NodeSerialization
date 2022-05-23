#include "variant.h"

namespace qv
{
    Variant::Variant() noexcept :
        m_intValue(),
        m_doubleValue(),
        m_stringValue(),
        m_geometryValue()
    {

    }
    Variant::Variant(const Variant& value) noexcept :
        m_intValue(value.m_intValue),
        m_doubleValue(value.m_doubleValue),
        m_stringValue(value.m_stringValue),
        m_geometryValue(value.m_geometryValue)
    {
        
    }
    Variant::Variant(int value) noexcept
    {
        setValue(value);
    }
    Variant::Variant(double value) noexcept
    {
        setValue(value);
    }
    Variant::Variant(const std::string& value) noexcept
    {
        setValue(value);
    }
    Variant::Variant(const rv::ReMat& value) noexcept
    {
        setValue(value);
    }
    Variant::Variant(const rv::Point<double>& value) noexcept
    {
        setValue(value);
    }
    Variant::Variant(const rv::Pose<double>& value) noexcept
    {
        setValue(value);
    }
    Variant::Variant(const rv::Line<double>& value) noexcept
    {
        setValue(value);
    }
    Variant::Variant(const rv::Circle<double>& value) noexcept
    {
        setValue(value);
    }
    Variant::Variant(const rv::RotatedRect<double>& value) noexcept
    {
        setValue(value);
    }
    Variant::Variant(const GeometryComplex& value) noexcept
    {
        setValue(value);
    }
    Variant::Variant(const std::vector<int>& value) noexcept
    {
        setValue(value);
    }
    Variant::Variant(const std::vector<double>& value) noexcept
    {
        setValue(value);
    }
    Variant::Variant(const std::vector<std::string>& value) noexcept
    {
        setValue(value);
    }
    Variant::Variant(const std::vector<rv::Point<double>>& value) noexcept
    {
        setValue(value);
    }
    Variant::Variant(const std::vector<rv::Pose<double>>& value) noexcept
    {
        setValue(value);
    }
    Variant::Variant(const std::vector<rv::Line<double>>& value) noexcept
    {
        setValue(value);
    }
    Variant::Variant(const std::vector<rv::Circle<double>>& value) noexcept
    {
        setValue(value);
    }
    Variant::Variant(const std::vector<rv::RotatedRect<double>>& value) noexcept
    {
        setValue(value);
    }
    Variant::Variant(const std::vector<GeometryComplex>& value) noexcept
    {
        setValue(value);
    }

    void Variant::setValue(const Variant& value) noexcept
    {
        m_intValue = value.m_intValue;
        m_doubleValue = value.m_doubleValue;
        m_stringValue = value.m_stringValue;
        m_geometryValue = value.m_geometryValue;
    }
    void Variant::setValue(int value) noexcept
    {
        clear();
        m_type = VariantType::Int;
        m_intValue.setValue(value);
    }
    void Variant::setValue(double value) noexcept
    {
        clear();
        m_type = VariantType::Double;
        m_doubleValue.setValue(value);
    }
    void Variant::setValue(const std::string& value) noexcept
    {
        clear();
        m_type = VariantType::String;
        m_stringValue.setValue(value);
    }
    void Variant::setValue(const rv::ReMat& value) noexcept
    {
        clear();
        m_type = VariantType::Image;
        m_imageValue = value;
    }
    void Variant::setValue(const rv::Point<double>& value) noexcept
    {
        clear();
        m_type = VariantType::Point;
        m_geometryValue.setValue(value);

    }
    void Variant::setValue(const rv::Pose<double>& value) noexcept
    {
        clear();
        m_type = VariantType::Pose;
        m_geometryValue.setValue(value);
    }
    void Variant::setValue(const rv::Line<double>& value) noexcept
    {
        clear();
        m_type = VariantType::Line;
        m_geometryValue.setValue(value);
    }
    void Variant::setValue(const rv::Circle<double>& value) noexcept
    {
        clear();
        m_type = VariantType::Circle;
        m_geometryValue.setValue(value);
    }
    void Variant::setValue(const rv::RotatedRect<double>& value) noexcept
    {
        clear();
        m_type = VariantType::Rect;
        m_geometryValue.setValue(value);
    }
    void Variant::setValue(const GeometryComplex& value) noexcept
    {
        clear();
        m_geometryValue.setValue(value);

        switch (value.type)
        {
        case rv::GeometryType::Point:
            m_type = VariantType::Point;
        case rv::GeometryType::Pose:
            m_type = VariantType::Pose;
        case rv::GeometryType::Line:
            m_type = VariantType::Line;
        case rv::GeometryType::Circle:
            m_type = VariantType::Circle;
        case rv::GeometryType::RotatedRect:
            m_type = VariantType::Rect;
        default:
            break;
        }
    }
    void Variant::setValue(const std::vector<int>& value) noexcept
    {
        clear();
        m_type = VariantType::Int;
        m_intValue.setValue(value);
    }
    void Variant::setValue(const std::vector<double>& value) noexcept
    {
        clear();
        m_type = VariantType::Double;
        m_doubleValue.setValue(value);
    }
    void Variant::setValue(const std::vector<std::string>& value) noexcept
    {
        clear();
        m_type = VariantType::String;
        m_stringValue.setValue(value);
    }
    void Variant::setValue(const std::vector<rv::Point<double>>& value) noexcept
    {
        clear();
        m_type = VariantType::Point;
        std::vector<GeometryComplex> geometry;
        for (size_t i = 0; i < value.size(); i++)
        {
            geometry.emplace_back(value[i]);
        }
        m_geometryValue.setValue(geometry);
    }
    void Variant::setValue(const std::vector<rv::Pose<double>>& value) noexcept
    {
        clear();
        m_type = VariantType::Pose;
        std::vector<GeometryComplex> geometry;
        for (size_t i = 0; i < value.size(); i++)
        {
            geometry.emplace_back(value[i]);
        }
        m_geometryValue.setValue(geometry);
    }
    void Variant::setValue(const std::vector<rv::Line<double>>& value) noexcept
    {
        clear();
        m_type = VariantType::Line;
        std::vector<GeometryComplex> geometry;
        for (size_t i = 0; i < value.size(); i++)
        {
            geometry.emplace_back(value[i]);
        }
        m_geometryValue.setValue(geometry);
    }
    void Variant::setValue(const std::vector<rv::Circle<double>>& value) noexcept
    {
        clear();
        m_type = VariantType::Circle;
        std::vector<GeometryComplex> geometry;
        for (size_t i = 0; i < value.size(); i++)
        {
            geometry.emplace_back(value[i]);
        }
        m_geometryValue.setValue(geometry);
    }
    void Variant::setValue(const std::vector<rv::RotatedRect<double>>& value) noexcept
    {
        clear();
        m_type = VariantType::Rect;
        std::vector<GeometryComplex> geometry;
        for (size_t i = 0; i < value.size(); i++)
        {
            geometry.emplace_back(value[i]);
        }
        m_geometryValue.setValue(geometry);
    }
    void Variant::setValue(const std::vector<GeometryComplex>& value) noexcept
    {
        clear();
        if (value.size() > 0)
        {
            switch (value[0].type)
            {
            case rv::GeometryType::Point:
                m_type = VariantType::Point;
            case rv::GeometryType::Pose:
                m_type = VariantType::Pose;
            case rv::GeometryType::Line:
                m_type = VariantType::Line;
            case rv::GeometryType::Circle:
                m_type = VariantType::Circle;
            case rv::GeometryType::RotatedRect:
                m_type = VariantType::Rect;
            default:
                break;
            }
            m_geometryValue.setValue(value);
        }

    }

    bool Variant::supportInt() const
    {
        return m_type == VariantType::Int;
    }
    bool Variant::supportDouble() const
    {
        return (m_type == VariantType::Int) || (m_type == VariantType::Double);
    }
    bool Variant::supportString() const
    {
        return m_type == VariantType::String;
    }
    bool Variant::supportReMat() const
    {
        return m_type == VariantType::Image;
    }
    bool Variant::supportGeometry() const
    {
        return (m_type == VariantType::Point) ||
            (m_type == VariantType::Pose) || 
            (m_type == VariantType::Line) || 
            (m_type == VariantType::Circle) || 
            (m_type == VariantType::Rect);
    }
    bool Variant::supportPoint() const
    {
        return m_type == VariantType::Point;
    }
    bool Variant::supportPose() const
    {
        return m_type == VariantType::Pose;
    }
    bool Variant::supportLine() const
    {
        return m_type == VariantType::Line;
    }
    bool Variant::supportCircle() const
    {
        return m_type == VariantType::Circle;
    }
    bool Variant::supportRect() const
    {
        return m_type == VariantType::Rect;
    }

    int Variant::getInt() const
    {
        if (m_type == VariantType::Int)
        {
            return m_intValue.getValue();
        }
        return 0;
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
        return 0;
    }
    std::string Variant::getString() const
    {
        if (m_type == VariantType::String)
        {
            return m_stringValue.getValue();
        }
        return std::string();
    }
    rv::ReMat Variant::getReMat() const
    {
        if (m_type == VariantType::Image)
        {
            return m_imageValue;
        }
        return rv::ReMat();
    }
    rv::ReMat Variant::getImage() const
    {
        return getReMat();
    }
    rv::Point<double> Variant::getPoint() const
    {
        if (supportGeometry())
        {
            GeometryComplex geometry = m_geometryValue.getValue();
            rv::Point<double> value;
            if (geometry.tryGetPoint(value))
            {
                return value;
            }
        }
        return rv::Point<double>();
    }
    rv::Pose<double> Variant::getPose() const
    {
        if (supportGeometry())
        {
            GeometryComplex geometry = m_geometryValue.getValue();
            rv::Pose<double> value;
            if (geometry.tryGetPose(value))
            {
                return value;
            }
        }
        return rv::Pose<double>();
    }
    rv::Line<double> Variant::getLine() const
    {
        if (supportGeometry())
        {
            GeometryComplex geometry = m_geometryValue.getValue();
            rv::Line<double> value;
            if (geometry.tryGetLine(value))
            {
                return value;
            }
        }
        return rv::Line<double>();
    }
    rv::Circle<double> Variant::getCircle() const
    {
        if (supportGeometry())
        {
            GeometryComplex geometry = m_geometryValue.getValue();
            rv::Circle<double> value;
            if (geometry.tryGetCircle(value))
            {
                return value;
            }
        }
        return rv::Circle<double>();
    }
    rv::RotatedRect<double> Variant::getRect() const
    {
        if (supportGeometry())
        {
            GeometryComplex geometry = m_geometryValue.getValue();
            rv::RotatedRect<double> value;
            if (geometry.tryGetRect(value))
            {
                return value;
            }
        }
        return rv::RotatedRect<double>();
    }
    std::vector<int> Variant::getIntArray() const
    {
        if (m_type == VariantType::Int)
        {
            return m_intValue.getValues();
        }
        return std::vector<int>();
    }
    std::vector<double> Variant::getDoubleArray() const
    {
        if (m_type == VariantType::Int)
        {
            std::vector<double> value;
            const std::vector<int>& value2 = m_intValue.getValues();
            for (size_t i = 0; i < value2.size(); i++)
            {
                value.emplace_back(value2[i]);
            }

            return value;
        }
        else if (m_type == VariantType::Double)
        {
            return m_doubleValue.getValues();
        }
        return std::vector<double>();
    }
    std::vector<std::string> Variant::getStringArray() const
    {
        if (m_type == VariantType::Double)
        {
            return m_stringValue.getValues();
        }
        return std::vector<std::string>();
    }
    std::vector<rv::Point<double>> Variant::getPointArray() const
    {
        if (supportGeometry())
        {
            std::vector<rv::Point<double>> values;
            std::vector<GeometryComplex> geometries = m_geometryValue.getValues();
            for (size_t i = 0; i < geometries.size(); i++)
            {
                rv::Point<double> value;
                if (geometries[i].tryGetPoint(value))
                {
                    values.emplace_back(std::move(value));
                }
            }
            return values;
        }
        return std::vector<rv::Point<double>>();
    }
    std::vector<rv::Pose<double>> Variant::getPoseArray() const
    {
        if (supportGeometry())
        {
            std::vector<rv::Pose<double>> values;
            std::vector<GeometryComplex> geometries = m_geometryValue.getValues();
            for (size_t i = 0; i < geometries.size(); i++)
            {
                rv::Pose<double> value;
                if (geometries[i].tryGetPose(value))
                {
                    values.emplace_back(std::move(value));
                }
            }
            return values;
        }
        return std::vector<rv::Pose<double>>();
    }
    std::vector<rv::Line<double>> Variant::getLineArray() const
    {
        if (supportGeometry())
        {
            std::vector<rv::Line<double>> values;
            std::vector<GeometryComplex> geometries = m_geometryValue.getValues();
            for (size_t i = 0; i < geometries.size(); i++)
            {
                rv::Line<double> value;
                if (geometries[i].tryGetLine(value))
                {
                    values.emplace_back(std::move(value));
                }
            }
            return values;
        }
        return std::vector<rv::Line<double>>();
    }
    std::vector<rv::Circle<double>> Variant::getCircleArray() const
    {
        if (supportGeometry())
        {
            std::vector<rv::Circle<double>> values;
            std::vector<GeometryComplex> geometries = m_geometryValue.getValues();
            for (size_t i = 0; i < geometries.size(); i++)
            {
                rv::Circle<double> value;
                if (geometries[i].tryGetCircle(value))
                {
                    values.emplace_back(std::move(value));
                }
            }
            return values;
        }
        return std::vector<rv::Circle<double>>();
    }
    std::vector<rv::RotatedRect<double>> Variant::getRectArray() const
    {
        if (supportGeometry())
        {
            std::vector<rv::RotatedRect<double>> values;
            std::vector<GeometryComplex> geometries = m_geometryValue.getValues();
            for (size_t i = 0; i < geometries.size(); i++)
            {
                rv::RotatedRect<double> value;
                if (geometries[i].tryGetRect(value))
                {
                    values.emplace_back(std::move(value));
                }
            }
            return values;
        }
        return std::vector<rv::RotatedRect<double>>();
    }

    void Variant::clear()
    {
        m_intValue.clear();
        m_doubleValue.clear();
        m_stringValue.clear();
        m_imageValue.clear();
        m_geometryValue.clear();

        m_type = VariantType::Empty;
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
            return m_imageValue.empty() ? 0 : 1;
        case qv::Variant::VariantType::Point:
        case qv::Variant::VariantType::Pose:
        case qv::Variant::VariantType::Line:
        case qv::Variant::VariantType::Circle:
        case qv::Variant::VariantType::Rect:
            return m_geometryValue.length();
        default:
            break;
        }

        return 0;
    }
}
