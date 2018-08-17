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
	RECT	rc;				// ��Ʈ
	float	x, y;			// �Ѿ� ��ǥ
	float	angle;			// �Ѿ˰���
	float	speed;			// �Ѿ� ���ǵ�
	float	radius;			// �Ѿ� ������
	float	power;
	int		frameX;
	int		type;
	bool	isFire;			// �߻翩��
};

class Bullet : public gameNode
{
private:
	vector<tagBullet>			_vBullet;
	vector<tagBullet>::iterator	_viBullet;

	tagBullet	_ball;

	int			_bulletMax;		// �ִ� �Ѿ� ����
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
	void	bulletMove();												// �̵�
	void	removeBullet(int arrNum);									// �Ѿ� �����ٶ�
	void resetBullet();

	// �Ѿ� ���� ������
	vector<tagBullet>			getVBullet() { return _vBullet; }
	vector<tagBullet>::iterator	getVIBullet() { return _viBullet; }
	tagBullet	getBall() { return _ball; }
	RECT	getBallRc() { return _ball.rc; }
	bool	getBallFire() { return _ball.isFire; }
	void	setBallFire(bool i) { _ball.isFire = i; }
};