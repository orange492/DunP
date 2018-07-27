#include "stdafx.h"
#include "playGround.h"


HRESULT playGround::Image_init(void)
{
	/////////////////////////¸Ê
	IMAGEMANAGER->addFrameImage("map", "image/map/map(41,51).bmp", 0, 0, 1312, 1632, MAPTILEX, MAPTILEY, true, RGB(0, 255, 255));
	//IMAGEMANAGER->addFrameImage("map", "image/map/sample(12,9).bmp", 0, 0, 288, 384, SAMPLETILEX, SAMPLETILEY, true, RGB(0, 255, 255));
	IMAGEMANAGER->addFrameImage("sample", "image/map/sample(12,9).bmp", 0, 0, 288, 384, SAMPLETILEX, SAMPLETILEY, true, RGB(0, 255, 255));
	IMAGEMANAGER->addFrameImage("tree", "image/map/tree(12,36).bmp", 0, 0, 384, 1152, 12, 36, true, RGB(0, 255, 255));
	IMAGEMANAGER->addImage("tile", "image/map/tile.bmp", 0, 0, 32, 32, true, RGB(0, 255, 255));
	IMAGEMANAGER->addImage("tile2", "image/map/tile2.bmp", 0, 0, 32, 32, true, RGB(0, 255, 255));
	
	/////////////////////////UI
	IMAGEMANAGER->addImage("cursor", "image/UI/cursor.bmp", 0, 0, 100, 100, true, RGB(0, 255, 255));
	IMAGEMANAGER->addImage("UI", "image/UI/UI.bmp", 0, 0, 1920, 1080, true, RGB(0, 255, 255));
	//IMAGEMANAGER->addImage("UI2", "image/UI/UI2.bmp", 0, 0, 1920, 1080, true, RGB(0, 255, 255));
	IMAGEMANAGER->addImage("side", "image/UI/Side.bmp", 0, 0, 1920, 1080, true, RGB(0, 255, 255));
	IMAGEMANAGER->addFrameImage("button", "image/UI/button.bmp", 0, 0, 160, 120, 1, 2, true, RGB(0, 255, 255));
	IMAGEMANAGER->addImage("stone", "image/UI/stone.bmp", 0, 0, 30, 34, true, RGB(0, 255, 255));

	/////////////////////////¸÷
	IMAGEMANAGER->addImage("slot", "image/UI/slot.bmp", 0, 0, 250, 100, true, RGB(0, 255, 255));
	IMAGEMANAGER->addImage("slot2", "image/UI/slot2.bmp", 0, 0, 250, 100, true, RGB(0, 255, 255));
	IMAGEMANAGER->addFrameImage("type", "image/UI/type.bmp", 0, 0, 128, 112, 4, 7, true, RGB(0, 255, 255));
	IMAGEMANAGER->addFrameImage("Fimg", "image/UI/Fimg.bmp", 0, 0, 120, 120, 3, 3, true, RGB(0, 255, 255));
	IMAGEMANAGER->addFrameImage("a0", "image/mon/a0.bmp", 0, 0, 320, 32, 10, 1, true, RGB(0, 255, 255));
	IMAGEMANAGER->addFrameImage("a1", "image/mon/a1.bmp", 0, 0, 680, 180, 10, 3, true, RGB(0, 255, 255));
	IMAGEMANAGER->addFrameImage("a2", "image/mon/a2.bmp", 0, 0, 672, 288, 7, 3, true, RGB(0, 255, 255));

	//IMAGEMANAGER->addImage("black", "image/UI/Black(1920x1080).bmp", 0, 0, 1920, 1080, true, RGB(255, 0, 255), true);
	//IMAGEMANAGER->addImage("gray", "image/UI/gray(1920x1080).bmp", 0, 0, 1920, 1080, false, RGB(255, 0, 255), true);

	return S_OK;
}