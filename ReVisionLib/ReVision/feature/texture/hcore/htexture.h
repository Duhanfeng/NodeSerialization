#pragma once

#include <vector>
#include "ReVision/remat.h"
#include "../itexture.h"

namespace rv
{
    class HTexture : public ITexture
    {
    public:
        virtual void setImage(InputReMat remat, InputRegion region) override;
        virtual bool getFeature(FeatureGroup& features, const FeatureGroupEnable& enable = FeatureGroupEnable()) override;
        virtual int getGroupLength(const FeatureGroupEnable& enable = FeatureGroupEnable()) override;

    protected:
        void getCoocFeature(CoocAngle angle, CoocMatrixFeature& feature);
        void getSobelAmpHistoAbs(double(&histo)[32]);
        void getGrayHistoAbs(double(&histo)[32]);

    protected:
        HMat m_himage;
        HMat m_hregion;

    };

}