#include "nodeBase.h"
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <ReVisionLib/revision.hpp>

using namespace qv;

NodeBase::NodeBase(void* _parent) :
    parent(_parent)
{
    //构建唯一GUID
    boost::uuids::uuid a_uuid = boost::uuids::random_generator()();
    guid = boost::uuids::to_string(a_uuid);
}

NodeBase::~NodeBase()
{
    dispose();

}

qv::RunStatus qv::NodeBase::run(rv::IReWindow* rewindow)
{
    Variant* imVariant = getInputSource(inputImage);
    if (imVariant == nullptr)
    {
        runResult = RunStatus();
        runResult.message = "输入图像为空!";
        runResult.result = RunResult::Error;
        return runResult;
    }

    rv::ReMat src = imVariant->getReMat();

    return runImage(src, rewindow);
}
 
qv::RunStatus qv::NodeBase::triggerNonRun(rv::IReWindow* rewindow)
{
    runResult = qv::RunStatus();
    runResult.message = "不满足执行条件";
    
    return runResult;
}

void qv::NodeBase::dispose()
{

}

NodeInfo qv::NodeBase::getInfo()
{
    NodeInfo info;
    info.guid = guid;
    info.name = name;
    info.description = description;
    info.nodeID = nodeID;

    return info;
}

void qv::NodeBase::setRegion(const rv::Region& _region, const rv::Pose<double>& pose)
{
    region = _region;
    srcPose = pose;

}

rv::Region qv::NodeBase::affineTransRegion(const rv::Pose<double>& dstPose)
{
    if (!isEnableRefer)
    {
        return region;
    }

    if (!region.isShapeRetatedRect())
    {
        return region;
    }

    cv::RotatedRect rect = region.toCvRotatedRect();

    //目标坐标从srcPose->dstPose,计算其region仿射
    cv::Mat matrix = rv::HomMat2D::vectorAngleToRigid(srcPose.center.x, srcPose.center.y, srcPose.angle, dstPose.center.x, dstPose.center.y, dstPose.angle);
    cv::Point2f newCenter;
    rv::HomMat2D::transformPoint2D(matrix, rect.center, newCenter);

    cv::RotatedRect newRect(newCenter, rect.size, rect.angle + (float)rv::rad2deg(dstPose.angle - srcPose.angle));

    return rv::Region(newRect);
}


rv::Region qv::NodeBase::affineTransRegion(const rv::Region& _region, const rv::Pose<double>& dstPose)
{
    if (!isEnableRefer)
    {
        return _region;
    }

    if (!_region.isShapeRetatedRect())
    {
        return _region;
    }

    cv::RotatedRect rect = _region.toCvRotatedRect();

    //目标坐标从srcPose->dstPose,计算其region仿射
    cv::Mat matrix = rv::HomMat2D::vectorAngleToRigid(srcPose.center.x, srcPose.center.y, srcPose.angle, dstPose.center.x, dstPose.center.y, dstPose.angle);
    cv::Point2f newCenter;
    rv::HomMat2D::transformPoint2D(matrix, rect.center, newCenter);

    cv::RotatedRect newRect(newCenter, rect.size, rect.angle + (float)rv::rad2deg(dstPose.angle - srcPose.angle));

    return rv::Region(newRect);
}

void qv::NodeBase::updateReferPose()
{
    //更新仿射参数
    Variant* var = getInputSource(referPose);
    if (var != nullptr)
    {
        srcPose = var->getPose(); //获取当前目标点的点位
    }
}

Variant* qv::NodeBase::getInputSource(const NodeParamDescription& input)
{
    if (getSuperiorNodeVariant != nullptr)
    {
        return getSuperiorNodeVariant(guid, input.paramName);
    }
    else
    {
        locationInputs[input.paramName].setType(input.type);
        return &locationInputs[input.paramName];
    }

}

Variant* qv::NodeBase::getOutputSource(const NodeParamDescription& output)
{
    if (getCurrentNodeVariant != nullptr)
    {
        return getCurrentNodeVariant(guid, output.paramName);
    }
    else
    {
        locationOutputs[output.paramName].setType(output.type);
        return &locationOutputs[output.paramName];
    }

}
