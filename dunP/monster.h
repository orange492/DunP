#pragma once
#include "gameNode.h"
#include "progressBar.h"

enum DIR {DOWN,UP,LEFT,RIGHT,LB,RB,LT,RT};

class monster : public gameNode
{
	//image* _img;
	//TYPE _type;
	progressBar* _hpbar;
	tagMonster _dex;
	loca	_tile;
	RECT _rc;
	DIR _dir;
	int _num;
	int _hp;
	int _spd;
	//int _power;
	//int _spd;
	//int _atSpd;
	bool _act;

	int _count;
	int _currentX;
	//int _currentY;

	vector<int>				_vRoad;
	vector<int>::iterator	_viRoad;

public:
	HRESULT init(int id, int num, tagMonster dex, int hp, int dir, vector<int> road);
	void release();
	void update();
	void move();
	void render();

	bool getAct() { return _act; }

	monster();
	~monster();
};

