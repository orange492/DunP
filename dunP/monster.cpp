#include "stdafx.h"
#include "monster.h"


HRESULT monster::init(int id,tagMonster dex, int hp, int dir, vector<int> road)
{
	_hpbar = new progressBar;
	_dex = dex;
	_act = true;
	_hp = hp;
	_count = 0;
	_dir = (DIR)dir;
	_vRoad = road;
	_vRoad = road;
	int x=_vRoad[_vRoad.size()-1]%100;
	int y=_vRoad[_vRoad.size()-1]/100;
	_tile = {(float)x*TILESIZE,(float)y*TILESIZE };
	//SetRect(&_rc, x * TILESIZE, y * TILESIZE, x* TILESIZE + TILESIZE, y * TILESIZE + TILESIZE);
	//_vRoad.erase(_vRoad.begin() + _vRoad.size() - 1);
	_hpbar->init(_tile.x+5, _tile.y-5 , 20, 5, id);

	return S_OK;
}

void monster::release()
{
}

void monster::update()
{
	if (_vRoad.size() > 1)
		move();
	_hpbar->setGauge(_hp, _dex.hp);
	_hpbar->setX(_tile.x + 5);
	_hpbar->setY(_tile.y);
	_hpbar->update();
}

void monster::move()
{
	if (_vRoad[_vRoad.size() - 2])
	if (_vRoad[_vRoad.size() - 2] - _vRoad[_vRoad.size() - 1] == 1)
	{
		_dir = RIGHT;
		_tile.x += _dex.spd;
		if (_tile.x / TILESIZE >= _vRoad[_vRoad.size() - 2] % 100)
		{
			//_tile.x = _vRoad[_vRoad.size() - 2] % 100* TILEX;
			_vRoad.erase(_vRoad.begin() + _vRoad.size() - 1);
		}
	}
	else if (_vRoad[_vRoad.size() - 2] - _vRoad[_vRoad.size() - 1] == -1)
	{
		_dir = LEFT;
		_tile.x -= _dex.spd;
		if (_tile.x / TILESIZE <= _vRoad[_vRoad.size() - 2] % 100)
		{
			_vRoad.erase(_vRoad.begin() + _vRoad.size() - 1);
		}
	}
	else if (_vRoad[_vRoad.size() - 2] - _vRoad[_vRoad.size() - 1] == 100)
	{
		_dir = DOWN;
		_tile.y += _dex.spd;
		if (_tile.y / TILESIZE >= _vRoad[_vRoad.size() - 2] / 100)
		{
			_vRoad.erase(_vRoad.begin() + _vRoad.size() - 1);
		}
	}
	else if (_vRoad[_vRoad.size() - 2] - _vRoad[_vRoad.size() - 1] == -100)
	{
		_dir = UP;
		_tile.y -= _dex.spd;
		if (_tile.y / TILESIZE <= _vRoad[_vRoad.size() - 2] / 100)
		{
			_vRoad.erase(_vRoad.begin() + _vRoad.size() - 1);
		}
	}
	else if (_vRoad[_vRoad.size() - 2] - _vRoad[_vRoad.size() - 1] == 101)
	{
		_dir = RB;
		_tile.x += _dex.spd;
		_tile.y += _dex.spd;
		if (_tile.y / TILESIZE >= _vRoad[_vRoad.size() - 2] / 100&& _tile.x / TILESIZE >= _vRoad[_vRoad.size() - 2] % 100)
		{
			_vRoad.erase(_vRoad.begin() + _vRoad.size() - 1);
		}
	}
	else if (_vRoad[_vRoad.size() - 2] - _vRoad[_vRoad.size() - 1] == 99)
	{
		_dir = LB;
		_tile.x -= _dex.spd;
		_tile.y += _dex.spd;
		if (_tile.y / TILESIZE >= _vRoad[_vRoad.size() - 2] / 100-1&& _tile.x / TILESIZE <= _vRoad[_vRoad.size() - 2] % 100)
		{
			_vRoad.erase(_vRoad.begin() + _vRoad.size() - 1);
		}
	}
	else if (_vRoad[_vRoad.size() - 2] - _vRoad[_vRoad.size() - 1] == -101)
	{
		_dir = LT;
		_tile.x -= _dex.spd;
		_tile.y -= _dex.spd;
		if (_tile.y / TILESIZE <= _vRoad[_vRoad.size() - 2] / 100 && _tile.x / TILESIZE <= _vRoad[_vRoad.size() - 2] % 100)
		{
			_vRoad.erase(_vRoad.begin() + _vRoad.size() - 1);
		}
	}
	else if (_vRoad[_vRoad.size() - 2] - _vRoad[_vRoad.size() - 1] == -99)
	{
		_dir = RT;
		_tile.x += _dex.spd;
		_tile.y -= _dex.spd;
		if (_tile.y / TILESIZE <= _vRoad[_vRoad.size() - 2] / 100 && _tile.x / TILESIZE >= _vRoad[_vRoad.size() - 2] % 100-1)
		{
			_vRoad.erase(_vRoad.begin() + _vRoad.size() - 1);
		}
	}
}

void monster::render()
{
	char str[128];
	sprintf_s(str, "%d",_dex.num);

	++_count;
	if (_count%10 == 0)
	{
		_currentX == 3 ? _currentX = 0 : _currentX++;
		_count = 0;
	}
	int currentX;

	_dex.num ==0 ? _currentX == 3 ? currentX = 2 : currentX = _currentX : _currentX == 3 ? currentX = 1 : currentX = _currentX;
	
	_rc = RectMake(_tile.x, _tile.y, TILESIZE, TILESIZE);
	fdraw(str, DC, _rc.left, _rc.top, currentX,_dir);
	_hpbar->render();
}

monster::monster()
{
}


monster::~monster()
{
}
