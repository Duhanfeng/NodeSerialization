#pragma once

#include <vector>
#include <map>
#include <memory>
#include <QEyeVisionLibrary/QEyeVisionLib.hpp>

namespace qv
{
    /// <summary>
    /// Ԥ����ڵ�ö��
    /// ����:�������ͼ����д���,����������ͼ���һ���㷨
    /// </summary>
    enum class PreprocessNodeEnum
    {
        StartValue = 100001,
        Threshold = StartValue,         //��ֵ��
        Smoothness,                     //ͼ��ƽ��
        Morphology,                     //��̬ѧ����
        ColorConvert,                   //��ɫת��
        ImageProcess,                   //����Ԥ����

        EndValue,
    };

    /// <summary>
    /// ��λ
    /// </summary>
    enum class LocationNodeEnum
    {
        StartValue = 200001,
        ShapeMatch = StartValue,        //��״ƥ��
        NccMatch,                       //�����ƥ��
        ColorMatch,                     //��ɫƥ��
        ColorFind,                      //��ɫ����
        EndValue,
    };

    /// <summary>
    /// ����
    /// </summary>
    enum class ClassificationNodeEnum
    {
        StartValue = 300001,
        Blob = StartValue,              //Blob
        Texture,                        //����

        EndValue,
    };

    /// <summary>
    /// ����
    /// </summary>
    enum class MeasurementNodeEnum
    {
        StartValue = 400001,
        EdgeDetector = StartValue,      //��Ե���
        FindLine,                       //ֱ�߲���
        FindCircle,                     //Բ����
        FindRect,                       //���β���
        FitLine,                        //ֱ�����
        FitCircle,                      //Բ���
        DistancePP,                     //����-���
        DistancePL,                     //����-����
        AngleLL,                        //�Ƕ�-����
        AngleLX,                        //�Ƕ�-����
        ProjectionPL,                   //ͶӰ-����
        IntersectionLL,                 //����-����
        IntersectionLC,                 //����-��Բ
        IntersectionCC,                 //����-ԲԲ

        EndValue,
    };

    /// <summary>
    /// ʶ��
    /// </summary>
    enum class IDNodeEnum
    {
        StartValue = 500001,
        DataCode = StartValue,          //ɨ��

        EndValue,
    };

    enum class NodeIDEnum
    {
        None = -1,
        Threshold = (int)PreprocessNodeEnum::Threshold,
        Smoothness = (int)PreprocessNodeEnum::Smoothness,
        Morphology = (int)PreprocessNodeEnum::Morphology,
        ColorConvert = (int)PreprocessNodeEnum::ColorConvert,
        ImageProcess = (int)PreprocessNodeEnum::ImageProcess,

        ShapeMatch = (int)LocationNodeEnum::ShapeMatch,
        NccMatch = (int)LocationNodeEnum::NccMatch,
        ColorMatch = (int)LocationNodeEnum::ColorMatch,
        ColorFind = (int)LocationNodeEnum::ColorFind,

        Blob = (int)ClassificationNodeEnum::Blob,
        Texture = (int)ClassificationNodeEnum::Texture,

        EdgeDetector = (int)MeasurementNodeEnum::EdgeDetector,
        FindLine = (int)MeasurementNodeEnum::FindLine,
        FindCircle = (int)MeasurementNodeEnum::FindCircle,
        FindRect = (int)MeasurementNodeEnum::FindRect,
        FitLine = (int)MeasurementNodeEnum::FitLine,
        FitCircle = (int)MeasurementNodeEnum::FitCircle,
        DistancePP = (int)MeasurementNodeEnum::DistancePP,
        DistancePL = (int)MeasurementNodeEnum::DistancePL,
        AngleLL = (int)MeasurementNodeEnum::AngleLL,
        AngleLX = (int)MeasurementNodeEnum::AngleLX,
        ProjectionPL = (int)MeasurementNodeEnum::ProjectionPL,
        IntersectionLL = (int)MeasurementNodeEnum::IntersectionLL,
        IntersectionLC = (int)MeasurementNodeEnum::IntersectionLC,
        IntersectionCC = (int)MeasurementNodeEnum::IntersectionCC,

        DataCode = (int)IDNodeEnum::DataCode,

        ExpandNode = (int)900001,   //(Ԥ����)
    };

    class NodeClassInfo
    {
    public:
        NodeIDEnum nodeID = NodeIDEnum::None;
        int categoryIndex = -1;
        std::string categoryName;
        std::string categoryDisplay;
        std::string nodeName;
        std::string nodeDisplay;
        std::string description;
    };

    class NodeFactory
    {
    public:
        NodeFactory(const NodeFactory&) = delete;
        NodeFactory& operator=(const NodeFactory&) = delete;
        static NodeFactory& getInstance()
        {
            static NodeFactory instance;
            return instance;
        }
    private:
        NodeFactory();

    public:
        const std::vector<NodeClassInfo>& getNodeInfos();
        NodeClassInfo getNodeInfo(NodeIDEnum nodeID);
        NodeBase* createNode(NodeIDEnum nodeID, void* parent = nullptr);

    private:
        std::vector<NodeClassInfo> nodeInfos;
        std::map<NodeIDEnum, NodeClassInfo> nodeInfoMap;
    };

}
