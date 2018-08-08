#pragma once
#include "monster.h"
#include "gameNode.h"

class monsterManager : public gameNode
{
#define DEXNUM 3

	struct tagMon
	{
		int num;
		int have;
		int hp;
		//RECT rc;
		//bool act;
	};

	tagMonster _dex[DEXNUM];

	vector<monster*>			_vAmon;
	vector<monster*>::iterator	_viAmon;

	vector<tagMon>				_vDmon;
	vector<tagMon>::iterator	_viDmon;

	vector<monster*>			_vEmon;
	vector<monster*>::iterator	_viEmon;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void setHave(int num, int i) { _vDmon[num].have = i; }
	void addDmon(int i);
	void addAmon(int i);
	void addEmon(int id, int i, int dir, vector<int> road);

	void dexSetting();
	void eraseDmon(int arrNum);
	void eraseAmon(int arrNum);
	void dexSet(int i, image * img, string name, TYPE type, POINT size, int fhp, int power, float spd, float atSpd, int food, bool evo, bool dir0, bool dir1, bool dir2, bool dir3);
	//void evolution(bool ad, int i);
	tagMonster getDex(int i) { return _dex[i]; }
	vector<tagMon>	getVDmon() { return _vDmon; }

	monsterManager();
	~monsterManager();
};
