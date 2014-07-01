#include "HelloWorldScene.h"
#include "tinyxml2\tinyxml2.h"


USING_NS_CC;

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

//	tinyxml2::XMLDocument *doc = new tinyxml2::XMLDocument;
//	tinyxml2::XMLError error= doc->LoadFile("test.xml");
//	CCLog("error ID is %d",error);

	ssize_t size;
	unsigned char* content= FileUtils::getInstance()->getFileData("test.xml","r",&size);
	tinyxml2::XMLDocument *doc = new tinyxml2::XMLDocument;
	doc->Parse((char*)content,size);
//	xmlDoc.Parse(pFileContent, 0, TIXML_ENCODING_UTF8);
	tinyxml2::XMLElement* rootEle = doc->RootElement();
    tinyxml2::XMLElement* dic = rootEle->FirstChildElement();
	tinyxml2::XMLElement* key = dic->FirstChildElement();
	tinyxml2::XMLElement* string = key->NextSiblingElement();
	tinyxml2::XMLElement* array = string->NextSiblingElement();
	tinyxml2::XMLElement* icon0 = array->FirstChildElement();

	std::string filePath = "write.xml";

	tinyxml2::XMLDocument* writeDoc = new tinyxml2::XMLDocument;
	if(NULL == writeDoc)
	{
		CCLog("the wirte file is null!");
	}
	tinyxml2::XMLDeclaration *pDel = writeDoc->NewDeclaration("xml version=\"1.0\" encoding=\"UTF-8\"");
	if(pDel == NULL)
	{
		CCLog("pdel is null");
	}
	writeDoc->LinkEndChild(pDel);
	
	tinyxml2::XMLElement* plistElement = writeDoc->NewElement("plist");
	plistElement->SetAttribute("version","1.0");
	writeDoc->LinkEndChild(plistElement);

	tinyxml2::XMLElement *dicElement = writeDoc->NewElement("dict");
	plistElement->LinkEndChild(dicElement);

	tinyxml2::XMLElement *keyElement = writeDoc->NewElement("key");
	keyElement->LinkEndChild(writeDoc->NewText("keyText"));
	dicElement->LinkEndChild(keyElement);

	tinyxml2::XMLElement *stringElement = writeDoc->NewElement("string");
	stringElement->LinkEndChild(writeDoc->NewText("stringText"));
	dicElement->LinkEndChild(stringElement);

	tinyxml2::XMLElement *arrayElement = writeDoc->NewElement("array");
	dicElement->LinkEndChild(arrayElement);
	for( int i = 0 ; i < 3 ; i++)
	{
		tinyxml2::XMLElement *strEle = writeDoc->NewElement("string");
		strEle->LinkEndChild(writeDoc->NewText("icon"));
		arrayElement->LinkEndChild(strEle);
	}
	tinyxml2::XMLError error = writeDoc->SaveFile(filePath.c_str());
	writeDoc->Print();

	CCLog("error ID is %d",error);
	
	auto label = LabelTTF::create(icon0->GetText(), "Arial", 24);
    
    // position the label on the center of the screen
    label->setPosition(Point(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);

    return true;
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
