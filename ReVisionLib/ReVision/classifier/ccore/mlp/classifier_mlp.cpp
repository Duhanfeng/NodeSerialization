#include "classifier_mlp.h"

namespace rv
{
    void ClassifierMLP::create(int featureNum, int classNum, Preprocessing preProcessing, int componentNum)
    {
        m_featureNum = featureNum;
        m_classNum = classNum;

        m_trainData.clear();
        m_trainLabels.clear();

        cv::Mat layerSizes = cv::Mat::zeros(1, hiddenNum + 2, CV_32SC1);
        layerSizes.at<int>(0, 0) = featureNum;
        for (int i = 1; i < layerSizes.cols; i++)
        {
            layerSizes.at<int>(0, i) = classNum;
        }

        try
        {
            m_model = cv::ml::ANN_MLP::create();
            m_model->setLayerSizes(layerSizes);
            m_model->setTrainMethod(cv::ml::ANN_MLP::BACKPROP, 0.1, 0.1);
            m_model->setActivationFunction(cv::ml::ANN_MLP::SIGMOID_SYM);
            m_model->setTermCriteria(cv::TermCriteria(cv::TermCriteria::MAX_ITER, maxIterations, errorTolerance));

        }
        catch (const std::exception& ex)
        {
            std::cout << ex.what() << std::endl;
        }

    }

    void ClassifierMLP::addSample(const std::vector<double>& features, int classID)
    {
        if ((m_model != nullptr) && m_featureNum == features.size())
        {
            m_trainData.push_back(features);
            m_trainLabels.push_back(classID);
        }

    }

    double ClassifierMLP::train()
    {
        if (m_model == nullptr)
        {
            return 0;
        }

        int dataCount = (int)m_trainData.size();

        cv::Mat trainDataMat = cv::Mat::zeros(dataCount, m_featureNum, CV_32FC1);
        cv::Mat labelsMat = cv::Mat::zeros(dataCount, m_classNum, CV_32FC1);

        for (int i = 0; i < dataCount; i++)
        {
            for (int j = 0; j < m_featureNum; j++)
            {
                trainDataMat.at<float>(i, j) = (float)m_trainData[i][j];
            }
            labelsMat.at<float>(i, m_trainLabels[i]) = 1.0f;
        }

        bool trainResult = false;
        try
        {
            trainResult = m_model->train(trainDataMat, cv::ml::ROW_SAMPLE, labelsMat);
        }
        catch (const std::exception& ex)
        {
            std::cout << ex.what() << std::endl;
        }

        return trainResult ? 1 : 0;
    }

    int ClassifierMLP::classify(const std::vector<double>& features, double& confidence)
    {
        if (m_model == nullptr)
        {
            return -1;
        }

        cv::Mat result;
        m_model->predict(features, result);

        if (!result.empty())
        {
            double maxVal = 0;
            cv::Point maxLoc;
            cv::minMaxLoc(result, nullptr, &maxVal, nullptr, &maxLoc);
            confidence = maxVal;
            return maxLoc.x;
        }

        return -1;
    }

    void ClassifierMLP::clear()
    {
        m_model->clear();
        m_model = nullptr;

    }

}
