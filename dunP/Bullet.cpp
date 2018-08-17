#include "stdafx.h"
#include "Bullet.h"


Bullet::Bullet(){}

Bullet::~Bullet(){}

HRESULT Bullet::init(int bulletMax)
{
	_bulletMax	= bulletMax;
	_count = 0;
	return S_OK;
}

void Bullet::release(){}

void Bullet::update()
{
	_count++;
	if (_count % 10 == 0)
	{
		_count = 0;
		_ball.frameX==7 ? _ball.frameX =0 : _ball.frameX++;
		
	}
	bulletMove();
}

void Bullet::render()
{
	char str[128];
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		sprintf_s(str, "b%d", (*_viBullet).type);
		draw(str,DC, _viBullet->rc.left, _viBullet->rc.top);
	}
	if(_ball.isFire==true)
		fdraw("ball", DC, _ball.rc.left, _ball.rc.top,_ball.frameX,0);
}

void Bullet::bulletFire(const char* imgName, float x, float y, float angle, int power, float speed, int type)
{
	if (_bulletMax < _vBullet.size()) return;
	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.speed = (speed+1)*2;
	bullet.x = x;
	bullet.y  = y;
	bullet.angle = angle;
	bullet.power = power;
	bullet.type = type;

	bullet.rc = RectMakeCenter(bullet.x, bullet.y, 16, 16);
	
	_vBullet.push_back(bullet);
}

void Bullet::ballFire(float x, float y, float angle)
{
	_ball.speed = 3;
	_ball.x = x;
	_ball.y = y;
	_ball.frameX = 0;
	_ball.angle = angle;
	_ball.rc = RectMakeCenter(_ball.x, _ball.y,29, 25);
	_ball.isFire = true;
}

void Bullet::bulletMove()
{

	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); _viBullet++)
	{
		_viBullet->x += cosf(_viBullet->angle) * _viBullet->speed;
		_viBullet->y += -sinf(_viBullet->angle)* _viBullet->speed;

		_viBullet->rc = RectMakeCenter(_viBullet->x-8, _viBullet->y-8,16, 16);
	}

	_ball.x += cosf(_ball.angle) * _ball.speed;
	_ball.y += -sinf(_ball.angle)* _ball.speed;
	_ball.rc = RectMakeCenter(_ball.x - 15, _ball.y - 13, 29, 25);
}


void Bullet::removeBullet(int arrNum)
{
	_vBullet.erase(_vBullet.begin() + arrNum);
}

void Bullet::resetBullet()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
		_viBullet=_vBullet.erase(_viBullet);
}