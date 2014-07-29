#ifndef _GUILayer_H_
#define _GUILayer_H_
#include "cocos2d.h"
#include <UIWidget.h>

USING_NS_CC;

class GuiLayer : public LayerColor
{
public:
	virtual bool init();
	void labelInit();
	static GuiLayer* create(Color4B color);
	void restartGameEvent(Ref* sender,cocos2d::ui::TouchEventType type);
	void exitGameEvent(Ref *sender,cocos2d::ui::TouchEventType type);
	CREATE_FUNC(GuiLayer);
private:
	LabelTTF* _label;
};
#endif