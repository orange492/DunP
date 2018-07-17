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
#define CAMERAX 1100
#define CAMERAY 1080

// Ÿ�� �԰�
#define TILESIZE 32
#define TILESIZE2 32

// Ÿ�� �� ������
#define TILESIZEX TILESIZE * TILEX
#define TILESIZEY TILESIZE * TILEY

// ���̴� Ÿ�ϼ�
#define SAMPLETILEX 12
#define SAMPLETILEY 9

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
	OBJ_NONE, 	OBJ_1,	OBJ_2,	OBJ_3,	OBJ_4,   OBJ_6,  OBJ_7 ,  OBJ_8,  OBJ_9 , OBJ_TRAP,	OBJ_ETC
};

// ������ ����
enum POS
{
	//������ �� �÷��̾� ������ ��(��������)	�÷��̾� ����� ����		������ ����		��������
	POS_PLAYER, POS_ENEMY1, POS_ENEMY2, POS_TREASURE
};

// Ÿ�� ����ü
struct tagTile
{
	TERRAIN terrain;			// ����
	OBJECT	object;				// ������Ʈ
	POS		position;			//������
	RECT	rc;					// ��Ʈ
	int		terrainFrameX;		// ���� ������ ��ȣ
	int		terrainFrameY;		// ���� ������ ��ȣ
	int		objFrameX;			// ������Ʈ ������ ��ȣ
	int		objFrameY;			// ������Ʈ ������ ��ȣ
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

#endif 