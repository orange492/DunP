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
#define SAMPLEX 150		//����
#define SAMPLEY 500		//����

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
	OBJ_NONE, 	OBJ_WALL, OBJ_TREE, OBJ_TRAP,	OBJ_ETC
};

// ������ ����
enum POS
{
	//������ �� �÷��̾� ������ ��(��������)	�÷��̾� ����� ����		������ ����		��������
	POS_1, POS_2, POS_3, POS_4, POS_5, POS_6, POS_7, POS_8, POS_9, POS_10, POS_11, POS_12, POS_13, POS_14, POS_15, POS_16, POS_17, POS_18
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