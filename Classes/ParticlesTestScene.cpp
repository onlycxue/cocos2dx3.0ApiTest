#include "ParticlesTestScene.h"

bool ParticlesTestScene::init()
{
	if(!Layer::init())
	{
		return false;
	}
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(ParticlesTestScene::onTouchBegan,this);
	listener->onTouchMoved = CC_CALLBACK_2(ParticlesTestScene::onTouchMoved,this);
	listener->onTouchEnded = CC_CALLBACK_2(ParticlesTestScene::onTouchEnded,this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);
	return true;
}
bool ParticlesTestScene::onTouchBegan(Touch* touch,Event* event)
{

	auto particle = ParticleSystemQuad::create("Desktop.plist");
	particle->setTexture(TextureCache::getInstance()->addImage("fire.png"));
	particle->setPosition(touch->getLocation());
	particle->setBlendAdditive(true);
	//particle->runAction(EaseOut::create(MoveTo::create(2,Vec2(0,0)),2.0f));
	particle->runAction(MoveTo::create(2,Vec2(0,0)));
	addChild(particle,10);
	return true;
}
void ParticlesTestScene::onTouchMoved(Touch* touch,Event* event)
{
//	auto particle = ParticleFire::create();
//	particle->setTexture(TextureCache::getInstance()->addImage("fire.png"));
//	particle->setPosition(touch->getLocation());
//	particle->runAction(EaseOut::create(MoveTo::create(2,Vec2(0,0)),2.0f));
//	addChild(particle,10);
}
void ParticlesTestScene::onTouchEnded(Touch* touch,Event*event)
{

}
Scene* ParticlesTestScene::createScene()
{
	auto layer = ParticlesTestScene::create();
	auto scene = Scene::create();
	scene->addChild(layer);
	return scene;
}