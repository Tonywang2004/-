#include "MoveLittleHero.h"
#include "ApplyLittleHero.h"
#include "cocos2d.h"
#include<vector>

//��ʼ��,ȷ����ɫ
littleHero::littleHero() : numPlayer(3) {
}

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
            //���ؽ�ɫͼƬ
            preloadWalkingFrames(numPlayer);
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
        //����Ƿ�Ϊ�Ҽ�����ƶ�
        if (moveToClick && moveToClick->getMouseButton() == cocos2d::EventMouse::MouseButton::BUTTON_RIGHT) {
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
            cocos2d::Rect designBoardRect(400,250,1880,1080);

            // ����Ʒֱ����µ���������ת��Ϊʵ�ʷֱ����µ�����
            cocos2d::Rect actualBoardRect(
                designBoardRect.origin.x * scaleX,
                designBoardRect.origin.y * scaleY,
                designBoardRect.size.width * scaleX,
                designBoardRect.size.height * scaleY
            );

            if (actualBoardRect.containsPoint(location)) {
                // �������Ч�����ڣ��ƶ�Ӣ��
                moveHeroToLocation(location, numPlayer);
            }

        }
    }
}

//�ƶ�СС����
void littleHero::moveHeroToLocation(const cocos2d::Vec2& location, const int& numPlayer) {
    // ֹͣ���ж���
    this->stopHeroAction(numPlayer);

    // �������߶�����֡
    cocos2d::Vector<cocos2d::SpriteFrame*> walkFrames;
    for (int i = 0; i <= 7; ++i) {
        //�˴��ɿ������Ӽ���ССӢ��
        std::string frameName = "LittlePlayer_" + std::to_string(numPlayer) + "_" + std::to_string(i) + ".png"; //֡ͼƬ
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
    auto callback = cocos2d::CallFunc::create([this, numPlayer]() {
        this->stopHeroAction(numPlayer); // ֹͣ���ж���
        });

    // ���ƶ����������߶����ͻص���ϳ�һ������
    auto sequence = cocos2d::Sequence::create(moveAndAnimate, callback, nullptr);

    // ִ�����ж���
    this->runAction(sequence);
}

void littleHero::stopHeroAction(const int& numPlayer) {
    // ֹͣ���߶������ָ���վ��״̬�ľ���֡
    this->stopAllActions();
    auto frame = cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName("LittlePlayer_" + std::to_string(numPlayer) + "_8" + ".png");
    if (frame) {
        this->setSpriteFrame(frame);
    }
}

//�������߶���֡�����Ҫ����СС���飬ע��ú���
void  littleHero::preloadWalkingFrames(const int& numPlayer) {
    // д��δ���ʱ����Ļ�ֱ���
    const float designWidth = 2560.0f;
    const float designHeight = 1440.0f;

    // ��ȡ��ǰ�Ӵ���С
    auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

    // ������������
    float scaleX = visibleSize.width / designWidth;
    float scaleY = visibleSize.height / designHeight;

    // ��ǰ֡ͼƬ�ĳߴ�
    float originalFrameWidth = 400.0f;
    float originalFrameHeight = 320.0f;

    // ����֡�ߴ�����Ӧ��ǰ�ֱ���
    float frameWidth = originalFrameWidth * scaleX;
    float frameHeight = originalFrameHeight * scaleY;
    for (int i = 0; i <= 8; ++i) {
        std::string frameName = "LittlePlayer_" + std::to_string(numPlayer) + "_" + std::to_string(i) + ".png"; // ����player1֡ͼƬ
        auto frame = cocos2d::SpriteFrame::create(frameName, cocos2d::Rect(0, 0, frameWidth, frameHeight));
        cocos2d::SpriteFrameCache::getInstance()->addSpriteFrame(frame, frameName);
    }
    for (int i = 0; i <= 8; ++i) {
        std::string frameName = "LittlePlayer_" + std::to_string(numPlayer) + "_" + std::to_string(i) + ".png"; // ����player2֡ͼƬ
        auto frame = cocos2d::SpriteFrame::create(frameName, cocos2d::Rect(0, 0, frameWidth, frameHeight));
        cocos2d::SpriteFrameCache::getInstance()->addSpriteFrame(frame, frameName);
    }
    for (int i = 0; i <= 8; ++i) {
        std::string frameName = "LittlePlayer_" + std::to_string(numPlayer) + "_" + std::to_string(i) + ".png"; // ����player3֡ͼƬ
        auto frame = cocos2d::SpriteFrame::create(frameName, cocos2d::Rect(0, 0, frameWidth, frameHeight));
        cocos2d::SpriteFrameCache::getInstance()->addSpriteFrame(frame, frameName);
    }
    for (int i = 0; i <= 8; ++i) {
        std::string frameName = "LittlePlayer_" + std::to_string(numPlayer) + "_" + std::to_string(i) + ".png"; // ����player4֡ͼƬ
        auto frame = cocos2d::SpriteFrame::create(frameName, cocos2d::Rect(0, 0, frameWidth, frameHeight));
        cocos2d::SpriteFrameCache::getInstance()->addSpriteFrame(frame, frameName);
    }
}