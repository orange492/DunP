#include "stdafx.h"
#include "MapTool.h"

//오브젝트그리기-사라지는거,덮을때 빨개지는거 헤결하자!//걍두기로함

//지우개, 전체지우개, 그리개 - 나무 막아둠
//바위갯수 넘었을 때, 나무걸렸을때 빨강
//있던 벽에 연결하면  자연스럽게 하기
//그냥타일 까는 것
//가로세로이미지만들기
//가로세로길 추가

//맵 저장슬롯
//던전입구




HRESULT MapTool::init()
{
	setup();
	_select = ROOM;
	// 버튼 렉트
	for (int i = 0; i < 5; i++)
	{
		_rc[i] = RectMakeCenter((WINSIZEX / 2 + 485) + i * 105, 150, 90, 60);
	}
	for (int i = 5; i < 10; i++)
	{
		_rc[i] = RectMakeCenter((WINSIZEX / 2 + 485) + (i-5) * 105, 1000, 90, 60);
	}
	//_rc[5]= RectMakeCenter((WINSIZEX / 2 + 535)+105, 1000, 90, 60);
	//_rc[6]= RectMakeCenter((WINSIZEX / 2 + 535)+210, 1000, 90, 60);

	_currentTileO = { 0,0 };
	_currentTileT = { 5,0 };
	_currentXY = { 30,30 };
	//_tree = 1;

	_drag = 0;
	_eraser = true;
	_rock[0] =_rock[1] = 200;

	for (int i = 0; i < TILEX * TILEY; i++)
	{
		setTFrame(i, 9, 0);
		_tiles[i].terrain = TR_NULL;
		_tiles[i].object = OBJ_NULL;
	}
	setTree();
	
	return S_OK;
}

void MapTool::release(){}

void MapTool::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		setmap();
		_mouseTile[1] = _mouseTile[0];
		_drag = 1;
	}
	else if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		if (_select == ROOM)
			_drag = 2;
		else if (_select == HROAD)
			_drag = 3;
		else if (_select == VROAD)
			_drag = 4;
		else if (_select == TERRAINDRAW)
			_drag = 5;
		else if (_select == OBJDRAW)
			_drag = 6;
		else if (_select == ITEMDRAW)
			_drag = 9;
		else if (_select ==	MONSTER)
			_drag = 10;
	}
	else if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		_mouseTile[1] = _mouseTile[0];
		_drag = -1;
	}
	else if (KEYMANAGER->isOnceKeyUp(VK_RBUTTON))
	{
		_eraser==false ?	_drag = 7 : _drag=8;
	}

	//else if (KEYMANAGER->isOnceKeyDown('Y'))
	//{
	//	for (int i = 0; i < TILEX * TILEY; i++)
	//	{
	//		_tiles[i].terrainFrameX = _currentTileT.x;
	//		_tiles[i].terrainFrameY = _currentTileT.y;

	//		_tiles[i].terrain = terrainSelect(_currentTileT.x, _currentTileT.y);
	//	}
	//}

	//else if (KEYMANAGER->isOnceKeyDown('U'))
	//{
	//	findDoor();
	//}

	/*for (int i = 0; i < TILEX * TILEY; i++)
	{*/
	_mouseTile[0].x = getMemDCPoint().x / 32;
	_mouseTile[0].y = getMemDCPoint().y / 32;
	//}
}

