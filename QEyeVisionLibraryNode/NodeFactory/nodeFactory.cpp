#include "nodeFactory.h"

#include <initializer_list>
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

qv::NodeFactory::NodeFactory()
{
    nodeInfos =
    {
        { qv::NodeIDEnum::Threshold,       0,   "Preprocess",        u8"预处理",    "Threshold",          u8"二值化",      ""   },
        { qv::NodeIDEnum::Smoothness,      0,   "Preprocess",        u8"预处理",    "Smoothness",         u8"图像平滑",    ""   },
        { qv::NodeIDEnum::Morphology,      0,   "Preprocess",        u8"预处理",    "Morphology",         u8"形态学",      ""   },
        { qv::NodeIDEnum::ColorConvert,    0,   "Preprocess",        u8"预处理",    "ColorConvert",       u8"颜色转换",    ""   },
        { qv::NodeIDEnum::ImageProcess,    0,   "Preprocess",        u8"预处理",    "ImageProcess",       u8"常用预处理",  ""   },
                                           
        { qv::NodeIDEnum::ShapeMatch,      1,   "Location",          u8"定位",      "ShapeMatch",         u8"轮廓匹配",    ""   },
        { qv::NodeIDEnum::NccMatch,        1,   "Location",          u8"定位",      "NccMatch",           u8"灰度匹配",    ""   },
        { qv::NodeIDEnum::ColorMatch,      1,   "Location",          u8"定位",      "ColorMatch",         u8"颜色匹配",    ""   },
        { qv::NodeIDEnum::ColorFind,       1,   "Location",          u8"定位",      "ColorFind",          u8"颜色查找",    ""   },
                                           
        { qv::NodeIDEnum::Blob,            2,   "Classification",    u8"分类",      "Blob",               u8"轮廓分类",    ""   },
        { qv::NodeIDEnum::Texture,         2,   "Classification",    u8"分类",      "Texture",            u8"纹理分类",    ""   },
                                           
        { qv::NodeIDEnum::EdgeDetector,    3,   "Measurement",       u8"测量",      "EdgeDetector",       u8"边缘检测",    ""   },
        { qv::NodeIDEnum::FindLine,        3,   "Measurement",       u8"测量",      "FindLine",           u8"直线查找",    ""   },
        { qv::NodeIDEnum::FindCircle,      3,   "Measurement",       u8"测量",      "FindCircle",         u8"圆查找",      ""   },
        { qv::NodeIDEnum::FindRect,        3,   "Measurement",       u8"测量",      "FindRect",           u8"矩形查找",    ""   },
        { qv::NodeIDEnum::FitLine,         3,   "Measurement",       u8"测量",      "FitLine",            u8"直线拟合",    ""   },
        { qv::NodeIDEnum::FitCircle,       3,   "Measurement",       u8"测量",      "FitCircle",          u8"圆拟合",      ""   },
        { qv::NodeIDEnum::DistancePP,      3,   "Measurement",       u8"测量",      "DistancePP",         u8"距离-点点",   ""   },
        { qv::NodeIDEnum::DistancePL,      3,   "Measurement",       u8"测量",      "DistancePL",         u8"距离-点线",   ""   },
        { qv::NodeIDEnum::AngleLL,         3,   "Measurement",       u8"测量",      "AngleLL",            u8"角度-线线",   ""   },
        { qv::NodeIDEnum::AngleLX,         3,   "Measurement",       u8"测量",      "AngleLX",            u8"角度-线轴",   ""   },
        { qv::NodeIDEnum::ProjectionPL,    3,   "Measurement",       u8"测量",      "ProjectionPL",       u8"投影-点线",   ""   },
        { qv::NodeIDEnum::IntersectionLL,  3,   "Measurement",       u8"测量",      "IntersectionLL",     u8"交点-线线",   ""   },
        { qv::NodeIDEnum::IntersectionLC,  3,   "Measurement",       u8"测量",      "IntersectionLC",     u8"交点-线圆",   ""   },
        { qv::NodeIDEnum::IntersectionCC,  3,   "Measurement",       u8"测量",      "IntersectionCC",     u8"交点-圆圆",   ""   },
                                           
        { qv::NodeIDEnum::DataCode,        4,   "ID",                u8"识别",      "DataCode",           u8"扫码",        ""   },
    };

    for (size_t i = 0; i < nodeInfos.size(); i++)
    {
        nodeInfoMap.emplace(nodeInfos[i].nodeID, nodeInfos[i]);
    }

}

