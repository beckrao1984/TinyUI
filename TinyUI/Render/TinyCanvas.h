#pragma once
#include "../Common/TinyString.h"
#include "../Common/TinyEvent.h"
#include "TinyImage.h"
#include "TinyTransform.h"

namespace TinyUI
{
#ifndef M_PI
#define M_PI	3.14159265358979323846
#endif
#ifndef M_PI_2
#define M_PI_2	1.57079632679489661923
#endif
#ifndef M_PI_4
#define M_PI_4	0.785398163397448309616
#endif
#define  HSLMAX			255   
#define  RGBMAX			255  
#define HSLUNDEFINED	(HSLMAX*2/3)
	/// <summary>
	/// RGBtoHSL
	/// </summary>
	RGBQUAD RGBtoHSL(RGBQUAD lRGBColor);
	/// <summary>
	/// HUEtoRGB
	/// </summary>
	FLOAT HUEtoRGB(FLOAT n1, FLOAT n2, FLOAT hue);
	/// <summary>
	/// HSLtoRGB
	/// </summary>
	RGBQUAD HSLtoRGB(RGBQUAD lHSLColor);
	/// <summary>
	/// 画布类
	/// </summary>
	class TinyCanvas
	{
	public:
		TinyCanvas();
		TinyCanvas(HDC hDC);
		virtual ~TinyCanvas();
		operator HDC() const;
		/// <summary>
		/// 初始化DC
		/// </summary>
		BOOL InitializeDC(HDC hDC);
		/// <summary>
		/// DC句柄
		/// </summary>
		HDC Handle() const;
		/// <summary>
		/// 设置画板铅笔
		/// </summary>
		HPEN SetPen(HPEN hPen);
		/// <summary>
		/// 设置画板画刷
		/// </summary>
		HBRUSH SetBrush(HBRUSH hBrush);
		/// <summary>
		/// 设置字体
		/// </summary>
		HFONT SetFont(HFONT hFont);
		/// <summary>
		/// 平移变换
		/// </summary>
		BOOL TranslateTransform(FLOAT x, FLOAT y);
		/// <summary>
		/// 旋转变换
		/// </summary>
		BOOL RotateTransform(FLOAT angle);
		/// <summary>
		/// 缩放变换
		/// </summary>
		BOOL ScaleTransform(FLOAT sx, FLOAT sy);
		/// <summary>
		/// 剪切变换
		/// </summary>
		BOOL ShearTransform(FLOAT sh, FLOAT sv);
		/// <summary>
		/// 重置矩阵
		/// </summary>
		BOOL ResetTransform();
		/// <summary>
		/// 设置文字颜色
		/// </summary>
		BOOL SetTextColor(COLORREF color);
		/// <summary>
		/// 设置文字对齐方式
		/// </summary>
		BOOL SetTextAlign(UINT align);
		/// <summary>
		/// 绘制文本
		/// </summary>
		BOOL DrawString(const TinyString& str, LPRECT lprc, UINT format);
		/// <summary>
		/// 在指定位置绘制原始的Image
		/// </summary>
		BOOL DrawImage(TinyImage& image, INT x, INT y);
		/// <summary>
		/// 在指定位置绘制指定大小的Image
		/// </summary>
		BOOL DrawImage(TinyImage& image, INT x, INT y, INT cx, INT cy);
		/// <summary>
		/// 在指定位置绘制原始Image的部分缩放自适应
		/// </summary>
		BOOL DrawImage(TinyImage& image, const RECT& destRect, INT srcX, INT srcY, INT srcCX, INT srcCY);
		/// <summary>
		/// 在指定位置绘制原始Image的部分缩放自适应
		/// </summary>
		BOOL DrawImage(TinyImage& image, const RECT& destRect, const RECT& srcRect);
		/// <summary>
		/// 绘制9宫格中间矩形和4个角大小不变其余的拉伸
		/// </summary>
		BOOL DrawImage(TinyImage& image, const RECT& dstPaint, const RECT& srcPaint, const RECT& srcCenter);
		/// <summary>
		/// 绘制9宫格中间矩形和4个角大小不变其余的拉伸
		/// </summary>
		BOOL DrawImage(TinyImage& image, const RECT& dstPaint, const RECT& dstCenter, const RECT& srcPaint, const RECT& srcCenter);
		/// <summary>
		/// 绘制线(必须设置铅笔)
		/// </summary>
		BOOL DrawLine(INT sx, INT sy, INT dx, INT dy);
		/// <summary>
		/// 绘制线(必须设置铅笔)
		/// </summary>
		BOOL DrawLine(POINT pt1, POINT pt2);
		/// <summary>
		/// 绘制多条曲线(必须设置铅笔)
		/// </summary>
		BOOL DrawLines(POINT* pts, INT size);
		/// <summary>
		/// 绘制多条曲线(必须设置铅笔)
		/// </summary>
		BOOL DrawPolygon(POINT* pts, INT size);
		/// <summary>
		/// 绘制线(必须设置铅笔)
		/// </summary>
		BOOL DrawRectangle(const RECT& rect);
		/// <summary>
		/// 绘制矩形(必须设置铅笔)
		/// </summary>
		BOOL DrawRectangle(INT x, INT y, INT cx, INT cy);
		/// <summary>
		/// 绘制圆弧(必须设置铅笔)
		/// </summary>
		BOOL DrawArc(INT x, INT y, INT radius, FLOAT startAngle, FLOAT sweepAngle);
		/// <summary>
		/// 绘制弧度(必须设置铅笔)
		/// </summary>
		BOOL DrawArc(INT x, INT y, INT cx, INT cy, FLOAT startAngle, FLOAT sweepAngle);
		/// <summary>
		/// 绘制圆扇形(必须设置铅笔)
		/// </summary>
		BOOL DrawPie(INT x, INT y, INT radius, FLOAT startAngle, FLOAT sweepAngle);
		/// <summary>
		/// 绘制扇形(必须设置铅笔)
		/// </summary>
		BOOL DrawPie(INT x, INT y, INT cx, INT cy, FLOAT startAngle, FLOAT sweepAngle);
		/// <summary>
		/// 绘制贝塞尔曲线(必须设置铅笔)
		/// </summary>
		BOOL DrawBeziers(POINT* pts, INT size);
		/// <summary>
		/// 绘制椭圆(必须设置铅笔)
		/// </summary>
		BOOL DrawEllipse(const RECT& rect);
		/// <summary>
		/// 绘制椭圆(必须设置铅笔)
		/// </summary>
		BOOL DrawEllipse(INT x, INT y, INT cx, INT cy);
		/// <summary>
		/// 填充扇形(必须设置画刷)
		/// </summary>
		BOOL FillPie(INT x, INT y, INT cx, INT cy, FLOAT startAngle, FLOAT sweepAngle);
		/// <summary>
		/// 填充多边形(必须设置画刷)
		/// </summary>
		BOOL FillPolygon(POINT* pts, INT size);
		/// <summary>
		/// 填充矩形(必须设置画刷)
		/// </summary>
		BOOL FillRectangle(const RECT& rect);
		/// <summary>
		/// 填充矩形(必须设置画刷)
		/// </summary>
		BOOL FillRectangle(INT x, INT y, INT cx, INT cy);
		/// <summary>
		/// 填充椭圆(必须设置画刷)
		/// </summary>
		BOOL FillEllipse(INT x, INT y, INT cx, INT cy);
		/// <summary>
		/// 填充椭圆(必须设置画刷)
		/// </summary>
		BOOL FillEllipse(const RECT& rect);
		/// <summary>
		/// 填充区域(必须设置画刷)
		/// </summary>
		BOOL FillRegion(HRGN hRgn);
		/// <summary>
		/// 设置裁剪区域
		/// </summary>
		BOOL SetClip(const RECT& rect);
		/// <summary>
		/// 设置裁剪区域
		/// </summary>
		BOOL SetClip(HRGN hRgn);
		/// <summary>
		/// 设置裁剪区域
		/// </summary>
		BOOL SetClip(INT x, INT y, INT cx, INT cy);
		/// <summary>
		/// 设置裁剪区域
		/// </summary>
		BOOL SetClip(const RECT& rect, INT iCombineMode);
		/// <summary>
		/// 设置裁剪区域
		/// </summary>
		BOOL SetClip(HRGN hRgn, INT iCombineMode);
		/// <summary>
		/// 设置裁剪区域
		/// </summary>
		BOOL SetClip(INT x, INT y, INT cx, INT cy, INT iCombineMode);
		/// <summary>
		/// 从裁剪区域中去掉添加矩形
		/// </summary>
		BOOL IntersectClip(const RECT& rect);
		/// <summary>
		/// 从裁剪区域中去掉添加矩形
		/// </summary>
		BOOL IntersectClip(INT x, INT y, INT cx, INT cy);
		/// <summary>
		/// 从裁剪区域中去掉添加区域
		/// </summary>
		BOOL IntersectClip(HRGN hRgn);
		/// <summary>
		/// 从裁剪区域中去掉去掉矩形
		/// </summary>
		BOOL ExcludeClip(const RECT& rect);
		/// <summary>
		/// 从裁剪区域中去掉去掉矩形
		/// </summary>
		BOOL ExcludeClip(INT x, INT y, INT cx, INT cy);
		/// <summary>
		/// 从裁剪区域中去掉去掉区域
		/// </summary>
		BOOL ExcludeClip(HRGN hRgn);
		/// <summary>
		/// 充值裁剪区域
		/// </summary>
		BOOL ResetClip();
		/// <summary>
		/// 返回裁剪区域是否为空
		/// </summary>
		BOOL IsClipEmpty() const;
		/// <summary>
		/// 返回可见的裁剪区域是否为空
		/// </summary>
		BOOL IsVisibleClipEmpty() const;
		/// <summary>
		/// 返回当前画布矩形是否可见
		/// </summary>
		BOOL IsVisible(const RECT& rect);
		/// <summary>
		/// 返回当前画布矩形是否可见
		/// </summary>
		BOOL IsVisible(POINT pt);
		/// <summary>
		/// 获得可见的最小矩形大小
		/// </summary>
		INT GetClipRectangle(LPRECT lprc);
	protected:
		HDC			m_hDC;
		HFONT		m_hFONT;
		HPEN		m_hPEN;
		HBRUSH		m_hBRUSH;
		HRGN		m_hRGN;
		INT			m_iSave;
		TinyMatrix	m_matrix;
	};
};



