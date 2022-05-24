#pragma once

#include <vector>
#include <map>
#include <memory>
#include <QEyeVisionLibrary/QEyeVisionLib.hpp>

namespace qv
{
    /// <summary>
    /// 预处理节点枚举
    /// 定义:会对输入图像进行处理,并输出处理后图像的一类算法
    /// </summary>
    enum class PreprocessNodeEnum
    {
        StartValue = 100001,
        Threshold = StartValue,         //二值化
        Smoothness,                     //图像平滑
        Morphology,                     //形态学处理
        ColorConvert,                   //颜色转换
        ImageProcess,                   //常用预处理

        EndValue,
    };

    /// <summary>
    /// 定位
    /// </summary>
    enum class LocationNodeEnum
    {
        StartValue = 200001,
        ShapeMatch = StartValue,        //形状匹配
        NccMatch,                       //相关性匹配
        ColorMatch,                     //颜色匹配
        ColorFind,                      //颜色查找
        EndValue,
    };

    /// <summary>
    /// 分类
    /// </summary>
    enum class ClassificationNodeEnum
    {
        StartValue = 300001,
        Blob = StartValue,              //Blob
        Texture,                        //纹理

        EndValue,
    };

    /// <summary>
    /// 测量
    /// </summary>
    enum class MeasurementNodeEnum
    {
        StartValue = 400001,
        EdgeDetector = StartValue,      //边缘检测
        FindLine,                       //直线查找
        FindCircle,                     //圆查找
        FindRect,                       //矩形查找
        FitLine,                        //直线拟合
        FitCircle,                      //圆拟合
        DistancePP,                     //距离-点点
        DistancePL,                     //距离-点线
        AngleLL,                        //角度-线线
        AngleLX,                        //角度-线轴
        ProjectionPL,                   //投影-点线
        IntersectionLL,                 //交点-线线
        IntersectionLC,                 //交点-线圆
        IntersectionCC,                 //交点-圆圆

        EndValue,
    };

    /// <summary>
    /// 识别
    /// </summary>
    enum class IDNodeEnum
    {
        StartValue = 500001,
        DataCode = StartValue,          //扫码

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

        ExpandNode = (int)900001,   //(预留用)
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
