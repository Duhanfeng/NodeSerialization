#pragma once

#include <iostream>
#include "geometry/geometry.hpp"
#include "remat.h"
#include "region.h"

namespace rv
{
    enum class DrawStyle
    {
        FillUp,
        Margin,
    };

    enum class GraphicsStyle
    {
        Simple,     //简易模式,只包括边缘或填充;
        Normal,     //普通模式,带有提示点以及半透明属性
    };

    class Color
    {
    public:
        Color() : Color(0, 0, 0) {};

        Color(int _r, int _g, int _b) :
            r(_r), g(_g), b(_b) {}

        Color(const Color& color) 
        {
            r = color.r;
            g = color.g;
            b = color.b;
        }

        int r;
        int g;
        int b;

    private:

    };

    //矩形复合图形
    class RectMix
    {
    public:
        RotatedRect<double> rotateRect;
        double caliperGap = 50;         //卡尺间隔(单位:像素)
        bool findLine = true;           //ture:查找直线,false:查找矩形

        //查找矩形相关
        double edgeGap[4] = { 50, 50, 50, 50 };         //边缘预留空白区域,顺序为:左,上,右,下
        double caliperLength[4] = { 50, 50, 50, 50 };   //卡尺长度,顺序为:左,上,右,下(正值时为从内到外,而负值时从外到内)
        int caliperWidth = 5;           //卡尺宽度(应当小于卡尺间隔)

    };

    //圆形复合图像
    class CircleMix
    {
    public:
        Annulus<double> annulus;       //圆环

        double caliperGap = 20;         //卡尺间隔(单位:度,角度制)
        int caliperWidth = 5;           //卡尺宽度(单位:像素)
    };

    class IReWindow
    {
        //样式
    public:

        //图形样式
        virtual void setGraphicsStyle(const GraphicsStyle& style) const = 0;
        virtual GraphicsStyle graphicsStyle() const = 0;
        virtual void setColor(const Color& color) const = 0;
        virtual Color color() const = 0;
        virtual void setLineWidth(int width) const = 0;
        virtual int lineWidth() const = 0;

        //填充
        virtual void setDrawStyle(const DrawStyle& style) const = 0;        //是否填充
        virtual DrawStyle drawStyle() const = 0;
        virtual void setFillUpColor(const Color& color) const = 0;          //填充颜色(Normal+FillUp 下可用)
        virtual Color fillUpColor() const = 0;
        virtual void setFillUpTransparency(int value) const = 0;            //填充的透明度(Normal+FillUp 下可用)
        virtual int fillUpTransparency() const = 0;

        //辅助点及辅助线
        virtual void showCenterPoint(bool isEnable) const = 0;              //是否显示中心点(Normal下可用)
        virtual bool isShowCenterPoint() const = 0;
        virtual void showPoint(bool isEnable) const = 0;                    //是否显示辅助点(Normal下可用)
        virtual bool isShowPoint() const = 0;
        virtual void setPointColor(const Color& color) const = 0;           //点中心颜色(isShowPoint = true下可用)
        virtual Color pointColor() const = 0;
        virtual void setPointWidth(int value) const = 0;                    //点宽度(isShowPoint = true下可用)
        virtual int pointWidth() const = 0;
        virtual void setRotatedPointColor(const Color& color) const = 0;    //旋转点颜色(isShowPoint = true下可用)
        virtual Color rotatedPointColor() const = 0;

        virtual void showShowSubLine(bool isEnable) const = 0;              //是否显示辅助线(Normal下可用)
        virtual bool isShowSubLine() const = 0;
        virtual void setSubLineColor(const Color& color) const = 0;         //辅助线颜色(isShowSubLine = true下可用)
        virtual Color subLineColor() const = 0;
        virtual void setSubLineWidth(int width) const = 0;                  //辅助线宽度(isShowSubLine = true下可用)
        virtual int subLineWidth() const = 0;

        //其他样式属性
        virtual void showText(bool isEnable) const = 0;                     //是否显示辅助文字
        virtual bool isShowText() const = 0;
        virtual void fixed(bool isEnable) const = 0;                        //true: 固定模式,尺寸改变时形状尺寸保持; false: 动态跟随,主界面改变时形状尺寸比例不变;
        virtual bool isFixed() const = 0;
        virtual void antialiasing(bool isEnable) const = 0;                 //抗锯齿
        virtual bool isAntialiasing() const = 0;

        //显示图形
    public:
        virtual void dispPoint(const Point<double>& point) const = 0;
        virtual void dispLine(const Line<double>& line) const = 0;
        virtual void dispCircle(const Circle<double>& circle) const = 0;
        virtual void dispRect(const Rectangle<double>& rect) const = 0;
        virtual void dispRotatedRect(const RotatedRect<double>& rect) const = 0;
        virtual void dispText(const Point<int>& loc, const std::string& string, int size) const = 0;
        virtual void dispImage(const ReMat& image) const = 0;
        virtual void dispRegion(const Region& region) const = 0;
        virtual void dispRectMix(const RectMix& def = RectMix()) const = 0;
        virtual void dispCircleMix(const CircleMix& def = CircleMix()) const = 0;

        //画图形
    public:
        virtual void drawLine(const Line<double>& def = Line<double>()) const = 0;
        virtual void drawCircle(const Circle<double>& def = Circle<double>()) const = 0;
        virtual void drawRect(const Rectangle<double>& def = Rectangle<double>()) const = 0;
        virtual void drawRotatedRect(const RotatedRect<double>& def = RotatedRect<double>()) const = 0;
        virtual void drawRectMix(const RectMix& mix) const = 0;
        virtual void drawCircleMix(const CircleMix& mix) const = 0;

        virtual Line<double> getLine() const = 0;
        virtual Circle<double> getCircle() const = 0;
        virtual Rectangle<double> getRect() const = 0;
        virtual RotatedRect<double> getRotatedRect() const = 0;
        virtual RectMix getRectMix() const = 0;
        virtual CircleMix getCircleMix() const = 0;

        //整体控制
    public:
        virtual void resetStyle() const = 0;    //复位样式
        virtual void flushBuffer() const = 0;   //将缓存中的图形显示
        virtual void clearShape() const = 0;    //将图像之外的形状删除
        virtual void clear() const = 0;         //将所有对象删除
        virtual void append(IReWindow* window) const = 0;   //形状追加

        virtual void setName(const std::string& name) { m_name = name; }
        virtual std::string name() { return m_name; }

    protected:
        std::string m_name;
    };

    class IReWindows
    {
    public:
        virtual void reset() = 0;
        virtual int count() = 0;
        virtual IReWindow* getNewWindow() = 0;
        virtual IReWindow* getWindow(int index) = 0;
        virtual void setImage(rv::InputReMat image) = 0;
        virtual void flushBuffer() = 0;

    };

}
