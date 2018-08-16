#include "stdafx.h"
#include "timeManager.h"


timeManager::timeManager()
	: _timer(NULL)
{
}


timeManager::~timeManager()
{
}

HRESULT timeManager::init()
{
	_timer = new timer;
	_timer->init();

	return S_OK;
}

void timeManager::release()
{
	if (_timer != NULL)
	{
		SAFE_DELETE(_timer);
	}
}

void timeManager::update(float lockFPS)
{
	if (_timer != NULL)
	{
		_timer->tick(lockFPS);
	}
}

void timeManager::reset()
{
	_timer->resetTime();
}

void timeManager::render(HDC hdc)
{
	char str[256];
	string frameRate;

	//폰트 뒷배경처리
	//투명 : TRANSPARENT
	//불투명 : OPAQUE
	//SetTextColor(hdc, RGB(255, 255, 255));
	SetTextColor(hdc, RGB(255, 255, 254)); // 눈에 편안하다는 green 255 로 수정 
	SetBkMode(hdc, TRANSPARENT);

#ifdef _DEBUG
	{
		/*wsprintf(str, "framePerSec(FPS) : %d", _timer->getFrameRate());
		TextOut(hdc, 0, 0, str, strlen(str));

		sprintf_s(str, "worldTime : %f", _timer->getWorldTime());
		TextOut(hdc, 0, 20, str, strlen(str));

		sprintf_s(str, "elapsedTime : %f", _timer->getElapsedTime());
		TextOut(hdc, 0, 40, str, strlen(str));*/
		//const char* str1 = "time: 1111";
		int time = _timer->getWorldTime();
		sprintf_s(str, "Time: %d", time);
		TextOut(hdc, 100, 25, str, strlen(str));
	}
#else
	{
		wsprintf(str, "framePerSec(FPS) : %d", _timer->getFrameRate());
		TextOut(hdc, 0, 0, str, strlen(str));
	}
#endif
}
