#include "serialization.h"

#include <fstream>
#include <boost/archive/binary_iarchive.hpp>    //二进制序列化
#include <boost/archive/binary_oarchive.hpp>    //二进制序列化
#include <boost/archive/text_iarchive.hpp>      //文本序列化
#include <boost/archive/text_oarchive.hpp>      //文本序列化
#include <boost/archive/xml_iarchive.hpp>       //XML文本序列化
#include <boost/archive/xml_oarchive.hpp>       //XML文本序列化
#include <boost/serialization/vector.hpp>       //序列化STL容器要导入
#include <boost/serialization/map.hpp>          //序列化STL容器要导入
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/shared_ptr_helper.hpp>
#include <boost/serialization/unique_ptr.hpp>
#include <boost/serialization/serialization.hpp>

#include "Preprocess/threshold/node.h"
#include "Preprocess/smoothness/node.h"
#include "Preprocess/morphology/node.h"
#include "Preprocess/colorConvert/node.h"
#include "Preprocess/imageProcess/node.h"
#include "Location/shapeMatch/node.h"
#include "Location/nccMatch/node.h"
#include "Location/colorFind/node.h"
#include "ID/dataCode/node.h"
#include "Measurement/findLine/node.h"
#include "Measurement/findCircle/node.h"
#include "Measurement/findRect/node.h"

template<class _Tp>
inline void registerNodeType(_Tp& value)
{
    value.template register_type<qv::ThresholdNode>(nullptr);
    value.template register_type<qv::SmoothnessNode>(nullptr);
    value.template register_type<qv::MorphologyNode>(nullptr);
    value.template register_type<qv::ColorConvertNode>(nullptr);
    value.template register_type<qv::ImageProcessNode>(nullptr);
    value.template register_type<qv::ShapeMatchNode>(nullptr);
    value.template register_type<qv::NccMatchNode>(nullptr);
    //value.template register_type<qv::ColorMatchNode>(nullptr);
    value.template register_type<qv::ColorFindNode>(nullptr);
    //value.template register_type<qv::BlobNode>(nullptr);
    //value.template register_type<qv::TextureNode>(nullptr);
    //value.template register_type<qv::EdgeDetectorNode>(nullptr);
    value.template register_type<qv::FindLineNode>(nullptr);
    value.template register_type<qv::FindCircleNode>(nullptr);
    value.template register_type<qv::FindRectNode>(nullptr);
    //value.template register_type<qv::FitLineNode>(nullptr);
    //value.template register_type<qv::FitCircleNode>(nullptr);
    //value.template register_type<qv::DistancePPNode>(nullptr);
    //value.template register_type<qv::DistancePLNode>(nullptr);
    //value.template register_type<qv::AngleLLNode>(nullptr);
    //value.template register_type<qv::AngleLXNode>(nullptr);
    //value.template register_type<qv::ProjectionPLNode>(nullptr);
    //value.template register_type<qv::IntersectionLLNode>(nullptr);
    //value.template register_type<qv::IntersectionLCNode>(nullptr);
    //value.template register_type<qv::IntersectionCCNode>(nullptr);
    value.template register_type<qv::DataCodeNode>(nullptr);
}

template<typename _Tp>
inline constexpr bool qv::serializeText(const _Tp& data, const std::string& file) noexcept
{
    try
    {
        std::ofstream bs(file, std::ios_base::out);
        boost::archive::text_oarchive bo(bs);
        registerNodeType(bo);
        bo << BOOST_SERIALIZATION_NVP(data);
        bs.close();
        return true;
    }
    catch (const std::exception& ex)
    {
        std::cout << "serializeText: " << ex.what() << std::endl;
    }

    return false;
}

template<typename _Tp>
inline constexpr bool qv::deserializeText(_Tp& data, const std::string& file) noexcept
{
    try
    {
        std::ifstream bs(file, std::ios_base::in);
        boost::archive::text_iarchive bi(bs);
        registerNodeType(bi);
        bi >> BOOST_SERIALIZATION_NVP(data);
        bs.close();
        return true;
    }
    catch (const std::exception& ex)
    {
        //如果反序列化失败,则置为默认,避免出现异常(例如,里面的变量一半反序列化一半默认的情况)
        data = _Tp();
        std::cout << "deserializeText: " << ex.what() << std::endl;
    }

    return false;
}

template<typename _Tp>
inline constexpr bool qv::serializeBin(const _Tp& data, const std::string& file) noexcept
{
    try
    {
        std::ofstream bs(file, std::ios_base::out | std::ios_base::binary);
        boost::archive::binary_oarchive bo(bs);     //二进制序列化并不具备跨平台性
        registerNodeType(bo);
        bo << BOOST_SERIALIZATION_NVP(data);
        bs.close();
        return true;
    }
    catch (const std::exception& ex)
    {
        std::cout << "serializeBin: " << ex.what() << std::endl;
    }

    return false;
}

template<typename _Tp>
inline constexpr bool qv::deserializeBin(_Tp& data, const std::string& file) noexcept
{
    try
    {
        std::ifstream bs(file, std::ios_base::in | std::ios_base::binary);
        boost::archive::binary_iarchive bi(bs);
        registerNodeType(bi);
        bi >> BOOST_SERIALIZATION_NVP(data);
        bs.close();
        return true;
    }
    catch (const std::exception& ex)
    {
        //如果反序列化失败,则置为默认,避免出现异常(例如,里面的变量一半反序列化一半默认的情况)
        data = _Tp();
        std::cout << "deserializeBin: " << ex.what() << std::endl;
    }

    return false;
}

template<typename _Tp>
inline constexpr bool qv::serializeXml(const _Tp& data, const std::string& file) noexcept
{
    try
    {
        std::ofstream bs(file, std::ios_base::out);
        boost::archive::xml_oarchive bo(bs, boost::archive::no_header);
        registerNodeType(bo);
        bo << BOOST_SERIALIZATION_NVP(data);
        bs.close();
        return true;
    }
    catch (const std::exception& ex)
    {
        std::cout << "serializeXml: " << ex.what() << std::endl;
    }

    return false;
}

template<typename _Tp>
inline constexpr bool qv::deserializeXml(_Tp& data, const std::string& file) noexcept
{
    try
    {
        std::ifstream bs(file, std::ios_base::in);
        boost::archive::xml_iarchive bi(bs, boost::archive::no_header);
        registerNodeType(bi);
        bi >> BOOST_SERIALIZATION_NVP(data);
        bs.close();
        return true;
    }
    catch (const std::exception& ex)
    {
        //如果反序列化失败,则置为默认,避免出现异常(例如,里面的变量一半反序列化一半默认的情况)
        data = _Tp();
        std::cout << "deserializeXml: " << ex.what() << std::endl;
    }

    return false;
}

