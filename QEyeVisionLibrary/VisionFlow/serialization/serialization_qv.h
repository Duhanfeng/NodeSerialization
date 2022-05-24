#pragma once

#include <iostream>
#include <fstream>
#include <boost/archive/binary_iarchive.hpp>    //二进制序列化
#include <boost/archive/binary_oarchive.hpp>    //二进制序列化
#include <boost/serialization/vector.hpp>       //序列化STL容器要导入
#include <boost/serialization/map.hpp>          //序列化STL容器要导入
#include <opencv2/opencv.hpp>

#include <ReVisionLib/ReVision.hpp>
#include <QEyeVisionLibrary/VisionFlow/variant/variant.h>
#include <QEyeVisionLibrary/VisionFlow/nodeBase.h>
#include <QEyeVisionLibrary/VisionFlow/flowUnit.h>
#include <QEyeVisionLibrary/VisionFlow/variant/variant_geometry.h>

namespace boost 
{
    namespace serialization 
    {
#pragma region geometry

        template <class Archive>
        void serialize(Archive& ar, qv::GeometryComplex& geometry, const unsigned int version)
        {
            ar& BOOST_SERIALIZATION_NVP(geometry.x);
            ar& BOOST_SERIALIZATION_NVP(geometry.y);
            ar& BOOST_SERIALIZATION_NVP(geometry.w);
            ar& BOOST_SERIALIZATION_NVP(geometry.h);
            ar& BOOST_SERIALIZATION_NVP(geometry.angle);
            ar& BOOST_SERIALIZATION_NVP(geometry.x2);
            ar& BOOST_SERIALIZATION_NVP(geometry.y2);
        }

#pragma endregion


#pragma region nodeBase

        template<class Archive>
        void serialize(Archive& ar, qv::NodeParamDescription& nodeParam, const unsigned int version)
        {
            ar& BOOST_SERIALIZATION_NVP(nodeParam.paramName);
            ar& BOOST_SERIALIZATION_NVP(nodeParam.description);
            ar& BOOST_SERIALIZATION_NVP(nodeParam.type);
            ar& BOOST_SERIALIZATION_NVP(nodeParam.defaultSource);
        }

        template<class Archive>
        void serialize(Archive& ar, qv::NodeInfo& data, const unsigned int version)
        {
            ar& BOOST_SERIALIZATION_NVP(data.guid);
            ar& BOOST_SERIALIZATION_NVP(data.name);
            ar& BOOST_SERIALIZATION_NVP(data.description);
            ar& BOOST_SERIALIZATION_NVP(data.nodeID);
        }

#pragma endregion

#pragma region 连接器相关

        template<class Archive>
        void serialize(Archive& ar, qv::NodePrecondition& data, const unsigned int version)
        {
            ar& BOOST_SERIALIZATION_NVP(data.useThis);
            ar& BOOST_SERIALIZATION_NVP(data.dstGuid);
            ar& BOOST_SERIALIZATION_NVP(data.isOkRun);
        }

        template<class Archive>
        void serialize(Archive& ar, qv::NodeOutputInfo& info, const unsigned int version)
        {
            ar& BOOST_SERIALIZATION_NVP(info.nodeGuid);
            ar& BOOST_SERIALIZATION_NVP(info.nodeName);
            ar& BOOST_SERIALIZATION_NVP(info.paramName);
            ar& BOOST_SERIALIZATION_NVP(info.type);
        }

        template<class Archive>
        void serialize(Archive& ar, qv::NodeConnection::NodeOutput& output, const unsigned int version)
        {
            ar& BOOST_SERIALIZATION_NVP(output.info);

        }

        template<class Archive>
        void serialize(Archive& ar, qv::NodeConnection& connection, const unsigned int version)
        {
            ar& BOOST_SERIALIZATION_NVP(connection.nodeIndexs);
            ar& BOOST_SERIALIZATION_NVP(connection.nodeCurrent);
            ar& BOOST_SERIALIZATION_NVP(connection.nodeSuperior);
            ar& BOOST_SERIALIZATION_NVP(connection.nodePrecondition);
        }

#pragma endregion

#pragma region 输出结果打包

        template<class Archive>
        void serialize(Archive& ar, qv::OutputSelection& output, const unsigned int version)
        {
            ar& BOOST_SERIALIZATION_NVP(output.guid);
            ar& BOOST_SERIALIZATION_NVP(output.paramName);
            ar& BOOST_SERIALIZATION_NVP(output.cmdName);
        }

        template<class Archive>
        void serialize(Archive& ar, qv::ResultOutputPacket& output, const unsigned int version)
        {
            ar& BOOST_SERIALIZATION_NVP(output.startChar);
            ar& BOOST_SERIALIZATION_NVP(output.endChar);
            ar& BOOST_SERIALIZATION_NVP(output.separateChar);
            ar& BOOST_SERIALIZATION_NVP(output.selections);
            ar& BOOST_SERIALIZATION_NVP(output.vectorSeparateChar);

            ar& BOOST_SERIALIZATION_NVP(output.isAmplifyFloat);
            ar& BOOST_SERIALIZATION_NVP(output.amplifyRate);
            ar& BOOST_SERIALIZATION_NVP(output.floatLength);
        }

#pragma endregion

    } // namespace serialization
} // namespace boost
