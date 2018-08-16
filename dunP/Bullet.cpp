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
	//bulletFrameX();
	//bulletFrameY();
}

void Bullet::render()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->img->render(DC, _viBullet->rc.left, _viBullet->rc.top);
	}
	if(_ball.isFire==true)
		fdraw("ball", DC, _ball.rc.left, _ball.rc.top,_ball.frameX,0);
}

void Bullet::bulletFire(const char* imgName, float x, float y, float angle, int power, float speed, int type)
{
	if (_bulletMax < _vBullet.size()) return;
	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.img = IMAGEMANAGER->findImage(imgName);
	bullet.speed = (speed+1)*2;
	//bullet.radius = bullet.img->getWidth() / 2;
	bullet.x = x;
	bullet.y  = y;
	bullet.angle = angle;
	bullet.power = power;
	bullet.type = type;

	bullet.rc = RectMakeCenter(bullet.x, bullet.y, bullet.img->getFrameWidth(), bullet.img->getFrameHeight());
	
	_vBullet.push_back(bullet);
}

void Bullet::ballFire(float x, float y, float angle)
{
	_ball.img= IMAGEMANAGER->findImage("ball");
	_ball.speed = 3;
	_ball.x = x;
	_ball.y = y;
	_ball.frameX = 0;
	_ball.angle = angle;
	_ball.rc = RectMakeCenter(_ball.x, _ball.y, _ball.img->getFrameWidth(), _ball.img->getFrameHeight());
	_ball.isFire = true;
}

//void Bullet::swordRender()
//{
//	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
//	{
//		if (_viBullet->speed == 0) _viBullet->img->frameRender(DC, _viBullet->x, _viBullet->y, 0, 0);
//		else
//		{
//			_viBullet->img->rotateRender(DC, _viBullet->x, _viBullet->y, _viBullet->angle);
//		}
//		if (KEYMANAGER->isToggleKey('M'))
//			Rectangle(DC, _viBullet->rc.left, _viBullet->rc.top, _viBullet->rc.right, _viBullet->rc.bottom);
//	}
//}

//void Bullet::changeSpeedAndAngle(float x, float y)
//{
//	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
//	{
//		if (_viBullet->speed == 0)
//		{
//			_viBullet->speed = 30;
//			_viBullet->angle = getAngle(_viBullet->x, _viBullet->y, x, y);
//			_viBullet->img = IMAGEMANAGER->findImage("RotateBossSword");
//			_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y, _viBullet->img->getFrameWidth(), _viBullet->img->getFrameHeight());
//			break;
//		}
//	}
//}
void Bullet::bulletMove()
{

	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); _viBullet++)
	{
		_viBullet->x += cosf(_viBullet->angle) * _viBullet->speed;
		_viBullet->y += -sinf(_viBullet->angle)* _viBullet->speed;

		_viBullet->rc = RectMakeCenter(_viBullet->x-8, _viBullet->y-8,16, 16);
				
		//if(_viBullet->rc.right<0)
	/*	if (_viBullet->range < getDistance(_viBullet->x, _viBullet->y, _viBullet->fireX, _viBullet->fireY))
		{
			if (_viBullet->swordIdx != -1)
			{
				EFFECTMANAGER->play("bossSword", _viBullet->x, _viBullet->y);
			}
			_viBullet = _vBullet.erase(_viBullet);
		}
		else _viBullet++;*/
	}

	_ball.x += cosf(_ball.angle) * _ball.speed;
	_ball.y += -sinf(_ball.angle)* _ball.speed;
	_ball.rc = RectMakeCenter(_ball.x - 15, _ball.y - 13, 29, 25);
}

//void Bullet::bulletFrameX()
//{
//	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
//	{
//		if (!_viBullet->isFrame) continue;
//		if (_viBullet->frameXY != WIDTH) continue;
//
//		_viBullet->frameIndex += 1;
//
//		if (_viBullet->frameIndex % 6 == 0)
//		{
//			_viBullet->frameX += 1;
//			if (_viBullet->frameX > _viBullet->img->getMaxFrameX()) _viBullet->frameX = 0;
//			_viBullet->frameIndex = 0;
//		}
//	}
//}
//
//void Bullet::bulletFrameY(void)
//{
//	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
//	{
//		if (!_viBullet->isFrame || _viBullet->frameXY != HEIGHT)
//		{
//			_viBullet++;
//			continue;
//		}
//		
//		_viBullet->frameIndex += 1;
//		if (_viBullet->frameIndex % 10 == 0)
//		{
//			_viBullet->frameY += 1;
//			_viBullet->frameIndex = 0;
//		}
//		
//		if (_viBullet->frameY > _viBullet->img->getMaxFrameY())
//		{
//			_viBullet = _vBullet.erase(_viBullet);
//		}
//		else _viBullet++;
//	}
//}

