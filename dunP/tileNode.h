#pragma once

#ifndef _TILE_H_
#define _TILE_H_

// 타일 갯수(50,50)은 맵의 기본입니당~~, 수정하면 커밋은 바꿔서 올려주세용~~
#define TILEX 100
#define TILEY 100
//(80,25)는 타운맵입니당
//#define TILEX 80
//#define TILEY 25

// 전체 맵 사이즈 입니다   수정 부우탁 드립니다
//#define BACKGROUNDSIZEX TILEX*TILESIZE
//#define BACKGROUNDSIZEY TILEY*TILESIZE

//작은 카메라 사이즈
#define CAMERAX 43*32
#define CAMERAY 1080

// 타일 규격
#define TILESIZE 32
#define TILESIZE2 32

// 타일 총 사이즈
#define TILESIZEX TILESIZE * TILEX
#define TILESIZEY TILESIZE * TILEY

// 샘플 타일셋
#define SAMPLETILEX 9
#define SAMPLETILEY 12

//샘플타일 위치
#define SAMPLEX 120		//뺄셈
#define SAMPLEY 450		//덧셈

// 찍히는 타일셋
#define MAPTILEX 41
#define MAPTILEY 51

// 맵이름
#define MAPNAME "map/myDungen.map"

// 지형	
enum TERRAIN
{
	TR_NULL,	TR_FLOOR,	TR_WATER
};

// 오브젝트
enum OBJECT
{
	OBJ_NULL, 	OBJ_WALL, OBJ_TREE, OBJ_MON ,OBJ_TRAP,	OBJ_ETC
};

// 포지션 정의
enum POS
{
	//워프할 때 플레이어 나오는 곳(워프지점)	플레이어 입장시 리젠		마법진 리젠		보물상자
	POS_1, POS_2, POS_3, POS_4, POS_5, POS_6, POS_7, POS_8, POS_9, POS_10, POS_11, POS_12, POS_13, POS_14, POS_15, POS_16, POS_17, POS_18
};

enum MPOS
{
	MPOS_0, MPOS_1, MPOS_2, MPOS_3, MPOS_4, MPOS_5, MPOS_6, MPOS_7, MPOS_8, MPOS_9
};

// 타일 구조체
struct tagTile
{
	TERRAIN terrain;			// 지형
	OBJECT	object;				// 오브젝트
	POS		position;			//포지션
	MPOS	monPos;
	RECT	rc;					// 렉트
	int		terrainFrameX;		// 지형 프레임 번호
	int		terrainFrameY;		// 지형 프레임 번호
	int		objFrameX;			// 오브젝트 프레임 번호
	int		objFrameY;			// 오브젝트 프레임 번호
	int		type;				//몇 번째 종류의 땅/벽/나무인지
	int		mon;				//어떤 몬스터가 베치되어있는지
	bool	fight;
};

// 타일셋 구조체
struct tagSampleTile
{
	RECT rctile;				// 타일셋 렉트
	int terrainFrameX;			// 타일셋 프레임 번호
	int terrainFrameY;			// 타일셋 프레임 번호
};

// 선택한 파일
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