#pragma once

#include "VisionFlow/nodeBase.h"
#include <ReVisionLib/revision.hpp>
#include <opencv2/opencv.hpp>
#include "wechat_qrcode/include/opencv2/wechat_qrcode.hpp"

namespace qv
{
    enum class DataCodeType
    {
        QRCode = 0,
        DMCode,
        PDF417,
        AutoBarCode,
    };

    class DataCodeNode : public NodeBase
    {
    public:
        DataCodeNode(void* _parent = nullptr);
        virtual RunStatus runImage(rv::InputReMat image, rv::IReWindow* rewindow = nullptr) override;
        virtual void dispose() override;
        virtual std::string className() const override;
        virtual std::string displayName() const override;

    public:
        DataCodeType dataCodeType = DataCodeType::QRCode;
        int timeOut = 0;            //超时,单位:ms
        int searchCount = 0;        //搜寻数量

    public:
        NodeParamDescription outputPoses = { "Poses", u8"坐标", Variant::VariantType::Pose };
        NodeParamDescription outputCodes = { "Codes", u8"识别字符", Variant::VariantType::String };

    private:
        cv::wechat_qrcode::WeChatQRCode* m_weChatQRCode = nullptr;
        std::vector<std::string> cv2zBar(cv::InputArray src, std::vector<cv::Mat>& points);

        //输出结果(不需要序列化)
        std::vector<rv::Pose<double>> resultPoses;
        std::vector<std::string> resultCodes;


    private:
        friend class boost::serialization::access;

        template <typename Archive>
        void serialize(Archive& ar, const unsigned int version)
        {
            ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP(NodeBase);
            ar& BOOST_SERIALIZATION_NVP(dataCodeType);
            ar& BOOST_SERIALIZATION_NVP(timeOut);
            ar& BOOST_SERIALIZATION_NVP(searchCount);
        }
    };

}
