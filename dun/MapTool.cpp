#include "stdafx.h"
#include "MapTool.h"

//지우개, 전체지우개, 그리개 - 나무 막아둠

HRESULT MapTool::init()
{
	setup();
	_select = OBJDRAW;
	// 버튼 렉트
	for (int i = 0; i < 5; i++)
	{
			_rc[i] = RectMakeCenter((WINSIZEX / 2 + 485) + i * 105, 150, 90, 60);
	}
	_rc[5]= RectMakeCenter((WINSIZEX / 2 + 535)+105, 1000, 90, 60);
	_rc[6]= RectMakeCenter((WINSIZEX / 2 + 535)+210, 1000, 90, 60);

	_currentTileO = { 0,0 };
	_currentTileT = { 5,0 };
	_currentXY = { 30,30 };
	//_tree = 1;

	_drag = 0;

	setTree();
	
	return S_OK;
}

void MapTool::release(){}

void MapTool::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		_mouseTile[1] = _mouseTile[0];
		_drag = 1;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		_drag = 2;
		setmap();
	}
	
	//if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))

	else if (KEYMANAGER->isStayKeyDown(VK_RBUTTON))
	{
		POINT mouse = getMemDCPoint();

		if (_ptMouse.x < CAMERAX && _ptMouse.y < CAMERAY)
		{
			for (int i = 0; i < TILEX * TILEY; i++)
			{
				if (PtInRect(&_tiles[i].rc, mouse)&& _tiles[i].object!=OBJ_TREE)
				{
					_tiles[i].objFrameX = NULL;
					_tiles[i].objFrameY = NULL;

					_tiles[i].object = OBJ_NONE;

					InvalidateRect(_hWnd, NULL, false);
					break;
				}
			}
		}
	}

	else if (KEYMANAGER->isOnceKeyDown('Y'))
	{
		for (int i = 0; i < TILEX * TILEY; i++)
		{
			_tiles[i].terrainFrameX = _currentTileT.x;
			_tiles[i].terrainFrameY = _currentTileT.y;

			_tiles[i].terrain = terrainSelect(_currentTileT.x, _currentTileT.y);
		}
	}

	else if (KEYMANAGER->isOnceKeyDown('U'))
	{
		for (int i = 0; i < TILEX * TILEY; i++)
		{
			if (_tiles[i].object != OBJ_TREE)
			{
				_tiles[i].objFrameX = NULL;
				_tiles[i].objFrameY = NULL;

				_tiles[i].object = OBJ_NONE;

				InvalidateRect(_hWnd, NULL, false);
			}
		}
	}

	for (int i = 0; i < TILEX * TILEY; i++)
	{
		_mouseTile[0].x = getMemDCPoint().x / 32;
		_mouseTile[0].y = getMemDCPoint().y / 32;
	}
		
}

