#include "stdafx.h"
#include "monsterManager.h"


HRESULT monsterManager::init()
{
	dexSetting();

	for (int i = 0; i < 10; i++)
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
	tagMon	mon;
	ZeroMemory(&mon, sizeof(tagMon));
	mon.num = _dex[i].num;
	mon.hp = _dex[i].hp;
	mon.act = false;
	_vDmon.push_back(mon);
}

void monsterManager::addAmon(int i)
{
	tagMon	mon;
	ZeroMemory(&mon, sizeof(tagMon));
	mon.num = _dex[i].num;
	mon.hp = _dex[i].hp;
	mon.act = false;
	_vAmon.push_back(mon);
}

void monsterManager::eraseDmon(int arrNum)
{
	_vDmon.erase(_vDmon.begin() + arrNum);
}

void monsterManager::eraseAmon(int arrNum)
{
	_vAmon.erase(_vAmon.begin() + arrNum);
}

void monsterManager::dexSetting()
{
	dexSet(0, IMAGEMANAGER->findImage("a0"), "이상해씨", GRASS, PointMake(1, 1), 10, 10, 1, 1,5, true, true, true, true, true);
	dexSet(1, IMAGEMANAGER->findImage("a1"), "이상해풀", GRASS, PointMake(2, 2), 15, 15, 2, 2,10, true, true, true, true, true);
	dexSet(2, IMAGEMANAGER->findImage("a2"), "이상해꽃", GRASS, PointMake(3, 3), 20, 20, 3, 3,15, false, true, true, true, true);
}

void monsterManager::dexSet(int i, image* img, string name, TYPE type, POINT size, int fhp, int power, int spd, int atSpd,int food, bool evo, bool dir0, bool dir1,bool dir2,bool dir3)
{
	_dex[i].num = i;
	_dex[i].img = new image;
	_dex[i].img = img;
	_dex[i].name = name;
	_dex[i].type = type;
	_dex[i].size = size;
	_dex[i].hp = fhp;
	_dex[i].power = power;
	_dex[i].spd = spd;
	_dex[i].atSpd = atSpd;
	_dex[i].food = food;
	_dex[i].evolution = evo;
	_dex[i].dir[0] = dir0;
	_dex[i].dir[1] = dir1;
	_dex[i].dir[2] = dir2;
	_dex[i].dir[3] = dir3;
}

void monsterManager::evolution(bool ad, int i)
{
	if (ad == 0&& _dex[_vDmon[i].num].evolution==true)
	{
		_vDmon[i].num +=1;
	}
	else if(ad == 1 && _dex[_vAmon[i].num].evolution == true)
	{
		_vAmon[i].num += 1;
	}
}

monsterManager::monsterManager()
{
}


monsterManager::~monsterManager()
{
}
