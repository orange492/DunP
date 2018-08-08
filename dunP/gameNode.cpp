#include "stdafx.h"
#include "gameNode.h"

gameNode::gameNode()
{
}


gameNode::~gameNode()
{

}

void gameNode::saveData()
{
}

// �ʱ�ȭ �Լ�
HRESULT gameNode::init(void)  
{
	_hdc = GetDC(_hWnd);
	_managerInit = false;
	
	return S_OK;
}

HRESULT gameNode::init(bool managerInit)
{
	_hdc = GetDC(_hWnd);
	_managerInit = managerInit;

	//�Ŵ����� ����Ѵٸ�
	if (_managerInit)
	{
		//SetTimer(_hWnd, 1, 10, NULL);
		KEYMANAGER->init();
		IMAGEMANAGER->init();
		TIMEMANAGER->init();
		SOUNDMANAGER->init();
		EFFECTMANAGER->init();
		SCENEMANAGER->init();
		KEYANIMANAGER->init();
		CAMERAMANAGER->init();
		TXTDATA->init();
		INIDATA->init();
	}


	return S_OK;
}

//�޸� ���� �Լ�
void gameNode::release(void)  
{

	if (_managerInit)
	{
		//KillTimer(_hWnd, 1);
		KEYMANAGER->releaseSingleton();

		IMAGEMANAGER->release();
		IMAGEMANAGER->releaseSingleton();

		TIMEMANAGER->release();
		TIMEMANAGER->releaseSingleton();

		SOUNDMANAGER->release();
		SOUNDMANAGER->releaseSingleton();

		EFFECTMANAGER->release();
		EFFECTMANAGER->releaseSingleton();

		SCENEMANAGER->release();
		SCENEMANAGER->releaseSingleton();

		CAMERAMANAGER->release();
		CAMERAMANAGER->releaseSingleton();

		KEYANIMANAGER->release();
		KEYANIMANAGER->releaseSingleton();

		TXTDATA->release();
		TXTDATA->releaseSingleton();

		INIDATA->releaseSingleton();
	}
	//�ʱ�ȭ���ٶ� GetDC�� ��������Ƿ� DC�������ش�
	ReleaseDC(_hWnd, _hdc);
}

//����
void gameNode::update(void)	  
{
	KEYMANAGER->update();
	SOUNDMANAGER->update();
	CAMERAMANAGER->update();
}

//�׸���
void gameNode::render(void)
{

}

LRESULT gameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;		//���� �� �� �غ��ÿ�1
	HDC hdc;

	switch (iMessage)
	{
		case WM_SETCURSOR:
			SetCursor(NULL);
			return TRUE;
		case WM_LBUTTONDOWN:
			_leftButtonDown = true;
			
		break;
		case WM_LBUTTONUP:
			_leftButtonDown = false;
		break;
		case WM_MOUSEWHEEL:
			if (CAMERAMANAGER->getSelect() != 6) break;
			if ((SHORT)HIWORD(wParam) > 0)
			{
				CAMERAMANAGER->setCameraPoint(PointMake(CAMERAMANAGER->getCameraPoint().x, CAMERAMANAGER->getCameraPoint().y - 110));
				CAMERAMANAGER->setScroll(CAMERAMANAGER->getScroll() - 1);
				if (CAMERAMANAGER->getCameraPoint().y < 50)
				{
					CAMERAMANAGER->setCameraPoint(PointMake(CAMERAMANAGER->getCameraPoint().x, 50));
					CAMERAMANAGER->setScroll(CAMERAMANAGER->getScroll() + 1);
				}
			}
			else
			{
				CAMERAMANAGER->setCameraPoint(PointMake(CAMERAMANAGER->getCameraPoint().x, CAMERAMANAGER->getCameraPoint().y + 110));
				CAMERAMANAGER->setScroll(CAMERAMANAGER->getScroll() + 1);
				if (CAMERAMANAGER->getCameraPoint().y + 750 > 800 + (CAMERAMANAGER->getMonNum() - 13) / 2 * 110)
				{
					if(CAMERAMANAGER->getMonNum()<13)
						CAMERAMANAGER->setCameraPoint(PointMake(CAMERAMANAGER->getCameraPoint().x, 50));
					else
						CAMERAMANAGER->setCameraPoint(PointMake(CAMERAMANAGER->getCameraPoint().x, (CAMERAMANAGER->getMonNum() - 13) / 2 * 110 + 50));
					CAMERAMANAGER->setScroll(CAMERAMANAGER->getScroll() - 1);
				}
				//MessageBox(_hWnd, "�Ʒ��ΰ���", "�Ʒ��ΰ���", NULL);
			}
				return 0;
		break;
		case WM_MOUSEMOVE:
			_ptMouse.x = LOWORD(lParam);
			_ptMouse.y = HIWORD(lParam);
		break;

		case WM_KEYDOWN:
			switch (wParam)
			{
			case VK_ESCAPE:
				//�����ðڽ��ϱ� ��ðڽ��ϱ�?
				this->saveData();
				PostMessage(hWnd, WM_DESTROY, 0, 0);
				break;
			}
			break;

		case WM_DESTROY:
			PostQuitMessage(0);
		break;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

void gameNode::draw(const char* str,HDC hdc,int x, int y)
{
	IMAGEMANAGER->findImage(str)->render(hdc,x,y);
}

void gameNode::fdraw(const char* str, HDC hdc, int x, int y)
{
	IMAGEMANAGER->findImage(str)->frameRender(hdc, x, y);
}

void gameNode::fdraw(const char* str, HDC hdc, int x, int y, int fx, int fy)
{
	IMAGEMANAGER->findImage(str)->frameRender(hdc, x, y,fx,fy);
}