void MapTool::render()
{
	IMAGEMANAGER->render("side", UIDC);
	IMAGEMANAGER->render("sample", UIDC, WINSIZEX - IMAGEMANAGER->findImage("sample")->getWidth()- SAMPLEX, SAMPLEY);
	if (_select == ROOM)
	{
		fdraw("map",UIDC, 1650 - 32, 300 - 32, 1 + 7 * (_wall / 16) - 1, 4 + 3 * (_wall % 16) - 1);
		fdraw("map",UIDC, 1650, 300 - 32, 1 + 7 * (_wall / 16), 4 + 3 * (_wall % 16) - 1);
		fdraw("map",UIDC, 1650 - 32, 300, 1 + 7 * (_wall / 16) - 1, 4 + 3 * (_wall % 16));
		fdraw("map",UIDC, 1650 + 32, 300, 1 + 7 * (_wall / 16) - 1, 4 + 3 * (_wall % 16));
		fdraw("map",UIDC, 1650 + 32, 300-32, 3 + 7 * (_wall / 16) - 1, 3 + 3 * (_wall % 16));
		fdraw("map",UIDC, 1650 + 32, 300+32, 3 + 7 * (_wall / 16) - 1, 5 + 3 * (_wall % 16));
		fdraw("map",UIDC, 1650, 300+32, 2 + 7 * (_wall / 16) - 1, 3 + 3 * (_wall % 16));
		fdraw("map",UIDC, 1650-32, 300+32, 1 + 7 * (_wall / 16) - 1, 5 + 3 * (_wall % 16));
		fdraw("map",UIDC, 1650, 300, 25 + 7 * (_floor / 16), 3 + 3 * (_floor % 16));
	}
	if (_select == HROAD)
	{
		fdraw("map",UIDC, 1650-32, 300 - 32, 1 + 7 * (_wall / 16), 4 + 3 * (_wall % 16) - 1);
		fdraw("map",UIDC, 1650, 300 - 32, 1 + 7 * (_wall / 16), 4 + 3 * (_wall % 16) - 1);
		fdraw("map",UIDC, 1650+32, 300 - 32, 1 + 7 * (_wall / 16), 4 + 3 * (_wall % 16) - 1);
		fdraw("map",UIDC, 1650-32, 300 + 32, 1 + 7 * (_wall / 16), 4 + 3 * (_wall % 16) - 1);
		fdraw("map",UIDC, 1650, 300 + 32, 1 + 7 * (_wall / 16), 4 + 3 * (_wall % 16) - 1);
		fdraw("map",UIDC, 1650+32, 300 + 32, 1 + 7 * (_wall / 16), 4 + 3 * (_wall % 16) - 1);
		fdraw("map",UIDC, 1650-32, 300, 24 + 7 * (_floor / 16), 4 + 3 * (_floor % 16));
		fdraw("map",UIDC, 1650, 300, 25 + 7 * (_floor / 16), 4 + 3 * (_floor % 16));
		fdraw("map",UIDC, 1650+32, 300, 26 + 7 * (_floor / 16), 4 + 3 * (_floor % 16));
	}
	if (_select == VROAD)
	{
		fdraw("map", UIDC, 1650 - 32, 300 - 32, 0 + 7 * (_wall / 16), 5 + 3 * (_wall % 16) - 1);
		fdraw("map", UIDC, 1650-32, 300, 0 + 7 * (_wall / 16), 5 + 3 * (_wall % 16) - 1);
		fdraw("map", UIDC, 1650-32, 300 + 32, + 7 * (_wall / 16), 5 + 3 * (_wall % 16) - 1);
		fdraw("map", UIDC, 1650 + 32, 300 - 32, 0 + 7 * (_wall / 16), 5 + 3 * (_wall % 16) - 1);
		fdraw("map", UIDC, 1650+32, 300, 0 + 7 * (_wall / 16), 5 + 3 * (_wall % 16) - 1);
		fdraw("map", UIDC, 1650+32, 300 + 32, + 7 * (_wall / 16), 5 + 3 * (_wall % 16) - 1);

		fdraw("map", UIDC, 1650 , 300-32, 23 + 7 * (_floor / 16), 3 + 3 * (_floor % 16));
		fdraw("map", UIDC, 1650, 300, 23 + 7 * (_floor / 16), 4 + 3 * (_floor % 16));
		fdraw("map", UIDC, 1650 , 300+32, 23 + 7 * (_floor / 16), 5 + 3 * (_floor % 16));
	}
	if(_select==OBJDRAW)
		fdraw("map",UIDC, 1650, 300, 1 + 7 * (_wall / 16), 4+ 3 * (_wall % 16));
	if (_select == TERRAINDRAW)
		fdraw("map",UIDC, 1650, 300, 25 + 7 * (_floor / 16), 3 + 3 * (_floor % 16));
	
	// 버튼 렉트
	//for (int i = 0; i < 10; i++)
	//{
	//	Rectangle(UIDC, _rc[i].left, _rc[i].top, _rc[i].right, _rc[i].bottom);
	//}
	for (int i = 0; i < 10; i++)
	{
		fdraw("button",UIDC, _rc[i].left, _rc[i].top ,0,0);
		if (_select == ROOM)
		{
			fdraw("button",UIDC, _rc[0].left, _rc[0].top, 0, 1);
		}
		else if (_select == HROAD)
		{
			fdraw("button",UIDC, _rc[1].left, _rc[1].top, 0, 1);
		}
		else if (_select == VROAD)
		{
			fdraw("button",UIDC, _rc[2].left, _rc[2].top, 0, 1);
		}
		else if (_select == TERRAINDRAW|| _select == OBJDRAW)
		{
			fdraw("button",UIDC, _rc[3].left, _rc[3].top, 0, 1);
		}
		else if (_select == ITEMDRAW)
		{
			fdraw("button",UIDC, _rc[4].left, _rc[4].top, 0, 1);
		}
		else if (_select == MONSTER)
		{
			fdraw("button",UIDC, _rc[5].left, _rc[5].top, 0, 1);
		}
		if (_eraser==false)
		{
			fdraw("button",UIDC, _rc[6].left, _rc[6].top, 0, 1);
		}
		else if (_eraser == true)
		{
			fdraw("button",UIDC, _rc[7].left, _rc[7].top, 0, 1);
		}
	}

	// 폰트
	SetTextColor(UIDC, RGB(10, 10, 10));
	SetBkMode(UIDC, TRANSPARENT);
	HFONT font, oldFont;
	font = CreateFont(30, 0, 0, 0, 100, 0, 0, 0, DEFAULT_CHARSET,
		OUT_STRING_PRECIS, CLIP_CHARACTER_PRECIS, PROOF_QUALITY,
		DEFAULT_PITCH | FF_SWISS, TEXT("HY얕은샘물M"));
	oldFont = (HFONT)SelectObject(UIDC, font);
	DrawText(UIDC, TEXT("방"), strlen("방"), &_rc[0], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	DrawText(UIDC, TEXT("가로길"), strlen("가로길"), &_rc[1], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	DrawText(UIDC, TEXT("세로길"), strlen("세로길"), &_rc[2], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	DrawText(UIDC, TEXT("타일"), strlen("타일"), &_rc[3], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	DrawText(UIDC, TEXT("아이템"), strlen("몬스터"), &_rc[4], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	DrawText(UIDC, TEXT("몬스터"), strlen("몬스터"), &_rc[5], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	DrawText(UIDC, TEXT("벽삭제"), strlen("아몬터"), &_rc[6], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	DrawText(UIDC, TEXT("다삭제"), strlen("아몬터"), &_rc[7], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	DrawText(UIDC, TEXT("세이브"), strlen("세이브"), &_rc[8], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	DrawText(UIDC, TEXT("로드"), strlen("몬터"), &_rc[9], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	SelectObject(UIDC, oldFont);
	DeleteObject(font);

	// 지형
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (_tiles[i].rc.left < WINSIZEX + CAMERAMANAGER->getCameraCenter().x - WINSIZEX / 2 && _tiles[i].rc.top < WINSIZEY + CAMERAMANAGER->getCameraCenter().y - WINSIZEY / 2
			&& _tiles[i].rc.right > CAMERAMANAGER->getCameraCenter().x - WINSIZEX / 2 && _tiles[i].rc.bottom > CAMERAMANAGER->getCameraCenter().y - WINSIZEY / 2)
		fdraw("map",DC, _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
		//if(i == 444)
	}

	// 오브젝트
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		// 오브젝트 속성이 아니면 그리지마
		if (_tiles[i].object == OBJ_NULL) continue;
		if (_tiles[i].rc.left < WINSIZEX + CAMERAMANAGER->getCameraCenter().x - WINSIZEX / 2 && _tiles[i].rc.top < WINSIZEY + CAMERAMANAGER->getCameraCenter().y - WINSIZEY / 2
			&& _tiles[i].rc.right > CAMERAMANAGER->getCameraCenter().x - WINSIZEX / 2 && _tiles[i].rc.bottom > CAMERAMANAGER->getCameraCenter().y - WINSIZEY / 2)
		{

			if (_tiles[i].object == OBJ_WALL)
				fdraw("map",DC, _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].objFrameX, _tiles[i].objFrameY);
			else if (_tiles[i].object == OBJ_TREE)
				IMAGEMANAGER->frameRender("tree", DC, _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].objFrameX, _tiles[i].objFrameY);
			else
				IMAGEMANAGER->frameRender("samplemap", DC, _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].objFrameX, _tiles[i].objFrameY);
		}
	}

	dragMake();

	if (KEYMANAGER->isStayKeyDown(VK_TAB))
	{
		_canMove = false;

		for (int i = 0; i < TILEX * TILEY; i++)
		{
			//Rectangle(DC,_tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].rc.right, _tiles[i].rc.bottom);
			char str[128];
			sprintf_s(str, "%d,%d", i % 100, i / 100);
			//TextOut(DC, _tiles[i].rc.left, _tiles[i].rc.top, str, strlen(str));
			SetTextColor(DC, RGB(255, 255, 255));
			SetBkMode(DC, TRANSPARENT);
			HFONT font, oldFont;
			font = CreateFont(15, 0, 0, 0, 100, 0, 0, 0, DEFAULT_CHARSET,
				OUT_STRING_PRECIS, CLIP_CHARACTER_PRECIS, PROOF_QUALITY,
				DEFAULT_PITCH | FF_SWISS, TEXT("HY얕은샘물M"));
			oldFont = (HFONT)SelectObject(DC, font);
			DrawText(DC, TEXT(str), strlen(str), &_tiles[i].rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			SelectObject(DC, oldFont);
			DeleteObject(font);
		}
			
		/*for (int i = 0; i < TILEX * TILEY; i++)
		{
			Rectangle(DC, _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].rc.right, _tiles[i].rc.bottom);
			char str[128];
			sprintf_s(str, "%d", i);
			TextOut(DC, _tiles[i].rc.left, _tiles[i].rc.top, str, strlen(str));
		}

		for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; i++)
		{
			Rectangle(UIDC, _sampleTile[i].rctile.left, _sampleTile[i].rctile.top, _sampleTile[i].rctile.right, _sampleTile[i].rctile.bottom);
			char str[128];
			sprintf_s(str, "%d", i);
			TextOut(UIDC, _sampleTile[i].rctile.left, _sampleTile[i].rctile.top, str, strlen(str));
		}*/
	}
	else
		_canMove = true;

	
}

void MapTool::save()
{
	HANDLE	file;
	DWORD	save;

	file = CreateFile(MAPNAME, GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &save, NULL);

	CloseHandle(file);
}

void MapTool::load()
{
	HANDLE	file;
	DWORD	load;

	ZeroMemory(&_tiles, sizeof(tagTile) * TILEX * TILEY);

	file = CreateFile(MAPNAME, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &load, NULL);

	//for (int i = 0; i < TILEX * TILEY; i++)
	//{
	//	//if (_tiles[i].objFrameX==20 &&_tiles[i].objFrameY==0 )
	//		//_tiles[i].object = ;
	//}

	CloseHandle(file);

	
	/*for (int i = 353; i < TILEX*TILEY; i++)
	{
		_tiles[i].terrainFrameX = 596%22;
		_tiles[i].terrainFrameY = 596/22;
		_tiles[i].objFrameX = 0;
		_tiles[i].objFrameY = 0;
		_tiles[i].terrain = terrainSelect(_tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
		_tiles[i].object = OBJ_NULL;
	}*/
}

void MapTool::setup()
{
	
	for (int i = 0; i < SAMPLETILEY; ++i)
	{
		for (int j = 0; j < SAMPLETILEX; ++j)
		{
			_sampleTile[i * SAMPLETILEX + j].terrainFrameX = j;
			_sampleTile[i * SAMPLETILEX + j].terrainFrameY = i;

			SetRect(&_sampleTile[i * SAMPLETILEX + j].rctile,
				(WINSIZEX - IMAGEMANAGER->findImage("sample")->getWidth()) + j * TILESIZE - SAMPLEX,
				i * TILESIZE+ SAMPLEY,
				(WINSIZEX - IMAGEMANAGER->findImage("sample")->getWidth()) + j * TILESIZE + TILESIZE- SAMPLEX,
				i * TILESIZE + TILESIZE+ SAMPLEY);
		}
	}

	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			SetRect(&_tiles[i * TILEX + j].rc, j * TILESIZE, i * TILESIZE, j* TILESIZE + TILESIZE, i * TILESIZE + TILESIZE);
		}
	}

	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		_tiles[i].terrainFrameX = 0;
		_tiles[i].terrainFrameY = 0;
		_tiles[i].objFrameX = 0;
		_tiles[i].objFrameY = 0;
		_tiles[i].terrain = terrainSelect(_tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
		_tiles[i].object = OBJ_NULL;
	}
}

void MapTool::setmap()
{
	POINT mouse = getMemDCPoint();
	for (int i = 0; i < 10; i++)
	{
		if (PtInRect(&_rc[i], _ptMouse))
		{
			if (i == 8)
			{
				save();
				break;
			}
			else if (i == 9)
			{
				load();
				break;
			}
			else 
			{
				if (i == 0) _select = ROOM;
				if (i == 1) _select = HROAD;
				if (i == 2) _select = VROAD;
				if (i == 3) _select = OBJDRAW;
				if (i == 4) _select = ITEMDRAW;
				if (i == 5) _select = MONSTER;
				if (i == 6) _eraser = false;
				if (i == 7) _eraser = true;
				break;
			}
		}
	}

	for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; i++)
	{
		if (PtInRect(&_sampleTile[i].rctile, _ptMouse))
		{
			if (objSelect(_sampleTile[i].terrainFrameX, _sampleTile[i].terrainFrameY) == OBJ_NULL)
			{
				set_floor(i);
				_currentTileT.x = _sampleTile[i].terrainFrameX;
				_currentTileT.y = _sampleTile[i].terrainFrameY;
				if (_select == TERRAINDRAW || _select == OBJDRAW)
					_select = TERRAINDRAW;
			}
			else
			{
				set_wall(i);
				//_currentTileO.x = _sampleTile[i].terrainFrameX;
				//_currentTileO.y = _sampleTile[i].terrainFrameY;
				if (_select == TERRAINDRAW || _select == OBJDRAW)
					_select = OBJDRAW;
			}
			break;
		}
	}

	//if (_ptMouse.x < CAMERAX&&_ptMouse.y < CAMERAY)
	//{
	//	for (int i = 0; i < TILEX * TILEY; i++)
	//	{
	//		if (PtInRect(&_tiles[i].rc, mouse) && _tiles[i].object != OBJ_TREE)
	//		{
	//			if (_select == TERRAINDRAW)
	//			{
	//				_tiles[i].terrainFrameX = _currentTileT.x;
	//				_tiles[i].terrainFrameY = _currentTileT.y;

	//				_tiles[i].terrain = terrainSelect(_currentTileT.x, _currentTileT.y);
	//			
	//			}
	//			else if (_select == OBJDRAW)
	//			{
	//				_tiles[i].objFrameX = _currentTileO.x;
	//				_tiles[i].objFrameY = _currentTileO.y;

	//				_tiles[i].object = objSelect(_currentTileO.x, _currentTileO.y);
	//			}
	//			if (_select == ERASER)
	//			{
	//				_tiles[i].objFrameX = NULL;
	//				_tiles[i].objFrameY = NULL;

	//				_tiles[i].object = OBJ_NULL;
	//			}

	//			InvalidateRect(_hWnd, NULL, false);
	//			break;
	//		}
	//	}
	//}
}

TERRAIN MapTool::terrainSelect(int FrameX, int FrameY)
{
	/*for (int i = 15; i < 19; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (FrameX == i && FrameY == j) return TR_WALL;
		}
	}

	for (int i = 19; i < 24; i++)
	{
		for (int j = 0; j < 18; j++)
		{
			if (FrameX == i && FrameY == j) return TR_WALL;
		}
	}*/

	return TR_FLOOR;
}

OBJECT MapTool::objSelect(int FrameX, int FrameY)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			if (FrameX == i && FrameY == j) return OBJ_WALL;
		}
	}

	//for (int i = 3; i < 13; i++)
	//{
	//	for (int j = 0; j < 3; j++)
	//	{
	//		if (FrameX == i && FrameY == j) return OBJ_GROUND; 
	//	}
	//}

	//for (int i = 3; i < 5; i++)
	//{
	//	if (FrameX == i && FrameY == 3) return OBJ_GROUND;
	//}
	//
	//for (int i = 3; i < 11; i++)
	//{
	//	if (FrameX == i && FrameY == 4) return OBJ_GROUND;
	//}
	//
	//for (int i = 10; i < 20; i++)
	//{
	//	if (FrameX == i && FrameY == 1) return OBJ_GROUND;
	//}

	//for (int i = 5; i < 10; i++)
	//{
	//	for (int j = 17; j < 18; j++)
	//	{
	//		if(FrameX == i && FrameY == j) return OBJ_GROUND;
	//	}
	//}
	//
	//for (int i = 15; i < 21; i++)
	//{
	//	if (FrameX == i && FrameY == 18) return OBJ_GROUND;
	//}

	//for (int i = 0; i < 4; i++)
	//{
	//	if (FrameX == i && FrameY == 24) return OBJ_GROUND;
	//}

	//for (int i = 0; i < 19; i++)
	//{
	//	if (FrameX == i && FrameY == 25) return OBJ_GROUND;
	//}

	//for (int i = 17; i < 20; i++)
	//{
	//	if (FrameX == i && FrameY == 13) return OBJ_THORN;
	//}

	////오브젝트인지 잘 모르겠음
	//for (int i = 5; i < 8; i++)
	//{
	//	for (int j = 5; j < 8; j++)
	//	{
	//		if (i == 6 && j == 6) continue;
	//		if (FrameX == i && FrameY == j) return OBJ_GROUND;
	//	}
	//}
	//for (int i = 8; i < 11; i++)
	//{
	//	if (FrameX = i && FrameY == 5) return OBJ_GROUND;
	//}

	//if (FrameX == 8 && FrameY == 6) return OBJ_GROUND;
	////여기까지

	//if (FrameX == 11 && FrameY == 0) return OBJ_GROUND;
	//if (FrameX == 12 && FrameY == 0) return OBJ_GROUND;
	//if (FrameX == 13 && FrameY == 0) return OBJ_GROUND;
	//if (FrameX == 7 && FrameY == 3) return OBJ_GROUND;
	//if (FrameX == 8 && FrameY == 3) return OBJ_GROUND;
	//if (FrameX == 10 && FrameY == 3) return OBJ_GROUND;
	//if (FrameX == 11 && FrameY == 18) return OBJ_GROUND;
	//if (FrameX == 12 && FrameY == 18) return OBJ_GROUND;
	//if (FrameX == 3 && FrameY == 12) return	OBJ_GOGROUND;
	//if (FrameX == 6 && FrameY == 24) return OBJ_GROUND;
	//if (FrameX == 7 && FrameY == 24) return OBJ_GROUND;
	//if (FrameX == 8 && FrameY == 24) return OBJ_GROUND;


	return OBJ_NULL;
}

void MapTool::setTree()
{
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (_tiles[i].object == OBJ_TREE)
		{
			_tiles[i].object = OBJ_NULL;
		}
	}

	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j <  1; j++)
		{
			setPosition(i * 100 + j, TR_NULL, OBJ_TREE, POS_5,_tree);
		}
	}
	for (int i = 0; i < 100; i++)	//오른쪽이빈나무
	{
		for (int j = 1; j < 2; j++)
		{
			setPosition(i * 100 + j, TR_NULL, OBJ_TREE, POS_6, _tree);
		}
	}
	for (int i = 0; i < 100; i++)	//왼쪽이빈나무
	{
		for (int j = _currentXY.x+2; j < _currentXY.x+3; j++)
		{
			setPosition(i * 100 + j, TR_NULL, OBJ_TREE, POS_4, _tree);
		}
	}
	for (int i = 0; i <100; i++)
	{
		for (int j = _currentXY.x+3; j < 100; j++)
		{
			setPosition(i * 100 + j, TR_NULL, OBJ_TREE, POS_5, _tree);
		}
	}


	for (int i = 0; i <4; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			setPosition(i * 100 + j, TR_NULL, OBJ_TREE, POS_5, _tree);
		}
	}
	for (int i = 4; i <5; i++)		//아래쪽이빈나무
	{
		for (int j = 1; j < 100; j++)
		{
			if(j<_currentXY.x+2)
				setPosition(i * 100 + j, TR_NULL, OBJ_TREE, POS_8, _tree);
			else
				setPosition(i * 100 + j, TR_NULL, OBJ_TREE, POS_5, _tree);
		}
	}
	for (int i = _currentXY.y+5; i <_currentXY.y+6; i++)		//윗쪽이빈나무
	{
		for (int j = 1; j < 100; j++)
		{
			_tiles[i * 100 + j].object = OBJ_TREE;
			if (j<_currentXY.x + 2)
				setPosition(i * 100 + j, TR_NULL, OBJ_TREE, POS_2, _tree);
			else
				setPosition(i * 100 + j, TR_NULL, OBJ_TREE, POS_5, _tree);
		}
	}
	for (int i = _currentXY.y+6; i <100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			setPosition(i * 100 + j, TR_NULL, OBJ_TREE, POS_5, _tree);
		}
	}

	for (int i = 4; i <100; i++)
	{
		for (int j = 1; j < 100; j++)
		{
			if (i == 4 && j == 1)		//오른쪽아래가빈나무
			{
				setPosition(i * 100 + j, TR_NULL, OBJ_TREE, POS_11, _tree);
			}
			if (i == 4 && j == _currentXY.x+2)		//왼쪽아래가빈나무
			{
				setPosition(i * 100 + j, TR_NULL, OBJ_TREE, POS_12, _tree);
			}
			if (i == _currentXY.y+5 && j ==1)		//오른쪽위가빈나무
			{
				setPosition(i * 100 + j, TR_NULL, OBJ_TREE, POS_14, _tree);
			}
			if (i == _currentXY.y + 5 && j == _currentXY.x + 2)		//왼쪽위가빈나무
			{
				setPosition(i * 100 + j, TR_NULL, OBJ_TREE, POS_15, _tree);
			}
		}
	}
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (_tiles[i].object == OBJ_TREE)
		{
			switch (_tiles[i].position)
			{
			case POS_2:
				setOFrame(i, 1 + 7 * (_tiles[i].type / 11), 3 + 3 * (_tiles[i].type % 11));
				break;
			case POS_4:
				setOFrame(i, 7 * (_tiles[i].type / 11), 4 + 3 * (_tiles[i].type % 11));
				break;
			case POS_5:
				setOFrame(i, 1 + 7 * (_tiles[i].type / 11), 4 + 3 * (_tiles[i].type % 11));
				break;
			case POS_6:
				setOFrame(i, 2 + 7 * (_tiles[i].type / 11), 4 + 3 * (_tiles[i].type % 11));
				break;
			case POS_8:
				setOFrame(i, 1 + 7 * (_tiles[i].type / 11), 5 + 3 * (_tiles[i].type % 11));
				break;
			case POS_11:
				setOFrame(i, 4 + 7 * (_tiles[i].type / 11), 3 + 3 * (_tiles[i].type % 11));
				break;
			case POS_12:
				setOFrame(i, 5 + 7 * (_tiles[i].type / 11), 3 + 3 * (_tiles[i].type % 11));

				break;
			case POS_14:
				setOFrame(i, 4 + 7 * (_tiles[i].type / 11), 4 + 3 * (_tiles[i].type % 11));
				break;
			case POS_15:
				setOFrame(i, 5 + 7 * (_tiles[i].type / 11), 4 + 3 * (_tiles[i].type % 11));
				break;
			default:
				break;
			}
		}
	}
}