void MapTool::render()
{
	IMAGEMANAGER->render("side", UIDC);
	IMAGEMANAGER->render("sample", UIDC, WINSIZEX - IMAGEMANAGER->findImage("sample")->getWidth()- SAMPLEX, SAMPLEY);
	
	// 버튼 렉트
	for (int i = 0; i < 7; i++)
	{
		//Rectangle(UIDC, _rc[i].left, _rc[i].top, _rc[i].right, _rc[i].bottom);
	}
	for (int i = 0; i < 7; i++)
	{
		IMAGEMANAGER->frameRender("button", UIDC, _rc[i].left, _rc[i].top ,0,0);
		if (_select == ROOM)
		{
			IMAGEMANAGER->frameRender("button", UIDC, _rc[0].left, _rc[0].top, 0, 1);
		}
		else if (_select == ROAD)
		{
			IMAGEMANAGER->frameRender("button", UIDC, _rc[1].left, _rc[1].top, 0, 1);
		}
		else if (_select == TERRAINDRAW|| _select == OBJDRAW)
		{
			IMAGEMANAGER->frameRender("button", UIDC, _rc[2].left, _rc[2].top, 0, 1);
		}
		else if (_select == ITEMDRAW)
		{
			IMAGEMANAGER->frameRender("button", UIDC, _rc[3].left, _rc[3].top, 0, 1);
		}
		if (_select == MONSTER)
		{
			IMAGEMANAGER->frameRender("button", UIDC, _rc[4].left, _rc[4].top, 0, 1);
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
	DrawText(UIDC, TEXT("길"), strlen("길"), &_rc[1], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	DrawText(UIDC, TEXT("타일"), strlen("타일"), &_rc[2], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	DrawText(UIDC, TEXT("아이템"), strlen("아이템"), &_rc[3], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	DrawText(UIDC, TEXT("몬스터"), strlen("몬스터"), &_rc[4], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	DrawText(UIDC, TEXT("세이브"), strlen("몬스터"), &_rc[5], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	DrawText(UIDC, TEXT("로드"), strlen("몬터"), &_rc[6], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	SelectObject(UIDC, oldFont);
	DeleteObject(font);


	// 지형
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (_tiles[i].rc.left < WINSIZEX + CAMERAMANAGER->getCameraCenter().x - WINSIZEX / 2 && _tiles[i].rc.top < WINSIZEY + CAMERAMANAGER->getCameraCenter().y - WINSIZEY / 2
			&& _tiles[i].rc.right > CAMERAMANAGER->getCameraCenter().x - WINSIZEX / 2 && _tiles[i].rc.bottom > CAMERAMANAGER->getCameraCenter().y - WINSIZEY / 2)
		IMAGEMANAGER->frameRender("map", DC, _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
		//if(i == 444)
	}

	// 오브젝트
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		// 오브젝트 속성이 아니면 그리지마
		if (_tiles[i].object == OBJ_NONE) continue;
		if (_tiles[i].rc.left < WINSIZEX + CAMERAMANAGER->getCameraCenter().x - WINSIZEX / 2 && _tiles[i].rc.top < WINSIZEY + CAMERAMANAGER->getCameraCenter().y - WINSIZEY / 2
			&& _tiles[i].rc.right > CAMERAMANAGER->getCameraCenter().x - WINSIZEX / 2 && _tiles[i].rc.bottom > CAMERAMANAGER->getCameraCenter().y - WINSIZEY / 2)
		{

			if (_tiles[i].object == OBJ_WALL)
				IMAGEMANAGER->frameRender("map", DC, _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].objFrameX, _tiles[i].objFrameY);
			else if (_tiles[i].object == OBJ_TREE)
				IMAGEMANAGER->frameRender("tree", DC, _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].objFrameX, _tiles[i].objFrameY);
		}
	}
	int x = _mouseTile[0].x - _mouseTile[1].x;
	int y = _mouseTile[0].y - _mouseTile[1].y;
	if (_mouseTile[0].x < _mouseTile[1].x) x *= -1;
	if (_mouseTile[0].y < _mouseTile[1].y) y *= -1;
	int x2=1;
	int y2=1;
	if (_drag !=0)
	{
		for (int i = 0; i <= y; i++)
		{
			for (int j = 0; j <= x; j++)
			{
				if (_mouseTile[0].y < _mouseTile[1].y) y2=-1;
				if (_mouseTile[0].x < _mouseTile[1].x) x2=-1;
				IMAGEMANAGER->findImage("tile")->render(DC, _tiles[_mouseTile[1].x + j*x2 + (_mouseTile[1].y + i*y2) * 100].rc.left, _tiles[_mouseTile[1].x + j * x2 + (_mouseTile[1].y + i * y2) * 100].rc.top);
				if (_drag == 2)
				{

				}
			}
		}
	}
	if (_drag == 2)
		_drag = 0;
	IMAGEMANAGER->findImage("tile")->render(DC, _tiles[_mouseTile[0].x + (_mouseTile[0].y) * 100].rc.left, _tiles[_mouseTile[0].x + (_mouseTile[0].y ) * 100].rc.top);

	if (KEYMANAGER->isStayKeyDown(VK_TAB))
	{
		_canMove = false;

		for (int i = 0; i < TILEX * TILEY; i++)
		{
			//Rectangle(DC,_tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].rc.right, _tiles[i].rc.bottom);
			char str[128];
			sprintf_s(str, "%d,%d", i % 100, i / 100);
			//TextOut(DC, _tiles[i].rc.left, _tiles[i].rc.top, str, strlen(str));
			SetTextColor(DC, RGB(10, 10, 10));
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

		/*for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; i++)
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
		_tiles[i].object = OBJ_NONE;
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
		_tiles[i].object = OBJ_NONE;
	}
}

void MapTool::setmap()
{
	POINT mouse = getMemDCPoint();
	for (int i = 0; i < 7; i++)
	{
		if (PtInRect(&_rc[i], _ptMouse))
		{
			if (i == 5)
			{
				save();
				break;
			}
			else if (i == 6)
			{
				load();
				break;
			}
			else 
			{
				if (i == 0) _select = ROOM;
				if (i == 1) _select = ROAD;
				if (i == 2) _select = OBJDRAW;
				if (i == 3) _select = ITEMDRAW;
				if (i == 4) _select = MONSTER;
				break;
			}
		}
	}

	for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; i++)
	{
		if (PtInRect(&_sampleTile[i].rctile, _ptMouse))
		{
			if (objSelect(_sampleTile[i].terrainFrameX, _sampleTile[i].terrainFrameY) == OBJ_NONE)
			{
				_currentTileT.x = _sampleTile[i].terrainFrameX;
				_currentTileT.y = _sampleTile[i].terrainFrameY;
				if (_select == TERRAINDRAW || _select == OBJDRAW)
				_select = TERRAINDRAW;
			}
			else
			{
				_currentTileO.x = _sampleTile[i].terrainFrameX;
				_currentTileO.y = _sampleTile[i].terrainFrameY;
				if (_select == TERRAINDRAW || _select == OBJDRAW)
				_select = OBJDRAW;
			}
			break;
		}
	}

	if (_ptMouse.x < CAMERAX&&_ptMouse.y < CAMERAY)
	{
		for (int i = 0; i < TILEX * TILEY; i++)
		{
			if (PtInRect(&_tiles[i].rc, mouse) && _tiles[i].object != OBJ_TREE)
			{
				if (_select == TERRAINDRAW)
				{
					_tiles[i].terrainFrameX = _currentTileT.x;
					_tiles[i].terrainFrameY = _currentTileT.y;

					_tiles[i].terrain = terrainSelect(_currentTileT.x, _currentTileT.y);
				
				}
				else if (_select == OBJDRAW)
				{
					_tiles[i].objFrameX = _currentTileO.x;
					_tiles[i].objFrameY = _currentTileO.y;

					_tiles[i].object = objSelect(_currentTileO.x, _currentTileO.y);
				}
				if (_select == ERASER)
				{
					_tiles[i].objFrameX = NULL;
					_tiles[i].objFrameY = NULL;

					_tiles[i].object = OBJ_NONE;
				}

				InvalidateRect(_hWnd, NULL, false);
				break;
			}
		}
	}
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


	return OBJ_NONE;
}

void MapTool::setTree()
{
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (_tiles[i].object == OBJ_TREE)
		{
			_tiles[i].object = OBJ_NONE;
		}
	}

	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j <  1; j++)
		{
			_tiles[i*100+j].objFrameX = _currentTileO.x;
			_tiles[i * 100 + j].objFrameY = _currentTileO.y;

			_tiles[i * 100 + j].object = OBJ_TREE;
			_tiles[i * 100 + j].position = POS_5;
		}
	}
	for (int i = 0; i < 100; i++)	//오른쪽이빈나무
	{
		for (int j = 1; j < 2; j++)
		{
			_tiles[i * 100 + j].objFrameX = _currentTileO.x;
			_tiles[i * 100 + j].objFrameY = _currentTileO.y;

			_tiles[i * 100 + j].object = OBJ_TREE;
			_tiles[i * 100 + j].position = POS_6;
		}
	}
	for (int i = 0; i < 100; i++)	//왼쪽이빈나무
	{
		for (int j = _currentXY.x+2; j < _currentXY.x+3; j++)
		{
			_tiles[i * 100 + j].objFrameX = _currentTileO.x;
			_tiles[i * 100 + j].objFrameY = _currentTileO.y;

			_tiles[i * 100 + j].object = OBJ_TREE;
			_tiles[i * 100 + j].position = POS_4;
		}
	}
	for (int i = 0; i <100; i++)
	{
		for (int j = _currentXY.x+3; j < 100; j++)
		{
			_tiles[i * 100 + j].objFrameX = _currentTileO.x;
			_tiles[i * 100 + j].objFrameY = _currentTileO.y;

			_tiles[i * 100 + j].object = OBJ_TREE;
			_tiles[i * 100 + j].position = POS_5;
		}
	}


	for (int i = 0; i <4; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			_tiles[i * 100 + j].objFrameX = _currentTileO.x;
			_tiles[i * 100 + j].objFrameY = _currentTileO.y;

			_tiles[i * 100 + j].object = OBJ_TREE;
			_tiles[i * 100 + j].position = POS_5;
		}
	}
	for (int i = 4; i <5; i++)		//아래쪽이빈나무
	{
		for (int j = 1; j < 100; j++)
		{
			_tiles[i * 100 + j].objFrameX = _currentTileO.x;
			_tiles[i * 100 + j].objFrameY = _currentTileO.y;

			_tiles[i * 100 + j].object = OBJ_TREE;
			if(j<_currentXY.x+2)
				_tiles[i * 100 + j].position = POS_8;
			else
				_tiles[i * 100 + j].position = POS_5;
		}
	}
	for (int i = _currentXY.y+5; i <_currentXY.y+6; i++)		//윗쪽이빈나무
	{
		for (int j = 1; j < 100; j++)
		{
			_tiles[i * 100 + j].objFrameX = _currentTileO.x;
			_tiles[i * 100 + j].objFrameY = _currentTileO.y;

			_tiles[i * 100 + j].object = OBJ_TREE;
			if (j<_currentXY.x + 2)
				_tiles[i * 100 + j].position = POS_2;
			else
				_tiles[i * 100 + j].position = POS_5;
		}
	}
	for (int i = _currentXY.y+6; i <100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			_tiles[i * 100 + j].objFrameX = _currentTileO.x;
			_tiles[i * 100 + j].objFrameY = _currentTileO.y;

			_tiles[i * 100 + j].object = OBJ_TREE;
			_tiles[i * 100 + j].position = POS_5;
		}
	}

	for (int i = 4; i <100; i++)
	{
		for (int j = 1; j < 100; j++)
		{
			if (i == 4 && j == 1)		//오른쪽아래가빈나무
			{
				_tiles[i * 100 + j].objFrameX = _currentTileO.x;
				_tiles[i * 100 + j].objFrameY = _currentTileO.y;

				_tiles[i * 100 + j].object = OBJ_TREE;
				_tiles[i * 100 + j].position = POS_11;
			}
			if (i == 4 && j == _currentXY.x+2)		//왼쪽아래가빈나무
			{
				_tiles[i * 100 + j].objFrameX = _currentTileO.x;
				_tiles[i * 100 + j].objFrameY = _currentTileO.y;

				_tiles[i * 100 + j].object = OBJ_TREE;
				_tiles[i * 100 + j].position = POS_12;
			}
			if (i == _currentXY.y+5 && j ==1)		//오른쪽위가빈나무
			{
				_tiles[i * 100 + j].objFrameX = _currentTileO.x;
				_tiles[i * 100 + j].objFrameY = _currentTileO.y;
				_tiles[i * 100 + j].position = POS_14;

				_tiles[i * 100 + j].object = OBJ_TREE;
			}
			if (i == _currentXY.y + 5 && j == _currentXY.x + 2)		//왼쪽위가빈나무
			{
				_tiles[i * 100 + j].objFrameX = _currentTileO.x;
				_tiles[i * 100 + j].objFrameY = _currentTileO.y;

				_tiles[i * 100 + j].object = OBJ_TREE;
				_tiles[i * 100 + j].position = POS_15;
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
				_tiles[i].objFrameX = 1+7*(_tree/11);
				_tiles[i].objFrameY =3+3*(_tree%11);
				break;
			case POS_4:
				_tiles[i].objFrameX =  7 * (_tree / 11);
				_tiles[i].objFrameY = 4 + 3 * (_tree % 11);
				break;
			case POS_5:
				_tiles[i].objFrameX = 1+7 * (_tree / 11);
				_tiles[i].objFrameY = 4 + 3 * (_tree % 11);
				break;
			case POS_6:
				_tiles[i].objFrameX = 2 + 7 * (_tree / 11);
				_tiles[i].objFrameY = 4 + 3 * (_tree % 11);
				break;
			case POS_8:
				_tiles[i].objFrameX = 1 + 7 * (_tree / 11);
				_tiles[i].objFrameY = 5 + 3 * (_tree % 11);
				break;
			case POS_11:
				_tiles[i].objFrameX = 4 + 7 * (_tree / 11);
				_tiles[i].objFrameY = 3 + 3 * (_tree % 11);
				break;
			case POS_12:
				_tiles[i].objFrameX = 5 + 7 * (_tree / 11);
				_tiles[i].objFrameY = 3 + 3 * (_tree % 11);
				break;
			case POS_14:
				_tiles[i].objFrameX = 4 + 7 * (_tree / 11);
				_tiles[i].objFrameY = 4 + 3 * (_tree % 11);
				break;
			case POS_15:
				_tiles[i].objFrameX = 5 + 7 * (_tree / 11);
				_tiles[i].objFrameY = 4 + 3 * (_tree % 11);
				break;
			default:
				break;
			}
		}
	}
}

MapTool::MapTool(){}

MapTool::~MapTool(){}
