#include "stdafx.h"
#include "monsterManager.h"


HRESULT monsterManager::init()
{
	dexSetting();

	for (int i = 0; i < 5; i++)
	{
		addDmon(1);
		addDmon(0);
		addDmon(0);
	}
	//addEmon(0);
	
	return S_OK;
}

void monsterManager::release()
{
}

void monsterManager::update()
{
	for (_viEmon = _vEmon.begin(); _viEmon != _vEmon.end(); ++_viEmon)
	{
		(*_viEmon)->update();
	}
}

void monsterManager::render()
{
	for (_viEmon = _vEmon.begin(); _viEmon != _vEmon.end(); ++_viEmon)
	{
		if((*_viEmon)->getAct()==true)
			(*_viEmon)->render();
	}
}

void monsterManager::addDmon(int i)
{
	for (_viDmon = _vDmon.begin(); _viDmon != _vDmon.end(); ++_viDmon)
	{
		if ((*_viDmon).num == i)
		{
			(*_viDmon).have += 1;
			return;
		}
	}
	tagMon	mon;
	ZeroMemory(&mon, sizeof(tagMon));
	mon.num = _dex[i].num;
	mon.hp = _dex[i].hp;
	mon.have = 1;
	//mon.act = false;
	_vDmon.push_back(mon);
	if (_vDmon.size() >1)
	{
		int i = _vDmon.size()-1;
		tagMon temp;
		while ((_vDmon[i].num < _vDmon[i-1].num))
		{
			temp = _vDmon[i];
			_vDmon[i] = _vDmon[i-1];
			_vDmon[i-1] = temp;
			i -= 1;
			if (i == 0)
				break;
		}
	}
}

void monsterManager::addAmon(int i)
{
	//tagMon	mon;
	//ZeroMemory(&mon, sizeof(tagMon));
	//mon.num = _dex[i].num;
	//mon.hp = _dex[i].hp;
	//mon.act = false;
	//_vAmon.push_back(mon);
}

void monsterManager::addEmon(int id,int i, int dir, vector<int> road)
{
	monster*	mon;
	mon = new monster;
	mon->init(id, i,_dex[i],_dex[i].hp, dir, road);

	_vEmon.push_back(mon);
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
	dexSet(1, IMAGEMANAGER->findImage("a1"), "이상해풀", GRASS, PointMake(2, 2), 15, 15, 0.9, 0.9,10, true, true, true, true, true);
	dexSet(2, IMAGEMANAGER->findImage("a2"), "이상해꽃", GRASS, PointMake(3, 3), 20, 20, 0.8, 0.8,15, false, true, true, true, true);
}

void monsterManager::dexSet(int i, image* img, string name, TYPE type, POINT size, int fhp, int power, float spd, float atSpd,int food, bool evo, bool dir0, bool dir1,bool dir2,bool dir3)
{
	_dex[i].num = i;
//	_dex[i].img = new image;
	//_dex[i].img = img;
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

//void monsterManager::evolution(bool ad, int i)
//{
//	if (ad == 0)//&& _dex[_vDmon[i].num].evolution==true)
//	{
//		_vDmon[i].num +=1;
//	}
//	//else if(ad == 1)// && _dex[_vAmon[i].num].evolution == true)
//	//{
//	//	_vAmon[i].num += 1;
//	//}
//}

monsterManager::monsterManager()
{
}


monsterManager::~monsterManager()
{
}
