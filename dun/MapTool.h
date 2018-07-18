#pragma once
#include "tileNode.h"
#include "gameNode.h"

enum SELECT
{
	ROOM,
	ROAD,
	TERRAINDRAW,
	OBJDRAW,
	ITEMDRAW,
	MONSTER,
	ERASER
};


class MapTool :	public gameNode
{
private:
	tagTile		_tiles[TILEX * TILEY];
	tagCurrentTile	_mouseTile[2];
	tagCurrentTile	_currentTileT;
	tagCurrentTile	_currentTileO;
	tagCurrentTile	_currentXY;
	tagSampleTile	_sampleTile[SAMPLETILEX * SAMPLETILEY];
	//DWORD		_attribute[TILEX * TILEY];				// Ÿ�� �Ӽ�	

	RECT		_rc[7];									// ��ư ��Ʈ
	SELECT		_select;

	//int			_pos[2];
	int			_tree;
	int		_drag;

	bool		_canMove;

public:

	HRESULT init();
	void release();
	void update();
	void render();
		
	void setTree();
	void setup();
	virtual void save();											// ���̺�
	virtual void load();											// �ε�
	virtual void setmap();

	TERRAIN		terrainSelect(int FrameX, int FrameY);		// � ������ �����ߴ���
	OBJECT		objSelect(int FrameX, int FrameY);			// ��� ������Ʈ�� �����ߴ���
	tagTile*	getTiles()		{ return _tiles; }			// Ÿ�� ������
	//DWORD*		getAttribute()	{ return _attribute; }		// Ÿ�� �Ӽ� ������

	tagCurrentTile	getCurrentXY() { return _currentXY; }
	bool	getCanMove() { return _canMove; }

	MapTool();
	~MapTool();
};

