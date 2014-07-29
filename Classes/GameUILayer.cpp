#include "GameUILayer.h"

bool GameUILayer::init()
{
	if(!Layer::init())
	{
		return false;
	}
	Layout* root = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ccs-ui/uilayer/GemUILayer.json"));
	//_rootLayout = static_cast<Layout*>(Helper::seekWidgetByName(root,"Panel"));
	//获取菜单键
	_stopButton = static_cast<Button*>(Helper::seekWidgetByName(root,"MenuButton"));
	_stopButton->addTouchEventListener(this,toucheventselector(GameUILayer::stopButtonEvent));
	//获取进度条
	_timeBar = static_cast<LoadingBar*>(Helper::seekWidgetByName(root,"TimeBar"));
	//_timeBar->setPercent(60);
	//获取分数
	_score = static_cast<TextBMFont*>(Helper::seekWidgetByName(root,"scoreNumber"));
	_score->setString("123456");
	addChild(root);
	_elapsedTime=0;
	this->scheduleUpdate();
	return true;
}
void GameUILayer::update(float dt)
{
	   _elapsedTime += dt;
    int leftSeconds = (int)(60-_elapsedTime);
    if (leftSeconds >= 0) {
        _timeBar->setPercent((60.0-_elapsedTime)/60.0*100);
    }else{
       // Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_DISPATCH_GAMEOVER);
    }
}
void GameUILayer::stopButtonEvent(Ref* target,TouchEventType type)
{
	switch(type)
	{
	case TOUCH_EVENT_ENDED:
		Director::getInstance()->end();
		break;
	default:
		break;
	}
		
}
void GameUILayer::setScore(int num)
{
	char number[100];
	sprintf(number,"%d",num);
	_score->setString(number);
}
void GameUILayer::setTimeBarPercent(float percent)
{
	_timeBar->setPercent(percent);
}
int GameUILayer::getScore()
{
	std::string numStr = _score->getString();
	return atoi(numStr.c_str());
}
float GameUILayer::getTimeBarPercent()
{
	return _timeBar->getPercent();
}