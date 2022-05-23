#include "nccModelInterface.h"

using namespace rv;

namespace qv
{
    NccModelInterface::NccModelInterface()
    {
        INccModel = rv::MatchInterface::create()->createNccModel();

    }

#pragma region 基本控制

    bool NccModelInterface::create(InputReMat image, InputRegion region)
    {
        
        return INccModel->create(image, region);
    }

    bool NccModelInterface::create(InputReMat image, InputRegion region, const IsotropicScaling& scaling)
    {

        return INccModel->create(image, region, scaling);
    }

    bool NccModelInterface::create(InputReMat image, InputRegion region, const AnisotropicScaling& scaling)
    {

        return INccModel->create(image, region, scaling);
    }

    void NccModelInterface::clear()
    {
        INccModel->clear();

    }

    bool NccModelInterface::find(InputReMat image, InputRegion region, std::vector<MatchResult>& results) const
    {
       
        return INccModel->find(image, region, results);
    }

#pragma endregion

#pragma region 参数配置

    double NccModelInterface::angleStart() const
    {

        return INccModel->angleStart();
    }

    void NccModelInterface::setAngleStart(double value)
    {
        INccModel->setAngleStart(value);
    }

    double NccModelInterface::angleEnd() const
    {

        return INccModel->angleEnd();
    }

    void NccModelInterface::setAngleEnd(double value)
    {
        INccModel->setAngleEnd(value);
    }

    double NccModelInterface::minScore() const
    {

        return INccModel->minScore();
    }

    void NccModelInterface::setMinScore(double value)
    {
        INccModel->setMinScore(value);
    }

    int NccModelInterface::numMatches() const
    {
        
        return INccModel->numMatches();
    }

    void NccModelInterface::setNumMatches(int value)
    {
        INccModel->setNumMatches(value);
    }

    double NccModelInterface::maxOverlap() const
    {

        return INccModel->maxOverlap();
    }

    void NccModelInterface::setMaxOverlap(double value)
    {
        INccModel->setMaxOverlap(value);
    }

    void NccModelInterface::getOrigin(cv::Point2d& originOffset, double& angle) const
    {
        INccModel->getOrigin(originOffset, angle);
    }

    void NccModelInterface::setOrigin(const cv::Point2d& originOffset, double angle)
    {
        INccModel->setOrigin(originOffset, angle);
    }

#pragma endregion

#pragma region 模板参数

    bool NccModelInterface::isCreated() const
    {

        return INccModel->isCreated();
    }

    ScalingMode NccModelInterface::scalingMode() const
    {
        return INccModel->scalingMode();
    }

    IsotropicScaling NccModelInterface::isotropicScaling() const
    {
        return INccModel->isotropicScaling();
    }

    AnisotropicScaling NccModelInterface::anisotropicScaling() const
    {
        return INccModel->anisotropicScaling();
    }

    ReMat NccModelInterface::templImage() const
    {
        return INccModel->templImage();
    }

    Region NccModelInterface::templRegion() const
    {
        return INccModel->templRegion();
    }

#pragma endregion
}
