#include "stdafx.h"
#include "star.h"
#include "MapTool.h"

//엔드만나면 넣어주는거
//벽아래는 대각선안되게
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

}

void star::render()
{

}

void star::setTiles(int start, int end, int endStart, int endX, int endY)
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
	bool out=0;

	for (int i = 0; i < _mapTool->getCurrentXY().y+6; ++i)
	{
		for (int j = 0; j <TILEX; ++j)
		{
			out = 0;
			tagNode node;
			node.parents = node.F = node.G = node.open = 0;
			node.H = setH(j,i,x,y);

			if ((_mapTool->getTiles()[j + i * TILEX].object != OBJ_NULL || _mapTool->getTiles()[j + i * TILEX].terrain == TR_NULL) && j + i * TILEX != end)
			{
				if (endStart != 0)
				{
					if (_mapTool->getTiles()[j + i * TILEX].object == OBJ_MON)
					{
						for (int k = 0; k < endX + 2; k++)
						{
							for (int l = 0; l < endY + 2; l++)
							{
								if (j + i * TILEX == endStart + l + k * 100)
								{
									node.type = BLANK;
									out = 1;
									break;
								}
								else
									node.type = WALL;
							}
							if (out == 1)
								break;
						}
					}
					else
						node.type = WALL;
				}
				else
				{
					if (_mapTool->getTiles()[j + i * TILEX].object == OBJ_MON&& _mapTool->getTiles()[j + i * TILEX].monPos==MPOS_0)
						node.type = BLANK;
					else
						node.type = WALL;
				}
			}
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
			{
				if(!(_vRoad.size()==0&& _mapTool->getTiles()[Road].monPos!=MPOS_0))
					_vRoad.push_back(Road);
			}
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

vector<int> star::findRoad(int start, int end, int endStart, int endX,int endY)
{
	setTiles(start, end, endStart, endX,endY);
	while (_vRoad.size() == 0)
	{
		pathFinder();
		if (_currentTile == TILEX+1)
			break;
	}
	return _vRoad;
}

vector<int> star::findRoad(int start, int end)
{
	setTiles(start, end,0,0,0);
	while (_vRoad.size() == 0)
	{
		pathFinder();
		if (_currentTile == TILEX + 1)
			break;
	}
	return _vRoad;
}