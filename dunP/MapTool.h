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

	tagTile			_tiles[TILEX * TILEY];					//��Ÿ��
	tagCurrentTile	_mouseTile[2];							//�巡���Ҷ� ���콺��ǥ
	tagCurrentTile	_currentTileT;							//���� ����Ÿ��
	tagCurrentTile	_currentTileO;							//���� ������ƮŸ��
	tagCurrentTile	_currentXY;								//���� ��밡���� ��ũ��
	tagSampleTile	_sampleTile[SAMPLETILEX * SAMPLETILEY];	//����Ÿ��	

	RECT		_rc[10];									//��ư ��Ʈ
	RECT		_mrc[14];									//���� ��ư ��Ʈ
	SELECT		_select;									//� ��ư ����������

	SAVEF		_save[3];									//���Կ� ����� �� ����
	SAVEF		_savef;										//���� ���̺�
	SAVEM		_savem;
	image*		_map;										//��ü �� �̹���
	image*		_tempImg;									//�����̹���
	image*		_minimap[3];								//�̴ϸ� ����

	int			_mapX, _mapY;								//�̴ϸʰ��μ���ũ��
	int			_stone[2];									//�ִ�,���� �������� ���� ��
	int			_food[2];									//�ִ�,���� �������� �ķ� ��
	int			_money;										//���� �������� ���� ��
	int			_monNum;									//���� ��ġ ���� ��
	int			_drag;										//�巡�� �� _select������ �ٸ� ��� ����
	int			_wall;										//���° �� ����������
	int			_floor;										//���° �ٴ� ����������
	int			_tree;										//���� ���� ����������
	int			_currentMon;								//�� ��° ���� ����������
	int			_player;
	int			_stage;
	int			_day;
	int			_monCount;
	int			_interval;
	int			_bulletCount;
	int			_ballCount;

	bool		_side;										//���̵彽�� ��/����
	bool		_eraser;									//���� ���찳 ����������

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
	virtual void save();											// ���̺�
	void save(int i);
	virtual void load();											// �ε�
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

	TERRAIN		terrainSelect(int FrameX, int FrameY);		// � ������ �����ߴ���
	OBJECT		objSelect(int FrameX, int FrameY);			// ��� ������Ʈ�� �����ߴ���
	tagTile*	getTiles()		{ return _tiles; }			// Ÿ�� ������
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

