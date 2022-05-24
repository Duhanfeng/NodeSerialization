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
        { qv::NodeIDEnum::Threshold,       0,   "Preprocess",        u8"Ԥ����",    "Threshold",          u8"��ֵ��",      ""   },
        { qv::NodeIDEnum::Smoothness,      0,   "Preprocess",        u8"Ԥ����",    "Smoothness",         u8"ͼ��ƽ��",    ""   },
        { qv::NodeIDEnum::Morphology,      0,   "Preprocess",        u8"Ԥ����",    "Morphology",         u8"��̬ѧ",      ""   },
        { qv::NodeIDEnum::ColorConvert,    0,   "Preprocess",        u8"Ԥ����",    "ColorConvert",       u8"��ɫת��",    ""   },
        { qv::NodeIDEnum::ImageProcess,    0,   "Preprocess",        u8"Ԥ����",    "ImageProcess",       u8"����Ԥ����",  ""   },
                                           
        { qv::NodeIDEnum::ShapeMatch,      1,   "Location",          u8"��λ",      "ShapeMatch",         u8"����ƥ��",    ""   },
        { qv::NodeIDEnum::NccMatch,        1,   "Location",          u8"��λ",      "NccMatch",           u8"�Ҷ�ƥ��",    ""   },
        { qv::NodeIDEnum::ColorMatch,      1,   "Location",          u8"��λ",      "ColorMatch",         u8"��ɫƥ��",    ""   },
        { qv::NodeIDEnum::ColorFind,       1,   "Location",          u8"��λ",      "ColorFind",          u8"��ɫ����",    ""   },
                                           
        { qv::NodeIDEnum::Blob,            2,   "Classification",    u8"����",      "Blob",               u8"��������",    ""   },
        { qv::NodeIDEnum::Texture,         2,   "Classification",    u8"����",      "Texture",            u8"�������",    ""   },
                                           
        { qv::NodeIDEnum::EdgeDetector,    3,   "Measurement",       u8"����",      "EdgeDetector",       u8"��Ե���",    ""   },
        { qv::NodeIDEnum::FindLine,        3,   "Measurement",       u8"����",      "FindLine",           u8"ֱ�߲���",    ""   },
        { qv::NodeIDEnum::FindCircle,      3,   "Measurement",       u8"����",      "FindCircle",         u8"Բ����",      ""   },
        { qv::NodeIDEnum::FindRect,        3,   "Measurement",       u8"����",      "FindRect",           u8"���β���",    ""   },
        { qv::NodeIDEnum::FitLine,         3,   "Measurement",       u8"����",      "FitLine",            u8"ֱ�����",    ""   },
        { qv::NodeIDEnum::FitCircle,       3,   "Measurement",       u8"����",      "FitCircle",          u8"Բ���",      ""   },
        { qv::NodeIDEnum::DistancePP,      3,   "Measurement",       u8"����",      "DistancePP",         u8"����-���",   ""   },
        { qv::NodeIDEnum::DistancePL,      3,   "Measurement",       u8"����",      "DistancePL",         u8"����-����",   ""   },
        { qv::NodeIDEnum::AngleLL,         3,   "Measurement",       u8"����",      "AngleLL",            u8"�Ƕ�-����",   ""   },
        { qv::NodeIDEnum::AngleLX,         3,   "Measurement",       u8"����",      "AngleLX",            u8"�Ƕ�-����",   ""   },
        { qv::NodeIDEnum::ProjectionPL,    3,   "Measurement",       u8"����",      "ProjectionPL",       u8"ͶӰ-����",   ""   },
        { qv::NodeIDEnum::IntersectionLL,  3,   "Measurement",       u8"����",      "IntersectionLL",     u8"����-����",   ""   },
        { qv::NodeIDEnum::IntersectionLC,  3,   "Measurement",       u8"����",      "IntersectionLC",     u8"����-��Բ",   ""   },
        { qv::NodeIDEnum::IntersectionCC,  3,   "Measurement",       u8"����",      "IntersectionCC",     u8"����-ԲԲ",   ""   },
                                           
        { qv::NodeIDEnum::DataCode,        4,   "ID",                u8"ʶ��",      "DataCode",           u8"ɨ��",        ""   },
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
