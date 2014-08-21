#include "PhysicsTest.h"

//注意_scene的创建方式
 Scene* PhysicsTest::_scene = Scene::createWithPhysics();
bool PhysicsTest::init()
{
	if(!Layer::init())
	{
		return false;
	}
	_spriteTexture = SpriteBatchNode::create("grossini_dance_atlas.png",100)->getTexture();

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(PhysicsTest::onTouchBegan,this);
	listener->onTouchMoved = CC_CALLBACK_2(PhysicsTest::onTouchMoved,this);
	listener->onTouchEnded = CC_CALLBACK_2(PhysicsTest::onTouchEnded,this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);

	Size size = Director::getInstance()->getWinSize();
	Size offset=Size(100,100);
	auto node = Node::create();
    node->setPhysicsBody(PhysicsBody::createEdgeBox(size-offset));
	node->setPosition(Vec2(size.width/2,size.height/2));
    this->addChild(node);

	Vec2 gravity(0,-80);
	_scene->getPhysicsWorld()->setGravity(gravity);
	_scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	
	addGrossiniAtPosition(Point(size.width/2,size.height/2),1.0f);
	return true;
}
Sprite* PhysicsTest::addGrossiniAtPosition(Point p,float scale)
{
	int posx,posy;
	posx = CCRANDOM_0_1() * 200.0f;
	posy = CCRANDOM_0_1() * 200.0f;

	posx = (posy % 4) * 85;
	posy = (posy % 3) * 121;

	auto sp = Sprite::createWithTexture(_spriteTexture,Rect(posx,posy,85,121));
	sp->setScale(scale);
	sp->setPhysicsBody(PhysicsBody::createBox(Size(100.0f,100.0f)));
	addChild(sp);
	sp->setPosition(p);
	sp->getPhysicsBody()->setTag(128);
	return sp;
}
bool PhysicsTest::onTouchBegan(Touch* touch,Event* event)
{
	auto location = touch->getLocation();
	auto arr = _scene->getPhysicsWorld()->getShapes(location);
	PhysicsBody* body = nullptr;
	for(auto& obj : arr)
	{
		if((obj->getBody()->getTag()&128) != 0)
		{
			body = obj->getBody();
		}
	}

	if (body != nullptr)
	{
		CCLog("yeah you create mouse!");
		Node* mouse = Node::create();
		mouse->setPhysicsBody(PhysicsBody::create(PHYSICS_INFINITY,PHYSICS_INFINITY));
		mouse->getPhysicsBody()->setDynamic(false);
		mouse->setPosition(location);
		this->addChild(mouse);

		PhysicsJointPin* joint = PhysicsJointPin::construct(mouse->getPhysicsBody(),body,location);
		joint->setMaxForce(5000.0f * body->getMass());
		_scene->getPhysicsWorld()->addJoint(joint);
		_mouses.insert(std::make_pair(touch->getID(), mouse));
	}
	return true;
}
void PhysicsTest::onTouchMoved(Touch* touch,Event* event)
{
	auto it = _mouses.find(touch->getID());    
    if (it != _mouses.end())
    {
        it->second->setPosition(touch->getLocation());
    }
}

void PhysicsTest::onTouchEnded(Touch* touch,Event* event)
{
	auto it = _mouses.find(touch->getID());    
    if (it != _mouses.end())
    {
        this->removeChild(it->second);
        _mouses.erase(it);
    }
	//Point location = touch->getLocation();
	
}

Scene* PhysicsTest::createScene()
{
	auto layer = PhysicsTest::create();
	_scene->addChild(layer);
	return _scene;
}