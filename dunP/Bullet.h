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
	image*	img;			// �Ѿ��̹���
	RECT	rc;				// ��Ʈ
	float	x, y;			// �Ѿ� ��ǥ
	float	angle;			// �Ѿ˰���
	float	speed;			// �Ѿ� ���ǵ�
	float	radius;			// �Ѿ� ������
	float	power;
	int		frameX;
	int		type;
	bool	isFire;			// �߻翩��

	//float   range;
	//bool	isFrame;
	//FRAMEXY frameXY;
	//int		frameIndex;
	//int		frameX, frameY;
	//int		bulletNum;		// �����̵����� üũ
	//int		swordIdx;
	
};

class Bullet : public gameNode
{
private:
	vector<tagBullet>			_vBullet;
	vector<tagBullet>::iterator	_viBullet;

	tagBullet	_ball;

	//tagBullet bullet;

	int			_bulletMax;		// �ִ� �Ѿ� ����
	//int			_index;			// ������ �ε�����
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
	//void	swordRender();
	//void	changeSpeedAndAngle(float x, float y);
	void	bulletMove();												// �̵�
	//void	bulletFrameX(void);												// �Ѿ� ������
	//void	bulletFrameY(void);
	void	removeBullet(int arrNum);									// �Ѿ� �����ٶ�
	void resetBullet();
	//void	bulletframe(const char* imgName);

	// �Ѿ� ���� ������
	vector<tagBullet>			getVBullet() { return _vBullet; }
	vector<tagBullet>::iterator	getVIBullet() { return _viBullet; }
	tagBullet	getBall() { return _ball; }
	RECT	getBallRc() { return _ball.rc; }
	void	setBallFire(bool i) { _ball.isFire = i; }

	//FRAMEXY getFrameXY(int i) { return _vBullet[i].frameXY; }
};

//class Bullet2 : public gameNode
//{
//private:
//	vector<tagBullet>			_vBullet2;
//	vector<tagBullet>::iterator	_viBullet2;
//
//	tagBullet bullet2;
//
//	int			_bulletMax;		// �ִ� �Ѿ� ����
//	int			_index;			// ������ �ε�����
//	int			_count2;
//	int			_count;
//	int			j;
//	int			start;
//public:
//	Bullet2();
//	~Bullet2();
//
//	HRESULT init(int bullletMax);
//	void	release();
//	void	update();
//	void	render();
//
//	void	bulletFire(const char* imgName, float x, float y, float angle, float speed, float range);
//	void	bulletMove();												// �̵�
//	void	removeBullet(int arrNum);									// �Ѿ� �����ٶ�
//	void	bulletframe(const char* imgName);
//
//	// �Ѿ� ���� ������
//	vector<tagBullet>			getVBullet() { return _vBullet2; }
//	vector<tagBullet>::iterator	getVIBullet() { return _viBullet2; }
//
//	tagBullet getbullet2() { return bullet2; }
//
//};
//
