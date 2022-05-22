#pragma once

#include <fstream>
#include <boost/archive/binary_iarchive.hpp>    //二进制序列化
#include <boost/archive/binary_oarchive.hpp>    //二进制序列化
#include <boost/archive/text_iarchive.hpp>      //文本序列化
#include <boost/archive/text_oarchive.hpp>      //文本序列化
#include <boost/serialization/vector.hpp>       //序列化STL容器要导入
#include <boost/serialization/map.hpp>          //序列化STL容器要导入
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/shared_ptr_helper.hpp>
#include <boost/serialization/unique_ptr.hpp>
#include <boost/serialization/serialization.hpp>

#include "node_A.h"
#include "node_B.h"


template<typename _Tp> inline bool serializeObj(const _Tp& data, const std::string& file)
{
    try
    {
        std::ofstream bs(file);
        //boost::archive::binary_oarchive bo(bs);   //二进制序列化并不具备跨平台性,改成文本序列化
        boost::archive::text_oarchive bo(bs);
        //bo.template register_type<NodeA>(nullptr);
        //bo.template register_type<NodeB>(nullptr);
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

template<typename _Tp> inline bool deserializeObj(_Tp& data, const std::string& file)
{
    try
    {
        std::ifstream bs(file, std::ios_base::in | std::ios_base::binary);
        //boost::archive::binary_iarchive bi(bs);
        boost::archive::text_iarchive bi(bs);
        //bi.template register_type<NodeA>(nullptr);
        //bi.template register_type<NodeB>(nullptr);
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

