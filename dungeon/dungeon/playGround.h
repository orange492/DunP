#pragma once
#include "gameNode.h"

class playGround : public gameNode
{
private:
	

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	playGround();
	~playGround();
	HRESULT Image_init(void);
	HRESULT Sound_init(void);
};

