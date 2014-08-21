#ifndef _PHYSICSTEST_H
#define _PHYSICSTEST_H
#include "cocos2d.h"

USING_NS_CC;

class PhysicsTest:public Layer
{
public:
	virtual bool init();
	Sprite* addGrossiniAtPosition(Point p,float scale);

	bool onTouchBegan(Touch* touch,Event* event);
	void onTouchMoved(Touch* touch,Event* event);
	void onTouchEnded(Touch* touch,Event* event);
	static Scene* createScene();

	CREATE_FUNC(PhysicsTest);
private:
	Texture2D* _spriteTexture;
	static Scene* _scene;
	std::unordered_map<int, Node*> _mouses;

};
#endif