const std::vector<qv::NodeClassInfo>& qv::NodeFactory::getNodeInfos()
{
    return nodeInfos;
}

qv::NodeClassInfo qv::NodeFactory::getNodeInfo(NodeIDEnum nodeID)
{
    if (nodeInfoMap.find(nodeID) != nodeInfoMap.end())
    {
        return nodeInfoMap[nodeID];
    }

    return qv::NodeClassInfo();
}

qv::NodeBase* qv::NodeFactory::createNode(NodeIDEnum nodeID, void* parent)
{
    qv::NodeBase* node = nullptr;

    switch (nodeID)
    {
    case qv::NodeIDEnum::Threshold:
        node = new ThresholdNode(parent);
        break;
    case qv::NodeIDEnum::Smoothness:
        node = new SmoothnessNode(parent);
        break;
    case qv::NodeIDEnum::Morphology:
        node = new MorphologyNode(parent);
        break;
    case qv::NodeIDEnum::ColorConvert:
        node = new ColorConvertNode(parent);
        break;
    case qv::NodeIDEnum::ImageProcess:
        node = new ImageProcessNode(parent);
        break;
    case qv::NodeIDEnum::ShapeMatch:
        node = new ShapeMatchNode(parent);
        break;
    case qv::NodeIDEnum::NccMatch:
        node = new NccMatchNode(parent);
        break;
    case qv::NodeIDEnum::ColorMatch:
        //node = new ColorMatchNode(parent);
        break;
    case qv::NodeIDEnum::ColorFind:
        node = new ColorFindNode(parent);
        break;
    case qv::NodeIDEnum::Blob:
        //node = new BlobNode(parent);
        break;
    case qv::NodeIDEnum::Texture:
        //node = new TextureNode(parent);
        break;
    case qv::NodeIDEnum::EdgeDetector:
        //node = new EdgeDetectorNode(parent);
        break;
    case qv::NodeIDEnum::FindLine:
        node = new FindLineNode(parent);
        break;
    case qv::NodeIDEnum::FindCircle:
        node = new FindCircleNode(parent);
        break;
    case qv::NodeIDEnum::FindRect:
        node = new FindRectNode(parent);
        break;
    case qv::NodeIDEnum::FitLine:
        //node = new FitLineNode(parent);
        break;
    case qv::NodeIDEnum::FitCircle:
        //node = new FitCircleNode(parent);
        break;
    case qv::NodeIDEnum::DistancePP:
        //node = new DistancePPNode(parent);
        break;
    case qv::NodeIDEnum::DistancePL:
        //node = new DistancePLNode(parent);
        break;
    case qv::NodeIDEnum::AngleLL:
        //node = new AngleLLNode(parent);
        break;
    case qv::NodeIDEnum::AngleLX:
        //node = new AngleLXNode(parent);
        break;
    case qv::NodeIDEnum::ProjectionPL:
        //node = new ProjectionPLNode(parent);
        break;
    case qv::NodeIDEnum::IntersectionLL:
        //node = new IntersectionLLNode(parent);
        break;
    case qv::NodeIDEnum::IntersectionLC:
        //node = new IntersectionLCNode(parent);
        break;
    case qv::NodeIDEnum::IntersectionCC:
        //node = new IntersectionCCNode(parent);
        break;
    case qv::NodeIDEnum::DataCode:
        node = new DataCodeNode(parent);
        break;
    default:
        break;
    }

    return node;
}