void Bullet::removeBullet(int arrNum)
{
	_vBullet.erase(_vBullet.begin() + arrNum);
}

void Bullet::resetBullet()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
		_viBullet=_vBullet.erase(_viBullet);
}

//void Bullet::bulletframe(const char * imgName)
//{
//	_count++;
//
//	bullet.img = IMAGEMANAGER->findImage(imgName);
//	bullet.img->setFrameY(0);
//	if (_index > bullet.img->getMaxFrameX()) _index = 0;
//
//	bullet.img->setFrameX(_index);
//	if(_count % 2 == 0) _index++;
//}


//Bullet2::Bullet2(){}
//
//Bullet2::~Bullet2(){}
//
//HRESULT Bullet2::init(int bulletMax)
//{
//	_bulletMax = bulletMax;
//	_index = _count2 = 0;
//	return S_OK;
//}
//
//void Bullet2::release()
//{
//}
//
//void Bullet2::update()
//{
//	bulletMove();
//}
//
//void Bullet2::render()
//{
//	for (_viBullet2 = _vBullet2.begin(); _viBullet2 != _vBullet2.end(); _viBullet2++)
//	{
//		_viBullet2->img->frameRender(DC, _viBullet2->rc.left, _viBullet2->rc.top);
//	}
//}
//
//void Bullet2::bulletFire(const char * imgName, float x, float y, float angle, float speed, float range)
//{
//	if (_bulletMax < _vBullet2.size()) return;
//
//	ZeroMemory(&bullet2, sizeof(tagBullet));
//	bullet2.img = IMAGEMANAGER->findImage(imgName);
//	bullet2.speed = speed;
//	bullet2.radius = bullet2.img->getWidth() / 2;
//	bullet2.x = bullet2.fireX = x;
//	bullet2.y = bullet2.fireY = y;
//	bullet2.angle = angle; 
//	bullet2.range = range;
//	bullet2.rc = RectMakeCenter(bullet2.x, bullet2.y, bullet2.img->getWidth(), bullet2.img->getHeight());
//
//	_vBullet2.push_back(bullet2);
//}
//
//void Bullet2::bulletMove()
//{
//	for (_viBullet2 = _vBullet2.begin(); _viBullet2 != _vBullet2.end();)
//	{
//		_viBullet2->x += cosf(_viBullet2->angle) * _viBullet2->speed; //1 * _viBullet2->speed; cosf(_viBullet2->angle) * _viBullet2->speed;
//		_viBullet2->y += -sinf(_viBullet2->angle)* _viBullet2->speed; //1 * _viBullet2->speed; -sinf(_viBullet2->angle)* _viBullet2->speed;
//		
//		_viBullet2->rc = RectMakeCenter(_viBullet2->x, _viBullet2->y, _viBullet2->img->getWidth(), _viBullet2->img->getHeight());
//
//		if (_viBullet2->range < getDistance(_viBullet2->x, _viBullet2->y, _viBullet2->fireX, _viBullet2->fireY))
//		{
//			_viBullet2 = _vBullet2.erase(_viBullet2);
//		}
//		else _viBullet2++;
//	}
//
//	
//}
//
//void Bullet2::removeBullet(int arrNum)
//{
//	_viBullet2 = _vBullet2.begin() + arrNum;
//	_vBullet2.erase(_viBullet2);
//}
//
//void Bullet2::bulletframe(const char * imgName)
//{
//	_count2++;
//
//	bullet2.img = IMAGEMANAGER->findImage(imgName);
//	bullet2.img->setFrameY(0);
//	if (_index > bullet2.img->getMaxFrameX()) _index = 0;
//
//	bullet2.img->setFrameX(_index);
//	if (_count2 % 2 == 0) _index++;
//}