void MapTool::setWall(int i)
{
	if (_tiles[i].object == OBJ_WALL)
	{
		switch (_tiles[i].position)
		{
		case POS_1:
			setOFrame(i, 0 + 7 * (_tiles[i].type / 16), 3 + 3 * (_tiles[i].type % 16));
			break;
		case POS_2:
			setOFrame(i, 1 + 7 * (_tiles[i].type / 16), 3 + 3 * (_tiles[i].type % 16));
			break;
		case POS_3:
			setOFrame(i, 2 + 7 * (_tiles[i].type / 16), 3 + 3 * (_tiles[i].type % 16));
			break;
		case POS_4:
			setOFrame(i, 0 + 7 * (_tiles[i].type / 16), 4 + 3 * (_tiles[i].type % 16));
			break;
		case POS_5:
			setOFrame(i, 1 + 7 * (_tiles[i].type / 16), 4 + 3 * (_tiles[i].type % 16));
			break;
		case POS_7:
			setOFrame(i, 0 + 7 * (_tiles[i].type / 16), 5 + 3 * (_tiles[i].type % 16));
			break;
		case POS_9:
			setOFrame(i, 2 + 7 * (_tiles[i].type / 16), 5 + 3 * (_tiles[i].type % 16));
			break;
		case POS_10:
			setOFrame(i, 3 + 7 * (_tiles[i].type / 16), 3 + 3 * (_tiles[i].type % 16));
			break;
		case POS_11:
			setOFrame(i, 4 + 7 * (_tiles[i].type / 16), 3 + 3 * (_tiles[i].type % 16));
			break;
		case POS_12:
			setOFrame(i, 5 + 7 * (_tiles[i].type / 16), 3 + 3 * (_tiles[i].type % 16));
			break;
		case POS_13:
			setOFrame(i, 3 + 7 * (_tiles[i].type / 16), 4 + 3 * (_tiles[i].type % 16));
			break;
		case POS_14:
			setOFrame(i, 4 + 7 * (_tiles[i].type / 16), 4 + 3 * (_tiles[i].type % 16));
			break;
		case POS_15:
			setOFrame(i, 5 + 7 * (_tiles[i].type / 16), 4 + 3 * (_tiles[i].type % 16));
			break;
		case POS_16:
			setOFrame(i, 3 + 7 * (_tiles[i].type / 16), 5 + 3 * (_tiles[i].type % 16));
			break;
		case POS_17:
			setOFrame(i, 4 + 7 * (_tiles[i].type / 16), 5 + 3 * (_tiles[i].type % 16));
			break;
		case POS_18:
			setOFrame(i, 5 + 7 * (_tiles[i].type / 16), 5 + 3 * (_tiles[i].type % 16));
			break;
		default:
			break;
		}
	}
}

