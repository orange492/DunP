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
		RECT rc;
		int fhp;
		int hp;
		int power;
		int spd;
		int atSpd;
		int food;
		bool evolution;
		bool active;
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
	void eraseDmon(int arrNum);
	void eraseAmon(int arrNum);
	void dexSet(int i, image * img, string name, TYPE type, POINT size, int fhp, int power, int spd, int atSpd, int food, bool evo, bool act, bool dir0, bool dir1, bool dir2, bool dir3);
	void evolution(bool ad, int i);
	tagMonster getDex(int i) { return _dex[i]; }
	vector<tagMonster>	getVDmon() { return _vDmon; }

	monsterManager();
	~monsterManager();
};

