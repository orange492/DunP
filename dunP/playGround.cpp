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
	

	//vector<string> vStr;
	//vStr.resize(4);
	//vStr = { "F","F","F","F" };
	//TXTDATA->txtSave("random.txt", vStr);

	//_player = new Player;
	//_player->init();
	//_im = new itemManager;
	//_im->init();

	//_town = new townScene;
	//_title = new titleScene;
	//_town->setImLink(_im);
	//_player->getInven()->setImLink(_im);

	//SCENEMANAGER->setPlayerAddressLink(_player);

	//SCENEMANAGER->addScene("타이틀", _title);
	//SCENEMANAGER->addScene("던전2", new dungeon2Scene);
	

	return S_OK;
}

void playGround::release(void)	
{
	gameNode::release();
	
}

void playGround::update(void)	
{
	gameNode::update();
	

	//SCENEMANAGER->update();
	//EFFECTMANAGER->update();
	//KEYANIMANAGER->update();

	if (mode == 맵툴)
	{
		//if (_mapTool->getCanMove() == false)	return;
		_mapTool->update();
		_mM->update();
		_star->update();

		if (KEYMANAGER->isStayKeyDown('D')&& CAMERAMANAGER->getCameraCenter().x + WINSIZEX / 2<(_mapTool->getCurrentXY().x+22)*32&&CAMERAMANAGER->getCameraCenter().x+WINSIZEX/2<TILESIZEX+500)
			CAMERAMANAGER->setCameraCenter(PointMake(CAMERAMANAGER->getCameraCenter().x + 50, CAMERAMANAGER->getCameraCenter().y));
		else if (KEYMANAGER->isStayKeyDown('S') && CAMERAMANAGER->getCameraCenter().y + WINSIZEX / 2<(_mapTool->getCurrentXY().y + 25) * 32&&CAMERAMANAGER->getCameraCenter().y + WINSIZEY / 2<TILESIZEY-20)
			CAMERAMANAGER->setCameraCenter(PointMake(CAMERAMANAGER->getCameraCenter().x, CAMERAMANAGER->getCameraCenter().y + 50));
		else if (KEYMANAGER->isStayKeyDown('A') && CAMERAMANAGER->getCameraCenter().x - WINSIZEX / 2>0)
			CAMERAMANAGER->setCameraCenter(PointMake(CAMERAMANAGER->getCameraCenter().x - 50, CAMERAMANAGER->getCameraCenter().y));
		else if (KEYMANAGER->isStayKeyDown('W')&& CAMERAMANAGER->getCameraCenter().y - WINSIZEY / 2>0)
			CAMERAMANAGER->setCameraCenter(PointMake(CAMERAMANAGER->getCameraCenter().x, CAMERAMANAGER->getCameraCenter().y - 50));
	
	}
}

