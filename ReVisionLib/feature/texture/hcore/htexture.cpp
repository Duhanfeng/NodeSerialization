#include "htexture.h"

namespace rv
{
    void HTexture::setImage(InputReMat remat, InputRegion region)
    {
        m_himage = remat.getHMat();
        m_hregion = region.toHMat();

        if (!m_hregion.IsInitialized())
        {
            m_hregion = m_himage;
        }

    }

    bool HTexture::getFeature(FeatureGroup& features, const FeatureGroupEnable& enable)
    {
        if (!m_himage.IsInitialized())
        {
            return false;
        }

        if (enable.isEnableIntensity)
        {
            HalconCpp::HTuple mean;
            HalconCpp::HTuple deviation;
            HalconCpp::Intensity(m_hregion, m_himage, &mean, &deviation);
            features.mean = mean.D();
            features.deviation = deviation.D();
        }
        if (enable.isEnablePlaneDeviation)
        {
            HalconCpp::HTuple planeDeviation;
            HalconCpp::PlaneDeviation(m_hregion, m_himage, &planeDeviation);
            features.planeDeviation = planeDeviation.D();
        }
        if (enable.isEnableEntropyGray)
        {
            HalconCpp::HTuple entropy;
            HalconCpp::HTuple anisotropy;
            HalconCpp::EntropyGray(m_hregion, m_himage, &entropy, &anisotropy);
            features.entropy = entropy.D();
            features.anisotropy = anisotropy.D();
        }
        if (enable.isEnableMinMaxGray)
        {
            HalconCpp::HTuple min;
            HalconCpp::HTuple max;
            HalconCpp::HTuple median;
            HalconCpp::MinMaxGray(m_hregion, m_himage, 50, &min, &max, &median);     //min=max=median
            features.median = median.D();
            HalconCpp::MinMaxGray(m_hregion, m_himage, 0, &min, &max, &median); 
            features.min = min.D();
            features.max = max.D();
        }
        if (enable.isEnableSurface)
        {
            HalconCpp::HTuple alpha;
            HalconCpp::HTuple beta;
            HalconCpp::HTuple gamma;
            HalconCpp::FitSurfaceFirstOrder(m_hregion, m_himage, "regression", 5, 2, &alpha, &beta, &gamma);
            features.alpha = alpha.D();
            features.beta = beta.D();
            features.gamma = gamma.D();
        }
        if (enable.isEnableFuzzy)
        {
            HalconCpp::HTuple fuzzyEntropy;
            HalconCpp::FuzzyEntropy(m_hregion, m_himage, 0, 255, &fuzzyEntropy);
            HalconCpp::HTuple fuzzyPerimeter;
            HalconCpp::FuzzyPerimeter(m_hregion, m_himage, 0, 255, &fuzzyPerimeter);
            features.fuzzyEntropy = fuzzyEntropy.D();
            features.fuzzyPerimeter = fuzzyPerimeter.D();
        }
        if (enable.isEnableGrayPlane)
        {
            HalconCpp::HTuple grayPlaneRow;
            HalconCpp::HTuple grayPlaneCol;
            HalconCpp::HTuple grayPlaneAlpha1;
            HalconCpp::HTuple grayPlaneBeta;
            HalconCpp::HTuple grayPlaneMean;
            HalconCpp::MomentsGrayPlane(m_hregion, m_himage, &grayPlaneRow, &grayPlaneCol, &grayPlaneAlpha1, &grayPlaneBeta, &grayPlaneMean);
            features.grayPlaneRow = grayPlaneRow.D();
            features.grayPlaneCol = grayPlaneCol.D();
            features.grayPlaneAlpha1 = grayPlaneAlpha1.D();
            features.grayPlaneBeta = grayPlaneBeta.D();
            features.grayPlaneMean = grayPlaneMean.D();
        }
        if (enable.isEnableEllipticAxis)
        {
            HalconCpp::HTuple ra;
            HalconCpp::HTuple rb;
            HalconCpp::HTuple phi;
            HalconCpp::EllipticAxisGray(m_hregion, m_himage, &ra, &rb, &phi);
            features.ra = ra.D();
            features.rb = rb.D();
            features.phi = phi.D();
        }
        if (enable.isEnableCoocFeature)
        {
            CoocMatrixFeature cooc_0, cooc_45, cooc_90, cooc_135;
            getCoocFeature(CoocAngle_0, cooc_0);
            getCoocFeature(CoocAngle_45, cooc_45);
            getCoocFeature(CoocAngle_90, cooc_90);
            getCoocFeature(CoocAngle_135, cooc_135);
            features.cooc_0 = cooc_0;
            features.cooc_45 = cooc_45;
            features.cooc_90 = cooc_90;
            features.cooc_135 = cooc_135;
        }
        if (enable.isEnableSobelAmpHisto)
        {
            getSobelAmpHistoAbs(features.sobelAmpHisto);
        }
        if (enable.isEnableGrayHisto)
        {
            getGrayHistoAbs(features.grayHisto);
        }

        return true;
    }

