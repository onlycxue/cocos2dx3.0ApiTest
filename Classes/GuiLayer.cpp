#include "GuiLayer.h"
#include "cocos-ext.h"
#include "CocoStudio.h"
#include "ui/CocosGUI.h"

using namespace ui;
using namespace cocostudio;
bool GuiLayer::init()
{
	if(!LayerColor::init())
	{
		return false;
	}
	Layout* layout = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ccs-ui/menu/menuUI.json"));
	Layout* root = static_cast<Layout*>(layout->getChildByName("Panel"));
	if(!root)
	{
		CCLog("root is null");
	}
	Button* restartButton = static_cast<Button*>(Helper::seekWidgetByName(layout,"restartButton"));
	restartButton->addTouchEventListener(this,toucheventselector(GuiLayer::restartGameEvent));
	Button* exitButton = static_cast<Button*>(Helper::seekWidgetByName(layout,"exitButton"));
	exitButton->addTouchEventListener(this,toucheventselector(GuiLayer::exitGameEvent));

	addChild(layout);
	labelInit();
	return true;
}

void GuiLayer::labelInit()
{
	Size winsize = Director::getInstance()->getWinSize();

	_label = LabelTTF::create("Hello cxue","Arial",24);
	_label->setPosition(Vec2(winsize.width/2,winsize.height/2));
	this->addChild(_label);

}
GuiLayer* GuiLayer::create(Color4B color)
{
	GuiLayer* layer = new GuiLayer();
	if(layer&&layer->initWithColor(color))
	{
		layer->init();
		return layer;
	}
	else
	{
		delete layer;
		return NULL;
	}

}
void GuiLayer::restartGameEvent(Ref* sender,TouchEventType type)
{
	switch (type)
	{
	case TOUCH_EVENT_ENDED:
		_label->setString("restart game");
	default:
		break;
	}
}
void GuiLayer::exitGameEvent(Ref* sender,TouchEventType type)
{
	switch (type)
	{
	case TOUCH_EVENT_ENDED:
		_label->setString("exit game");
	default:
		break;
	}
}