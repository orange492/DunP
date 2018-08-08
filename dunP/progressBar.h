#pragma once
#include "gameNode.h"

enum BARTYPE
{
	BAR_PLAYER,
	BAR_MONSTER,
	BAR_BOSS
};


class progressBar : public gameNode
{
private:
	RECT _rcProgress;	//프로그레스 바 렉트
	int _x, _y;			//좌표~
	float _width;		//프로그레스 바 가로크기
	char _front[128], _back[128];

	const char* _frontName;
	const char* _bottomName;

	image* _progressBarTop;
	image* _progressBarBottom;

public:
	progressBar();
	~progressBar();

	HRESULT init(int x, int y, int width, int height, int index);

	void release();
	void update();
	void render();

	void setGauge(float currentGauge, float maxGauge);

	void setX(int x) { _x = x; }
	void setY(int y) { _y = y; }

	RECT getRect()   { return _rcProgress; }
	float getWidth() { return _width; }
};

