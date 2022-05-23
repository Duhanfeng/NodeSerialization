#pragma once

#include "../../iclassifier.h"
#include <opencv2/opencv.hpp>

namespace rv
{
    class ClassifierMLP : public IClassifier
    {
    public:
        //创建
        int hiddenNum = 4;
        virtual void create(int featureNum, int classNum, Preprocessing preProcessing, int componentNum);

        //训练
        int maxIterations = 300;        //最大迭代次数
        double weightTolerance = 1;     //两次优化算法迭代间MLP权值差的阈值
        double errorTolerance = 0.0001; //两次优化算法迭代间平均误差差的阈值
        virtual void addSample(const std::vector<double>& features, int classID);
        virtual double train();

        //分类
        virtual int classify(const std::vector<double>& features, double& confidence);

        //清除
        virtual void clear();

    private:
        cv::Ptr<cv::ml::ANN_MLP> m_model = nullptr;

        double m_error = 0;                 //训练误差率

        int m_featureNum{ 0 };
        int m_classNum{ 0 };

        std::vector<std::vector<double>> m_trainData;
        std::vector<int> m_trainLabels;

    };

}
