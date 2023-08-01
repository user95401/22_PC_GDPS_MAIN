#include "EventLevelPage.hpp"

const char* EventLevelPage::getEventTimeString()
{
    switch (rand() % 22)
    {
    case 0:
        return "New event level in ... ?";
    case 1:
        return  "Events are pretty random";
    case 2:
        return  "Next event in random hours from now";
    case 3:
        return  "When is the next event?";
    case 4:
        return  "NEW EVENT! .... soon";
    case 5:
        return  "Why did I program this...";
    case 6:
        return  "I believe in you";
    case 7:
        return  "You can do it";
    case 8:
        return  "Next one is a banger";
    case 10:
        return  "This is fun";
    case 11:
        return  "I can't find anything";
    case 12:
        return  "Why is this a thing";
    case 13:
        return  "Do or do not. There is no try";
    case 14:
        return  "The cake is a lie";
    case 15:
        return  "Challenge accepted";
    case 16:
        return  "I wonder what's next";
    case 17:
        return  "Welcome to the event";
    case 18:
        return  "Jump cube, jump";
    case 19:
        return  "No event for you";
    case 20:
        return  "This looks interesting";
    case 21:
        return  "Free event is free";
    default:
        return "Why did I program this...";
    }
}

bool EventLevelPage::init() {
	auto winSize = CCDirector::sharedDirector()->getWinSize();
	if (!this->initWithColor({ 0, 0, 0, 0 })) return false;
	this->runAction(CCFadeTo::create(0.1,150));
	m_pLayer = CCLayer::create();
	this->addChild(m_pLayer);/*
	m_pLayer->runAction(CCSequence::create(
		CCMoveTo::create(0.0f, { 0, winSize.height / 2 }), 
		CCEaseBackOut::create(CCMoveTo::create(0.2f, { winSize.width / 2, winSize.height / 2 })),
		CCEaseBackOut::create(CCMoveBy::create(0.05f, { -3, 0 })),
		CCEaseBackOut::create(CCMoveBy::create(0.15f, { 4, 0 })),
		CCEaseBackOut::create(CCMoveBy::create(0.1f, { -1, 0 })),
		nullptr)
	);*/
	m_pLayer->setPosition({ 0, winSize.height / 2 });
	m_pLayer->runAction(CCEaseElasticOut::create(CCMoveTo::create(0.5f, ModUtils::getCenterPoint()), 0.6f));//:facepalm:

	m_pButtonMenu = CCMenu::create();
	m_pLayer->addChild(m_pButtonMenu, 5);

	auto bg = CCScale9Sprite::create("GJ_square04.png", { 0.0f, 0.0f, 80.0f, 80.0f });
	bg->setContentSize({ 420.000f, 280.000f });
	bg->setColor({ 193, 47, 251 });
	m_pLayer->addChild(bg);

	CCSprite* dailyLevelCorner1 = ModUtils::createSprite("dailyLevelCorner_001.png");
	dailyLevelCorner1->setPosition({ -185.500f, -115.500f });
	m_pLayer->addChild(dailyLevelCorner1);

	CCSprite* dailyLevelCorner2 = ModUtils::createSprite("dailyLevelCorner_001.png");
	dailyLevelCorner2->setPosition({ -185.500f, 115.500f });
	dailyLevelCorner2->setScaleY(-1);
	m_pLayer->addChild(dailyLevelCorner2);

	CCSprite* dailyLevelCorner3 = ModUtils::createSprite("dailyLevelCorner_001.png");
	dailyLevelCorner3->setPosition({ 185.500f, -115.500f });
	dailyLevelCorner3->setScaleX(-1);
	m_pLayer->addChild(dailyLevelCorner3);

	CCSprite* eventLevelLabel_001 = ModUtils::createSprite("eventLevelLabel_001.png");
	eventLevelLabel_001->setPosition({ 0.0f, 110.000f });
	m_pLayer->addChild(eventLevelLabel_001);

	m_pButtonMenu->addChild(CCMenuItemSpriteExtra::create(ModUtils::createSprite("GJ_closeBtn_001.png"), this, menu_selector(EventLevelPage::onClose)));
	m_pButtonMenu->setPosition({ -200.000f, 130.000f });
	auto historyBtn = gd::CCMenuItemSpriteExtra::create(ModUtils::createSprite("GJ_safeBtn_001.png"),this,nullptr);
	historyBtn->setPosition({ 380.0f, -20.0f });
	m_pButtonMenu->addChild(historyBtn);

	auto textBg = CCScale9Sprite::create("square02_001.png", { 0.0f, 0.0f, 80.0f, 80.0f });
	m_pLayer->addChild(textBg);
	textBg->setContentSize({ 380.000f, 116.000f });
	textBg->setOpacity(60);

	CCLabelBMFont* text = CCLabelBMFont::create("00:00:00", "bigFont.fnt");
	text->setScale(0.6);
	m_pLayer->addChild(text);

	CCLabelBMFont* text2 = CCLabelBMFont::create(getEventTimeString(), "goldFont.fnt");
	text2->setPosition(0, -125.000);
	text2->setScale(0.5);
	m_pLayer->addChild(text2);

	this->setKeypadEnabled(true);
	this->setTouchEnabled(true);

	return true;
}

void EventLevelPage::onClose(cocos2d::CCObject*) {
	removeFromParentAndCleanup(true);
}

EventLevelPage* EventLevelPage::create() {
	EventLevelPage* pRet = new EventLevelPage();
	if (pRet && pRet->init()) {
		pRet->autorelease();
		return pRet;
	}
	else {
		CC_SAFE_DELETE(pRet);
		return nullptr;
	}
}