#ifndef _PARTICLESTESTSCENE_H
#define _PARTICLESTESTSCENE_H
#include "cocos2d.h"
USING_NS_CC;
class ParticlesTestScene:public Layer
{
public:
	virtual bool init();
	bool onTouchBegan(Touch* touch,Event* event);
	void onTouchMoved(Touch* touch,Event* event);
	void onTouchEnded(Touch* touch,Event*event);
	static Scene* createScene();
	CREATE_FUNC(ParticlesTestScene);
};

#endif