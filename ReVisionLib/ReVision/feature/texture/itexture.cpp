#include "itexture.h"
#if ENABLE_HCORE
#include "hcore/htexture.h"
#endif

namespace rv
{
    bool ITexture::getFeature(std::vector<double>& features, const FeatureGroupEnable& enable)
    {
        features.clear();

        FeatureGroup featureGroup;
        if (!getFeature(featureGroup, enable))
        {
            return false;
        }

        if (enable.isEnableIntensity)
        {
            features.push_back(featureGroup.mean);
            features.push_back(featureGroup.deviation);
        }
        if (enable.isEnablePlaneDeviation)
        {
            features.push_back(featureGroup.planeDeviation);
        }
        if (enable.isEnableEntropyGray)
        {
            features.push_back(featureGroup.entropy);
            features.push_back(featureGroup.anisotropy);
        }
        if (enable.isEnableMinMaxGray)
        {
            features.push_back(featureGroup.min);
            features.push_back(featureGroup.max);
            features.push_back(featureGroup.median);
        }
        if (enable.isEnableSurface)
        {
            features.push_back(featureGroup.alpha);
            features.push_back(featureGroup.beta);
            features.push_back(featureGroup.gamma);
        }
        if (enable.isEnableFuzzy)
        {
            features.push_back(featureGroup.fuzzyEntropy);
            features.push_back(featureGroup.fuzzyPerimeter);
        }
        if (enable.isEnableGrayPlane)
        {
            features.push_back(featureGroup.grayPlaneRow);
            features.push_back(featureGroup.grayPlaneCol);
            features.push_back(featureGroup.grayPlaneAlpha1);
            features.push_back(featureGroup.grayPlaneBeta);
            features.push_back(featureGroup.grayPlaneMean);
        }
        if (enable.isEnableEllipticAxis)
        {
            features.push_back(featureGroup.ra);
            features.push_back(featureGroup.rb);
            features.push_back(featureGroup.phi);
        }
        if (enable.isEnableCoocFeature)
        {
            features.push_back(featureGroup.cooc_0.energy);
            features.push_back(featureGroup.cooc_0.correlation);
            features.push_back(featureGroup.cooc_0.homogeneity);
            features.push_back(featureGroup.cooc_0.contrast);
            features.push_back(featureGroup.cooc_45.energy);
            features.push_back(featureGroup.cooc_45.correlation);
            features.push_back(featureGroup.cooc_45.homogeneity);
            features.push_back(featureGroup.cooc_45.contrast);
            features.push_back(featureGroup.cooc_90.energy);
            features.push_back(featureGroup.cooc_90.correlation);
            features.push_back(featureGroup.cooc_90.homogeneity);
            features.push_back(featureGroup.cooc_90.contrast);
            features.push_back(featureGroup.cooc_135.energy);
            features.push_back(featureGroup.cooc_135.correlation);
            features.push_back(featureGroup.cooc_135.homogeneity);
            features.push_back(featureGroup.cooc_135.contrast);
        }
        if (enable.isEnableSobelAmpHisto)
        {
            for (size_t i = 0; i < sizeof(featureGroup.sobelAmpHisto) / sizeof(double); i++)
            {
                features.push_back(featureGroup.sobelAmpHisto[i]);
            }
        }
        if (enable.isEnableGrayHisto)
        {
            for (size_t i = 0; i < sizeof(featureGroup.grayHisto) / sizeof(double); i++)
            {
                features.push_back(featureGroup.grayHisto[i]);
            }
        }

        return true;
    }

    cv::Ptr<ITexture> rv::ITexture::create(bool useHCore)
    {
#if ENABLE_HCORE
        if (useHCore)
        {
            return cv::Ptr<ITexture>(new HTexture());
        }
#endif

        return cv::Ptr<ITexture>();
    }

}
