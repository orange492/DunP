#include "stdafx.h"
#include "monster.h"


HRESULT monster::init(int id,tagMonster dex, int hp, int dir, vector<int> road)
{
	_hpbar = new progressBar;
	_dex = dex;
	_act = false;
	_hp = hp;
	_count = 0;
	_dir = (DIR)dir;
	_vRoad = road;
	int x=_vRoad[_vRoad.size()-1]%100;
	int y=_vRoad[_vRoad.size()-1]/100;
	_tile = {(float)x*TILESIZE+16,(float)y*TILESIZE+16};
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
	_loca = _tile.x / 32 + (int)_tile.y / 32 * 100;
	_hpbar->setGauge(_hp, _dex.hp);
	_hpbar->setX(_tile.x-16 + 5);
	_hpbar->setY(_tile.y-16);
	_hpbar->update();
	/*if (KEYMANAGER->isStayKeyDown('B'))
		_hp -= 10;*/
}

void monster::move()
{
	if (_vRoad[_vRoad.size() - 2] - _vRoad[_vRoad.size() - 1] == 1)
	{
		_dir = RIGHT;
		_tile.x += _dex.spd;
		if ((_tile.x-16) / TILESIZE >= _vRoad[_vRoad.size() - 2] % 100)
		{
			//_tile.x = _vRoad[_vRoad.size() - 2] % 100* TILEX;
			_vRoad.erase(_vRoad.begin() + _vRoad.size() - 1);
		}
	}
	else if (_vRoad[_vRoad.size() - 2] - _vRoad[_vRoad.size() - 1] == -1)
	{
		_dir = LEFT;
		_tile.x -= _dex.spd;
		if ((_tile.x - 16) / TILESIZE <= _vRoad[_vRoad.size() - 2] % 100)
		{
			_vRoad.erase(_vRoad.begin() + _vRoad.size() - 1);
		}
	}
	else if (_vRoad[_vRoad.size() - 2] - _vRoad[_vRoad.size() - 1] == 100)
	{
		_dir = DOWN;
		_tile.y += _dex.spd;
		if ((_tile.y - 16) / TILESIZE >= _vRoad[_vRoad.size() - 2] / 100)
		{
			_vRoad.erase(_vRoad.begin() + _vRoad.size() - 1);
		}
	}
	else if (_vRoad[_vRoad.size() - 2] - _vRoad[_vRoad.size() - 1] == -100)
	{
		_dir = UP;
		_tile.y -= _dex.spd;
		if ((_tile.y - 16) / TILESIZE <= _vRoad[_vRoad.size() - 2] / 100)
		{
			_vRoad.erase(_vRoad.begin() + _vRoad.size() - 1);
		}
	}
	else if (_vRoad[_vRoad.size() - 2] - _vRoad[_vRoad.size() - 1] == 101)
	{
		_dir = RB;
		_tile.x += _dex.spd;
		_tile.y += _dex.spd;
		if ((_tile.y - 16) / TILESIZE >= _vRoad[_vRoad.size() - 2] / 100&& (_tile.x - 16) / TILESIZE >= _vRoad[_vRoad.size() - 2] % 100)
		{
			_vRoad.erase(_vRoad.begin() + _vRoad.size() - 1);
		}
	}
	else if (_vRoad[_vRoad.size() - 2] - _vRoad[_vRoad.size() - 1] == 99)
	{
		_dir = LB;
		_tile.x -= _dex.spd;
		_tile.y += _dex.spd;
		if ((_tile.y - 16) / TILESIZE >= _vRoad[_vRoad.size() - 2] / 100-1&& (_tile.x - 16) / TILESIZE <= _vRoad[_vRoad.size() - 2] % 100)
		{
			_vRoad.erase(_vRoad.begin() + _vRoad.size() - 1);
		}
	}
	else if (_vRoad[_vRoad.size() - 2] - _vRoad[_vRoad.size() - 1] == -101)
	{
		_dir = LT;
		_tile.x -= _dex.spd;
		_tile.y -= _dex.spd;
		if ((_tile.y - 16) / TILESIZE <= _vRoad[_vRoad.size() - 2] / 100 && (_tile.x - 16) / TILESIZE <= _vRoad[_vRoad.size() - 2] % 100)
		{
			_vRoad.erase(_vRoad.begin() + _vRoad.size() - 1);
		}
	}
	else if (_vRoad[_vRoad.size() - 2] - _vRoad[_vRoad.size() - 1] == -99)
	{
		_dir = RT;
		_tile.x += _dex.spd;
		_tile.y -= _dex.spd;
		if ((_tile.y - 16) / TILESIZE <= _vRoad[_vRoad.size() - 2] / 100 && (_tile.x - 16) / TILESIZE >= _vRoad[_vRoad.size() - 2] % 100-1)
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
	
	_rc = RectMake(_tile.x-16, _tile.y-16, TILESIZE, TILESIZE);
	fdraw(str, DC, _rc.left, _rc.top, currentX,_dir);
	//Rectangle(DC, _rc.left, _rc.top, _rc.right, _rc.bottom);
	_hpbar->render();
}

void monster::eraseRoad()
{
	for (_viRoad = _vRoad.begin(); _viRoad != _vRoad.end();)
	{
		_viRoad = _vRoad.erase(_viRoad);
	}
}

monster::monster()
{
}


monster::~monster()
{
}
