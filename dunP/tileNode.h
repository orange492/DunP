#pragma once

#ifndef _TILE_H_
#define _TILE_H_

// Ÿ�� ����(50,50)�� ���� �⺻�Դϴ�~~, �����ϸ� Ŀ���� �ٲ㼭 �÷��ּ���~~
#define TILEX 100
#define TILEY 100
//(80,25)�� Ÿ����Դϴ�
//#define TILEX 80
//#define TILEY 25

// ��ü �� ������ �Դϴ�   ���� �ο�Ź �帳�ϴ�
//#define BACKGROUNDSIZEX TILEX*TILESIZE
//#define BACKGROUNDSIZEY TILEY*TILESIZE

//���� ī�޶� ������
#define CAMERAX 43*32
#define CAMERAY 1080

// Ÿ�� �԰�
#define TILESIZE 32
#define TILESIZE2 32

// Ÿ�� �� ������
#define TILESIZEX TILESIZE * TILEX
#define TILESIZEY TILESIZE * TILEY

// ���� Ÿ�ϼ�
#define SAMPLETILEX 9
#define SAMPLETILEY 12

//����Ÿ�� ��ġ
#define SAMPLEX 120		//����
#define SAMPLEY 450		//����

// ������ Ÿ�ϼ�
#define MAPTILEX 41
#define MAPTILEY 51

// ���̸�
#define MAPNAME "map/myDungen.map"

// ����	
enum TERRAIN
{
	TR_NULL,	TR_FLOOR,	TR_WATER
};

// ������Ʈ
enum OBJECT
{
	OBJ_NULL, 	OBJ_WALL, OBJ_TREE, OBJ_MON ,OBJ_TRAP,	OBJ_ETC
};

// ������ ����
enum POS
{
	//������ �� �÷��̾� ������ ��(��������)	�÷��̾� ����� ����		������ ����		��������
	POS_1, POS_2, POS_3, POS_4, POS_5, POS_6, POS_7, POS_8, POS_9, POS_10, POS_11, POS_12, POS_13, POS_14, POS_15, POS_16, POS_17, POS_18
};

enum MPOS
{
	MPOS_0, MPOS_1, MPOS_2, MPOS_3, MPOS_4, MPOS_5, MPOS_6, MPOS_7, MPOS_8, MPOS_9
};

// Ÿ�� ����ü
struct tagTile
{
	TERRAIN terrain;			// ����
	OBJECT	object;				// ������Ʈ
	POS		position;			//������
	MPOS	monPos;
	RECT	rc;					// ��Ʈ
	int		terrainFrameX;		// ���� ������ ��ȣ
	int		terrainFrameY;		// ���� ������ ��ȣ
	int		objFrameX;			// ������Ʈ ������ ��ȣ
	int		objFrameY;			// ������Ʈ ������ ��ȣ
	int		type;				//�� ��° ������ ��/��/��������
	int		mon;				//� ���Ͱ� ��ġ�Ǿ��ִ���
	bool	fight;
};

// Ÿ�ϼ� ����ü
struct tagSampleTile
{
	RECT rctile;				// Ÿ�ϼ� ��Ʈ
	int terrainFrameX;			// Ÿ�ϼ� ������ ��ȣ
	int terrainFrameY;			// Ÿ�ϼ� ������ ��ȣ
};

// ������ ����
struct tagCurrentTile
{
	int x;
	int y;
};

enum TYPE { GRASS, FIRE, WATER };
enum DIR { DOWN, UP, LEFT, RIGHT, LB, RB, LT, RT };

struct tagMonster
{
	int num;
	//image* img;
	string name;
	TYPE type;
	POINT size;
	float spd;
	float atSpd;
	int hp;
	int power;
	int food;
	int frameX;
	int frameNum;
	bool evolution;
	bool dir[4];
};

struct tagMon
{
	RECT rc;
	int tile;
	int hp;
	int frameNum;
	int frameCount;
	int currentX;
	int currentY;
	int atCount;
	vector<int>				vSlot;
	vector<int>::iterator	viSlot;
};

#endif 