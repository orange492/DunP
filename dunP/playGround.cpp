#include "stdafx.h"
#include "playGround.h"


playGround::playGround(){}
playGround::~playGround(){}


HRESULT playGround::init(void)	
{
	gameNode::init(true);
	Image_init();
	Sound_init();
	_mapTool = new MapTool;
	_mM = new monsterManager;
	_star = new star;

	_star->setMtMemoryAddressLink(_mapTool);
	_mapTool->setmMMemoryAddressLink(_mM);
	_mapTool->setStarMemoryAddressLink(_star);
	_mM->setMtMemoryAddressLink(_mapTool);
	_mM->setStarMemoryAddressLink(_star);
	CAMERAMANAGER->setmMMemoryAddressLink(_mM);
	CAMERAMANAGER->setMtMemoryAddressLink(_mapTool);

	_mapTool->init();
	_mM->init();
	_star->init();

	mode = 맵툴;	
	
	_title = true;
	
	return S_OK;
}

void playGround::release(void)	
{
	gameNode::release();
	
}

void playGround::update(void)	
{
	gameNode::update();

	if (mode == 맵툴)
	{
		if (_title == false)
		{
			_mapTool->update();
			_mM->update();
			_star->update();

			if (KEYMANAGER->isStayKeyDown('D') && CAMERAMANAGER->getCameraCenter().x + WINSIZEX / 2 < (_mapTool->getCurrentXY().x + 22) * 32 && CAMERAMANAGER->getCameraCenter().x + WINSIZEX / 2 < TILESIZEX + 500)
				CAMERAMANAGER->setCameraCenter(PointMake(CAMERAMANAGER->getCameraCenter().x + 50, CAMERAMANAGER->getCameraCenter().y));
			else if (KEYMANAGER->isStayKeyDown('S') && CAMERAMANAGER->getCameraCenter().y + WINSIZEX / 2 < (_mapTool->getCurrentXY().y + 23) * 32 && CAMERAMANAGER->getCameraCenter().y + WINSIZEY / 2 < TILESIZEY - 20)
				CAMERAMANAGER->setCameraCenter(PointMake(CAMERAMANAGER->getCameraCenter().x, CAMERAMANAGER->getCameraCenter().y + 50));
			else if (KEYMANAGER->isStayKeyDown('A') && CAMERAMANAGER->getCameraCenter().x - WINSIZEX / 2 > 0)
				CAMERAMANAGER->setCameraCenter(PointMake(CAMERAMANAGER->getCameraCenter().x - 50, CAMERAMANAGER->getCameraCenter().y));
			else if (KEYMANAGER->isStayKeyDown('W') && CAMERAMANAGER->getCameraCenter().y - WINSIZEY / 2 > 0)
				CAMERAMANAGER->setCameraCenter(PointMake(CAMERAMANAGER->getCameraCenter().x, CAMERAMANAGER->getCameraCenter().y - 50));
		}
	}
}

