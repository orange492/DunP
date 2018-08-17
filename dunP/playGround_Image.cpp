#include "stdafx.h"
#include "playGround.h"


HRESULT playGround::Image_init(void)
{
	/////////////////////////¸Ê
	IMAGEMANAGER->addFrameImage("map", "image/map/map(41,51).bmp", 0, 0, 1312, 1632, MAPTILEX, MAPTILEY, true, RGB(0, 255, 255));
	IMAGEMANAGER->addFrameImage("sample", "image/map/sample(12,9).bmp", 0, 0, 288, 384, SAMPLETILEX, SAMPLETILEY, true, RGB(0, 255, 255));
	IMAGEMANAGER->addFrameImage("tree", "image/map/tree(12,36).bmp", 0, 0, 384, 1152, 12, 36, true, RGB(0, 255, 255));
	IMAGEMANAGER->addImage("tile", "image/map/tile.bmp", 0, 0, 32, 32, true, RGB(0, 255, 255));
	IMAGEMANAGER->addImage("tile2", "image/map/tile2.bmp", 0, 0, 32, 32, true, RGB(0, 255, 255));
	IMAGEMANAGER->addImage("tile3", "image/map/tile3.bmp", 0, 0, 32, 32, true, RGB(0, 255, 255));
	IMAGEMANAGER->addImage("road", "image/map/road.bmp", 0, 0, 32, 32, true, RGB(0, 255, 255));
	
	/////////////////////////UI
	IMAGEMANAGER->addImage("title", "image/UI/title.bmp", 0, 0, 1920, 1080, true, RGB(0, 255, 255));
	IMAGEMANAGER->addImage("continue", "image/UI/continue.bmp", 0, 0, 400, 100, true, RGB(0, 255, 255));
	IMAGEMANAGER->addImage("new", "image/UI/new.bmp", 0, 0, 400, 100, true, RGB(0, 255, 255));
	IMAGEMANAGER->addImage("cursor", "image/UI/cursor.bmp", 0, 0, 100, 100, true, RGB(0, 255, 255));
	IMAGEMANAGER->addImage("UI", "image/UI/UI.bmp", 0, 0, 1920, 1080, true, RGB(0, 255, 255));
	IMAGEMANAGER->addImage("side", "image/UI/Side.bmp", 0, 0, 1920, 1080, true, RGB(0, 255, 255));
	IMAGEMANAGER->addFrameImage("button", "image/UI/button.bmp", 0, 0, 160, 120, 1, 2, true, RGB(0, 255, 255));
	IMAGEMANAGER->addImage("stone2", "image/UI/stone2.bmp", 0, 0, 30, 34, true, RGB(0, 255, 255));
	IMAGEMANAGER->addImage("stone", "image/UI/stone.bmp", 0, 0, 100, 100, true, RGB(0, 255, 255));
	IMAGEMANAGER->addImage("food", "image/UI/food.bmp", 0, 0, 100, 100, true, RGB(0, 255, 255));
	IMAGEMANAGER->addImage("tree2", "image/UI/tree.bmp", 0, 0, 100, 100, true, RGB(0, 255, 255));
	IMAGEMANAGER->addImage("coin", "image/UI/coin.bmp", 0, 0, 100, 100, true, RGB(0, 255, 255));
	IMAGEMANAGER->addImage("b0", "image/UI/b0.bmp", 0, 0, 16, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("b1", "image/UI/b1.bmp", 0, 0, 16, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("b2", "image/UI/b2.bmp", 0, 0, 16, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ball", "image/UI/ball.bmp", 0, 0, 232, 25, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ball2", "image/UI/ball2.bmp", 0, 0, 25, 25, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ball3", "image/UI/ball3.bmp", 0, 0, 25, 25, true, RGB(255, 0, 255));

	/////////////////////////¸÷
	IMAGEMANAGER->addImage("slot", "image/UI/slot.bmp", 0, 0, 250, 100, true, RGB(0, 255, 255));
	IMAGEMANAGER->addImage("slot2", "image/UI/slot2.bmp", 0, 0, 250, 100, true, RGB(0, 255, 255));
	IMAGEMANAGER->addFrameImage("type", "image/UI/type.bmp", 0, 0, 128, 112, 4, 7, true, RGB(0, 255, 255));
	IMAGEMANAGER->addFrameImage("Fimg", "image/UI/Fimg.bmp", 0, 0, 240, 120, 6, 3, true, RGB(0, 255, 255));

	IMAGEMANAGER->addFrameImage("a0", "image/mon/a0.bmp", 0, 0, 320, 32, 10, 1, true, RGB(0, 255, 255));
	IMAGEMANAGER->addFrameImage("a1", "image/mon/a1.bmp", 0, 0, 680, 180, 10, 3, true, RGB(0, 255, 255));
	IMAGEMANAGER->addFrameImage("a2", "image/mon/a2.bmp", 0, 0, 672, 288, 7, 3, true, RGB(0, 255, 255));
	IMAGEMANAGER->addFrameImage("a3", "image/mon/a3.bmp", 0, 0, 500, 156, 10, 3, true, RGB(0, 255, 255));
	IMAGEMANAGER->addFrameImage("a4", "image/mon/a4.bmp", 0, 0, 869, 440, 11, 5, true, RGB(0, 255, 255));
	IMAGEMANAGER->addFrameImage("a5", "image/mon/a5.bmp", 0, 0, 624, 588, 6, 6, true, RGB(0, 255, 255));
	IMAGEMANAGER->addFrameImage("a6", "image/mon/a6.bmp", 0, 0, 588, 130, 12, 2, true, RGB(0, 255, 255));
	IMAGEMANAGER->addFrameImage("a7", "image/mon/a7.bmp", 0, 0, 923, 150, 13, 2, true, RGB(0, 255, 255));
	IMAGEMANAGER->addFrameImage("a8", "image/mon/a8.bmp", 0, 0, 830, 233, 10, 3, true, RGB(0, 255, 255));
	IMAGEMANAGER->addFrameImage("a9", "image/mon/a9.bmp", 0, 0, 627, 126, 11, 2, true, RGB(0, 255, 255));
	IMAGEMANAGER->addFrameImage("a10", "image/mon/a10.bmp", 0, 0, 750, 240, 10, 3, true, RGB(0, 255, 255));
	IMAGEMANAGER->addFrameImage("a11", "image/mon/a11.bmp", 0, 0, 594, 114, 9, 2, true, RGB(0, 255, 255));
	IMAGEMANAGER->addFrameImage("a12", "image/mon/a12.bmp", 0, 0, 747, 90, 9, 1, true, RGB(0, 255, 255));
	IMAGEMANAGER->addFrameImage("a13", "image/mon/a13.bmp", 0, 0, 495, 164, 11, 4, true, RGB(0, 255, 255));
	IMAGEMANAGER->addFrameImage("a14", "image/mon/a14.bmp", 0, 0, 850, 190, 10, 2, true, RGB(0, 255, 255));

	IMAGEMANAGER->addFrameImage("0", "image/mon/0.bmp", 0, 0, 192, 256, 6, 8, true, RGB(0, 255, 255));
	IMAGEMANAGER->addFrameImage("1", "image/mon/1.bmp", 0, 0, 192, 256, 6, 8, true, RGB(0, 255, 255));
	IMAGEMANAGER->addFrameImage("2", "image/mon/2.bmp", 0, 0, 192, 256, 6, 8, true, RGB(0, 255, 255));
	IMAGEMANAGER->addFrameImage("3", "image/mon/3.bmp", 0, 0, 192, 256, 6, 8, true, RGB(0, 255, 255));
	IMAGEMANAGER->addFrameImage("4", "image/mon/4.bmp", 0, 0, 192, 256, 6, 8, true, RGB(0, 255, 255));
	IMAGEMANAGER->addFrameImage("5", "image/mon/5.bmp", 0, 0, 192, 256, 6, 8, true, RGB(0, 255, 255));
	IMAGEMANAGER->addFrameImage("6", "image/mon/6.bmp", 0, 0, 192, 256, 6, 8, true, RGB(0, 255, 255));
	IMAGEMANAGER->addFrameImage("7", "image/mon/7.bmp", 0, 0, 192, 256, 6, 8, true, RGB(0, 255, 255));
	IMAGEMANAGER->addFrameImage("8", "image/mon/8.bmp", 0, 0, 192, 256, 6, 8, true, RGB(0, 255, 255));
	IMAGEMANAGER->addFrameImage("9", "image/mon/9.bmp", 0, 0, 192, 256, 6, 8, true, RGB(0, 255, 255));
	IMAGEMANAGER->addFrameImage("10", "image/mon/10.bmp", 0, 0, 192, 256, 6, 8, true, RGB(0, 255, 255));
	IMAGEMANAGER->addFrameImage("11", "image/mon/11.bmp", 0, 0, 192, 256, 6, 8, true, RGB(0, 255, 255));
	IMAGEMANAGER->addFrameImage("12", "image/mon/12.bmp", 0, 0, 192, 256, 6, 8, true, RGB(0, 255, 255));
	IMAGEMANAGER->addFrameImage("13", "image/mon/13.bmp", 0, 0, 192, 256, 6, 8, true, RGB(0, 255, 255));
	IMAGEMANAGER->addFrameImage("14", "image/mon/14.bmp", 0, 0, 192, 256, 6, 8, true, RGB(0, 255, 255));
	

	return S_OK;
}