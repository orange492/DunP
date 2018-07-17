#pragma once
#include "gameNode.h"
#include "MapTool.h"

//���� ������ �� ����2~8 + ���� => ������
enum changeMode { ����, Ÿ��Ʋ};

class playGround : public gameNode
{
private:
	changeMode mode;
	MapTool * _mapTool;
	

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

