#include "fit.h"

template<typename _Tp>
void Fit::fitLineBase(const std::vector<cv::Point_<_Tp>>& points, double& k, double& b)
{
    int N = (int)points.size();
    double A = 0.0;
    double B = 0.0;
    double C = 0.0;
    double D = 0.0;
    double E = 0.0;
    double F = 0.0;

    if (points.size() < 2)
    {
        return;
    }

    for (int i = 0; i < N; i++)
    {
        A += points[i].x * points[i].x;
        B += points[i].x;
        C += points[i].x * points[i].y;
        D += points[i].y;
    }

    // 计算斜率a和截距b  
    double temp = (N * A - B * B);
    if (temp != 0)  // 判断分母不为0  
    {
        k = (N * C - B * D) / temp;
        b = (A * D - B * C) / temp;
    }
    else
    {
        k = 1;
        b = 0;
    }
}

template<typename _Tp>
void Fit::fitCircleBase(const std::vector<cv::Point_<_Tp>>& points, cv::Point2d& center, double& radius)
{
    center.x = 0.0f;
    center.y = 0.0f;
    radius = 0.0f;

    if (points.size() < 3)
    {
        return;
    }

    double sum_x = 0.0f, sum_y = 0.0f;
    double sum_x2 = 0.0f, sum_y2 = 0.0f;
    double sum_x3 = 0.0f, sum_y3 = 0.0f;
    double sum_xy = 0.0f, sum_x1y2 = 0.0f, sum_x2y1 = 0.0f;

    int N = (int)points.size();
    for (int i = 0; i < N; i++)
    {
        double x = points[i].x;
        double y = points[i].y;
        double x2 = x * x;
        double y2 = y * y;
        sum_x += x;
        sum_y += y;
        sum_x2 += x2;
        sum_y2 += y2;
        sum_x3 += x2 * x;
        sum_y3 += y2 * y;
        sum_xy += x * y;
        sum_x1y2 += x * y2;
        sum_x2y1 += x2 * y;
    }

    double C, D, E, G, H;
    double a, b, c;

    C = N * sum_x2 - sum_x * sum_x;
    D = N * sum_xy - sum_x * sum_y;
    E = N * sum_x3 + N * sum_x1y2 - (sum_x2 + sum_y2) * sum_x;
    G = N * sum_y2 - sum_y * sum_y;
    H = N * sum_x2y1 + N * sum_y3 - (sum_x2 + sum_y2) * sum_y;
    a = (H * D - E * G) / (C * G - D * D);
    b = (H * C - E * D) / (D * D - G * C);
    c = -(a * sum_x + b * sum_y + sum_x2 + sum_y2) / N;

    center.x = a / (-2.0);
    center.y = b / (-2.0);
    radius = sqrt(a * a + b * b - 4 * c) / 2;

}

void Fit::fitLine(std::vector<cv::Point2f>& points, double& k, double& b)
{
    fitLineBase(points, k, b);
}

void Fit::fitLine(std::vector<cv::Point2d>& points, double& k, double& b)
{
    fitLineBase(points, k, b);
}

void Fit::fitCircle(std::vector<cv::Point2f>& points, cv::Point2d& center, double& radius)
{
    fitCircleBase(points, center, radius);
}

void Fit::fitCircle(std::vector<cv::Point2d>& points, cv::Point2d& center, double& radius)
{
    fitCircleBase(points, center, radius);
}