void MapTool::setFloor(int i)
{
	if (_tiles[i].terrain == TR_FLOOR)
	{
		switch (_tiles[i].position)
		{
		case POS_1:
			setTFrame(i, 20 + 7 * (_tiles[i].type /16), 3 + 3 * (_tiles[i].type %16));
			break;
		case POS_2:
			setTFrame(i, 21 + 7 * (_tiles[i].type / 16), 3 + 3 * (_tiles[i].type % 16));
			break;
		case POS_3:
			setTFrame(i, 22 + 7 * (_tiles[i].type / 16), 3 + 3 * (_tiles[i].type % 16));
			break;
		case POS_4:
			setTFrame(i, 20 + 7 * (_tiles[i].type / 16), 4 + 3 * (_tiles[i].type % 16));
			break;
		case POS_5:
			setTFrame(i, 21 + 7 * (_tiles[i].type / 16), 4 + 3 * (_tiles[i].type % 16));
			break;
		case POS_6:
			setTFrame(i, 22 + 7 * (_tiles[i].type / 16), 4 + 3 * (_tiles[i].type % 16));
			break;
		case POS_7:
			setTFrame(i, 20 + 7 * (_tiles[i].type / 16), 5 + 3 * (_tiles[i].type % 16));
			break;
		case POS_8:
			setTFrame(i, 21 + 7 * (_tiles[i].type / 16), 5 + 3 * (_tiles[i].type % 16));
			break;
		case POS_9:
			setTFrame(i, 22 + 7 * (_tiles[i].type / 16), 5 + 3 * (_tiles[i].type % 16));
			break;
		case POS_10:
			setTFrame(i, 23 + 7 * (_tiles[i].type / 16), 3 + 3 * (_tiles[i].type % 16));
			break;
		case POS_12:
			setTFrame(i, 25 + 7 * (_tiles[i].type / 16), 3 + 3 * (_tiles[i].type % 16));
			break;
		case POS_14:
			setTFrame(i, 23 + 7 * (_tiles[i].type / 16), 4 + 3 * (_tiles[i].type % 16));
			break;
		case POS_15:
			setTFrame(i, 24 + 7 * (_tiles[i].type / 16), 4 + 3 * (_tiles[i].type % 16));
			break;
		case POS_16:
			setTFrame(i, 25 + 7 * (_tiles[i].type / 16), 4 + 3 * (_tiles[i].type % 16));
			break;
		case POS_17:
			setTFrame(i, 26 + 7 * (_tiles[i].type / 16), 4 + 3 * (_tiles[i].type % 16));
			break;
		case POS_18:
			setTFrame(i, 23 + 7 * (_tiles[i].type / 16), 5 + 3 * (_tiles[i].type % 16));
			break;
		default:
			break;
		}
	}
}

