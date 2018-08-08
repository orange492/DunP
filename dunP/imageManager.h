#pragma once
#include "singletonBase.h"
#include "image.h"
#include <map>

class imageManager : public singletonBase<imageManager>
{
private:
	typedef map<string, image*>				mapImageList;
	typedef map<string, image*>::iterator	mapImageIter;

private:
	mapImageList _mImageList;

public:
	imageManager();
	~imageManager();

	HRESULT init(void);
	void release(void);

	image* addImage(string strKey, int width, int height, BOOL blend = FALSE);
	image * addImage(string strKey, int width, int height, bool trans, COLORREF transColor, BOOL blend = FALSE);
	image* addImage(string strKey, const char* fileName, int width, int height, bool trans, COLORREF transColor, BOOL blend = FALSE);
	image* addImage(string strKey, const char* fileName, float x, float y, int width, int height, bool trans, COLORREF transColor, BOOL blend = FALSE);

	image* addFrameImage(string strKey, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor, BOOL blend = FALSE);
	image* addFrameImage(string strKey, const char* fileName, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor, BOOL blend = FALSE);

	image * addRotateImage(string strKey, const char * fileName, int width, int height, bool trans, COLORREF transColor, BOOL blend = FALSE);

	image * addRotateImage(string strKey, int width, int height, bool trans, COLORREF transColor, BOOL blend);

	//image * addRotateImage(string strKey, int width, int height, BOOL blend);

	image * addRotateFrameImage(string strKey, const char * fileName, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor, BOOL blend = FALSE);



	//rotate
	void rotateRender(string strKey, HDC hdc, float x, float y, float angle);
	void rotateFrameRender(string strKey, HDC hdc, float x, float y, float angle);
	//Ű �� ã�� �Լ�
	image* findImage(string strKey);

	//�̱���ȭ �Ǿ��ִ� �̹��� �����ִ� �Լ�
	BOOL deleteImage(string strKey);

	//��� �̹��� ���� �Լ�
	BOOL deleteAll(void);

	void render(string strKey, HDC hdc);
	void render(string strKey, HDC hdc, int destX, int destY);
	void render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	//�����ӷ��� + ���������� �������� �߰��غ�����~
	void frameRender(string strKey, HDC hdc, int destX, int destY);
	void frameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);


	
	void loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offSetX, int offSetY);

	void alphaRender(string strKey, HDC hdc, BYTE alpha);
	void alphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

	void alphaFrameRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha);
	void alphaFrameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha);

	void alphaLoopRender(string strKey, HDC hdc, const LPRECT drawArea, int offSetX, int offSetY, BYTE alpha);

};
