#pragma once
#include "tileNode.h"
#include "gameNode.h"

class monsterManager;

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

class MapTool :	public gameNode
{
private:
	monsterManager * _mM;
	vector<int>				_vDoor;
	vector<int>::iterator	_viDoor;
	tagTile			_tiles[TILEX * TILEY];					//��Ÿ��
	tagCurrentTile	_mouseTile[2];							//�巡���Ҷ� ���콺��ǥ
	tagCurrentTile	_currentTileT;							//���� ����Ÿ��
	tagCurrentTile	_currentTileO;							//���� ������ƮŸ��
	tagCurrentTile	_currentXY;								//���� ��밡���� ��ũ��
	tagSampleTile	_sampleTile[SAMPLETILEX * SAMPLETILEY];	//����Ÿ��
	//DWORD		_attribute[TILEX * TILEY];					//Ÿ�� �Ӽ�	

	RECT		_rc[10];									//��ư ��Ʈ
	RECT		_mrc[14];									//���� ��ư ��Ʈ
	SELECT		_select;									//� ��ư ����������

	SAVEF		_save[3];									//���Կ� ����� �� ����
	SAVEF		_savef;										//���� ���̺�
	image*		_map;										//��ü �� �̹���
	image*		_tempImg;									//�����̹���
	image*		_minimap[3];								//�̴ϸ� ����
	int			_mapX, _mapY;								//�̴ϸʰ��μ���ũ��
	//int			_pos[2];
	int			_stone[2];									//�ִ�,���� �������� ���� ��
	int			_food[2];									//�ִ�,���� �������� �ķ� ��
	int			_monNum;									//���� ��ġ ���� ��
	int			_money;										//���� �������� ���� ��
	int			_drag;										//�巡�� �� _select������ �ٸ� ��� ����
	int			_wall;										//���° �� ����������
	int			_floor;										//���° �ٴ� ����������
	int			_tree;										//���� ���� ����������
	int			_currentMon;								//�� ��° ���� ����������
	
	bool		_side;										//���̵彽�� ��/����
	bool		_canMove;									//������ Ÿ�� Ȯ���Ҷ� �������̰�
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
	void setTerrain(int i, TERRAIN ter, POS pos);
	void setObject(int i, OBJECT obj, POS pos);
	void setOFrame(int i, int x, int y);
	void setTFrame(int i, int x, int y);
	void checkstone();
	int checkstoneTile(int i);
	void findDoor();
	void eraseDoor();
	void setMinimap(int i);
	void setMinimap2();
	void drawMap();
	void drawMap2();
	void drawList(int num);
	void cancelMon(tagCurrentTile i);
	void setup();
	virtual void save();											// ���̺�
	void save(int i);
	virtual void load();											// �ε�
	void load(int i);
	virtual void setmap();

	void setmMMemoryAddressLink(monsterManager* mM) { _mM = mM; }
	TERRAIN		terrainSelect(int FrameX, int FrameY);		// � ������ �����ߴ���
	OBJECT		objSelect(int FrameX, int FrameY);			// ��� ������Ʈ�� �����ߴ���
	tagTile*	getTiles()		{ return _tiles; }			// Ÿ�� ������
	//DWORD*		getAttribute()	{ return _attribute; }		// Ÿ�� �Ӽ� ������
	tagCurrentTile	getCurrentXY() { return _currentXY; }
	int getStone(int i) { return _stone[i]; }
	int getFood(int i) { return _food[i]; }
	bool	getCanMove() { return _canMove; }

	MapTool();
	~MapTool();
};

