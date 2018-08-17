#pragma once
#include "monster.h"
#include "gameNode.h"

class MapTool;
class star;

class monsterManager : public gameNode
{
#define DEXNUM 15

	MapTool * _mapTool;
	star * _star;

	tagMonster _dex[DEXNUM];

	vector<tagMon2>				_vDmon;
	vector<tagMon2>::iterator	_viDmon;

	vector<monster*>			_vEmon;
	vector<monster*>::iterator	_viEmon;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void setHave(int num, int i) { _vDmon[num].have = i; }
	void addDmon(int i);
	void addEmon(int id, int i, int dir, vector<int> road);

	void setVDmon(vector<tagMon2> mon) { _vDmon = mon; }

	void dexSetting();
	void dexSet(int i, image * img, string name, TYPE type, POINT size, int frameX, int frameNum, int fhp, int power, float spd, float atSpd, int food, int price, bool evo, bool dir0, bool dir1, bool dir2, bool dir3);
	void eraseDmon(int arrNum);
	void deleteEmon(int i);
	void eraseEmon();
	tagMonster getDex(int i) { return _dex[i]; }
	vector<tagMon2>	getVDmon() { return _vDmon; }
	vector<monster*>	getEmon() { return _vEmon; }
	void setMtMemoryAddressLink(MapTool* mt) { _mapTool = mt; }
	void setStarMemoryAddressLink(star* star) { _star = star; }

	monsterManager();
	~monsterManager();
};

