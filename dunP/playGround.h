#pragma once
#include "gameNode.h"
#include "MapTool.h"
#include "monsterManager.h"
#include "star.h"

//���� ������ �� ����2~8 + ���� => ������
enum changeMode { ����, Ÿ��Ʋ};

class playGround : public gameNode
{
private:
	star * _star;
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

