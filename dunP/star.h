#pragma once
#include "gameNode.h"

class MapTool;

enum NODE { BLANK, WALL, START, END }; //���� ��ĭ, ��, ������, �������� ����

struct tagNode
{
	NODE type; //��� Ÿ��
	int	parents; //�θ� ���
	float F; //G+H
	float G; //���������� ���� ������ �Ÿ�
	float H; //���� ������ �������� ��ֹ��� ���� �������� �� �Ÿ�
	int open; //���� ������� ����(0�ȿ���, 1����, 2�ٽ� ����)
};

class star : public gameNode
{
	MapTool * _mapTool; //���� Ŭ������ ���漱�� �� �ּҰ��� �޾ƿ� �����ߴ�.

	vector<tagNode>				_vList;
	vector<tagNode>::iterator	_viList; //��ü �� ��� ����

	vector<int>					_vOpen;
	vector<int>::iterator		_viOpen; //���� ����� Ÿ�Ϲ�ȣ�� ��� ����

	vector<int>					_vRoad;
	vector<int>::iterator		_viRoad; //���������� �ִܰŸ� �� ��� ����

	int _currentTile; //���� Ÿ��

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