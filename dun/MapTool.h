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
	//DWORD		_attribute[TILEX * TILEY];				// 타일 속성	

	RECT		_rc[7];									// 버튼 렉트
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
	virtual void save();											// 세이브
	virtual void load();											// 로드
	virtual void setmap();

	TERRAIN		terrainSelect(int FrameX, int FrameY);		// 어떤 지형을 선택했는지
	OBJECT		objSelect(int FrameX, int FrameY);			// 어던 오브젝트를 선택했는지
	tagTile*	getTiles()		{ return _tiles; }			// 타일 접근자
	//DWORD*		getAttribute()	{ return _attribute; }		// 타일 속성 접근자

	tagCurrentTile	getCurrentXY() { return _currentXY; }
	bool	getCanMove() { return _canMove; }

	MapTool();
	~MapTool();
};

