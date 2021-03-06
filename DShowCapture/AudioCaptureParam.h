#pragma once
#include "DShowCommon.h"

namespace Media
{
	class AudioCaptureParam
	{
	public:
		AudioCaptureParam();
		~AudioCaptureParam();
		WAVEFORMATEX GetFormat() const;
		void SetFormat(const WAVEFORMATEX& wfx);
		string ToString() const;
		static WAVEFORMATEX GetDefaultFormat();
	private:
		WAVEFORMATEX	m_wft;
	};

}
