#include "stdafx.h"
#include "actionTest.h"


actionTest::actionTest()
{
}


actionTest::~actionTest()
{
}

HRESULT actionTest::init()
{
	_action = new action;
	_action->init();

	_actionImage = IMAGEMANAGER->findImage("오브젝트");
	_actionImage->setX(WINSIZEX / 2);
	_actionImage->setY(WINSIZEY / 2);

	_action->moveTo(_actionImage, 50, 50, 5.0f);

	return S_OK;
}

void actionTest::release()
{
}

void actionTest::update()
{
	_action->update();
}

void actionTest::render()
{
	_actionImage->render(getMemDC(), _actionImage->getX(), _actionImage->getY());
}
