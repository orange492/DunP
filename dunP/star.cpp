#include "stdafx.h"
#include "star.h"
#include "MapTool.h"

//대각선때문에 막힐때 상하좌우를 커렌트타일로해주기//취소
//중간에 같으면 임시저장//취소
//엔드만나면 넣어주는거
//벽아래는 대각선안되게
//가던길계속가기
//아무데도갈수없을때

star::star()
{
}

star::~star()
{
}

HRESULT star::init()
{
	
	return S_OK;
}

void star::release()
{
}

void star::update()
{
	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		findRoad(603, 805);
	}
}

void star::render()
{
	//SetTextColor(DC, RGB(10, 10, 10));
	//SetBkMode(DC, TRANSPARENT);
	//HFONT font, oldFont;
	//font = CreateFont(15, 0, 0, 0, 100, 0, 0, 0, DEFAULT_CHARSET,
	//	OUT_STRING_PRECIS, CLIP_CHARACTER_PRECIS, PROOF_QUALITY,
	//	DEFAULT_PITCH | FF_SWISS, TEXT("HY얕은샘물M"));
	//oldFont = (HFONT)SelectObject(DC, font);

	//char str[128];
	////char str2[128];
	////char str3[128];
	////for (int i = 0; i <_vList.size(); ++i)
	////{
	////	if (i > 3000) break;
	////	if (_vList[i].open == 1)
	////		IMAGEMANAGER->findImage("tile")->render(DC,_mapTool->getTiles()[i].rc.left, _mapTool->getTiles()[i].rc.top);
	////	else if (_vList[i].open == 2)
	////		IMAGEMANAGER->findImage("tile2")->render(DC, _mapTool->getTiles()[i].rc.left, _mapTool->getTiles()[i].rc.top);
	////	//else
	////	//	sprintf_s(str, " ");
	////	sprintf_s(str, "%d", (int)_vList[i].F);
	////	sprintf_s(str2, "%d", (int)_vList[i].G);
	////	sprintf_s(str3, "%d", (int)_vList[i].H);
	////	//TextOut(DC, _mapTool->getTiles()[i].rc.left, _mapTool->getTiles()[i].rc.top, str, strlen(str));
	////	DrawText(DC, TEXT(str), strlen(str), &RectMake(_mapTool->getTiles()[i].rc.left+10, _mapTool->getTiles()[i].rc.top, 100, 50), DT_LEFT | DT_TOP | DT_SINGLELINE);
	////	DrawText(DC, TEXT(str2), strlen(str), &RectMake(_mapTool->getTiles()[i].rc.left + 10, _mapTool->getTiles()[i].rc.top+10, 100, 50), DT_LEFT | DT_TOP | DT_SINGLELINE);
	////	DrawText(DC, TEXT(str3), strlen(str), &RectMake(_mapTool->getTiles()[i].rc.left + 10, _mapTool->getTiles()[i].rc.top+20, 100, 50), DT_LEFT | DT_TOP | DT_SINGLELINE);
	////	//SetBkMode(DC, TRANSPARENT);
	////	//_mapTool->getTiles()[_vList[i].num].rc.left
	////	//_vList[i];
	////}

	///*for (int i = 0; i < _vRoad.size(); ++i)
	//{
	//	sprintf_s(str, "%d", _vRoad[i]);
	//	TextOut(DC, _mapTool->getTiles()[_vRoad[i]].rc.left, _mapTool->getTiles()[_vRoad[i]].rc.top, str, strlen(str));
	//}*/

	//SelectObject(DC, oldFont);
	//DeleteObject(font);
}

void star::setTiles(int start, int end)
{
	if (_vList.size() > 0)
	{
		for (_viList = _vList.begin(); _viList != _vList.end();)
		{
			_viList = _vList.erase(_viList);
		}
		for (_viOpen = _vOpen.begin(); _viOpen != _vOpen.end();)
		{
			_viOpen = _vOpen.erase(_viOpen);
		}
		for (_viRoad = _vRoad.begin(); _viRoad != _vRoad.end();)
		{
			_viRoad = _vRoad.erase(_viRoad);
		}
	}

	int x, y;
	x = end % TILEX;
	y = end / TILEX;

	for (int i = 0; i < _mapTool->getCurrentXY().y+6; ++i)
	{
		for (int j = 0; j <TILEX; ++j)
		{
			tagNode node;
			node.parents = node.F = node.G = node.open = 0;
			node.H = setH(j,i,x,y);

			if ((_mapTool->getTiles()[j + i * TILEX].object != OBJ_NULL|| _mapTool->getTiles()[j + i * TILEX].terrain==TR_NULL)&& j + i * TILEX!=end)
				node.type = WALL;
			else if (j + i * TILEX == start)
			{
				node.type = START;
				_currentTile = start;
			}
			else if (j + i * TILEX == end)
				node.type = END;
			else
				node.type = BLANK;

			_vList.push_back(node);
		}
	}
}

