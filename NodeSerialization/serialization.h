#pragma once

#include <fstream>
#include <boost/archive/binary_iarchive.hpp>    //���������л�
#include <boost/archive/binary_oarchive.hpp>    //���������л�
#include <boost/archive/text_iarchive.hpp>      //�ı����л�
#include <boost/archive/text_oarchive.hpp>      //�ı����л�
#include <boost/archive/xml_iarchive.hpp>       //XML�ı����л�
#include <boost/archive/xml_oarchive.hpp>       //XML�ı����л�
#include <boost/serialization/vector.hpp>       //���л�STL����Ҫ����
#include <boost/serialization/map.hpp>          //���л�STL����Ҫ����
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
        //��������л�ʧ��,����ΪĬ��,��������쳣(����,����ı���һ�뷴���л�һ��Ĭ�ϵ����)
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
        boost::archive::binary_oarchive bo(bs);   //���������л������߱���ƽ̨��
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
        //��������л�ʧ��,����ΪĬ��,��������쳣(����,����ı���һ�뷴���л�һ��Ĭ�ϵ����)
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
        //��������л�ʧ��,����ΪĬ��,��������쳣(����,����ı���һ�뷴���л�һ��Ĭ�ϵ����)
        data = _Tp();
        std::cout << "deserializeObj: " << ex.what() << std::endl;
    }

    return false;
}
