#include "stdafx.h"
#include "monsterManager.h"


HRESULT monsterManager::init()
{
	dexSetting();

	for (int i = 0; i < 20; i++)
	{
		addDmon(0);
		addDmon(1);
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

void monsterManager::dexSetting()
{
	dexSet(0, IMAGEMANAGER->findImage("a0"), "이상해씨", GRASS, PointMake(1, 1), true, 10, 10, 1, 1, true, true, true, true);
	dexSet(1, IMAGEMANAGER->findImage("a1"), "이상해풀", GRASS, PointMake(2, 2), true, 10, 10, 1, 1, true, true, true, true);
}

void monsterManager::dexSet(int i, image* img, string name, TYPE type, POINT size,bool evo, int fhp, int power, int spd, int atSpd,bool dir0, bool dir1,bool dir2,bool dir3)
{
	_dex[i].num = i;
	_dex[i].img = new image;
	_dex[i].img = img;
	_dex[i].name = name;
	_dex[i].type = type;
	_dex[i].size = size;
	_dex[i].evolution = evo;
	_dex[i].fhp = fhp;
	_dex[i].hp = _dex[i].fhp;
	_dex[i].power = power;
	_dex[i].spd = spd;
	_dex[i].atSpd = atSpd;
	_dex[i].dir[0] = dir0;
	_dex[i].dir[1] = dir1;
	_dex[i].dir[2] = dir2;
	_dex[i].dir[3] = dir3;
}

monsterManager::monsterManager()
{
}


monsterManager::~monsterManager()
{
}
