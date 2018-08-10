#pragma once
#include "gameNode.h"

class MapTool;

enum NODE {BLANK, WALL, START, END};

struct tagNode
{
	NODE type;
	int	parents;
	float F;
	float G;
	float H;
	int open;
};

class star : public gameNode
{
	MapTool * _mapTool;

	vector<tagNode>				_vList;
	vector<tagNode>::iterator	_viList; //ÀüÃ¼ ¸Ê ´ã´Â º¤ÅÍ

	vector<int>					_vOpen;
	vector<int>::iterator		_viOpen;

	vector<int>					_vRoad;
	vector<int>::iterator		_viRoad;

	int _currentTile;
	//int _sideF;
	//int _sideNum;

public:
	star();
	~star();

	HRESULT init();
	void release();
	void update();
	void render();

	void setTiles(int start, int end, int endStart, int endX, int endY);
	void pathFinder();
	void addOpenList(int num, bool side);
	int setH(int x1, int y1, int x2, int y2);
	vector<int> findRoad(int start, int end, int endStart, int endX, int endY);
	vector<int> findRoad(int start, int end);
	void setMtMemoryAddressLink(MapTool* mt) { _mapTool = mt; }
};

