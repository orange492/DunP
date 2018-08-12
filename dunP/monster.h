#pragma once
#include "gameNode.h"
#include "progressBar.h"

class monster : public gameNode
{
	//image* _img;
	//TYPE _type;
	progressBar* _hpbar;
	tagMonster _dex;
	POINTFLOAT	_tile;
	RECT _rc;
	DIR _dir;
	int _loca;
	int _hp;
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
	HRESULT init(int id, tagMonster dex, int hp, int dir, vector<int> road);
	void release();
	void update();
	void move();
	void render();

	void eraseRoad();

	void setAct(int act) { _act = act; }
	void setHp(int hp) { _hp = hp; }
	void setDir(DIR dir) { _dir = dir; }
	void setRoad(vector<int> road) { _vRoad = road; }

	vector<int> getRoad() { return _vRoad; }
	RECT getRc() { return _rc; }
	tagMonster getDex() { return _dex; }
	int getLoca() { return _loca; }
	int getHp() { return _hp; }
	int getCount() { return _count; }
	bool getAct() { return _act; }

	monster();
	~monster();
};

