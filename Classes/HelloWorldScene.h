#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Box2D\Box2D.h"
#include "GLES-Render.h"
#include <iostream>
#include "math\kazmath\kazmath\vec2.h"

USING_NS_CC;

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
	void update(float dt);
    void draw(Renderer *renderer,const kmMat4& transform, bool transformUpdated);
	b2World* world;
    
	bool onTouchBegan(Touch* touch,Event* event);
	void onTouchMoved(Touch* touch,Event* event);
	void onTouchEnd(Touch* touch,Event* event);
private:
	b2Body* groundBody;
	b2MouseJoint* mouseJoint;
};

#endif // __HELLOWORLD_SCENE_H__
