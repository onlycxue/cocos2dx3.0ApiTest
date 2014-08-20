#ifndef _BONETEST_H
#define _BONETEST_H
#include "cocos2d.h"
#include "cocos-ext.h"
#include "CocoStudio.h"
#include "CCArmature.h"
#include "CCArmatureDataManager.h"

USING_NS_CC;
using namespace cocostudio;
class BoneTest:public Layer
{
public:
	virtual bool init();
	
	bool onTouchBegan(Touch* touch,Event* event);
	void onTouchMoved(Touch* touch,Event* event);
	void onTouchEnded(Touch* touch,Event* event);
	static Scene* createScene();
	CREATE_FUNC(BoneTest);
private:
	//Animation* _animation;
	ArmatureAnimation* _animation;
	Armature* _armature;
	int _animationIndex;
};
#endif