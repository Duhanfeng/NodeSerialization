#pragma once

#include <fstream>
#include <boost/archive/binary_iarchive.hpp>    //���������л�
#include <boost/archive/binary_oarchive.hpp>    //���������л�
#include <boost/archive/text_iarchive.hpp>      //�ı����л�
#include <boost/archive/text_oarchive.hpp>      //�ı����л�
#include <boost/serialization/vector.hpp>       //���л�STL����Ҫ����
#include <boost/serialization/map.hpp>          //���л�STL����Ҫ����
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
        //boost::archive::binary_oarchive bo(bs);   //���������л������߱���ƽ̨��,�ĳ��ı����л�
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
        //��������л�ʧ��,����ΪĬ��,��������쳣(����,����ı���һ�뷴���л�һ��Ĭ�ϵ����)
        data = _Tp();
        std::cout << "deserializeObj: " << ex.what() << std::endl;
    }

    return false;
}

