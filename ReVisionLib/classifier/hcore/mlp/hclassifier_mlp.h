#pragma once

#include "classifier/iclassifier.h"
#include <remat.h>

namespace rv
{
    class HClassifierMLP : public IClassifier
    {
    public:
        HClassifierMLP();
        ~HClassifierMLP();

        //创建
        int hiddenNum = 10;
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
        std::shared_ptr<HalconCpp::HClassMlp> m_classMlp;

    };

}
