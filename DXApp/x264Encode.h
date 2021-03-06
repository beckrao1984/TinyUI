#pragma once
#include "I420Converter.h"
#include "RTMPPublisher.h"
extern "C"
{
#include "x264_config.h"
#include "x264.h"
}

#pragma comment(lib,"libx264.lib")

class RTMPPublisher;

class x264Encode
{
public:
	x264Encode();
	~x264Encode();
	BOOL	Open(INT cx, INT cy);
	BOOL	Encode(AVFrame* pI420, RTMPPublisher* publisher);
	void	Close();
private:
	BOOL	BuildParam(INT cx, INT cy);
private:
	x264_param_t*			m_x264Param;
	x264_picture_t*			m_x264Image;
	x264_t*					m_hx264;
	vector<BYTE>			m_pps;
	vector<BYTE>			m_sps;
	vector<BYTE>			m_sei;
	INT						m_size;
};