void MapTool::set_wall(int i)
{
int num = 0;

	for (int l = 0; l < 3; l++)
	{
		for (int k = 0; k < 12; k += 3)
		{
			for (int j = 0; j < 4; j++)
			{
				if (_sampleTile[i].terrainFrameX == j && _sampleTile[i].terrainFrameY == k + l)
					_wall = j + num;
			}
			num += 4;
		}
	}
}

void MapTool::set_floor(int i)
{
	int num = 0;

	for (int k = 0; k < 7; k++)
	{
		for (int j = 5; j < 9; j++)
		{
			if (_sampleTile[i].terrainFrameX == j && _sampleTile[i].terrainFrameY == k)
				_floor = j-5 + num;
		}
		num += 4;
	}
}

void MapTool::dragMake()
{
	int	temp;
	int count=0;
	int count2=0;
	int count3=-1;

	tagCurrentTile LT = _mouseTile[1];
	tagCurrentTile RB = _mouseTile[0];
	
	if (RB.y < LT.y)
	{
		temp = RB.y;
		RB.y = LT.y;
		LT.y = temp;
	}
	if (RB.x < LT.x)
	{
		temp = RB.x;
		RB.x = LT.x;
		LT.x = temp;
	}

	tagCurrentTile LT2 = LT;
	tagCurrentTile RB2 = RB;

	int x = RB.x - LT.x;
	int y = RB.y - LT.y;
	
	if (_tiles[_mouseTile[0].x + (_mouseTile[0].y) * 100].object == OBJ_TREE || _drag == -1 || _rock[1] - count<0)
		IMAGEMANAGER->findImage("tile2")->render(DC, _tiles[_mouseTile[0].x + (_mouseTile[0].y) * 100].rc.left, _tiles[_mouseTile[0].x + (_mouseTile[0].y) * 100].rc.top);
	else
		IMAGEMANAGER->findImage("tile")->render(DC, _tiles[_mouseTile[0].x + (_mouseTile[0].y) * 100].rc.left, _tiles[_mouseTile[0].x + (_mouseTile[0].y) * 100].rc.top);

	if (_drag != 0 )
	{
		for (int i = 0; i <= y; i++)
		{
			for (int j = 0; j <= x; j++)
			{
				temp = LT.x + j + (LT.y + i) * 100;
				if (_select==OBJDRAW)
				{
					if (_tiles[temp].terrain == TR_FLOOR|| _tiles[temp].object==OBJ_WALL) continue;
					if (_tiles[temp - 1].terrain == TR_FLOOR|| _tiles[temp + 1].terrain == TR_FLOOR || _tiles[temp - 100].terrain == TR_FLOOR || _tiles[temp + 100].terrain == TR_FLOOR
						|| _tiles[temp - 101].terrain == TR_FLOOR || _tiles[temp - 99].terrain == TR_FLOOR || _tiles[temp +101].terrain == TR_FLOOR || _tiles[temp +99].terrain == TR_FLOOR) count++;
				}
				else
				{
					if (checkRockTile(temp) == 0)
						count++;
				}
				IMAGEMANAGER->findImage("tile")->render(DC, _tiles[temp].rc.left, _tiles[temp].rc.top);
				if (_tiles[temp].object == OBJ_TREE || _drag == -1 || _drag == 7 || _drag == 8)
				{
					IMAGEMANAGER->findImage("tile2")->render(DC, _tiles[temp].rc.left, _tiles[temp].rc.top);
					if (_tiles[temp].object == OBJ_TREE)
					{
						if (_tiles[temp].position == POS_6)
							LT2.x = 2;
						else if (_tiles[temp].position == POS_8)
							LT2.y = 5;
						else if (_tiles[temp].position == POS_2)
							RB2.y = _currentXY.y + 4;
						else if (_tiles[temp].position == POS_4)
							RB2.x = _currentXY.x + 1;
					}
				}
				if (_select == ROOM && (x < 2 || y < 2))
				{
					if(count3==-1)	count3 = 0;
					if((i==0||i==y)&&_tiles[temp - 1].terrain == TR_FLOOR || _tiles[temp + 1].terrain == TR_FLOOR || _tiles[temp - 100].terrain == TR_FLOOR || _tiles[temp + 100].terrain == TR_FLOOR
						|| _tiles[temp - 101].terrain == TR_FLOOR || _tiles[temp - 99].terrain == TR_FLOOR || _tiles[temp + 101].terrain == TR_FLOOR || _tiles[temp + 99].terrain == TR_FLOOR) count3++;
					if ((j == 0 || j == x) && _tiles[temp - 1].terrain == TR_FLOOR || _tiles[temp + 1].terrain == TR_FLOOR || _tiles[temp - 100].terrain == TR_FLOOR || _tiles[temp + 100].terrain == TR_FLOOR
						|| _tiles[temp - 101].terrain == TR_FLOOR || _tiles[temp - 99].terrain == TR_FLOOR || _tiles[temp + 101].terrain == TR_FLOOR || _tiles[temp + 99].terrain == TR_FLOOR) count3++;
				}
			}
		}
		

		x = RB2.x - LT2.x;
		y = RB2.y - LT2.y;

		for (int i = 0; i <= y; i++)
		{
			for (int j = 0; j <= x; j++)
			{
				temp = LT2.x + j + (LT2.y + i) * 100;
				if (_rock[1] - count < 0||(_select==OBJDRAW&&count==0)|| (_select == ROOM && count3 == 0))
				{ 
					IMAGEMANAGER->findImage("tile2")->render(DC, _tiles[temp].rc.left, _tiles[temp].rc.top);
					if (_drag == 6&& _tiles[temp].object==OBJ_WALL)
					{
						_tiles[temp].type=_wall;
						setWall(temp);
					}
				}
				else
				{
					if (_drag == 2 && _tiles[temp].object != OBJ_TREE)
					{
						setPosition(temp, TR_FLOOR, OBJ_NULL, POS_5, _floor);
						if (j == 0 || j == x)
						{
							setPosition(temp, TR_NULL, OBJ_WALL, POS_4, _wall);
						}
						else if (i == 0 || i == y)
						{
							setPosition(temp, TR_NULL, OBJ_WALL, POS_2, _wall);
						}
						else if (i == 1)
						{
							setPosition(temp, TR_FLOOR, OBJ_NULL, POS_2, _floor);
						}
						else if (i == y - 1)
						{
							setPosition(temp, TR_FLOOR, OBJ_NULL, POS_8, _floor);
						}
						else if (j == 1)
						{
							setPosition(temp, TR_FLOOR, OBJ_NULL, POS_4, _floor);
						}
						else if (j == x - 1)
						{
							setPosition(temp, TR_FLOOR, OBJ_NULL, POS_6, _floor);
						}

						if (j == 0 && i == 0)
							setPosition(temp, TR_NULL, OBJ_WALL, POS_1, _wall);
						else if (j == 0 && i == y)
							setPosition(temp, TR_NULL, OBJ_WALL, POS_7, _wall);
						else if (j == x && i == 0)
							setPosition(temp, TR_NULL, OBJ_WALL, POS_3, _wall);
						else if (j == x && i == y)
							setPosition(temp, TR_NULL, OBJ_WALL, POS_9, _wall);
						if (x != 1 && y != 1)
						{
							if (j == 1 && i == 1)
								setPosition(temp, TR_FLOOR, OBJ_NULL, POS_1, _floor);
							else if (j == 1 && i == y - 1)
								setPosition(temp, TR_FLOOR, OBJ_NULL, POS_7, _floor);
							else if (j == x - 1 && i == 1)
								setPosition(temp, TR_FLOOR, OBJ_NULL, POS_3, _floor);
							else if (j == x - 1 && i == y - 1)
								setPosition(temp, TR_FLOOR, OBJ_NULL, POS_9, _floor);
						}
						if (x == 2 && j == 1 && i != 0 && i != y)
						{
							if (i == 1)
								setPosition(temp, TR_FLOOR, OBJ_NULL, POS_10, _floor);
							else if (i == y - 1)
								setPosition(temp, TR_FLOOR, OBJ_NULL, POS_18, _floor);
							else
								setPosition(temp, TR_FLOOR, OBJ_NULL, POS_14, _floor);
						}
						if (y == 2 && i == 1 && j != 0 && j != x)
						{
							if (j == 1)
								setPosition(temp, TR_FLOOR, OBJ_NULL, POS_15, _floor);
							else if (j == x - 1)
								setPosition(temp, TR_FLOOR, OBJ_NULL, POS_17, _floor);
							else
								setPosition(temp, TR_FLOOR, OBJ_NULL, POS_16, _floor);
						}
						/*		if (x == 0 && j == 1 && i != 0 && i != y)
								{
									if (i == 0)
										setPosition(temp, TR_NULL, OBJ_WALL, POS_10);
									else if (i == y)
										setPosition(temp, TR_NULL, OBJ_WALL, POS_18);
									else
										setPosition(temp, TR_NULL, OBJ_WALL, POS_14);
								}
								if (y == 0 && i == 1 && j != 0 && j != x)
								{
									if (j == 0)
										setPosition(temp, TR_NULL, OBJ_WALL, POS_15);
									else if (j == x)
										setPosition(temp, TR_NULL, OBJ_WALL, POS_17);
									else
										setPosition(temp, TR_NULL, OBJ_WALL, POS_16);
								}*/
						if (x==y&&x==0)
							setPosition(temp, TR_NULL, OBJ_WALL, POS_5, _wall);

						setWall(temp);
						setFloor(temp);
					}
					if (_drag == 3 && _tiles[temp].object != OBJ_TREE)
					{
						setPosition(temp, TR_FLOOR, OBJ_NULL, POS_5, _floor);

						if (i == 1)
						{
							setPosition(temp, TR_FLOOR, OBJ_NULL, POS_2, _floor);
						}
						else if (i == y - 1)
						{
							setPosition(temp, TR_FLOOR, OBJ_NULL, POS_8, _floor);
						}
						else if (j == 0)
						{
							setPosition(temp, TR_FLOOR, OBJ_NULL, POS_4, _floor);
						}
						else if (j == x )
						{
							setPosition(temp, TR_FLOOR, OBJ_NULL, POS_6, _floor);
						}

						if (x != 1 && y != 1)
						{
							if (j == 0 && i == 1)
								setPosition(temp, TR_FLOOR, OBJ_NULL, POS_1, _floor);
							else if (j == 0 && i == y - 1)
								setPosition(temp, TR_FLOOR, OBJ_NULL, POS_7, _floor);
							else if (j == x && i == 1)
								setPosition(temp, TR_FLOOR, OBJ_NULL, POS_3, _floor);
							else if (j == x && i == y - 1)
								setPosition(temp, TR_FLOOR, OBJ_NULL, POS_9, _floor);
						}
						if (y == 2 && i == 1)
						{
							if (j == 0)
								setPosition(temp, TR_FLOOR, OBJ_NULL, POS_15, _floor);
							else if (j == x)
								setPosition(temp, TR_FLOOR, OBJ_NULL, POS_17, _floor);
							else
								setPosition(temp, TR_FLOOR, OBJ_NULL, POS_16, _floor);
						}
						if (i == 0 || i == y)
						{
							setPosition(temp, TR_NULL, OBJ_WALL, POS_2, _wall);
						}
						if (_mouseTile[0].y == _mouseTile[1].y&&_mouseTile[0].x == _mouseTile[1].x)
							setPosition(temp, TR_NULL, OBJ_WALL, POS_5, _wall);

						setWall(temp);
						setFloor(temp);
					}
					if (_drag == 4 && _tiles[temp].object != OBJ_TREE)
					{
						setPosition(temp, TR_FLOOR, OBJ_NULL, POS_5, _floor);
						if (i == 0)
						{
							setPosition(temp, TR_FLOOR, OBJ_NULL, POS_2, _floor);
						}
						else if (i == y)
						{
							setPosition(temp, TR_FLOOR, OBJ_NULL, POS_8, _floor);
						}
						else if (j == 1)
						{
							setPosition(temp, TR_FLOOR, OBJ_NULL, POS_4, _floor);
						}
						else if (j == x - 1)
						{
							setPosition(temp, TR_FLOOR, OBJ_NULL, POS_6, _floor);
						}

						if (x != 1 && y != 1)
						{
							if (j == 1 && i ==0)
								setPosition(temp, TR_FLOOR, OBJ_NULL, POS_1, _floor);
							else if (j == 1 && i == y )
								setPosition(temp, TR_FLOOR, OBJ_NULL, POS_7, _floor);
							else if (j == x - 1 && i == 0)
								setPosition(temp, TR_FLOOR, OBJ_NULL, POS_3, _floor);
							else if (j == x - 1 && i == y)
								setPosition(temp, TR_FLOOR, OBJ_NULL, POS_9, _floor);
						}
						if (x == 2 && j == 1)
						{
							if (i == 0)
								setPosition(temp, TR_FLOOR, OBJ_NULL, POS_10, _floor);
							else if (i == y )
								setPosition(temp, TR_FLOOR, OBJ_NULL, POS_18, _floor);
							else
								setPosition(temp, TR_FLOOR, OBJ_NULL, POS_14, _floor);
						}
						if (j == 0 || j == x)
						{
							setPosition(temp, TR_NULL, OBJ_WALL, POS_4, _wall);
						}
						if (_mouseTile[0].y == _mouseTile[1].y&&_mouseTile[0].x == _mouseTile[1].x)
							setPosition(temp, TR_NULL, OBJ_WALL, POS_5, _wall);

						setWall(temp);
						setFloor(temp);
					}
					if (_drag == 5 && _tiles[temp].object != OBJ_TREE && _rock[1] >= 0)
					{
						setPosition(temp, TR_FLOOR, OBJ_NULL, POS_5, _floor);
						if (i == 0)
						{
							setPosition(temp, TR_FLOOR, OBJ_NULL, POS_2, _floor);
						}
						else if (i == y )
						{
							setPosition(temp, TR_FLOOR, OBJ_NULL, POS_8, _floor);
						}
						else if (j == 0)
						{
							setPosition(temp, TR_FLOOR, OBJ_NULL, POS_4, _floor);
						}
						else if (j == x)
						{
							setPosition(temp, TR_FLOOR, OBJ_NULL, POS_6, _floor);
						}
						if (x != 0 && y != 0)
						{
							if (j == 0 && i == 0)
								setPosition(temp, TR_FLOOR, OBJ_NULL, POS_1, _floor);
							else if (j == 0 && i == y )
								setPosition(temp, TR_FLOOR, OBJ_NULL, POS_7, _floor);
							else if (j == x  && i == 0)
								setPosition(temp, TR_FLOOR, OBJ_NULL, POS_3, _floor);
							else if (j == x  && i == y )
								setPosition(temp, TR_FLOOR, OBJ_NULL, POS_9, _floor);
						}
						if (x == 0 && j == 0)
						{
							if (i == 0)
								setPosition(temp, TR_FLOOR, OBJ_NULL, POS_10, _floor);
							else if (i == y)
								setPosition(temp, TR_FLOOR, OBJ_NULL, POS_18, _floor);
							else
								setPosition(temp, TR_FLOOR, OBJ_NULL, POS_14, _floor);
						}
						if (y == 0 && i == 0)
						{
							if (j == 0)
								setPosition(temp, TR_FLOOR, OBJ_NULL, POS_15, _floor);
							else if (j == x )
								setPosition(temp, TR_FLOOR, OBJ_NULL, POS_17, _floor);
							else
								setPosition(temp, TR_FLOOR, OBJ_NULL, POS_16, _floor);
						}
						if (_mouseTile[0].y == _mouseTile[1].y&&_mouseTile[0].x == _mouseTile[1].x)
							setPosition(temp, TR_FLOOR, OBJ_NULL, POS_12, _floor);

						//_tiles[temp].terrain = TR_FLOOR;
						//_tiles[temp].position = POS_5;
						setFloor(temp);
					}
					if (_drag == 6 && _tiles[temp].object != OBJ_TREE)
					{
						count2 = 0;
						if (_tiles[temp].terrain == TR_FLOOR) continue;
						if (_tiles[temp - 1].terrain == TR_FLOOR) count2 += 10;
						if (_tiles[temp + 1].terrain == TR_FLOOR) count2 += 12;
						if (_tiles[temp - 100].terrain == TR_FLOOR) count2 += 15;
						if (_tiles[temp + 100].terrain == TR_FLOOR) count2 += 19;
						if (count2 == 10)
						{
							if(_tiles[temp - 99].terrain == TR_FLOOR|| _tiles[temp + 101].terrain == TR_FLOOR)
								setPosition(temp, TR_NULL, OBJ_WALL, POS_13, _wall);
							else
								setPosition(temp, TR_NULL, OBJ_WALL, POS_4, _wall);
						}
						else if(count2 == 12)
						{
							if (_tiles[temp - 101].terrain == TR_FLOOR || _tiles[temp + 99].terrain == TR_FLOOR)
								setPosition(temp, TR_NULL, OBJ_WALL, POS_15, _wall);
							else
							setPosition(temp, TR_NULL, OBJ_WALL, POS_4, _wall);
						}
						else if (count2 == 15)
						{
							if (_tiles[temp + 101].terrain == TR_FLOOR || _tiles[temp + 99].terrain == TR_FLOOR)
								setPosition(temp, TR_NULL, OBJ_WALL, POS_11, _wall);
							else
							setPosition(temp, TR_NULL, OBJ_WALL, POS_2, _wall);
						}
						else if(count2 == 19)
						{
							if (_tiles[temp - 99].terrain == TR_FLOOR || _tiles[temp - 101].terrain == TR_FLOOR)
								setPosition(temp, TR_NULL, OBJ_WALL, POS_17, _wall);
							else
							setPosition(temp, TR_NULL, OBJ_WALL, POS_2, _wall);
						}
						else if(count2==22)	setPosition(temp, TR_NULL, OBJ_WALL, POS_4,_wall);
						else if(count2==34)	setPosition(temp, TR_NULL, OBJ_WALL, POS_2,_wall);
						else if(count2==27)	setPosition(temp, TR_NULL, OBJ_WALL, POS_3,_wall);
						else if(count2==25)	setPosition(temp, TR_NULL, OBJ_WALL, POS_1,_wall);
						else if(count2==31)	setPosition(temp, TR_NULL, OBJ_WALL, POS_9,_wall);
						else if(count2==29)	setPosition(temp, TR_NULL, OBJ_WALL, POS_7,_wall);
						else if(count2==37)	setPosition(temp, TR_NULL, OBJ_WALL, POS_12, _wall);
						else if(count2==46)	setPosition(temp, TR_NULL, OBJ_WALL, POS_18, _wall);
						else if(count2==44)	setPosition(temp, TR_NULL, OBJ_WALL, POS_16, _wall);
						else if(count2==41|| count2 == 56)	setPosition(temp, TR_NULL, OBJ_WALL, POS_5, _wall);
						else if (count2 == 0)
						{
							if (_tiles[temp - 101].terrain == TR_FLOOR) count2 += 10;
							if (_tiles[temp + 101].terrain == TR_FLOOR) count2 += 12;
							if (_tiles[temp - 99].terrain == TR_FLOOR) count2 += 15;
							if (_tiles[temp + 99].terrain == TR_FLOOR) count2 += 19;
							if (count2 == 22 || count2 == 34 || count2 == 37 || count2 == 46 || count2 == 41 || count2 == 44 || count2 == 56)	setPosition(temp, TR_NULL, OBJ_WALL, POS_14, _wall);
							else if (count2 == 10)	setPosition(temp, TR_NULL, OBJ_WALL, POS_9,_wall);
							else if (count2 == 12)	setPosition(temp, TR_NULL, OBJ_WALL, POS_1,_wall);
							else if (count2 == 15)	setPosition(temp, TR_NULL, OBJ_WALL, POS_7,_wall);
							else if (count2 == 19)	setPosition(temp, TR_NULL, OBJ_WALL, POS_3,_wall);
							else if (count2 == 27)	setPosition(temp, TR_NULL, OBJ_WALL, POS_13,_wall);
							else if (count2 == 25)	setPosition(temp, TR_NULL, OBJ_WALL, POS_17,_wall);
							else if (count2 == 31)	setPosition(temp, TR_NULL, OBJ_WALL, POS_11,_wall);
							else if (count2 == 29)	setPosition(temp, TR_NULL, OBJ_WALL, POS_15,_wall);
						}
						setWall(temp);
					}
				}
				if (_drag == 7 && _tiles[temp].object != OBJ_TREE)
				{
					_tiles[temp].terrainFrameX = 9;
					_tiles[temp].terrainFrameY = 0;
					_tiles[temp].objFrameX = NULL;
					_tiles[temp].objFrameY = NULL;

					_tiles[temp].object = OBJ_NULL;

					InvalidateRect(_hWnd, NULL, false);
				}
				if (_drag == 8&& _tiles[temp].object!=OBJ_TREE)
				{
					_tiles[temp].terrainFrameX = 9;
					_tiles[temp].terrainFrameY = 0;
					_tiles[temp].objFrameX = NULL;
					_tiles[temp].objFrameY = NULL;

					_tiles[temp].terrain =TR_NULL;
					_tiles[temp].object = OBJ_NULL;

					InvalidateRect(_hWnd, NULL, false);
				}
			}
		}
	}
	if (_drag != 0&&_drag != 1 && _drag != -1)
	{
		_drag = 0;
		floorDir();
		wallDir();
		checkRock();
	}

	
}