    int HTexture::getGroupLength(const FeatureGroupEnable& enable)
    {
        int length = 0;

        if (enable.isEnableIntensity)
        {
            length += 2;
        }
        if (enable.isEnablePlaneDeviation)
        {
            length += 1;
        }
        if (enable.isEnableEntropyGray)
        {
            length += 2;
        }
        if (enable.isEnableMinMaxGray)
        {
            length += 3;
        }
        if (enable.isEnableSurface)
        {
            length += 3;
        }
        if (enable.isEnableFuzzy)
        {
            length += 2;
        }
        if (enable.isEnableGrayPlane)
        {
            length += 5;
        }
        if (enable.isEnableEllipticAxis)
        {
            length += 3;
        }
        if (enable.isEnableCoocFeature)
        {
            length += 16;
        }
        if (enable.isEnableSobelAmpHisto)
        {
            length += 32;
        }
        if (enable.isEnableGrayHisto)
        {
            length += 32;
        }

        return length;
    }

    void rv::HTexture::getCoocFeature(CoocAngle angle, CoocMatrixFeature& feature)
    {
        if (m_himage.IsInitialized())
        {
            HalconCpp::HTuple energy, correlation, homogeneity, contrast;

            switch (angle)
            {
            case rv::ITexture::CoocAngle_0:
                HalconCpp::CoocFeatureImage(m_hregion, m_himage, 6, 0, &energy, &correlation, &homogeneity, &contrast);
                break;
            case rv::ITexture::CoocAngle_45:
                HalconCpp::CoocFeatureImage(m_hregion, m_himage, 6, 45, &energy, &correlation, &homogeneity, &contrast);
                break;
            case rv::ITexture::CoocAngle_90:
                HalconCpp::CoocFeatureImage(m_hregion, m_himage, 6, 90, &energy, &correlation, &homogeneity, &contrast);
                break;
            case rv::ITexture::CoocAngle_135:
                HalconCpp::CoocFeatureImage(m_hregion, m_himage, 6, 135, &energy, &correlation, &homogeneity, &contrast);
                break;
            default:
                break;
            }

            feature.energy = energy;
            feature.correlation = correlation;
            feature.homogeneity = homogeneity;
            feature.contrast = contrast;

        }
    }

    void HTexture::getSobelAmpHistoAbs(double(&histo)[32])
    {
        if (m_himage.IsInitialized())
        {
            //计算边缘振幅的绝对直方图
            HalconCpp::HObject edgeAmplitude;
            HalconCpp::SobelAmp(m_himage, &edgeAmplitude, "sum_abs", 3);
            HalconCpp::HTuple hhisto;
            HalconCpp::GrayHistoAbs(m_hregion, edgeAmplitude, 8, &hhisto);

            if (hhisto.Length() == (Hlong)32)
            {
                for (Hlong i = 0; i < hhisto.Length(); i++)
                {
                    histo[i] = hhisto[i].D();
                }
            }
        }
    }

    void HTexture::getGrayHistoAbs(double(&histo)[32])
    {
        if (m_himage.IsInitialized())
        {
            HalconCpp::HTuple hhisto;
            HalconCpp::GrayHistoAbs(m_hregion, m_himage, 8, &hhisto);

            if (hhisto.Length() == (Hlong)32)
            {
                for (Hlong i = 0; i < hhisto.Length(); i++)
                {
                    histo[i] = hhisto[i].D();
                }
            }
        }
    }

}
