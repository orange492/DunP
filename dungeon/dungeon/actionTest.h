#pragma once
#include "gameNode.h"
#include "action.h"

class actionTest : public gameNode
{
private:
	action* _action;
	image* _actionImage;

public:
	actionTest();
	~actionTest();

	HRESULT init();
	void release();
	void update();
	void render();
};

