#include "itextureClassifier.h"

namespace rv
{
    ITextureClassifier::ITextureClassifier(int classNum, IClassifier::Preprocessing preProcessing, int componentNum)
    {
        m_classNum = classNum;
        m_classifier = IClassifier::create();
        m_texture = ITexture::create();

        int featureNum = m_texture->getGroupLength();
        m_classifier->create(featureNum, classNum, preProcessing, componentNum);

        m_isInited = true;
    }

    void ITextureClassifier::addSample(InputReMat image, InputRegion region, int classID)
    {
        if (!m_isInited || (m_classifier == nullptr))
        {
            return;
        }

        if (classID >= m_classNum)
        {
            return;
        }

        //提取纹理特征
        std::vector<double> feature;
        m_texture->setImage(image, region);
        m_texture->getFeature(feature);

        //作为训练样本
        m_classifier->addSample(feature, classID);
    }

    double ITextureClassifier::train()
    {
        if (m_classifier == nullptr)
        {
            return 0.0;
        }

        return m_classifier->train();
    }

    int ITextureClassifier::classify(InputReMat image, InputRegion region, double& confidence)
    {
        if (!m_isInited || (m_classifier == nullptr))
        {
            return -1;
        }

        //提取纹理特征
        std::vector<double> feature;
        m_texture->setImage(image, region);
        m_texture->getFeature(feature);

        //分类
        return m_classifier->classify(feature, confidence);
    }

    cv::Ptr<ITextureClassifier> ITextureClassifier::create(int classNum, IClassifier::Preprocessing preProcessing, int componentNum, bool useHCore)
    {

        return cv::Ptr<ITextureClassifier>(new ITextureClassifier(classNum, preProcessing, componentNum));
    }

}
