#pragma once

#include <opencv2/opencv.hpp>

namespace rv
{
    class HomMat2D
    {
    public:

        static cv::Mat createIdentity()
        {

            return cv::Mat::eye(3, 3, CV_64FC1);
        }

        static cv::Mat createTranslation(double dx, double dy)
        {
            cv::Mat mat = createIdentity();
            mat.at<double>(0, 2) = dx;
            mat.at<double>(1, 2) = dy;

            return mat;
        }

        static cv::Mat createScale(double sx, double sy)
        {
            cv::Mat mat = createIdentity();
            mat.at<double>(0, 0) = sx;
            mat.at<double>(1, 1) = sy;

            return mat;
        }

        static cv::Mat createScale(double px, double py, double sx, double sy)
        {
            cv::Mat mat1 = createTranslation(-px, -py);
            cv::Mat mat2 = createScale(sx, sy);
            cv::Mat mat3 = createTranslation(px, py);

            return mat3 * mat2 * mat1;
        }

        static cv::Mat createRotation(double angle)
        {
            cv::Mat mat = createIdentity();
            double sa = std::sin(angle);
            double ca = std::cos(angle);
            mat.at<double>(0, 0) = ca;
            mat.at<double>(0, 1) = -sa;
            mat.at<double>(1, 0) = sa;
            mat.at<double>(1, 1) = ca;

            return mat;
        }

        static cv::Mat createRotation(double px, double py, double angle)
        {
            cv::Mat mat1 = createTranslation(-px, -py);
            cv::Mat mat2 = createRotation(angle);
            cv::Mat mat3 = createTranslation(px, py);

            return mat3 * mat2 * mat1;
        }

        static cv::Mat createReflectionX()
        {

            return createScale(1, -1);
        }

        static cv::Mat createReflectionY()
        {

            return createScale(-1, 1);
        }

        static cv::Mat vectorAngleToRigid(double x1, double y1, double angle1, double x2, double y2, double angle2)
        {
            //1.平移回原点
            cv::Mat mat1 = createTranslation(-x1, -y1);

            //2.旋转
            cv::Mat mat2 = createRotation(angle2 - angle1);

            //3.平移回目标点
            cv::Mat mat3 = createTranslation(x2, y2);

            return mat3 * mat2 * mat1;
        }

    public:

        static cv::Mat create3x1PointMatrix(double x, double y)
        {
            cv::Mat mat = cv::Mat(3, 1, CV_64FC1);
            mat.at<double>(0, 0) = x;
            mat.at<double>(1, 0) = y;
            mat.at<double>(2, 0) = 1;

            return mat;
        }

        static cv::Mat create3x1PointMatrix(const cv::Point2d& point)
        {

            return create3x1PointMatrix(point.x, point.y);
        }

        static void getPointFromPointMatrix(cv::InputArray homMat, double& x, double& y)
        {
            if (homMat.empty())
            {
                throw std::invalid_argument("矩阵为空");
            }

            if ((homMat.rows() != 3) || (homMat.cols() != 1))
            {
                throw std::invalid_argument("矩阵并非1x3点位矩阵");
            }

            x = homMat.getMat().at<double>(0, 0);
            y = homMat.getMat().at<double>(1, 0);
        }

    public:

        static void transformPoint2D(cv::InputArray homMat, double px, double py, double& qx, double& qy)
        {
            if (homMat.empty())
            {
                throw std::invalid_argument("矩阵为空");
            }

            if ((homMat.rows() != 3) || (homMat.cols() != 3))
            {
                throw std::invalid_argument("矩阵并非3x3矩阵");
            }

            //创建点位矩阵
            cv::Mat p = create3x1PointMatrix(px, py);

            //计算目标点位矩阵
            cv::Mat q = homMat.getMat() * p;

            qx = q.at<double>(0, 0);
            qy = q.at<double>(1, 0);

        }

        template <typename _Tp>
        static void transformPoint2D(cv::InputArray homMat, const cv::Point_<_Tp>& src, cv::Point_<_Tp>& dst)
        {
            if (homMat.empty())
            {
                throw std::invalid_argument("矩阵为空");
            }

            if ((homMat.rows() != 3) || (homMat.cols() != 3))
            {
                throw std::invalid_argument("矩阵并非3x3矩阵");
            }

            double qx = 0;
            double qy = 0;
            transformPoint2D(homMat, (double)src.x, (double)src.y, qx, qy);

            dst.x = _Tp(qx);
            dst.y = _Tp(qy);

        }

    private:

    };

}
