#include "stdafx.h"
#include "progressBar.h"


progressBar::progressBar()
{
}


progressBar::~progressBar()
{
}

HRESULT progressBar::init(int x, int y, int width, int height, int index)
{
	_x = x;
	_y = y;

	_rcProgress = RectMake(x, y, width, height);

	sprintf_s(_front, "frontBar%c", (char)index);
	sprintf_s(_back, "backBar%c", (char)index);


	_progressBarTop = IMAGEMANAGER->addImage(_front, "image/UI/hpBarTop.bmp", x, y, width, height, true, RGB(255, 0, 255));
	_progressBarBottom = IMAGEMANAGER->addImage(_back, "image/UI/hpBarBottom.bmp", x, y, width, height, true, RGB(255, 0, 255));

	//����ũ��� �̹����� ����ũ���!
	_width = _progressBarTop->getWidth();

	return S_OK;
}

void progressBar::release()
{
}

void progressBar::update()
{
	_rcProgress = RectMakeCenter(_x, _y, _width, _progressBarTop->getHeight());
}

void progressBar::render()
{

	//�׷��ٶ� �ڿ� ���������� ���� �׸���
	IMAGEMANAGER->render(_back, DC,
		_x,
		_y, 0, 0,
		_progressBarBottom->getWidth(), _progressBarBottom->getHeight());

	//�տ� �������� ����ũ�� Ȥ�� ����ũ�Ⱑ ���ؾ��ϱ⶧���� ������ ũ�Ⱚ�� ����
	IMAGEMANAGER->render(_front, DC,
		_x,
		_y, 0, 0,
		_width, _progressBarBottom->getHeight());
}

void progressBar::setGauge(float currentGauge, float maxGauge)
{
	_width = (currentGauge / maxGauge) * _progressBarBottom->getWidth();
}