void MapTool::wallDir()
{
	int count = 0;
	for (int i = 0; i < TILEX * (_currentXY.y + 6); i++)
	{
		count = 0;
		if (_tiles[i].object != OBJ_WALL) continue;
		if (_tiles[i - 1].terrain == TR_FLOOR) count += 10;
		if (_tiles[i + 1].terrain == TR_FLOOR) count += 12;
		if (_tiles[i - 100].terrain == TR_FLOOR) count += 15;
		if (_tiles[i + 100].terrain == TR_FLOOR) count += 19;
		if (count == 10)
		{
			if (_tiles[i - 99].terrain == TR_FLOOR || _tiles[i + 101].terrain == TR_FLOOR)
				setPosition(i, TR_NULL, OBJ_WALL, POS_13, _tiles[i].type);
			else
				setPosition(i, TR_NULL, OBJ_WALL, POS_4, _tiles[i].type);
		}
		else if (count == 12)
		{
			if (_tiles[i - 101].terrain == TR_FLOOR || _tiles[i + 99].terrain == TR_FLOOR)
				setPosition(i, TR_NULL, OBJ_WALL, POS_15, _tiles[i].type);
			else
				setPosition(i, TR_NULL, OBJ_WALL, POS_4, _tiles[i].type);
		}
		else if (count == 15)
		{
			if (_tiles[i + 101].terrain == TR_FLOOR || _tiles[i + 99].terrain == TR_FLOOR)
				setPosition(i, TR_NULL, OBJ_WALL, POS_11, _tiles[i].type);
			else
				setPosition(i, TR_NULL, OBJ_WALL, POS_2, _tiles[i].type);
		}
		else if (count == 19)
		{
			if (_tiles[i - 99].terrain == TR_FLOOR || _tiles[i - 101].terrain == TR_FLOOR)
				setPosition(i, TR_NULL, OBJ_WALL, POS_17, _tiles[i].type);
			else
				setPosition(i, TR_NULL, OBJ_WALL, POS_2, _tiles[i].type);
		}
		else if (count == 22)	setPosition(i, TR_NULL, OBJ_WALL, POS_4,_tiles[i].type);
		else if (count == 34)	setPosition(i, TR_NULL, OBJ_WALL, POS_2,_tiles[i].type);
		else if (count == 27)	setPosition(i, TR_NULL, OBJ_WALL, POS_3,_tiles[i].type);
		else if (count == 25)	setPosition(i, TR_NULL, OBJ_WALL, POS_1,_tiles[i].type);
		else if (count == 31)	setPosition(i, TR_NULL, OBJ_WALL, POS_9,_tiles[i].type);
		else if (count == 29)	setPosition(i, TR_NULL, OBJ_WALL, POS_7,_tiles[i].type);
		else if (count == 37)	setPosition(i, TR_NULL, OBJ_WALL, POS_12, _tiles[i].type);
		else if (count == 46)	setPosition(i, TR_NULL, OBJ_WALL, POS_18, _tiles[i].type);
		else if (count == 44)	setPosition(i, TR_NULL, OBJ_WALL, POS_16, _tiles[i].type);
		else if (count == 41 || count == 56)	setPosition(i, TR_NULL, OBJ_WALL, POS_5, _tiles[i].type);
		else if (count == 0)
		{
			if (_tiles[i - 101].terrain == TR_FLOOR) count += 10;
			if (_tiles[i + 101].terrain == TR_FLOOR) count += 12;
			if (_tiles[i - 99].terrain == TR_FLOOR) count += 15;
			if (_tiles[i + 99].terrain == TR_FLOOR) count += 19;
			if (count == 22 || count == 34 || count == 37 || count == 46 || count == 41 || count == 44 || count == 56)	setPosition(i, TR_NULL, OBJ_WALL, POS_14, _tiles[i].type);
			else if (count == 10)	setPosition(i, TR_NULL, OBJ_WALL, POS_9, _tiles[i].type);
			else if (count == 12)	setPosition(i, TR_NULL, OBJ_WALL, POS_1, _tiles[i].type);
			else if (count == 15)	setPosition(i, TR_NULL, OBJ_WALL, POS_7, _tiles[i].type);
			else if (count == 19)	setPosition(i, TR_NULL, OBJ_WALL, POS_3, _tiles[i].type);
			else if (count == 27)	setPosition(i, TR_NULL, OBJ_WALL, POS_13, _tiles[i].type);
			else if (count == 25)	setPosition(i, TR_NULL, OBJ_WALL, POS_17, _tiles[i].type);
			else if (count == 31)	setPosition(i, TR_NULL, OBJ_WALL, POS_11, _tiles[i].type);
			else if (count == 29)	setPosition(i, TR_NULL, OBJ_WALL, POS_15, _tiles[i].type);
			else if (count == 0)
			{
				setPosition(i, TR_NULL, OBJ_NULL, POS_15, _tiles[i].type);
				_tiles[i].terrainFrameX = 9;
				_tiles[i].terrainFrameY = 0;
			}
		}
		setWall(i);
	}
}

