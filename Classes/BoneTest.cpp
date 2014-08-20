#include "BoneTest.h"

bool BoneTest::init()
{
	if(!Layer::init())
	{
		return false;
	}
	//cocostudio::ArmatureDataManager::getInstance()->addArmatureFileInfo("tauren0.png","tauren0.plist","tauren.ExportJson");
	ArmatureDataManager::getInstance()->addArmatureFileInfo("tauren.ExportJson");
	_armature = Armature::create("tauren");
	_animation = _armature->getAnimation();
	Size winSize = Director::getInstance()->getWinSize();
	_armature->setPosition(Point(winSize.width/2,winSize.height/2));
	addChild(_armature);

	//CCParticleSystem *p1 = CCParticleSystemQuad::create("sun.plist");
	CCParticleSystem *p1 = CCParticleFire::create();
	addChild(p1);
	Bone *bone = Bone::create("p1");
	bone->addDisplay(p1,0);
	bone->changeDisplayByIndex(0,true);
	bone->setIgnoreMovementBoneData(true);
	bone->setLocalZOrder(100);
	_armature->addBone(bone,"armor");

	auto pic = Skin::create("weapon.png");
	pic->setPositionX(100);
	pic->setFlipX(true);
	_armature->getBone("ax")->addDisplay(pic,1);

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(BoneTest::onTouchBegan,this);
	listener->onTouchMoved = CC_CALLBACK_2(BoneTest::onTouchMoved,this);
	listener->onTouchEnded = CC_CALLBACK_2(BoneTest::onTouchEnded,this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);
	_animationIndex = 0;
	return true;
}
Scene* BoneTest::createScene()
{
	auto scene = Scene::create();
	auto layer = BoneTest::create();
	scene->addChild(layer);
	return scene;
}
bool BoneTest::onTouchBegan(Touch* touch,Event* event)
{
	return true;
}
void BoneTest::onTouchMoved(Touch* touch,Event* event)
{


}
void BoneTest::onTouchEnded(Touch* touch,Event* event)
{
	_animationIndex++;
	if(_animationIndex >=5 )
	{
		_animationIndex = 0;
		_armature->getBone("ax")->changeDisplayWithIndex(1,true);
	}
	_animation->playWithIndex(_animationIndex);
}