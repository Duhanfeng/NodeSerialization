#pragma once

#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

namespace rv
{
    class IClassifier
    {
    public:
        enum Preprocessing
        {
            None = 0,
            Normalization,          //归一化
            PrincipalComponents,    //主成分
            CanonicalVariates,      //典型变量
        };

        enum ClassMethod
        {
            KNN,
            GMM,
            SVM,
            MLP
        };

    public:

        //创建
        virtual void create(int featureNum, int classNum, Preprocessing preProcessing, int componentNum) = 0;

        //清除
        virtual void clear() = 0;

#pragma region 特征分类

        //训练
        virtual void addSample(const std::vector<double>& features, int classID) = 0;
        virtual double train() = 0;

        //分类
        virtual int classify(const std::vector<double>& features, double& confidence) = 0;

#pragma endregion

#pragma region 图像分类

#pragma endregion

        static cv::Ptr<IClassifier> create(ClassMethod method = ClassMethod::MLP, bool useHCore = true);

    };
}

