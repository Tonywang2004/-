#include "ApplyLittleHero.h"
#include "MoveLittleHero.h"
USING_NS_CC;

Scene* ApplyLittleHero::createScene()
{
    return  ApplyLittleHero::create();
}

bool  ApplyLittleHero::init()
{
    if (!Scene::init())
    {
        return false;
    }
    // ��ȡ��ǰ��Ļ�ĳߴ��ԭ��λ��
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // ������������
    auto backgroundSprite = Sprite::create("GameBack.jpg");
    if (backgroundSprite != NULL)
    {
        // ���ñ��������λ��
        backgroundSprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

        // ���ű����������Ļ
        float scaleX = visibleSize.width / backgroundSprite->getContentSize().width;
        float scaleY = visibleSize.height / backgroundSprite->getContentSize().height;
        backgroundSprite->setScale(scaleX, scaleY);

        // ������������ӵ�������
        this->addChild(backgroundSprite, 0); 
    }


    /*���ϳ�����Ϊʾ���������*/
    /*����ΪССӢ���ƶ�����*/

    // ����ССӢ��
    auto hero = littleHero::create("LittlePlayer_1_0.png"); 
    if (hero) {
        hero->setPosition(Vec2(visibleSize.width / 2.8 + origin.x, visibleSize.height / 2.8 + origin.y)); // ����Ӣ�۵�λ��
        hero->setScale(0.5);
        this->addChild(hero); // ��Ӣ����ӵ�������
    }
    //����ССӢ�۵Ķ���֡ͼƬ,�ò��ز�����
    preloadWalkingFrames();

    // �ڶԾֿ�ʼ,����ССӢ���ƶ�
    hero->enableMouseControl(true);

    // ����Ϸ׼���׶Σ��ر�ССӢ���ƶ�
    //hero->enableMouseControl(false);
 

    return true;
}

//�������߶���֡�����Ҫ����СС���飬ע��ú���
void  ApplyLittleHero::preloadWalkingFrames() {
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
    for (int i = 1; i <= 8; ++i) {
        std::string frameName = "LittlePlayer_1_" + std::to_string(i) + ".png"; // ����֡ͼƬ
        auto frame = cocos2d::SpriteFrame::create(frameName, cocos2d::Rect(0, 0, frameWidth, frameHeight));
        cocos2d::SpriteFrameCache::getInstance()->addSpriteFrame(frame, frameName);
    }
}
