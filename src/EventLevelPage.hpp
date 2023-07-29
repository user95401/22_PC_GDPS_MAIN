#ifndef __EventLevelPage_H__
#define __EventLevelPage_H__

#include <cocos2d.h>
#include <gd.h>
using namespace cocos2d;
using namespace gd;
using namespace cocos2d::extension;
#include "../../curly-eureka/mod_utils.hpp"

class EventLevelPage : public gd::FLAlertLayer {
protected:
	virtual bool init();
	void onClose(cocos2d::CCObject*);
public:
	static EventLevelPage* create();
	const char* getEventTimeString();
};

#endif