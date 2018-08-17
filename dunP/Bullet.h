#pragma once
#include "gameNode.h"
#include <vector>

enum FRAMEXY
{
	WIDTH,
	HEIGHT
};

struct tagBullet
{
	RECT	rc;				// ·ºÆ®
	float	x, y;			// ÃÑ¾Ë ÁÂÇ¥
	float	angle;			// ÃÑ¾Ë°¢µµ
	float	speed;			// ÃÑ¾Ë ½ºÇÇµå
	float	radius;			// ÃÑ¾Ë ¹ÝÁö¸§
	float	power;
	int		frameX;
	int		type;
	bool	isFire;			// ¹ß»ç¿©ºÎ
};

class Bullet : public gameNode
{
private:
	vector<tagBullet>			_vBullet;
	vector<tagBullet>::iterator	_viBullet;

	tagBullet	_ball;

	int			_bulletMax;		// ÃÖ´ë ÃÑ¾Ë °¹¼ö
	int			_count;

public:
	Bullet();
	~Bullet();

	HRESULT init(int bullletMax);
	void	release();
	void	update();
	void	render();

	void bulletFire(const char * imgName, float x, float y, float angle, int power, float speed, int type);
	void ballFire(float x, float y, float angle);
	void	bulletMove();												// ÀÌµ¿
	void	removeBullet(int arrNum);									// ÃÑ¾Ë Áö¿öÁÙ¶§
	void resetBullet();

	// ÃÑ¾Ë º¤ÅÍ Á¢±ÙÀÚ
	vector<tagBullet>			getVBullet() { return _vBullet; }
	vector<tagBullet>::iterator	getVIBullet() { return _viBullet; }
	tagBullet	getBall() { return _ball; }
	RECT	getBallRc() { return _ball.rc; }
	bool	getBallFire() { return _ball.isFire; }
	void	setBallFire(bool i) { _ball.isFire = i; }
};