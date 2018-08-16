#include "stdafx.h"
#include "monsterManager.h"
#include "MapTool.h"
#include "star.h"

HRESULT monsterManager::init()
{
	dexSetting();

	for (int i = 0; i < 15; i++)
	{
		addDmon(i);
	}
	//addEmon(0);
	
	return S_OK;
}

void monsterManager::release()
{
}

void monsterManager::update()
{
	int mon;
	for (_viEmon = _vEmon.begin(); _viEmon != _vEmon.end(); ++_viEmon)
	{
		(*_viEmon)->update();
		if ((*_viEmon)->getAct() == true && _mapTool->getFight((*_viEmon)->getLoca()) == false&& (*_viEmon)->getRoad().size()==1)
		{
			(*_viEmon)->eraseRoad();
			(*_viEmon)->setRoad(_star->findRoad((*_viEmon)->getLoca(), _mapTool->getPlayer(), _mapTool->getPlayer()-101,_dex[_mapTool->getTiles()[_mapTool->getPlayer()].mon].size.x, _dex[_mapTool->getTiles()[_mapTool->getPlayer()].mon].size.y));
			(*_viEmon)->setAct(false);
		}
		else if ((*_viEmon)->getAct() == true && _mapTool->getFight((*_viEmon)->getLoca()) == true && (*_viEmon)->getRoad().size() == 1&& (*_viEmon)->getCount()%10==9)
		{
			if (_dex[_mapTool->getTiles()[_mapTool->getTiles()[(*_viEmon)->getLoca()].mon2].mon].type - (*_viEmon)->getDex().type == 1 || _dex[_mapTool->getTiles()[_mapTool->getTiles()[(*_viEmon)->getLoca()].mon2].mon].type - (*_viEmon)->getDex().type == -2)
				(*_viEmon)->setHp((*_viEmon)->getHp() - ((_dex[_mapTool->getTiles()[_mapTool->getTiles()[(*_viEmon)->getLoca()].mon2].mon].power)/0.5)*1.5);
			else
				(*_viEmon)->setHp((*_viEmon)->getHp() - (_dex[_mapTool->getTiles()[_mapTool->getTiles()[(*_viEmon)->getLoca()].mon2].mon].power)/0.5);
			mon=_mapTool->findMon(_mapTool->getTiles()[(*_viEmon)->getLoca()].mon2);
			_mapTool->setMonHp(mon, _mapTool->getMon()[mon].hp - ((*_viEmon)->getDex().power) * 0.5);
		}
	}

	for (int i = 0; i < _vEmon.size(); i++)
	{
		if (_vEmon[i]->getHp() <= 0)
		{
			_mapTool->setMoney(_mapTool->getMoney() + _vEmon[i]->getDex().price);
			_mapTool->setFight(_vEmon[i]->getRoad()[0], false);
			 _vEmon.erase(_vEmon.begin() + i);
			 i--;
		}
	}
}

