#include "stdafx.h"
#include "star.h"
#include "MapTool.h"

//엔드만나면 넣어주는거/완
//벽아래는 대각선안되게/완
//아무데도갈수없을때/완

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
			_viList = _vList.erase(_viList);
		for (_viOpen = _vOpen.begin(); _viOpen != _vOpen.end();)
			_viOpen = _vOpen.erase(_viOpen);
		for (_viRoad = _vRoad.begin(); _viRoad != _vRoad.end();)
			_viRoad = _vRoad.erase(_viRoad);
	} //벡터들에 값이 들어있다면 다 지워줌


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
			node.H = setH(j,i,x,y); //현재 타일 위치와 end타일 위치 비교로 H계산

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
			}  //타일에 벽이나 몬스터가 있거나 플로어가 없으면 벽 타입으로 지정
			else if (j + i * TILEX == start)
			{
				node.type = START; //시작점이면 시작타입. 현재타일을 시작노드로
				_currentTile = start;
			}
			else if (j + i * TILEX == end)
				node.type = END; //끝점이면 끝타입
			else
				node.type = BLANK; // 벽도 시작점도 끝점도 아니면 빈칸 타입


			_vList.push_back(node); //벡터에 담기
		}
	}
}

void star::pathFinder()
{
	_vList[_currentTile].open = 2; //현재타일로 선택된 노드는 아얘 닫아줌

	//인접타일 열어준다
	if (_vList[_currentTile-1].type!=WALL&& _vList[_currentTile- TILEX].type != WALL)
		addOpenList(_currentTile - TILEX-1, 0); //대각선으로 이동 불가능할 때는 안 연다
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
		} //열린 노드 중 첫 노드를 임시 변수에 담음
		else if (_vList[*_viOpen].F < f&&_vList[*_viOpen].open == 1)
		{
			f = _vList[*_viOpen].F;
			num = *_viOpen;
		} //임시 변수보다 F가 작으면 그걸 임시 변수에 담음
		else if (_vList[*_viOpen].F == f&&_vList[*_viOpen].open == 1)
		{
			if(_vList[*_viOpen].H < h)
			f = _vList[*_viOpen].F;
			h = _vList[*_viOpen].H;
			num = *_viOpen;
		} //F가 같으면 H가 더 적은 노드(끝점에 더 가까운 노드)를 담음
	}
	for (_viOpen = _vOpen.begin(); _viOpen != _vOpen.end(); _viOpen++)
	{
		if (_currentTile == *_viOpen)
		{
			_viOpen = _vOpen.erase(_viOpen);
			break;
		} //현재타일(열렸다가 다시 닫힌 노드)은 열린 노드 벡터에서 지워줌
	}
	_currentTile = num;
}

void star::addOpenList(int num, bool side)
{
	int addG= _vList[_currentTile].G;
	side == true ? addG += 10 : addG += 14.14; //이동거리에 따라 G를 더해줌

	if (_vList[num].type == WALL) return;
	if (_vList[num].type == START) return;
	if (_vList[num].open == 2) return;  //벽, 시작점, 닫힌타일이면 함수 나감
	if (_vList[num].open == 1)
	{
		if (addG < _vList[num].G)
		{
			_vList[num].G = addG;
			_vList[num].parents = _currentTile;
			_vList[num].F = _vList[num].G + _vList[num].H;
		} //이미 열려있으면 G값이 더 작은지 보고 작으면 G값과 부모타일을 재설정
	}
	else
	{
		_vList[num].open = 1;
		_vOpen.push_back(num);
		_vList[num].G = addG;
		_vList[num].parents = _currentTile;
		_vList[num].F = _vList[num].G + _vList[num].H;
	} //닫혀있으면 열어줌

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
		} //끝점 노드에 도달하면 여기까지의 길을 road벡터에 담음
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
			break; //길이 막혔을 경우
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