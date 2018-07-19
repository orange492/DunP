#pragma once
#include "tileNode.h"
#include "gameNode.h"

enum SELECT
{
	ROOM,
	HROAD,
	VROAD,
	TERRAINDRAW,
	OBJDRAW,
	ITEMDRAW,
	MONSTER
};


class MapTool :	public gameNode
{
private:
	tagTile		_tiles[TILEX * TILEY];						//��Ÿ��
	tagCurrentTile	_mouseTile[2];							//�巡���Ҷ� ���콺��ǥ
	tagCurrentTile	_currentTileT;							//���� ����Ÿ��
	tagCurrentTile	_currentTileO;							//���� ������ƮŸ��
	tagCurrentTile	_currentXY;								//���� ��밡���� ��ũ��
	tagSampleTile	_sampleTile[SAMPLETILEX * SAMPLETILEY];	//����Ÿ��
	//DWORD		_attribute[TILEX * TILEY];					// Ÿ�� �Ӽ�	

	RECT		_rc[10];									// ��ư ��Ʈ
	SELECT		_select;									//� ��ư ����������

	//int			_pos[2];
	int			_rock[2];									//�ִ�,���� �������� ���� ��
	int			_food[2];									//�ִ�,���� �������� �ķ� ��
	int			_drag;										//�巡�� �� _select������ �ٸ� ��� ����
	int			_wall;										//���° �� ����������
	int			_floor;										//���° �ٴ� ����������
	int			_tree;										//���� ���� ����������

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
	void setPosition(int i, TERRAIN ter, OBJECT obj, POS pos);
	void setOFrame(int i, int x, int y);
	void setTFrame(int i, int x, int y);
	void checkRock();
	int checkRockTile(int i);
	void setup();
	virtual void save();											// ���̺�
	virtual void load();											// �ε�
	virtual void setmap();

	TERRAIN		terrainSelect(int FrameX, int FrameY);		// � ������ �����ߴ���
	OBJECT		objSelect(int FrameX, int FrameY);			// ��� ������Ʈ�� �����ߴ���
	tagTile*	getTiles()		{ return _tiles; }			// Ÿ�� ������
	//DWORD*		getAttribute()	{ return _attribute; }		// Ÿ�� �Ӽ� ������
	tagCurrentTile	getCurrentXY() { return _currentXY; }
	int getRock(int i) { return _rock[i]; }
	int getFood(int i) { return _food[i]; }
	bool	getCanMove() { return _canMove; }

	MapTool();
	~MapTool();
};