void MapTool::floorDir()
{
	int count = 0;
	for (int i = 0; i < TILEX * (_currentXY.y + 6); i++)
	{
		count = 0;
		if (_tiles[i].terrain != TR_FLOOR) continue;
		if (_tiles[i - 1].terrain == TR_FLOOR&& _tiles[i - 1].type== _tiles[i].type) count += 10;
		if (_tiles[i + 1].terrain == TR_FLOOR && _tiles[i + 1].type == _tiles[i].type) count += 12;
		if (_tiles[i - 100].terrain == TR_FLOOR && _tiles[i - 100].type == _tiles[i].type) count += 15;
		if (_tiles[i + 100].terrain == TR_FLOOR && _tiles[i + 100].type == _tiles[i].type) count += 19;
		if (count == 10)	setPosition(i, TR_FLOOR, OBJ_NULL, POS_17, _tiles[i].type);
		else if (count == 12)	setPosition(i, TR_FLOOR, OBJ_NULL, POS_15, _tiles[i].type);
		else if (count == 15)	setPosition(i, TR_FLOOR, OBJ_NULL, POS_18, _tiles[i].type);
		else if (count == 19)	setPosition(i, TR_FLOOR, OBJ_NULL, POS_10, _tiles[i].type);
		else if (count == 22)	setPosition(i, TR_FLOOR, OBJ_NULL, POS_16, _tiles[i].type);
		else if (count == 27)	setPosition(i, TR_FLOOR, OBJ_NULL, POS_7, _tiles[i].type);
		else if (count == 34)	setPosition(i, TR_FLOOR, OBJ_NULL, POS_14, _tiles[i].type);
		else if (count == 25)	setPosition(i, TR_FLOOR, OBJ_NULL, POS_9, _tiles[i].type);
		else if (count == 31)	setPosition(i, TR_FLOOR, OBJ_NULL, POS_1, _tiles[i].type);
		else if (count == 29)	setPosition(i, TR_FLOOR, OBJ_NULL, POS_3, _tiles[i].type);
		else if (count == 37)	setPosition(i, TR_FLOOR, OBJ_NULL, POS_8, _tiles[i].type);
		else if (count == 46)	setPosition(i, TR_FLOOR, OBJ_NULL, POS_4, _tiles[i].type);
		else if (count == 41)	setPosition(i, TR_FLOOR, OBJ_NULL, POS_2, _tiles[i].type);
		else if (count == 44)	setPosition(i, TR_FLOOR, OBJ_NULL, POS_6, _tiles[i].type);
		else if (count == 0)	setPosition(i, TR_FLOOR, OBJ_NULL, POS_12, _tiles[i].type);
		else if (count == 56)	setPosition(i, TR_FLOOR, OBJ_NULL, POS_5, _tiles[i].type);
		setFloor(i);
	}
}

