#include "../stdafx.h"
#include "TinyWave.h"

namespace TinyUI
{
	namespace Media
	{
		TinyWaveOut::TinyWaveOut()
			:hWaveOut(NULL)
		{
		}
		TinyWaveOut::~TinyWaveOut()
		{
			Close();
		}
		TinyWaveOut::operator HWAVEOUT() const throw()
		{
			return (hWaveOut);
		}
		MMRESULT TinyWaveOut::QueryFormat(LPWAVEFORMATEX pwfx)
		{
			ASSERT(pwfx != NULL);
			return waveOutOpen(NULL, WAVE_MAPPER, pwfx, NULL, 0, WAVE_FORMAT_QUERY);
		}
		MMRESULT TinyWaveOut::Open(LPWAVEFORMATEX pwfx, DWORD_PTR dwCallbackInstance)
		{
			ASSERT(pwfx != NULL);
			if (QueryFormat(pwfx) != MMSYSERR_NOERROR) return FALSE;
			return waveOutOpen(&hWaveOut, WAVE_MAPPER, pwfx, (DWORD_PTR)TinyWaveOut::waveOutProc, (DWORD_PTR)dwCallbackInstance, CALLBACK_FUNCTION);
		}
		void TinyWaveOut::GetErrorText(LPTSTR pzText, MMRESULT hRes)
		{
			waveOutGetErrorText(hRes, pzText, MAX_PATH);
		}
		MMRESULT TinyWaveOut::Pause()
		{
			if (hWaveOut == NULL) return S_FALSE;
			MMRESULT hRes = waveOutPause(hWaveOut);
			if (hRes != MMSYSERR_NOERROR)
			{
				waveOutClose(hWaveOut);
				hWaveOut = NULL;
				return S_FALSE;
			}
			return S_OK;
		}
		MMRESULT TinyWaveOut::Reset()
		{
			if (hWaveOut == NULL) return S_FALSE;
			MMRESULT hRes = waveOutReset(hWaveOut);
			if (hRes != MMSYSERR_NOERROR)
			{
				waveOutClose(hWaveOut);
				hWaveOut = NULL;
				return S_FALSE;
			}
			return S_OK;
		}
		MMRESULT TinyWaveOut::Restart()
		{
			if (hWaveOut == NULL) return S_FALSE;
			MMRESULT hRes = waveOutRestart(hWaveOut);
			if (hRes != MMSYSERR_NOERROR)
			{
				waveOutClose(hWaveOut);
				hWaveOut = NULL;
				return S_FALSE;
			}
			return S_OK;
		}
		MMRESULT TinyWaveOut::Close()
		{
			if (hWaveOut != NULL)
			{
				waveOutClose(hWaveOut);
				hWaveOut = NULL;
				return S_OK;
			}
			return S_FALSE;
		}
		MMRESULT TinyWaveOut::SetVolume(DWORD dwVolume)
		{
			MMRESULT hRes = waveOutSetVolume(hWaveOut, dwVolume);
			if (hRes != MMSYSERR_NOERROR)
			{
				waveOutClose(hWaveOut);
				hWaveOut = NULL;
			}
			return hRes;
		}
		MMRESULT TinyWaveOut::GetDevCaps(UINT_PTR uDeviceID, LPWAVEOUTCAPS pwoc)
		{
			if (hWaveOut == NULL) return S_FALSE;
			MMRESULT hRes = waveOutGetDevCaps(uDeviceID, pwoc, sizeof(WAVEOUTCAPS));
			if (hRes != MMSYSERR_NOERROR)
			{
				waveOutClose(hWaveOut);
				hWaveOut = NULL;
			}
			return hRes;
		}
		DWORD TinyWaveOut::GetVolume()
		{
			DWORD dwVolume;
			if (hWaveOut != NULL)
			{
				waveOutGetVolume(hWaveOut, &dwVolume);
			}
			return dwVolume;
		}
		MMRESULT TinyWaveOut::GetPosition(LPMMTIME pmmt)
		{
			if (hWaveOut == NULL || pmmt == NULL) return S_FALSE;
			MMRESULT hRes = waveOutGetPosition(hWaveOut, pmmt, sizeof(WAVEOUTCAPS));
			if (hRes != MMSYSERR_NOERROR)
			{
				waveOutClose(hWaveOut);
				hWaveOut = NULL;
			}
			return hRes;
		}
		DWORD TinyWaveOut::GetNumDevs()
		{
			return waveOutGetNumDevs();
		}
		MMRESULT TinyWaveOut::Prepare(LPWAVEHDR pwh)
		{
			if (hWaveOut == NULL || pwh == NULL) return S_FALSE;
			MMRESULT hRes = waveOutPrepareHeader(hWaveOut, pwh, sizeof(WAVEOUTCAPS));
			if (hRes != MMSYSERR_NOERROR)
			{
				waveOutClose(hWaveOut);
				hWaveOut = NULL;
			}
			return hRes;
		}
		MMRESULT TinyWaveOut::Unprepare(LPWAVEHDR pwh)
		{
			if (hWaveOut == NULL || pwh == NULL) return S_FALSE;
			MMRESULT hRes = waveOutUnprepareHeader(hWaveOut, pwh, sizeof(WAVEHDR));
			if (hRes != MMSYSERR_NOERROR)
			{
				waveOutClose(hWaveOut);
				hWaveOut = NULL;
			}
			return hRes;
		}
		MMRESULT TinyWaveOut::Write(LPWAVEHDR pwh)
		{
			if (hWaveOut == NULL || pwh == NULL) return S_FALSE;
			MMRESULT hRes = waveOutWrite(hWaveOut, pwh, sizeof(WAVEHDR));
			if (hRes != MMSYSERR_NOERROR)
			{
				waveOutClose(hWaveOut);
				hWaveOut = NULL;
			}
			return hRes;
		}
		MMRESULT TinyWaveOut::SetPlaybackRate(DWORD dwRate)
		{
			if (hWaveOut == NULL) return S_FALSE;
			MMRESULT hRes = waveOutSetPlaybackRate(hWaveOut, dwRate);
			if (hRes != MMSYSERR_NOERROR)
			{
				waveOutClose(hWaveOut);
				hWaveOut = NULL;
			}
			return hRes;
		}
		MMRESULT TinyWaveOut::BreakLoop()
		{
			if (hWaveOut == NULL) return S_FALSE;
			MMRESULT hRes = waveOutBreakLoop(hWaveOut);
			if (hRes != MMSYSERR_NOERROR)
			{
				waveOutClose(hWaveOut);
				hWaveOut = NULL;
			}
			return hRes;
		}
		void TinyWaveOut::SendMessage(UINT uMsg, DWORD_PTR dwParam1, DWORD_PTR dwParam2)
		{
			waveOutMessage(hWaveOut, uMsg, dwParam1, dwParam2);
		}
		void CALLBACK TinyWaveOut::waveOutProc(HWAVEOUT hwo, UINT uMsg, DWORD_PTR dwInstance, DWORD_PTR dwParam1, DWORD_PTR dwParam2)
		{
			TinyWaveOut* waveOut = (TinyWaveOut*)dwInstance;
			switch (uMsg)
			{
			case MM_WOM_OPEN:
				waveOut->OnOpen();
				break;
			case MM_WOM_CLOSE:
				waveOut->OnClose();
				break;
			case MM_WOM_DONE:
				waveOut->OnDone((LPWAVEHDR)dwParam1, dwInstance);
				break;
			}
		}
		void TinyWaveOut::OnDone(LPWAVEHDR wp, DWORD_PTR dwInstance)
		{
			WaveDone(wp, dwInstance);
		}
		void TinyWaveOut::OnOpen()
		{
		}
		void TinyWaveOut::OnClose()
		{

		}
		//////////////////////////////////////////////////////////////////////////
		TinyWaveIn::TinyWaveIn()
			:hWaveIn(NULL)
		{

		}
		TinyWaveIn::~TinyWaveIn()
		{
			Close();
		}
		MMRESULT TinyWaveIn::QueryFormat(LPWAVEFORMATEX pwfx)
		{
			ASSERT(pwfx != NULL);
			return waveInOpen(NULL, WAVE_MAPPER, pwfx, NULL, 0, WAVE_FORMAT_QUERY);
		}
		TinyWaveIn::operator HWAVEIN() const throw()
		{
			return (hWaveIn);
		}
		MMRESULT TinyWaveIn::Open(LPWAVEFORMATEX pwfx, DWORD_PTR dwCallbackInstance)
		{
			ASSERT(pwfx != NULL);
			if (QueryFormat(pwfx) != MMSYSERR_NOERROR) return FALSE;
			return waveInOpen(&hWaveIn, WAVE_MAPPER, pwfx, (DWORD_PTR)TinyWaveIn::waveInProc, (DWORD_PTR)dwCallbackInstance, CALLBACK_FUNCTION);
		}
		MMRESULT TinyWaveIn::Close()
		{
			if (hWaveIn != NULL)
			{
				waveInClose(hWaveIn);
				hWaveIn = NULL;
				return S_OK;
			}
			return S_FALSE;
		}
		MMRESULT TinyWaveIn::Start()
		{
			if (hWaveIn == NULL) return S_FALSE;
			MMRESULT hRes = waveInStart(hWaveIn);
			if (hRes != MMSYSERR_NOERROR)
			{
				waveInClose(hWaveIn);
				hWaveIn = NULL;
				return S_FALSE;
			}
			return S_OK;
		}
		MMRESULT TinyWaveIn::Stop()
		{
			if (hWaveIn == NULL) return S_FALSE;
			MMRESULT hRes = waveInStop(hWaveIn);
			if (hRes != MMSYSERR_NOERROR)
			{
				waveInClose(hWaveIn);
				hWaveIn = NULL;
				return S_FALSE;
			}
			return S_OK;
		}
		MMRESULT TinyWaveIn::Reset()
		{
			if (hWaveIn == NULL) return S_FALSE;
			MMRESULT hRes = waveInReset(hWaveIn);
			if (hRes != MMSYSERR_NOERROR)
			{
				waveInClose(hWaveIn);
				hWaveIn = NULL;
				return S_FALSE;
			}
			return S_OK;
		}
		MMRESULT TinyWaveIn::Prepare(LPWAVEHDR pwh)
		{
			if (hWaveIn == NULL || pwh == NULL) return S_FALSE;
			MMRESULT hRes = waveInPrepareHeader(hWaveIn, pwh, sizeof(WAVEOUTCAPS));
			if (hRes != MMSYSERR_NOERROR)
			{
				waveInClose(hWaveIn);
				hWaveIn = NULL;
			}
			return hRes;
		}
		MMRESULT TinyWaveIn::Unprepare(LPWAVEHDR pwh)
		{
			if (hWaveIn == NULL || pwh == NULL) return S_FALSE;
			MMRESULT hRes = waveInUnprepareHeader(hWaveIn, pwh, sizeof(WAVEHDR));
			if (hRes != MMSYSERR_NOERROR)
			{
				waveInClose(hWaveIn);
				hWaveIn = NULL;
			}
			return hRes;
		}
		MMRESULT TinyWaveIn::Add(LPWAVEHDR pwh)
		{
			if (hWaveIn == NULL || pwh == NULL) return S_FALSE;
			MMRESULT hRes = waveInAddBuffer(hWaveIn, pwh, sizeof(WAVEHDR));
			if (hRes != MMSYSERR_NOERROR)
			{
				waveInClose(hWaveIn);
				hWaveIn = NULL;
			}
			return hRes;
		}
		MMRESULT TinyWaveIn::GetPosition(LPMMTIME pmmt)
		{
			if (hWaveIn == NULL || pmmt == NULL) return S_FALSE;
			MMRESULT hRes = waveInGetPosition(hWaveIn, pmmt, sizeof(WAVEINCAPS));
			if (hRes != MMSYSERR_NOERROR)
			{
				waveInClose(hWaveIn);
				hWaveIn = NULL;
			}
			return hRes;
		}
		void TinyWaveIn::GetErrorText(LPTSTR pzText, MMRESULT hRes)
		{
			waveInGetErrorText(hRes, pzText, MAX_PATH);
		}
		void TinyWaveIn::OnOpen()
		{

		}
		void TinyWaveIn::OnClose()
		{

		}
		void TinyWaveIn::OnData(LPWAVEHDR wp, DWORD_PTR dwInstance)
		{

		}
		void CALLBACK TinyWaveIn::waveInProc(HWAVEIN hwi, UINT uMsg, DWORD_PTR dwInstance, DWORD_PTR dwParam1, DWORD_PTR dwParam2)
		{
			TinyWaveIn* waveIn = (TinyWaveIn*)dwInstance;
			switch (uMsg)
			{
			case MM_WIM_OPEN:
				waveIn->OnOpen();
				break;
			case MM_WIM_CLOSE:
				waveIn->OnClose();
				break;
			case MM_WIM_DATA:
				waveIn->OnData((LPWAVEHDR)dwParam1, dwInstance);
				break;
			}
		}
		//////////////////////////////////////////////////////////////////////////
		TinyWavePlayer::TinyWavePlayer()
		{
			m_wavePlayDone.Reset(new Delegate<void(LPWAVEHDR, DWORD_PTR)>(this, &TinyWavePlayer::PlayDone));
			m_waveOut.WaveDone += m_wavePlayDone;
			m_dwBlocks = m_dwBlockNext = m_dwBlockOut = 0;
			m_bPlaying = FALSE;
		}
		TinyWavePlayer::~TinyWavePlayer()
		{
			m_waveOut.WaveDone -= m_wavePlayDone;
			while (m_dwBlocks > 0)
			{
				--m_dwBlocks;
				m_waveOut.Unprepare(m_audioBlockPtr[m_dwBlocks]);
				LocalFree((LPBYTE)m_audioBlockPtr[m_dwBlocks]);
			}
			m_waveOut.Close();
			m_waveFile.Close();
			m_dwBlockNext = m_dwBlockOut = 0;
			m_bPlaying = FALSE;
		}
		BOOL TinyWavePlayer::LoadStream(LPVOID pStream, DWORD bufferSize)
		{
			m_waveFile.Close();
			if (!m_waveFile.Open(pStream, bufferSize)) return FALSE;
			WAVEFORMATEX waveEx = m_waveFile.GetFormat();
			if (m_waveOut.Open(&waveEx, (DWORD_PTR)&m_waveOut) != MMSYSERR_NOERROR)
				return FALSE;
			for (m_dwBlocks = 0; m_dwBlocks < MAX_AUDIO_BUFFERS; m_dwBlocks++)
			{
				if (!(m_audioBlockPtr[m_dwBlocks] = (LPWAVEHDR)LocalAlloc(LPTR, (DWORD)(sizeof(WAVEHDR) + AUDIO_BUFFER_SIZE))))
					break;
				m_audioBlockPtr[m_dwBlocks]->dwFlags = WHDR_DONE;
				m_audioBlockPtr[m_dwBlocks]->lpData = (LPSTR)((LPBYTE)m_audioBlockPtr[m_dwBlocks] + sizeof(WAVEHDR));
				m_audioBlockPtr[m_dwBlocks]->dwBufferLength = AUDIO_BUFFER_SIZE;
				if (m_waveOut.Prepare(m_audioBlockPtr[m_dwBlocks]) != MMSYSERR_NOERROR)
				{
					LocalFree(m_audioBlockPtr[m_dwBlocks]);
					continue;
				}
			}
			if (m_dwBlocks < MIN_AUDIO_BUFFERS)
			{
				while (m_dwBlocks > 0)
				{
					--m_dwBlocks;
					m_waveOut.Unprepare(m_audioBlockPtr[m_dwBlocks]);
					LocalFree((LPBYTE)m_audioBlockPtr[m_dwBlocks]);
				}
				m_waveOut.Close();
				m_waveFile.Close();
			}
			return TRUE;
		}
		BOOL TinyWavePlayer::LoadFile(LPSTR szFilename)
		{
			m_waveFile.Close();
			if (!m_waveFile.Open(szFilename)) return FALSE;
			WAVEFORMATEX waveEx = m_waveFile.GetFormat();
			if (m_waveOut.Open(&waveEx, (DWORD_PTR)&m_waveOut) != MMSYSERR_NOERROR)
				return FALSE;
			for (m_dwBlocks = 0; m_dwBlocks < MAX_AUDIO_BUFFERS; m_dwBlocks++)
			{
				if (!(m_audioBlockPtr[m_dwBlocks] = (LPWAVEHDR)LocalAlloc(LPTR, (DWORD)(sizeof(WAVEHDR) + AUDIO_BUFFER_SIZE))))
					break;
				m_audioBlockPtr[m_dwBlocks]->dwFlags = WHDR_DONE;
				m_audioBlockPtr[m_dwBlocks]->lpData = (LPSTR)((LPBYTE)m_audioBlockPtr[m_dwBlocks] + sizeof(WAVEHDR));
				m_audioBlockPtr[m_dwBlocks]->dwBufferLength = AUDIO_BUFFER_SIZE;
				if (m_waveOut.Prepare(m_audioBlockPtr[m_dwBlocks]) != MMSYSERR_NOERROR)
				{
					LocalFree(m_audioBlockPtr[m_dwBlocks]);
					continue;
				}
			}
			if (m_dwBlocks < MIN_AUDIO_BUFFERS)
			{
				while (m_dwBlocks > 0)
				{
					--m_dwBlocks;
					m_waveOut.Unprepare(m_audioBlockPtr[m_dwBlocks]);
					LocalFree((LPBYTE)m_audioBlockPtr[m_dwBlocks]);
				}
				m_waveOut.Close();
				m_waveFile.Close();
			}
			return FALSE;
		}
		BOOL TinyWavePlayer::IsPlaying()
		{
			BOOL bFlags = FALSE;
			for (DWORD i = 0; i < m_dwBlocks; i++)
			{
				if ((m_audioBlockPtr[i]->dwFlags & WHDR_DONE) == 0)//正在播放
				{
					bFlags = TRUE;
				}
			}
			return bFlags;
		}
		BOOL TinyWavePlayer::Seek(DWORD newPos)
		{
			newPos += m_waveFile.GetDataOffset();
			return m_waveFile.Seek(newPos, SEEK_SET);
		}
		BOOL TinyWavePlayer::Pause()
		{
			m_bPlaying = FALSE;
			return m_waveOut.Pause();
		}
		BOOL TinyWavePlayer::Restart()
		{
			m_bPlaying = TRUE;
			return m_waveOut.Restart();
		}
		DWORD TinyWavePlayer::GetDataSize()
		{
			return m_waveFile.GetDataSize();
		}
		void TinyWavePlayer::PlayData()
		{
			if (!m_bPlaying) return;
			while (m_dwBlockOut < m_dwBlocks)
			{
				DWORD numberOfBytesRead = 0;
				m_waveFile.Read((LPBYTE)m_audioBlockPtr[m_dwBlockNext]->lpData, min(AUDIO_BUFFER_SIZE, m_dwSizeL), &numberOfBytesRead);
				m_dwSizeL -= numberOfBytesRead;
				if (numberOfBytesRead > 0)
				{
					m_audioBlockPtr[m_dwBlockNext]->dwBytesRecorded = numberOfBytesRead;
					m_waveOut.Write(m_audioBlockPtr[m_dwBlockNext]);
					if (m_dwSizeL <= 0)
					{
						++m_dwBlockOut;
						++m_dwBlockNext;
					}
				}
				if (m_dwSizeL <= 0) break;
				++m_dwBlockOut;
				++m_dwBlockNext;
				if (m_dwBlockNext >= m_dwBlocks)
				{
					m_dwBlockNext = 0;
				}
			}
		}
		BOOL TinyWavePlayer::Reset()
		{
			return m_waveOut.Reset();
		}
		BOOL TinyWavePlayer::Play(BOOL bLoop)
		{
			do
			{
				m_bPlaying = TRUE;
				m_dwBlockOut = m_dwBlockNext = 0;
				m_dwSizeL = m_waveFile.GetDataSize();
				PlayData();//播放数据
				if (m_waveOut.Restart() != MMSYSERR_NOERROR) return FALSE;
				while (m_dwBlockOut > 0)
				{
					MSG msg = { 0 };
					if (PeekMessage(&msg, 0, 0, 0, PM_NOREMOVE) && (msg.message == PLAY_QUIT))
					{
						//收到窗口退出消息
						m_bPlaying = FALSE;
						do
						{
							LoopEmpty();
						} while (IsPlaying());
						m_waveOut.Reset();
						while (m_dwBlocks > 0)
						{
							--m_dwBlocks;
							m_waveOut.Unprepare(m_audioBlockPtr[m_dwBlocks]);
							LocalFree((LPBYTE)m_audioBlockPtr[m_dwBlocks]);
						}
						m_waveOut.Close();
						m_waveFile.Close();
						break;
					}
				}
			} while (bLoop);
			return TRUE;
		}
		void TinyWavePlayer::PlayDone(LPWAVEHDR wp, DWORD_PTR dwInstance)
		{
			if (wp->dwFlags & WHDR_DONE)
			{
				--m_dwBlockOut;
				PlayData();
			}
		}
		//////////////////////////////////////////////////////////////////////////
		TinyWaveTape::TinyWaveTape()
		{

		}
		TinyWaveTape::~TinyWaveTape()
		{

		}
		BOOL TinyWaveTape::LoadFile(LPTSTR pzFile)
		{
			return FALSE;
		}
		BOOL TinyWaveTape::Start()
		{
			return FALSE;
		}
		BOOL TinyWaveTape::Stop()
		{
			return FALSE;
		}
		BOOL TinyWaveTape::Reset()
		{
			return FALSE;
		}
		//////////////////////////////////////////////////////////////////////////
		//Wave File http://msdn.microsoft.com/en-us/library/windows/desktop/dd742884(v=vs.85).aspx
		BOOL TinyWaveFile::Open(LPTSTR pzFile)
		{
			if (!pzFile) return FALSE;
			if (hmmio != NULL)
			{
				mmioClose(hmmio, 0);
				hmmio = NULL;
			}
			if ((hmmio = mmioOpen(pzFile, NULL, MMIO_READ | MMIO_ALLOCBUF)) == NULL) return FALSE;
			MMCKINFO    mmckRIFF;
			MMCKINFO    mmck;
			MMRESULT    wError;
			WORD		wFormatSize;
			mmckRIFF.fccType = mmioWAVE;
			if (wError = mmioDescend(hmmio, &mmckRIFF, NULL, MMIO_FINDRIFF))
			{
				return FALSE;
			}
			mmck.ckid = mmioFMT;
			if (wError = mmioDescend(hmmio, &mmck, &mmckRIFF, MMIO_FINDCHUNK))
			{
				return FALSE;
			}
			if (mmck.cksize < sizeof(WAVEFORMAT))
			{
				return FALSE;
			}
			wFormatSize = (WORD)mmck.cksize;
			if ((DWORD)mmioRead(hmmio, (HPSTR)&waveEx, mmck.cksize) != mmck.cksize)//读取WAVEFORMAT
			{
				goto MMIO_ERROR;
			}
			if (waveEx.wFormatTag == WAVE_FORMAT_PCM)//PCM格式
			{
				if (wFormatSize < sizeof(PCMWAVEFORMAT))
				{
					goto MMIO_ERROR;
				}
			}
			else
			{
				if ((wFormatSize < sizeof(WAVEFORMATEX)) || (wFormatSize < sizeof(WAVEFORMATEX) + waveEx.cbSize))
				{
					goto MMIO_ERROR;
				}
				if (waveEx.cbSize != 0)
				{
					LPBYTE extraBytes = (LPBYTE)LocalAlloc(LPTR, waveEx.cbSize);
					if (extraBytes != NULL)
					{
						if (mmioRead(hmmio, (HPSTR)extraBytes, waveEx.cbSize) != waveEx.cbSize)
						{
							SAFE_LOCAL_DELETE(extraBytes);
							goto MMIO_ERROR;
						}
					}
				}
			}
			if (wError = mmioAscend(hmmio, &mmck, 0))
			{
				goto MMIO_ERROR;
			}
			mmck.ckid = mmioDATA;
			if (wError = mmioDescend(hmmio, &mmck, &mmckRIFF, MMIO_FINDCHUNK))
			{
				goto MMIO_ERROR;
			}
			dwLSize = dwSize = mmck.cksize;
			dwDataOffset = mmck.dwDataOffset;
			if (-1 == mmioSeek(hmmio, mmck.dwDataOffset, SEEK_SET))
			{
				goto MMIO_ERROR;
			}
			return TRUE;
		MMIO_ERROR:
			mmioClose(hmmio, 0);
			return FALSE;
		}
		BOOL TinyWaveFile::Open(LPVOID pStream, DWORD bufferSize)
		{
			if (pStream == NULL) return FALSE;
			if (hmmio != NULL)
			{
				mmioClose(hmmio, 0);
				hmmio = NULL;
			}
			//内存流
			MMIOINFO mmioInfo;
			ZeroMemory(&mmioInfo, sizeof(MMIOINFO));
			mmioInfo.fccIOProc = FOURCC_MEM;
			mmioInfo.cchBuffer = bufferSize;
			mmioInfo.pchBuffer = (CHAR*)pStream;
			if ((hmmio = mmioOpen(NULL, &mmioInfo, MMIO_READ | MMIO_ALLOCBUF)) == NULL) return FALSE;
			MMCKINFO    mmckRIFF;
			MMCKINFO    mmck;
			MMRESULT    wError;
			WORD		wFormatSize;
			mmckRIFF.fccType = mmioWAVE;
			if (wError = mmioDescend(hmmio, &mmckRIFF, NULL, MMIO_FINDRIFF))
			{
				return FALSE;
			}
			mmck.ckid = mmioFMT;
			if (wError = mmioDescend(hmmio, &mmck, &mmckRIFF, MMIO_FINDCHUNK))
			{
				return FALSE;
			}
			if (mmck.cksize < sizeof(WAVEFORMAT))
			{
				return FALSE;
			}
			wFormatSize = (WORD)mmck.cksize;
			if ((DWORD)mmioRead(hmmio, (HPSTR)&waveEx, mmck.cksize) != mmck.cksize)//读取WAVEFORMAT
			{
				goto MMIO_ERROR;
			}
			if (waveEx.wFormatTag == WAVE_FORMAT_PCM)//PCM格式
			{
				if (wFormatSize < sizeof(PCMWAVEFORMAT))
				{
					goto MMIO_ERROR;
				}
			}
			else
			{
				if ((wFormatSize < sizeof(WAVEFORMATEX)) || (wFormatSize < sizeof(WAVEFORMATEX) + waveEx.cbSize))
				{
					goto MMIO_ERROR;
				}
				if (waveEx.cbSize != 0)
				{
					LPBYTE extraBytes = (LPBYTE)LocalAlloc(LPTR, waveEx.cbSize);
					if (extraBytes != NULL)
					{
						if (mmioRead(hmmio, (HPSTR)extraBytes, waveEx.cbSize) != waveEx.cbSize)
						{
							SAFE_LOCAL_DELETE(extraBytes);
							goto MMIO_ERROR;
						}
					}
				}
			}
			if (wError = mmioAscend(hmmio, &mmck, 0))
			{
				goto MMIO_ERROR;
			}
			mmck.ckid = mmioDATA;
			if (wError = mmioDescend(hmmio, &mmck, &mmckRIFF, MMIO_FINDCHUNK))
			{
				goto MMIO_ERROR;
			}
			dwLSize = dwSize = mmck.cksize;
			dwDataOffset = mmck.dwDataOffset;
			if (-1 == mmioSeek(hmmio, mmck.dwDataOffset, SEEK_SET))
			{
				goto MMIO_ERROR;
			}
			return TRUE;
		MMIO_ERROR:
			mmioClose(hmmio, 0);
			return FALSE;
		}
		void TinyWaveFile::Close()
		{
			if (hmmio != NULL)
			{
				mmioClose(hmmio, 0);
				hmmio = NULL;
			}
			dwSize = dwLSize = dwDataOffset = 0;
		}
		BOOL TinyWaveFile::Read(BYTE* lpBuffer, DWORD nNumberOfBytesToRead, LPDWORD lpNumberOfBytesRead)
		{
			if (hmmio == NULL) return FALSE;
			*lpNumberOfBytesRead = 0;
			MMIOINFO mmioinfo;
			if (MMSYSERR_NOERROR != mmioGetInfo(hmmio, &mmioinfo, 0)) return FALSE;
			UINT cbDataIn = nNumberOfBytesToRead;
			if (cbDataIn > dwSize) cbDataIn = dwLSize;
			dwLSize -= cbDataIn;
			for (DWORD cT = 0; cT < cbDataIn; cT++)
			{
				if (mmioinfo.pchNext == mmioinfo.pchEndRead)
				{
					if (MMSYSERR_NOERROR != mmioAdvance(hmmio, &mmioinfo, MMIO_READ)) return FALSE;
					if (mmioinfo.pchNext == mmioinfo.pchEndRead) return FALSE;
				}
				*((BYTE*)lpBuffer + cT) = *((BYTE*)mmioinfo.pchNext);
				mmioinfo.pchNext++;
			}
			if (MMSYSERR_NOERROR != mmioSetInfo(hmmio, &mmioinfo, 0)) return FALSE;
			*lpNumberOfBytesRead = cbDataIn;
			return TRUE;
		}
		BOOL TinyWaveFile::Seek(LONG lOffset, INT iOrigin)
		{
			if (hmmio == NULL) return FALSE;
			if (-1 == mmioSeek(hmmio, lOffset, iOrigin)) return FALSE;
			return TRUE;
		}
		WAVEFORMATEX TinyWaveFile::GetFormat()
		{
			return waveEx;
		}
		DWORD TinyWaveFile::GetDataSize()
		{
			return dwSize;
		}
		DWORD TinyWaveFile::GetDataOffset()
		{
			return dwDataOffset;
		}
		BOOL TinyWaveFile::ResetFile()
		{
			return Seek(dwDataOffset, SEEK_SET);
		}
	};
}