void star::pathFinder()
{
	_vList[_currentTile].open = 2;

	if (_vList[_currentTile-1].type!=WALL&& _vList[_currentTile- TILEX].type != WALL)
		addOpenList(_currentTile - TILEX-1, 0);
	addOpenList(_currentTile - TILEX, 1);
	if (_vList[_currentTile + 1].type != WALL && _vList[_currentTile - TILEX].type != WALL)
		addOpenList(_currentTile - TILEX+1, 0);
	addOpenList(_currentTile - 1, 1);
	addOpenList(_currentTile + 1, 1);
	if (_vList[_currentTile - 1].type != WALL && _vList[_currentTile + TILEX].type != WALL)
		addOpenList(_currentTile + TILEX-1, 0);
	addOpenList(_currentTile + TILEX, 1);
	if (_vList[_currentTile + 1].type != WALL && _vList[_currentTile + TILEX].type != WALL)
		addOpenList(_currentTile + TILEX+1, 0);

	/*if (_sideNum == 0)
	{*/
	int f = 0;
	int h = 0;
	int num= TILEX+1;

	for (_viOpen = _vOpen.begin(); _viOpen != _vOpen.end(); _viOpen++)
	{
		if (f == 0)
		{
			f = _vList[*_viOpen].F;
			h = _vList[*_viOpen].H;
			num = *_viOpen;
		}
		else if (_vList[*_viOpen].F < f&&_vList[*_viOpen].open == 1)
		{
			f = _vList[*_viOpen].F;
			num = *_viOpen;
		}
		else if (_vList[*_viOpen].F == f&&_vList[*_viOpen].open == 1)
		{
			if(_vList[*_viOpen].H < h)
			f = _vList[*_viOpen].F;
			h = _vList[*_viOpen].H;
			num = *_viOpen;
		}
	}
	for (_viOpen = _vOpen.begin(); _viOpen != _vOpen.end(); _viOpen++)
	{
		if (_currentTile == *_viOpen)
		{
			_viOpen = _vOpen.erase(_viOpen);
			break;
		}
	}
	_currentTile = num;
}

void star::addOpenList(int num, bool side)
{
	int addG= _vList[_currentTile].G;
	side == true ? addG += 10 : addG += 14.14;

	if (_vList[num].type == WALL) return;
	if (_vList[num].type == START) return;
	if (_vList[num].open == 2) return;
	if (_vList[num].open == 1)
	{
		if (addG < _vList[num].G)
		{
			_vList[num].G = addG;
			_vList[num].parents = _currentTile;
			_vList[num].F = _vList[num].G + _vList[num].H;
		}
	}
	else
	{
		_vList[num].open = 1;
		_vOpen.push_back(num);
		_vList[num].G = addG;
		_vList[num].parents = _currentTile;
		_vList[num].F = _vList[num].G + _vList[num].H;
	}

	if (_vList[num].type == END)
	{
		int Road = num;
		while (_vList[Road].type != START)
		{
			if(Road!=num)
				_vRoad.push_back(Road);
			Road = _vList[Road].parents;
		}
		_vRoad.push_back(Road);
		return;
	}
}

int star::setH(int x1, int y1, int x2, int y2)
{
	int x, y;
	x=x2 - x1 ;
	y=y2 - y1 ;
	if (x < 0) x *= -1;
	if (y < 0) y *= -1;
	
	return 10 * (x + y);
}

vector<int> star::findRoad(int start, int end)
{
	setTiles(start, end);
	while (_vRoad.size() == 0)
	{
		pathFinder();
		if (_currentTile == TILEX+1)
			break;
	}
	return _vRoad;
}