void MapTool::setPosition(int i, TERRAIN ter, OBJECT obj, POS pos, int type)
{
	_tiles[i].terrain = ter;
	_tiles[i].object = obj;
	_tiles[i].position = pos;
	_tiles[i].type = type;
}

void MapTool::setTerrain(int i, TERRAIN ter, POS pos)
{
	//_tiles[i].terrain = ter;
	//_tiles[i].position = pos;
}

void MapTool::setObject(int i, OBJECT obj, POS pos)
{
	/*_tiles[i].object = obj;
	_tiles[i].position = pos;*/
}

void MapTool::setOFrame(int i, int x, int y)
{
	_tiles[i].objFrameX = x;
	_tiles[i].objFrameY = y;
}

void MapTool::setTFrame(int i, int x, int y)
{
	_tiles[i].terrainFrameX = x;
	_tiles[i].terrainFrameY = y;
}

void MapTool::checkRock()
{
	int count=0;
	for (int i = 0; i < TILEX * (_currentXY.y + 5); i++)
	{
		if ((_tiles[i].object != OBJ_NULL || _tiles[i].terrain != TR_NULL)&& _tiles[i].object != OBJ_TREE)	count++;
	}
	_rock[1] = _rock[0] - count;
}

int MapTool::checkRockTile(int i)
{
	if ((_tiles[i].object != OBJ_NULL || _tiles[i].terrain != TR_NULL) && _tiles[i].object != OBJ_TREE)
		return 1;
	else 
		return 0;
}

void MapTool::findDoor()
{
	for (int i = 0; i < TILEX * (_currentXY.y + 6); i++)
	{
		if (_tiles[i].terrain != TR_FLOOR) continue;
		if ((_tiles[i - 1].terrain != TR_FLOOR && _tiles[i - 1].object != OBJ_WALL) || (_tiles[i + 1].terrain != TR_FLOOR && _tiles[i + 1].object != OBJ_WALL)
			|| (_tiles[i - 100].terrain != TR_FLOOR && _tiles[i - 100].object != OBJ_WALL) || (_tiles[i + 100].terrain != TR_FLOOR && _tiles[i + 100].object != OBJ_WALL)
			|| (_tiles[i -101].terrain != TR_FLOOR && _tiles[i -101].object != OBJ_WALL) || (_tiles[i -99].terrain != TR_FLOOR && _tiles[i -99].object != OBJ_WALL) 
			|| (_tiles[i + 101].terrain != TR_FLOOR && _tiles[i + 101].object != OBJ_WALL) || (_tiles[i + 99].terrain != TR_FLOOR && _tiles[i +99].object != OBJ_WALL))
			_vDoor.push_back(i);
	}
	//for (_viDoor = _vDoor.begin(); _viDoor != _vDoor.end(); _viDoor++)
	//{
	//	_tiles[*_viDoor].object = OBJ_WALL;
	//	setWall(*_viDoor);
	//}
}

void MapTool::eraseDoor()
{
	for (_viDoor = _vDoor.begin(); _viDoor != _vDoor.end();)
	{
		_viDoor = _vDoor.erase(_viDoor);
	}
}


MapTool::MapTool(){}

MapTool::~MapTool(){}
