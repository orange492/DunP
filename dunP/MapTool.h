#pragma once
#include "tileNode.h"
#include "gameNode.h"
#include "progressBar.h"
#include "Bullet.h"

class monsterManager;
class star;

enum SELECT
{
	ROOM,
	HROAD,
	VROAD,
	TERRAINDRAW,
	OBJDRAW,
	ITEMDRAW,
	MONSTER,
	SAVE,
	LOAD
};

struct SAVEF
{
	tagCurrentTile current;
	int stone;
};

struct SAVEM
{
	tagCurrentTile current;
	int stone[2];
	int food[2];
	int money;
	int day;
};

struct tagMon
{
	progressBar *hpbar;
	RECT rc;
	float hp;
	int id;
	int tile;
	int frameNum;
	int frameCount;
	int currentX;
	int currentY;
	int atCount;
	vector<int>				vSlot;
	vector<int>::iterator	viSlot;
};

class MapTool :	public gameNode
{
private:
	monsterManager * _mM;
	star * _star;
	Bullet* _bullet;


	vector<tagMon>				_vMon;
	vector<tagMon>::iterator	_viMon;

	vector<int>				_vMonNum;
	vector<int>::iterator	_viMonNum;

	vector<int>				_vDoor;
	vector<int>::iterator	_viDoor;
	
	vector<int>				_vRoad;
	vector<int>::iterator	_viRoad;

	tagTile			_tiles[TILEX * TILEY];					//맵타일
	tagCurrentTile	_mouseTile[2];							//드래그할때 마우스좌표
	tagCurrentTile	_currentTileT;							//현재 지형타일
	tagCurrentTile	_currentTileO;							//현재 오브젝트타일
	tagCurrentTile	_currentXY;								//현재 사용가능한 맵크기
	tagSampleTile	_sampleTile[SAMPLETILEX * SAMPLETILEY];	//샘플타일	

	RECT		_rc[10];									//버튼 렉트
	RECT		_mrc[14];									//몬스터 버튼 렉트
	SELECT		_select;									//어떤 버튼 선택중인지

	SAVEF		_save[3];									//슬롯에 저장된 맵 정보
	SAVEF		_savef;										//템프 세이브
	SAVEM		_savem;
	image*		_map;										//전체 맵 이미지
	image*		_tempImg;									//템프이미지
	image*		_minimap[3];								//미니맵 정보

	int			_mapX, _mapY;								//미니맵가로세로크기
	int			_stone[2];									//최대,현재 보유중인 벽돌 수
	int			_food[2];									//최대,현재 보유중인 식량 수
	int			_money;										//현재 보유중인 돈의 양
	int			_monNum;									//현재 배치 몬스터 수
	int			_drag;										//드래그 후 _select에따라 다른 기능 실행
	int			_wall;										//몇번째 벽 선택중인지
	int			_floor;										//몇번째 바닥 선택중인지
	int			_tree;										//무슨 나무 선택중인지
	int			_currentMon;								//몇 번째 몬스터 선택중인지
	int			_player;
	int			_stage;
	int			_day;
	int			_monCount;
	int			_interval;
	int			_bulletCount;
	int			_ballCount;

	bool		_side;										//사이드슬롯 온/오프
	bool		_eraser;									//무슨 지우개 선택중인지

public:

	HRESULT init();
	void release();
	void update();
	void render();
		
	void setTree();
	void setWall(int i);
	void setFloor(int i);
	void set_wall(int i);
	void set_floor(int i);
	void dragMake();
	void wallDir();
	void floorDir();
	void setPosition(int i, TERRAIN ter, OBJECT obj, POS pos, int type);
	void setOFrame(int i, int x, int y);
	void setTFrame(int i, int x, int y);
	void checkstone();
	int checkstoneTile(int i);
	void findDoor();
	void setMinimap(int i);
	void setMinimap2();
	void drawMap();
	void drawMap2(bool first);
	void drawList(int num);
	void cancelMon(tagCurrentTile i, bool drag, bool die);
	tagCurrentTile findMon(tagCurrentTile i);
	void findRoad();
	void setMon(int i);
	int findMonVec(int i);
	void monFrame();
	void monUpdate();
	void collision();
	void setup();
	virtual void save();											// 세이브
	void save(int i);
	virtual void load();											// 로드
	void load(int i);
	virtual void setmap();
	int	 findMon(int i);

	void setmMMemoryAddressLink(monsterManager* mM) { _mM = mM; }
	void setStarMemoryAddressLink(star* star) { _star = star; }

	void setMonHp(int i, int hp) { _vMon[i].hp = hp; }
	void setMoney(int money) { _money = money; }
	void setFight(int i,bool fight) { _tiles[i].fight=fight; }
	void setStage(int i) { _stage = i; }
	void setCount(int i) { _monCount = i; }
	void setSide(bool i) { _side = i; }

	TERRAIN		terrainSelect(int FrameX, int FrameY);		// 어떤 지형을 선택했는지
	OBJECT		objSelect(int FrameX, int FrameY);			// 어던 오브젝트를 선택했는지
	tagTile*	getTiles()		{ return _tiles; }			// 타일 접근자
	tagCurrentTile	getCurrentXY() { return _currentXY; }
	vector<int> getDoor() { return _vDoor; }
	vector<tagMon> getMon() { return _vMon; }

	int getSelect() { return _select; }
	int getStone(int i) { return _stone[i]; }
	int getFood(int i) { return _food[i]; }
	int getMoney() { return _money; }
	int getPlayer() { return _player; }
	int	getStage() { return _stage; }
	int	getDay() { return _day; }
	int	getBallCount() { return _ballCount; }
	bool	getFight(int i) { return _tiles[i].fight; }

	MapTool();
	~MapTool();
};

