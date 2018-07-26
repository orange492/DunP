#include "stdafx.h"
#include "monsterManager.h"


HRESULT monsterManager::init()
{
	dexSetting();

	for (int i = 0; i < 2; i++)
	{
		addDmon(0);
		addDmon(0);
		addDmon(1);
	}
	
	return S_OK;
}

void monsterManager::release()
{
}

void monsterManager::update()
{
}

void monsterManager::render()
{
}

void monsterManager::addDmon(int i)
{
	tagMonster	mon;
	ZeroMemory(&mon, sizeof(tagMonster));
	mon = _dex[i];
	mon.name = _dex[i].name;
	_vDmon.push_back(mon);
}

void monsterManager::addAmon(int i)
{
	tagMonster	mon;
	ZeroMemory(&mon, sizeof(tagMonster));
	mon = _dex[i];
	mon.name = _dex[i].name;
	_vAmon.push_back(mon);
}

void monsterManager::eraseDmon(int arrNum)
{
	_vDmon.erase(_vDmon.begin() + arrNum);
	
}

void monsterManager::eraseAmon(int arrNum)
{
	_viAmon = _vAmon.begin() + arrNum;
	_vAmon.erase(_viAmon);
}

void monsterManager::dexSetting()
{
	dexSet(0, IMAGEMANAGER->findImage("a0"), "이상해씨", GRASS, PointMake(1, 1), 10, 10, 1, 1,5, true,false, true, true, true, true);
	dexSet(1, IMAGEMANAGER->findImage("a1"), "이상해풀", GRASS, PointMake(2, 2), 15, 15, 2, 2,10, true,false, true, true, true, true);
	dexSet(2, IMAGEMANAGER->findImage("a2"), "이상해꽃", GRASS, PointMake(3, 3), 20, 20, 3, 3,15, false,false, true, true, true, true);
}

void monsterManager::dexSet(int i, image* img, string name, TYPE type, POINT size, int fhp, int power, int spd, int atSpd,int food, bool evo, bool act, bool dir0, bool dir1,bool dir2,bool dir3)
{
	_dex[i].num = i;
	_dex[i].img = new image;
	_dex[i].img = img;
	_dex[i].name = name;
	_dex[i].type = type;
	_dex[i].size = size;
	_dex[i].fhp = fhp;
	_dex[i].hp = _dex[i].fhp;
	_dex[i].power = power;
	_dex[i].spd = spd;
	_dex[i].atSpd = atSpd;
	_dex[i].food = food;
	_dex[i].evolution = evo;
	_dex[i].active = act;
	_dex[i].dir[0] = dir0;
	_dex[i].dir[1] = dir1;
	_dex[i].dir[2] = dir2;
	_dex[i].dir[3] = dir3;
}

void monsterManager::evolution(bool ad, int i)
{
	if (ad == 0)
	{
		_vDmon[i].num +=1;
		_vDmon[i].img = _dex[_vDmon[i].num].img;
		_vDmon[i].name = _dex[_vDmon[i].num].name;
		_vDmon[i].type = _dex[_vDmon[i].num].type;
		_vDmon[i].size = _dex[_vDmon[i].num].size;
		_vDmon[i].fhp = _dex[_vDmon[i].num].fhp;
		_vDmon[i].hp = _dex[_vDmon[i].num].fhp;
		_vDmon[i].power = _dex[_vDmon[i].num].power;
		_vDmon[i].spd = _dex[_vDmon[i].num].spd;
		_vDmon[i].atSpd = _dex[_vDmon[i].num].atSpd;
		_vDmon[i].food = _dex[_vDmon[i].num].food;
		_vDmon[i].evolution = _dex[_vDmon[i].num].evolution;
		_vDmon[i].dir[0] = _dex[_vDmon[i].num].dir[0];
		_vDmon[i].dir[1] = _dex[_vDmon[i].num].dir[1];
		_vDmon[i].dir[2] = _dex[_vDmon[i].num].dir[2];
		_vDmon[i].dir[3] = _dex[_vDmon[i].num].dir[3];
	}
	else
	{
		_vAmon[i].num += 1;
		_vAmon[i].img = _dex[_vDmon[i].num].img;
		_vAmon[i].name = _dex[_vDmon[i].num].name;
		_vAmon[i].type = _dex[_vDmon[i].num].type;
		_vAmon[i].size = _dex[_vDmon[i].num].size;
		_vAmon[i].fhp = _dex[_vDmon[i].num].fhp;
		_vAmon[i].hp = _dex[_vDmon[i].num].fhp;
		_vAmon[i].power = _dex[_vDmon[i].num].power;
		_vAmon[i].spd = _dex[_vDmon[i].num].spd;
		_vAmon[i].atSpd = _dex[_vDmon[i].num].atSpd;
		_vAmon[i].food = _dex[_vDmon[i].num].food;
		_vAmon[i].evolution = _dex[_vDmon[i].num].evolution;
		_vAmon[i].dir[0] = _dex[_vDmon[i].num].dir[0];
		_vAmon[i].dir[1] = _dex[_vDmon[i].num].dir[1];
		_vAmon[i].dir[2] = _dex[_vDmon[i].num].dir[2];
		_vAmon[i].dir[3] = _dex[_vDmon[i].num].dir[3];
	}
}

monsterManager::monsterManager()
{
}


monsterManager::~monsterManager()
{
}
