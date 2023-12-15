#include "MoveLittleHero.h"
#include "ApplyLittleHero.h"
#include "cocos2d.h"
#include<vector>


 // ��̬����ССӢ��
littleHero* littleHero::create(const std::string& filename) {
    littleHero* hero = new littleHero();
    if (hero && hero->initWithFile(filename)) {
        hero->autorelease();
        return hero;
    }
    CC_SAFE_DELETE(hero);
    return nullptr;
}

// ���û�ͣ��������,enabled Ϊ true ʱ���������ƣ�Ϊ false ʱ����
void littleHero::enableMouseControl(bool enabled) {
    if (enabled) {
        if (!_mouseListener) {
            // ��ʼ��������
            initMouseListener();
        }
        // ����������ӵ��¼��ַ���
        _eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);
    }
    else {
        if (_mouseListener) {
            // �Ƴ�������
            _eventDispatcher->removeEventListener(_mouseListener);
        }
    }
}

// ��ʼ������¼�������
void littleHero::initMouseListener() {
    _mouseListener = cocos2d::EventListenerMouse::create();
    _mouseListener->onMouseDown = CC_CALLBACK_1(littleHero::setMouseParameter, this);
}

//���ƶ���Χ��λ�ò�������
void littleHero::setMouseParameter(cocos2d::Event* event) {
    cocos2d::EventMouse* moveToClick = dynamic_cast<cocos2d::EventMouse*>(event);
    if (moveToClick) {
        cocos2d::EventMouse* moveToClick = dynamic_cast<cocos2d::EventMouse*>(event);
        if (moveToClick) {
            //��ȡ�ƶ�λ�õ�����
            cocos2d::Vec2 location = moveToClick->getLocationInView();
            location = cocos2d::Director::getInstance()->convertToGL(location);
            //��֪��y��Ϊʲô�Ƿ��ģ��˴��ֶ�����
            auto refreshSize = cocos2d::Director::getInstance()->getWinSize();
            location.y = refreshSize.height - location.y;

            // ��ȡʵ�ʷֱ���
            cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

            // ��д�˴�����ʱ�ķֱ���Ϊ 2560*1440
            cocos2d::Size designSize = cocos2d::Size(2560, 1440);

            // ����ʵ�ʷֱ�������Ʒֱ��ʵ����ű���
            float scaleX = visibleSize.width / designSize.width;
            float scaleY = visibleSize.height / designSize.height;

            // ��������Ʒֱ����µ�λ�úʹ�С
            cocos2d::Rect designBoardRect(880, 550, 780, 750);

            // ����Ʒֱ����µ���������ת��Ϊʵ�ʷֱ����µ�����
            cocos2d::Rect actualBoardRect(
                designBoardRect.origin.x * scaleX,
                designBoardRect.origin.y * scaleY,
                designBoardRect.size.width * scaleX,
                designBoardRect.size.height * scaleY
            );

            if (actualBoardRect.containsPoint(location)) {
                // �������Ч�����ڣ��ƶ�Ӣ��
                moveHeroToLocation(location);
            }
        }
    }
}

//�ƶ�СС����
void littleHero::moveHeroToLocation(const cocos2d::Vec2& location) {
    // ֹͣ���ж���
    this->stopAllActions();

    // �������߶�����֡
    cocos2d::Vector<cocos2d::SpriteFrame*> walkFrames;
    for (int i = 1; i <= 8; ++i) {
        //�˴��ɿ������Ӽ���ССӢ��
        std::string frameName = "LittlePlayer_1_" + std::to_string(i) + ".png"; //֡ͼƬ
        auto frame = cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName);
        if (frame) {
            walkFrames.pushBack(frame);
        }
    }

    // �������߶���
    auto walkAnimation = cocos2d::Animation::createWithSpriteFrames(walkFrames, 0.1f);//ÿ֡0.1s
    auto walkAnimate = cocos2d::Animate::create(walkAnimation);

    // �����ƶ������ĳ���ʱ��
    float moveDuration = 1.8f;
    auto moveTo = cocos2d::MoveTo::create(moveDuration, location);

    // �����ظ����߶����Ĵ������Ը��������ƶ�ʱ��
    int numRepeats = static_cast<int>(moveDuration / (8 * 0.1f));//��ʱ�����һ�׶�����ʱ��
    auto repeatWalkAnimate = cocos2d::Repeat::create(walkAnimate, numRepeats);

    // ʹ�� Spawn ͬʱִ���ƶ��������ظ������߶���
    auto moveAndAnimate = cocos2d::Spawn::createWithTwoActions(moveTo, repeatWalkAnimate);

    // ����������ɺ�Ļص�����ֹͣ���ж���
    auto callback = cocos2d::CallFunc::create([this]() {
        this->stopAllActions(); // ֹͣ���ж���
        });

    // ���ƶ����������߶����ͻص���ϳ�һ������
    auto sequence = cocos2d::Sequence::create(moveAndAnimate, callback, nullptr);

    // ִ�����ж���
    this->runAction(sequence);
}

void littleHero::stopHeroAction() {
    // ֹͣ���߶������ָ���վ��״̬�ľ���֡
    this->stopAllActions();
    auto frame = cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName("LittlePlayer_1_0.png");
    if (frame) {
        this->setSpriteFrame(frame);
    }
}