void playGround::render(void)
{
	//PatBlt(DC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	PatBlt(DC, CAMERAMANAGER->getCameraCenter().x - WINSIZEX / 2, CAMERAMANAGER->getCameraCenter().y - WINSIZEY / 2, WINSIZEX, WINSIZEY, WHITENESS);
	PatBlt(UIDC, 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);

	/////////////////////////////////////////////////////////////////////////////////////////////// 이 위로는 건들지 마시오
	
	//if (mode == 맵툴)	
	_mapTool->render();
	_mM->render();
	_star->render();
	
	/////////////////////////////////////////////////////////////////////////////////////////////// 이 아래로도 건들지 마시오
		//IMAGEMANAGER->render("cursor", UIDC, _ptMouse.x, _ptMouse.y);
	

	//if(mode == 타이틀)
	//IMAGEMANAGER->findImage("카메라DC")->render(UIDC, 54,240,CAMERAMANAGER->getCameraPoint().x, CAMERAMANAGER->getCameraPoint().y, 600, 670);
	//->render(UIDC, 54, 240, CAMERAMANAGER->getCameraPoint().x, CAMERAMANAGER->getCameraPoint().y, 600, 670);
	
	IMAGEMANAGER->render("UI", UIDC);
	//IMAGEMANAGER->render("UI2", UIDC);

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
	DrawText(UIDC, TEXT(str), strlen(str), &RectMake(1470,25,200,50), DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	wsprintf(str, "%d / %d", _mapTool->getFood(1), _mapTool->getFood(0));
	DrawText(UIDC, TEXT(str), strlen(str), &RectMake(1710,25,200,50), DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	SelectObject(UIDC, oldFont);
	DeleteObject(font);
	TIMEMANAGER->render(UIDC);
	//if (_mapTool->getCanMove() == true)
	IMAGEMANAGER->render("cursor", UIDC, _ptMouse.x, _ptMouse.y);
	CAMERAMANAGER->render(this->getBackBuffer());
	//CAMERAMANAGER->render(this->getBackBuffer());
	this->getBackBuffer()->render(getHDC(), 0, 0, CAMERAMANAGER->getCameraCenter().x - WINSIZEX / 2, CAMERAMANAGER->getCameraCenter().y - WINSIZEY / 2, WINSIZEX, WINSIZEY);
	//IMAGEMANAGER->render("cursor", getHDC(), _ptMouse.x, _ptMouse.y);
	
	// 맨마지막으로 카메라 매니저 의 DC를 그려줍니다.
	// CAMERAMANAGER->setCameraX()  CAMERAMANAGER->setCameraY() 를 이용하면   X ,Y 에  WINSIZEX , WINSIZEY 만큼 화면에 그려주고있는 렉트를 이동시킬 수 있음 .
	// 그리고 모든 렌더의 hdc 는 CAMERAMANAGER->getCameraDC()->getMemDC() 로 해주어야함 !~~!!$!$!#ㄸ!#ㄸ!$!$#@$!@#@!
}
 

void playGround::saveData()
{
	/*vector<string> vStr = TXTDATA->txtLoad("data.txt");
	vector<tagData> vData;
	
	vData.clear();
	vData.resize(3);

	for (int i = 0; i < 3; i++)
	{
		vData[i].idx = -1;
	}

	for (int i = 0; i < vStr.size() / 6; i++)
	{
		int idx = atoi(vStr[i * 6].c_str());
		vData[idx].idx = idx;
		vData[idx].hour = atoi(vStr[i * 6 + 1].c_str());
		vData[idx].min = atoi(vStr[i * 6 + 2].c_str());
		vData[idx].floor = atoi(vStr[i * 6 + 3].c_str());
		vData[idx].gold = atoi(vStr[i * 6 + 4].c_str());
		vData[idx].dash = atoi(vStr[i * 6 + 5].c_str());
	}

	if (vData[_fileNum].idx == -1)
	{
		vData[_fileNum].idx = _fileNum;
		vData[_fileNum].hour = TIMEMANAGER->getWorldTime() / 3600;
		vData[_fileNum].min = TIMEMANAGER->getWorldTime() / 60;
		vData[_fileNum].floor = _floorNum;
		vData[_fileNum].gold = _player->getGold();
		vData[_fileNum].dash = 2;
	}
	else
	{
		vData[_fileNum].idx += _fileNum;
		vData[_fileNum].hour += TIMEMANAGER->getWorldTime() / 3600;
		vData[_fileNum].min += TIMEMANAGER->getWorldTime() / 60;
		vData[_fileNum].floor = _floorNum;
		vData[_fileNum].gold = _player->getGold();
		vData[_fileNum].dash = 2;
	}

	vector<string> vString;
	for (int i = 0; i < 3; i++)
	{
		if (vData[i].idx == -1)continue;
		char str[128];
		vString.push_back(itoa(vData[i].idx, str, 10));
		vString.push_back(itoa(vData[i].hour, str, 10));
		vString.push_back(itoa(vData[i].min, str, 10));
		vString.push_back(itoa(vData[i].floor, str, 10));
		vString.push_back(itoa(vData[i].gold, str, 10));
		vString.push_back(itoa(vData[i].dash, str, 10));
	}
	TXTDATA->txtSave("data.txt", vString);*/
}