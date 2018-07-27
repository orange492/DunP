#pragma once
class monsterManager
{
#define DEXNUM 3
	enum TYPE	{GRASS, FIRE, WATER};

	struct tagMonster
	{
		int num;
		image* img;
		string name;
		TYPE type;
		POINT size;
		int hp;
		int power;
		int spd;
		int atSpd;
		int food;
		bool evolution;
		bool dir[4];
	};

	struct tagMon
	{
		int num;
		int hp;
		RECT rc;
		bool act;
	};

	tagMonster _dex[DEXNUM];
	vector<tagMon>				_vAmon;
	vector<tagMon>::iterator	_viAmon;
	vector<tagMon>				_vDmon;
	vector<tagMon>::iterator	_viDmon;
	vector<tagMon>				_vEmon;
	vector<tagMon>::iterator	_viEmon;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void addDmon(int i);
	void addAmon(int i);

	void dexSetting();
	void eraseDmon(int arrNum);
	void eraseAmon(int arrNum);
	void dexSet(int i, image * img, string name, TYPE type, POINT size, int fhp, int power, int spd, int atSpd, int food, bool evo, bool dir0, bool dir1, bool dir2, bool dir3);
	void evolution(bool ad, int i);
	tagMonster getDex(int i) { return _dex[i]; }
	vector<tagMon>	getVDmon() { return _vDmon; }

	monsterManager();
	~monsterManager();
};

