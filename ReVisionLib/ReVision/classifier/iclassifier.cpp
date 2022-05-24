#include "iclassifier.h"
#include "ccore/mlp/classifier_mlp.h"
#if ENABLE_HCORE
#include "hcore/mlp/hclassifier_mlp.h"
#endif

namespace rv
{
    cv::Ptr<IClassifier> IClassifier::create(ClassMethod method, bool useHCore)
    {
#if ENABLE_HCORE
        if (useHCore)
        {
            switch (method)
            {
            case rv::IClassifier::KNN:
                break;
            case rv::IClassifier::GMM:
                break;
            case rv::IClassifier::SVM:
                break;
            case rv::IClassifier::MLP:
                return cv::Ptr<IClassifier>(new HClassifierMLP());
            default:
                break;
            }

            return cv::Ptr<IClassifier>();
        }
#endif

        switch (method)
        {
        case rv::IClassifier::KNN:
            break;
        case rv::IClassifier::GMM:
            break;
        case rv::IClassifier::SVM:
            break;
        case rv::IClassifier::MLP:
            return cv::Ptr<IClassifier>(new ClassifierMLP());
        default:
            break;
        }

        return cv::Ptr<IClassifier>();
    }
}