#ifndef _GAME_UI_LAYER_H
#define _GAME_UI_LAYER_H
#include "cocos2d.h"
#include "cocos-ext.h"
#include "CocoStudio.h"
#include "ui/CocosGUI.h"
#include <UIWidget.h>

USING_NS_CC;
using namespace ui;

class GameUILayer :public Layer
{
public:
	virtual bool init();
	void stopButtonEvent(Ref* target,TouchEventType type);
	void setScore(int num);
	void setTimeBarPercent(float percent);
	int getScore();
	float getTimeBarPercent();
	void update(float dt);
	CREATE_FUNC(GameUILayer);
private:
	Layout* _rootLayout;
	Button* _stopButton;
	LoadingBar* _timeBar;
	TextBMFont* _score;
	float _elapsedTime;
};

#endif