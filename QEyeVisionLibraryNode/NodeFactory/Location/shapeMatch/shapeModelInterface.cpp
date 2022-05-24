#include "shapeModelInterface.h"

using namespace rv;

namespace qv
{
    ShapeModelInterface::ShapeModelInterface()
    {
        IShapeModel = rv::MatchInterface::create()->createShapeModel();

    }

#pragma region 基本控制

    bool ShapeModelInterface::create(InputReMat image, InputRegion region)
    {
        
        return IShapeModel->create(image, region);
    }

    bool ShapeModelInterface::create(InputReMat image, InputRegion region, const IsotropicScaling& scaling)
    {

        return IShapeModel->create(image, region, scaling);
    }

    bool ShapeModelInterface::create(InputReMat image, InputRegion region, const AnisotropicScaling& scaling)
    {

        return IShapeModel->create(image, region, scaling);
    }

    void ShapeModelInterface::clear()
    {
        IShapeModel->clear();

    }

    bool ShapeModelInterface::find(InputReMat image, InputRegion region, std::vector<MatchResult>& results) const
    {
       
        return IShapeModel->find(image, region, results);
    }

    void ShapeModelInterface::getContour(std::vector<cv::Point2d>& points) const
    {
        IShapeModel->getContour(points);
    }

#pragma endregion

#pragma region 参数配置

    double ShapeModelInterface::angleStart() const
    {

        return IShapeModel->angleStart();
    }

    void ShapeModelInterface::setAngleStart(double value)
    {
        IShapeModel->setAngleStart(value);
    }

    double ShapeModelInterface::angleEnd() const
    {

        return IShapeModel->angleEnd();
    }

    void ShapeModelInterface::setAngleEnd(double value)
    {
        IShapeModel->setAngleEnd(value);
    }

    double ShapeModelInterface::minScore() const
    {

        return IShapeModel->minScore();
    }

    void ShapeModelInterface::setMinScore(double value)
    {
        IShapeModel->setMinScore(value);
    }

    int ShapeModelInterface::numMatches() const
    {
        
        return IShapeModel->numMatches();
    }

    void ShapeModelInterface::setNumMatches(int value)
    {
        IShapeModel->setNumMatches(value);
    }

    double ShapeModelInterface::maxOverlap() const
    {

        return IShapeModel->maxOverlap();
    }

    void ShapeModelInterface::setMaxOverlap(double value)
    {
        IShapeModel->setMaxOverlap(value);
    }

    void ShapeModelInterface::getOrigin(cv::Point2d& originOffset, double& angle) const
    {
        IShapeModel->getOrigin(originOffset, angle);
    }

    void ShapeModelInterface::setOrigin(const cv::Point2d& originOffset, double angle)
    {
        IShapeModel->setOrigin(originOffset, angle);
    }

#pragma endregion

#pragma region 模板参数

    bool ShapeModelInterface::isCreated() const
    {

        return IShapeModel->isCreated();
    }

    ScalingMode ShapeModelInterface::scalingMode() const
    {
        return IShapeModel->scalingMode();
    }

    IsotropicScaling ShapeModelInterface::isotropicScaling() const
    {
        return IShapeModel->isotropicScaling();
    }

    AnisotropicScaling ShapeModelInterface::anisotropicScaling() const
    {
        return IShapeModel->anisotropicScaling();
    }

    ReMat ShapeModelInterface::templImage() const
    {
        return IShapeModel->templImage();
    }

    Region ShapeModelInterface::templRegion() const
    {
        return IShapeModel->templRegion();
    }

#pragma endregion
}
