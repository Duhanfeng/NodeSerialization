#pragma once

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

#include "node_A.h"
#include "node_B.h"


template<typename _Tp> inline bool serializeText(const _Tp& data, const std::string& file)
{
    try
    {
        std::ofstream bs(file);
        boost::archive::text_oarchive bo(bs);
        bo << data;
        bs.close();
        return true;
    }
    catch (const std::exception& ex)
    {
        std::cout << "serializeObj: " << ex.what() << std::endl;
    }

    return false;
}

template<typename _Tp> inline bool deserializeText(_Tp& data, const std::string& file)
{
    try
    {
        std::ifstream bs(file, std::ios_base::in);
        boost::archive::text_iarchive bi(bs);
        bi >> data;
        bs.close();
        return true;
    }
    catch (const std::exception& ex)
    {
        //如果反序列化失败,则置为默认,避免出现异常(例如,里面的变量一半反序列化一半默认的情况)
        data = _Tp();
        std::cout << "deserializeObj: " << ex.what() << std::endl;
    }

    return false;
}


template<typename _Tp> inline bool serializeBin(const _Tp& data, const std::string& file)
{
    try
    {
        std::ofstream bs(file);
        boost::archive::binary_oarchive bo(bs);   //二进制序列化并不具备跨平台性
        bo << data;
        bs.close();
        return true;
    }
    catch (const std::exception& ex)
    {
        std::cout << "serializeObj: " << ex.what() << std::endl;
    }

    return false;
}

template<typename _Tp> inline bool deserializeBin(_Tp& data, const std::string& file)
{
    try
    {
        std::ifstream bs(file, std::ios_base::in | std::ios_base::binary);
        boost::archive::binary_iarchive bi(bs);
        bi >> data;
        bs.close();
        return true;
    }
    catch (const std::exception& ex)
    {
        //如果反序列化失败,则置为默认,避免出现异常(例如,里面的变量一半反序列化一半默认的情况)
        data = _Tp();
        std::cout << "deserializeObj: " << ex.what() << std::endl;
    }

    return false;
}


template<typename _Tp> inline bool serializeXml(const _Tp& data, const std::string& file)
{
    try
    {
        std::ofstream bs(file);
        boost::archive::xml_oarchive bo(bs, boost::archive::no_header);
        bo << BOOST_SERIALIZATION_NVP(data);
        bs.close();
        return true;
    }
    catch (const std::exception& ex)
    {
        std::cout << "serializeObj: " << ex.what() << std::endl;
    }

    return false;
}

template<typename _Tp> inline bool deserializeXml(_Tp& data, const std::string& file)
{
    try
    {
        std::ifstream bs(file, std::ios_base::in);
        boost::archive::xml_iarchive bi(bs, boost::archive::no_header);
        bi >> BOOST_SERIALIZATION_NVP(data);
        bs.close();
        return true;
    }
    catch (const std::exception& ex)
    {
        //如果反序列化失败,则置为默认,避免出现异常(例如,里面的变量一半反序列化一半默认的情况)
        data = _Tp();
        std::cout << "deserializeObj: " << ex.what() << std::endl;
    }

    return false;
}