void monsterManager::render()
{
	for (_viEmon = _vEmon.begin(); _viEmon != _vEmon.end(); ++_viEmon)
	{
		if((*_viEmon)->getRoad().size() == 1)
		{
			if (_mapTool->getTiles()[(*_viEmon)->getLoca() - 1].object == OBJ_MON && _mapTool->getTiles()[(*_viEmon)->getLoca() - 1].monPos != MPOS_0)
				(*_viEmon)->setDir(LEFT);
			else if (_mapTool->getTiles()[(*_viEmon)->getLoca() + 1].object == OBJ_MON && _mapTool->getTiles()[(*_viEmon)->getLoca() + 1].monPos != MPOS_0)
				(*_viEmon)->setDir(RIGHT);
			else if (_mapTool->getTiles()[(*_viEmon)->getLoca() - 100].object == OBJ_MON && _mapTool->getTiles()[(*_viEmon)->getLoca() - 100].monPos != MPOS_0)
				(*_viEmon)->setDir(UP);
			else if (_mapTool->getTiles()[(*_viEmon)->getLoca() + 100].object == OBJ_MON && _mapTool->getTiles()[(*_viEmon)->getLoca() + 100].monPos != MPOS_0)
				(*_viEmon)->setDir(DOWN);
			else if (_mapTool->getTiles()[(*_viEmon)->getLoca() - 101].object == OBJ_MON && _mapTool->getTiles()[(*_viEmon)->getLoca() - 101].monPos != MPOS_0)
				(*_viEmon)->setDir(LT);
			else if (_mapTool->getTiles()[(*_viEmon)->getLoca() - 99].object == OBJ_MON && _mapTool->getTiles()[(*_viEmon)->getLoca() - 99].monPos != MPOS_0)
				(*_viEmon)->setDir(RT);
			else if (_mapTool->getTiles()[(*_viEmon)->getLoca() + 101].object == OBJ_MON && _mapTool->getTiles()[(*_viEmon)->getLoca() + 101].monPos != MPOS_0)
				(*_viEmon)->setDir(RB);
			else if (_mapTool->getTiles()[(*_viEmon)->getLoca() +99].object == OBJ_MON && _mapTool->getTiles()[(*_viEmon)->getLoca() +99].monPos != MPOS_0)
				(*_viEmon)->setDir(LB);
		}	
		//if((*_viEmon)->getAct()==true)
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
	tagMon2	mon;
	ZeroMemory(&mon, sizeof(tagMon2));
	mon.num = _dex[i].num;
	mon.hp = _dex[i].hp;
	mon.have = 1;
	//mon.act = false;
	_vDmon.push_back(mon);
	if (_vDmon.size() >1)
	{
		int i = _vDmon.size()-1;
		tagMon2 temp;
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

//void monsterManager::addAmon(int i)
//{
//	//tagMon	mon;
//	//ZeroMemory(&mon, sizeof(tagMon));
//	//mon.num = _dex[i].num;
//	//mon.hp = _dex[i].hp;
//	//mon.act = false;
//	//_vAmon.push_back(mon);
//}

void monsterManager::addEmon(int id,int i, int dir, vector<int> road)
{
	monster*	mon;
	mon = new monster;
	mon->init(id, _dex[i],_dex[i].hp, dir, road);

	_vEmon.push_back(mon);
}

void monsterManager::eraseDmon(int arrNum)
{
	_vDmon.erase(_vDmon.begin() + arrNum);
}

void monsterManager::eraseAmon(int arrNum)
{
	//_vAmon.erase(_vAmon.begin() + arrNum);
}

void monsterManager::deleteEmon(int i)
{
	_vEmon.erase(_vEmon.begin() + i);
}

void monsterManager::eraseEmon()
{
	for (_viEmon = _vEmon.begin(); _viEmon != _vEmon.end();)
	{
		_viEmon = _vEmon.erase(_viEmon);
	}
}

void monsterManager::dexSetting()
{
	dexSet(0, IMAGEMANAGER->findImage("a0"), "이상해씨", GRASS, PointMake(1, 1), 10,10, 100, 1, 0.9, 0.9, 5,20, true, true, true, true, true);
	dexSet(1, IMAGEMANAGER->findImage("a1"), "이상해풀", GRASS, PointMake(2, 2), 10,30, 170, 2, 0.8, 0.8,10,40, true, true, true, true, true);
	dexSet(2, IMAGEMANAGER->findImage("a2"), "이상해꽃", GRASS, PointMake(3, 3), 7,18, 270, 2, 0.7, 0.7,15,60, false, true, true, true, true);
	dexSet(3, IMAGEMANAGER->findImage("a3"), "파이리", FIRE, PointMake(1, 2), 10,27, 100, 1, 1, 0.8,5,20, true, true, true, true, true);
	dexSet(4, IMAGEMANAGER->findImage("a4"), "리자드", FIRE, PointMake(2, 2), 11,46, 150, 2, 1.1, 0.8,10,40, true, true, true, true, true);
	dexSet(5, IMAGEMANAGER->findImage("a5"), "리자몽", FIRE, PointMake(3, 3), 6,36, 180, 3, 1.2, 0.8,15,60, false, true, true, true, true);
	dexSet(6, IMAGEMANAGER->findImage("a6"), "꼬부기", WATER, PointMake(1, 2), 12,17, 100, 1, 1, 0.8,5,20, true, true, true, true, true);
	dexSet(7, IMAGEMANAGER->findImage("a7"), "어니부기", WATER, PointMake(2, 2), 13,18, 170, 2, 0.9, 0.8,10,40, true, true, true, true, true);
	dexSet(8, IMAGEMANAGER->findImage("a8"), "거북왕", WATER, PointMake(3, 3), 10,30, 250, 2, 0.8, 0.8,15,60, false, true, true, true, true);
	dexSet(9, IMAGEMANAGER->findImage("a9"), "스라크", GRASS, PointMake(2, 2), 11,15, 100, 2, 1.2, 0.8,5,50, true, true, true, true, true);
	dexSet(10, IMAGEMANAGER->findImage("a10"), "핫산", GRASS, PointMake(3, 3), 10,30, 150, 3, 1.3, 0.8,10,100, false, true, true, true, true);
	dexSet(11, IMAGEMANAGER->findImage("a11"), "식스테일", FIRE, PointMake(2, 2), 9,18, 120, 1, 1.3, 0.8,5,50, true, true, true, true, true);
	dexSet(12, IMAGEMANAGER->findImage("a12"), "나인테일", FIRE, PointMake(3, 3), 9,9, 200, 2, 1.2, 0.8,10,100, false, true, true, true, true);
	dexSet(13, IMAGEMANAGER->findImage("a13"), "셀러", WATER, PointMake(2, 2), 11,44, 160, 1, 0.7, 0.8,5,50, true, true, true, true, true);
	dexSet(14, IMAGEMANAGER->findImage("a14"), "파르셀", WATER, PointMake(3, 3), 10,18, 300, 1, 0.6, 0.8,10,100, false, true, true, true, true);
}

void monsterManager::dexSet(int i, image* img, string name, TYPE type, POINT size, int frameX, int frameNum, int fhp, int power, float spd, float atSpd, int food,int price, bool evo, bool dir0, bool dir1, bool dir2, bool dir3)
{
	_dex[i].num = i;
//	_dex[i].img = new image;
	//_dex[i].img = img;
	_dex[i].name = name;
	_dex[i].type = type;
	_dex[i].size = size;
	_dex[i].frameX = frameX;
	_dex[i].frameNum = frameNum;
	_dex[i].hp = fhp;
	_dex[i].power = power;
	_dex[i].spd = spd;
	_dex[i].atSpd = atSpd;
	_dex[i].food = food;
	_dex[i].price = price;
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