void playGround::render(void)
{
	PatBlt(DC, CAMERAMANAGER->getCameraCenter().x - WINSIZEX / 2, CAMERAMANAGER->getCameraCenter().y - WINSIZEY / 2, WINSIZEX, WINSIZEY, WHITENESS);
	PatBlt(UIDC, 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);

	/////////////////////////////////////////////////////////////////////////////////////////////// 이 위로는 건들지 마시오
	
	if (_title == true)
	{
		draw("title", DC, 0, 0);
		if (PtInRect(&RectMake(880, 700, 170, 60), _ptMouse))
		{
			draw("new", DC, 880, 699);
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				int rand = RND->getInt(3);
				if(rand==0)
					_mM->addDmon(0);
				else if (rand == 1)
					_mM->addDmon(3);
				else if (rand == 2)
					_mM->addDmon(6);
				_title = false;
			}
		}
		if (PtInRect(&RectMake(795, 855, 335, 60), _ptMouse))
		{
			draw("continue", DC, 798, 855);
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				_mapTool->load();
				_mapTool->checkstone();
				_mapTool->drawMap();
				_title = false;
			}
		}
	}
	else
	{
		_mapTool->render();
		_mM->render();
		_star->render();
	}
	
	if (_title == false)
	{
		IMAGEMANAGER->render("UI", UIDC);
		char str[128];
		SetTextColor(UIDC, RGB(255, 255, 255));
		SetBkMode(UIDC, TRANSPARENT);
		HFONT font, oldFont;
		font = CreateFont(30, 0, 0, 0, 100, 0, 0, 0, DEFAULT_CHARSET,
			OUT_STRING_PRECIS, CLIP_CHARACTER_PRECIS, PROOF_QUALITY,
			DEFAULT_PITCH | FF_SWISS, TEXT("HY얕은샘물M"));
		oldFont = (HFONT)SelectObject(UIDC, font);
		wsprintf(str, "%d", _mapTool->getMoney(), _mapTool->getMoney());
		DrawText(UIDC, TEXT(str), strlen(str), &RectMake(1280, 25, 200, 50), DT_LEFT | DT_VCENTER | DT_SINGLELINE);
		wsprintf(str, "%d / %d", _mapTool->getStone(1), _mapTool->getStone(0));
		DrawText(UIDC, TEXT(str), strlen(str), &RectMake(1470, 25, 200, 50), DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		wsprintf(str, "%d / %d", _mapTool->getFood(1), _mapTool->getFood(0));
		DrawText(UIDC, TEXT(str), strlen(str), &RectMake(1710, 25, 200, 50), DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		SelectObject(UIDC, oldFont);

		font = CreateFont(50, 0, 0, 0, 100, 0, 0, 0, DEFAULT_CHARSET,
			OUT_STRING_PRECIS, CLIP_CHARACTER_PRECIS, PROOF_QUALITY,
			DEFAULT_PITCH | FF_SWISS, TEXT("HY얕은샘물M"));
		oldFont = (HFONT)SelectObject(UIDC, font);
		
		if (_mapTool->getStage()== 0)
		{
			DrawText(UIDC, TEXT("입구 생성 후 플레이어를 선택해주세요"), strlen("입구 생성 후 플레이어를 선택해주세요"), &RectMake(50, -7, 700, 100), DT_LEFT | DT_VCENTER | DT_SINGLELINE);
		}
		else if (_mapTool->getStage() == 1)
		{
			DrawText(UIDC, TEXT("전투!"), strlen("전투!"), &RectMake(100, 7, 500, 70), DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			if (PtInRect(&RectMake(100, 7, 500, 70), _ptMouse))
			{
				SetTextColor(UIDC, RGB(250, 250, 0));
				DrawText(UIDC, TEXT("전투!"), strlen("전투!"), &RectMake(100, 7, 500, 70), DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
				{
					_mapTool->setSide(false);
					_mapTool->setStage(2);
					_mapTool->setCount(0);
					TIMEMANAGER->reset();
				}
			}
		}
		else if (_mapTool->getStage() == 2)
		{
			TIMEMANAGER->render(UIDC);
		}
		SetTextColor(UIDC, RGB(0, 1, 0));
		wsprintf(str, "Day %d", _mapTool->getDay());
		DrawText(UIDC, TEXT(str), strlen(str), &RectMake(850, -7, 200, 100), DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		DeleteObject(font);
	}
	draw("ball2", UIDC, 650, 30);
	IMAGEMANAGER->render("ball3", UIDC, 650, 30,0, 0, (float)_mapTool->getBallCount() * 25 / 1000 , 25);

	IMAGEMANAGER->render("cursor", UIDC, _ptMouse.x, _ptMouse.y);
	CAMERAMANAGER->render(this->getBackBuffer());
	this->getBackBuffer()->render(getHDC(), 0, 0, CAMERAMANAGER->getCameraCenter().x - WINSIZEX / 2, CAMERAMANAGER->getCameraCenter().y - WINSIZEY / 2, WINSIZEX, WINSIZEY);
	
	// 맨마지막으로 카메라 매니저 의 DC를 그려줍니다.
	// CAMERAMANAGER->setCameraX()  CAMERAMANAGER->setCameraY() 를 이용하면   X ,Y 에  WINSIZEX , WINSIZEY 만큼 화면에 그려주고있는 렉트를 이동시킬 수 있음 .
	// 그리고 모든 렌더의 hdc 는 CAMERAMANAGER->getCameraDC()->getMemDC() 로 해주어야함 !~~!!$!$!#ㄸ!#ㄸ!$!$#@$!@#@!
}
