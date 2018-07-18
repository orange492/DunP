#include "stdafx.h"
#include "playGround.h"


HRESULT playGround::Image_init(void)
{
	/////////////////////////¸Ê
	//IMAGEMANAGER->addFrameImage("map", "image/map/map(41,51).bmp", 0, 0, 1312, 1632, MAPTILEX, MAPTILEY, true, RGB(0, 255, 255));
	IMAGEMANAGER->addFrameImage("map", "image/map/sample(12,9).bmp", 0, 0, 288, 384, SAMPLETILEX, SAMPLETILEY, true, RGB(0, 255, 255));
	IMAGEMANAGER->addFrameImage("sample", "image/map/sample(12,9).bmp", 0, 0, 288, 384, SAMPLETILEX, SAMPLETILEY, true, RGB(0, 255, 255));
	IMAGEMANAGER->addFrameImage("tree", "image/map/tree(12,36).bmp", 0, 0, 384, 1152, 12, 36, true, RGB(0, 255, 255));
	IMAGEMANAGER->addImage("tile", "image/map/tile.bmp", 0, 0, 32, 32, true, RGB(0, 255, 255));
	
	/////////////////////////UI
	IMAGEMANAGER->addImage("cursor", "image/UI/cursor.bmp", 0, 0, 100, 100, true, RGB(0, 255, 255));
	IMAGEMANAGER->addImage("UI", "image/UI/UI.bmp", 0, 0, 1920, 1080, true, RGB(0, 255, 255));
	IMAGEMANAGER->addImage("side", "image/UI/Side.bmp", 0, 0, 1920, 1080, true, RGB(0, 255, 255));
	IMAGEMANAGER->addFrameImage("button", "image/UI/button.bmp", 0, 0, 160, 120, 1, 2, true, RGB(0, 255, 255));

	//IMAGEMANAGER->addImage("black", "image/UI/Black(1920x1080).bmp", 0, 0, 1920, 1080, true, RGB(255, 0, 255), true);
	//IMAGEMANAGER->addImage("gray", "image/UI/gray(1920x1080).bmp", 0, 0, 1920, 1080, false, RGB(255, 0, 255), true);

	return S_OK;
}