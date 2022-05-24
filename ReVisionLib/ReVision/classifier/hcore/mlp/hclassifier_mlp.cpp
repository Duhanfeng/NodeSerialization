#include "hclassifier_mlp.h"
#include <HalconCpp.h>

namespace rv
{
    HClassifierMLP::HClassifierMLP()
    {
        m_classMlp = std::shared_ptr<HalconCpp::HClassMlp>(new HalconCpp::HClassMlp());
    }

    HClassifierMLP::~HClassifierMLP()
    {
        m_classMlp = nullptr;
    }

    void HClassifierMLP::create(int featureNum, int classNum, Preprocessing preProcessing, int componentNum)
    {
        if (m_classMlp == nullptr)
        {
            return;
        }
        HalconCpp::HTuple hpreProcess;
        switch (preProcessing)
        {
        case IClassifier::PrincipalComponents:
            hpreProcess = "principal_components";
            break;
        case IClassifier::CanonicalVariates:
            hpreProcess = "canonical_variates";
            break;
        default:
            hpreProcess = "normalization";
            break;
        }

        //hiddenNum = (hiddenNum > std::max<int>(featureNum, classNum)) ? std::min<int>(featureNum, classNum) : hiddenNum;
        m_classMlp->CreateClassMlp(featureNum, hiddenNum, classNum, "softmax", hpreProcess, componentNum, 42);

    }

    void HClassifierMLP::addSample(const std::vector<double>& features, int classID)
    {
        if ((m_classMlp == nullptr) || (m_classMlp->GetHandle() == 0))
        {
            return;
        }

        HalconCpp::HTuple hFeatures;
        for (size_t i = 0; i < features.size(); i++)
        {
            hFeatures.Append(features[i]);
        }
        try
        {
            m_classMlp->AddSampleClassMlp(hFeatures, classID);
        }
        catch (const HalconCpp::HOperatorException& ex)
        {
            std::cout << ex.ErrorMessage() << std::endl;
        }
        catch (const std::exception& ex)
        {
            std::cout << ex.what() << std::endl;
        }
    }

    double HClassifierMLP::train()
    {
        if ((m_classMlp == nullptr) || (m_classMlp->GetHandle() == 0))
        {
            return -1;
        }

        HalconCpp::HTuple hError(0.0);
        try
        {
            //HalconCpp::HTuple hErrorLog;
            m_classMlp->TrainClassMlp(maxIterations, weightTolerance, errorTolerance, &hError);
        }
        catch (const HalconCpp::HOperatorException&)
        {
            //备注: 如果未传入数据就训练,则会报错
        }

        return hError.D();
    }

    int HClassifierMLP::classify(const std::vector<double>& features, double& confidence)
    {
        if ((m_classMlp == nullptr) || (m_classMlp->GetHandle() == 0))
        {
            return -1;
        }

        HalconCpp::HTuple hFeatures;
        for (size_t i = 0; i < features.size(); i++)
        {
            hFeatures.Append(features[i]);
        }

        return (int)m_classMlp->ClassifyClassMlp(hFeatures, 1, &confidence);
    }

    void HClassifierMLP::clear()
    {
        if ((m_classMlp == nullptr) || (m_classMlp->GetHandle() == 0))
        {
            return;
        }

        m_classMlp->Clear();
    }

}
