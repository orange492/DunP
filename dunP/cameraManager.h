#pragma once
#include "singletonBase.h"
//#include "image.h"
//#include "tileNode.h"
#define moveValue 1

class monsterManager;
class MapTool;

class cameraManager  : public  singletonBase<cameraManager>
{
private:
	monsterManager * _mM;
	MapTool * _mapTool;
	image*	_camera;
	POINT	_center;
	
	image * _cameraDC;
	POINT	_point;
	int		_scroll;
	int		_monNum;
	int		_select;
	/*
	image * _cameraDC2;
	RECT _cameraRc;
	RECT _cameraRc2;
	float _cameraX, _cameraY;
	float _cameraX2, _cameraY2;*/

public:
	HRESULT init();
	void update();
	void release();

	void cameraShaking();

	//void cameraShaking();
	//
	//void setCameraX(float x) { _cameraX = x; }
	//void setCameraX2(float x) { _cameraX2 = x; }
	//void setCameraY(float y) { _cameraY = y; }
	//void setCameraY2(float y) { _cameraY2 = y; }
	//float getCameraX() { return _cameraX; }
	//float getCameraX2() { return _cameraX2; }
	//float getCameraY() { return _cameraY; }
	//float getCameraY2() { return _cameraY2; }
	//
	//
	//
	//image * getCameraDC() { return _cameraDC; }
	//image * getCameraDC2() { return _cameraDC2; }
	//RECT getCameraRc() { return _cameraRc; }
	//RECT getCameraRc2() { return _cameraRc2; }
	cameraManager();
	~cameraManager();

	void render(void);
	void render(image* img);
	void cameraRender(HDC hdc);

	HDC getCameraDC(void) { return _camera->getMemDC(); }
	HDC getCameraDC2(void) { return _cameraDC->getMemDC(); }
	void setCameraCenter(POINT point);
	void setCameraPoint(POINT point);

	void setCameraX(long x);
	void setCameraY(long y);
	void setScroll(int scroll) { _scroll = scroll; }

	POINT getCameraCenter(void) { return _center; }
	POINT getCameraPoint(void) { return _point; }
	image* getCamera(void) { return _camera; }
	int getMonNum() { return _monNum; }
	int getSelect() { return _select; }
	int getScroll() { return _scroll; }
	void setmMMemoryAddressLink(monsterManager* mM) { _mM = mM; }
	void setMtMemoryAddressLink(MapTool* mt) { _mapTool = mt; }
};

