#pragma once
class monsterManager
{
#define DEXNUM 2
	enum TYPE	{GRASS, FIRE, WATER};

	struct tagMonster
	{
		int num;
		image* img;
		string name;
		TYPE type;
		POINT size;
		bool evolution;
		int fhp;
		int hp;
		int power;
		int spd;
		int atSpd;
		bool dir[4];
	};

	tagMonster _dex[DEXNUM];
	vector<tagMonster>				_vAmon;
	vector<tagMonster>::iterator	_viAmon;
	vector<tagMonster>				_vDmon;
	vector<tagMonster>::iterator	_viDmon;
	vector<tagMonster>				_vEmon;
	vector<tagMonster>::iterator	_viEmon;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void addDmon(int i);
	void addAmon(int i);

	void dexSetting();
	void dexSet(int i, image * img, string name, TYPE type, POINT size, bool evo, int fhp, int power, int spd, int atSpd, bool dir0, bool dir1, bool dir2, bool dir3);
	tagMonster getDex(int i) { return _dex[i]; }
	vector<tagMonster>	getVDmon() { return _vDmon; }

	monsterManager();
	~monsterManager();
};

