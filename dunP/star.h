#pragma once
#include "gameNode.h"

class MapTool;

enum NODE { BLANK, WALL, START, END }; //노드는 빈칸, 벽, 시작점, 끝점으로 나뉨

struct tagNode
{
	NODE type; //노드 타입
	int	parents; //부모 노드
	float F; //G+H
	float G; //시작점부터 현재 노드까지 거리
	float H; //현재 노드부터 끝점까지 장애물이 없다 가정했을 때 거리
	int open; //열린 노드인지 여부(0안열림, 1열림, 2다시 닫힘)
};

class star : public gameNode
{
	MapTool * _mapTool; //맵툴 클래스를 전방선언 후 주소값을 받아와 연결했다.

	vector<tagNode>				_vList;
	vector<tagNode>::iterator	_viList; //전체 맵 담는 벡터

	vector<int>					_vOpen;
	vector<int>::iterator		_viOpen; //열린 노드의 타일번호를 담는 벡터

	vector<int>					_vRoad;
	vector<int>::iterator		_viRoad; //최종적으로 최단거리 길 담는 벡터

	int _currentTile; //현재 타일

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