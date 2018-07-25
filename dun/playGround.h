#pragma once
#include "gameNode.h"
#include "MapTool.h"
#include "monsterManager.h"

//몬스터 나오는 맵 던전2~8 + 보스 => 랜덤맵
enum changeMode { 맵툴, 타이틀};

class playGround : public gameNode
{
private:
	changeMode mode;
	MapTool * _mapTool;
	monsterManager * _mM;

	int _money;
	int _rock;
	int _food;
	

public:
	virtual HRESULT init(void);
	virtual HRESULT Image_init(void);
	virtual HRESULT Sound_init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	void saveData();

	playGround();
	~playGround();
};

