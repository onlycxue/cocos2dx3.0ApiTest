#include "HelloWorldScene.h"
#include "GLES-Render.h"


#define PTM_RATIO 32

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

	Size screenSize = Director::getInstance()->getWinSize();
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = LabelTTF::create("Hello World", "Arial", 24);
    
    // position the label on the center of the screen
    label->setPosition(Point(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("random.png");

    // position the sprite on the center of the screen
    //sprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
	 this->addChild(sprite, 0);
    
	b2Vec2 gravity;
	gravity.Set(0.0f,-10.0f);
	//构造世界
	bool doSleep = true;
	world =  new b2World(gravity);
	world->SetAllowSleeping(doSleep);
	world->SetContinuousPhysics(true);

	//开启调试	
	GLESDebugDraw* m_debugDraw=new GLESDebugDraw(PTM_RATIO);  
	world->SetDebugDraw(m_debugDraw);  
	uint32 flags = 0;  
//	flags += b2Draw::e_shapeBit;  
//	flags += b2Draw::e_jointBit;  
	//flags += b2Draw::e_aabbBit;  
//	flags += b2Draw::e_pairBit;  
//	flags += b2Draw::e_centerOfMassBit; 

	m_debugDraw->SetFlags(flags); 

	//创建边框刚体
	b2BodyDef groundBodyDef;
	groundBody = world->CreateBody(&groundBodyDef);
	//给边框刚体创建夹具
	b2PolygonShape groundbox;
	groundbox.SetAsBox(screenSize.width/PTM_RATIO,0,b2Vec2(0,0),0);
	groundBody->CreateFixture(&groundbox,0);

	groundbox.SetAsBox(screenSize.width/PTM_RATIO,0,b2Vec2(0,screenSize.height/PTM_RATIO),0);
	groundBody->CreateFixture(&groundbox,0);

	groundbox.SetAsBox(0,screenSize.height/PTM_RATIO,b2Vec2(0,0),0);
	groundBody->CreateFixture(&groundbox,0);

	groundbox.SetAsBox(0,screenSize.height/PTM_RATIO,b2Vec2(screenSize.width/PTM_RATIO,0),0);
	groundBody->CreateFixture(&groundbox,0);

	//定义一个刚体
	b2BodyDef bodyDef;
	
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(screenSize.width/2/PTM_RATIO,screenSize.height/PTM_RATIO);
	bodyDef.userData = sprite;  //用于同步跟新精灵的属性

	//创建这个刚体
	b2Body *body = world->CreateBody(&bodyDef);
	
	//b2PolygonShape dynamicBox;
	//dynamicBox.SetAsBox(1.0f,1.0f);
	b2CircleShape circle;
	circle.m_radius = 1.2f;
	//定义刚体的夹具属性
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circle;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 0.6;
	body->CreateFixture(&fixtureDef);
	
	//world->SetContactListener(this);
        
	
//	int velocity = 8;
//	int position = 1;
//	world->Step(0.03,velocity,position);
	world->DrawDebugData();
	this->scheduleUpdate();
	//监听触摸事件
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan,this);
	listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved,this);
	listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnd,this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);
    return true;
}

void  HelloWorld::update(float dt)
{
	int velocity = 8;
	int position = 1;
	world->Step(dt,velocity,position);
	//同步精灵与刚体的位置
	for(b2Body *b = world->GetBodyList();b;b= b->GetNext())
	{
		if(b->GetUserData() != NULL)
		{
			auto myActor = (Sprite*)b->GetUserData();
			Point nodePos = myActor->getParent()->convertToWorldSpace(Point(b->GetPosition().x* PTM_RATIO,b->GetPosition().y*PTM_RATIO));
			myActor->setPosition(nodePos);
			myActor->setRotation( -1 * CC_RADIANS_TO_DEGREES(b->GetAngle()) );
		}
	}
}

//实时画box2d的debug数据。
void HelloWorld::draw(Renderer *renderer, const kmMat4& transform, bool transformUpdated)
{
    ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );   
    kmGLPushMatrix();  
    world->DrawDebugData();  
    kmGLPopMatrix();     


}
void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
bool HelloWorld::onTouchBegan(Touch* touch,Event* event)
{
	Point mousePt = touch->getLocation();
	b2Body *pBody = world->GetBodyList();
	for(;pBody != NULL;pBody = pBody->GetNext())
	{
		//根据刚体获取其夹具
		b2Fixture *pFixture = pBody->GetFixtureList();
		for(;pFixture != NULL;pFixture = pFixture->GetNext())
		{
			b2Vec2 mouseVec;
			mouseVec.Set(mousePt.x/PTM_RATIO,mousePt.y/PTM_RATIO);
			//判断当前的点是否在夹具上
			if(pFixture->TestPoint(mouseVec))
			{
				CCLog("mouseVec is in Point!\n");
				//定义鼠标关节
				b2MouseJointDef md;
				md.bodyA = groundBody;
				md.bodyB = pBody;
				md.target = mouseVec;
				md.maxForce = 1000.0f * pBody->GetMass();
				mouseJoint = (b2MouseJoint*)world->CreateJoint(&md);
				if(mouseJoint==NULL)
				{
					CCLog("mouseJoint is Null!\n");
				}
				pBody->SetAwake(true);
				return true;
			}
		}

	}
	return false;
}
void HelloWorld::onTouchMoved(Touch* touch,Event* event)
{
	CCPoint nodePos = convertToNodeSpace(touch->getLocation());
	b2Vec2 mouseWorldPos = b2Vec2(nodePos.x/PTM_RATIO,nodePos.y/PTM_RATIO);

	if(mouseJoint)
	{
		CCLOG("mouse Joint is ok");
		//跟新关节的位置
		mouseJoint->SetTarget(mouseWorldPos);
	}
}
void HelloWorld::onTouchEnd(Touch* touch,Event* event)
{
	if(mouseJoint)
	{
		CCLog("mouseJoint is delete\n");
		//删除关节
		world->DestroyJoint(mouseJoint);
		mouseJoint = NULL;
	}
}