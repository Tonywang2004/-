#include "transitionScene.h"
#include "openScene.h"
USING_NS_CC;

Scene* Transition::createScene()
{
    return Transition::create();
}


bool Transition::init()
{
    if (!Scene::init())
    {
        return false;
    }
    // ��ȡ��ǰ��Ļ�ĳߴ��ԭ��λ��
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

     // ������������
    auto backgroundSprite_1 = Sprite::create("background_b.png");
    if (backgroundSprite_1 != NULL)
    {
        // ���ñ��������λ��
        backgroundSprite_1->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

        // ���ű����������Ļ
        float scaleX = visibleSize.width / backgroundSprite_1->getContentSize().width;
        float scaleY = visibleSize.height / backgroundSprite_1->getContentSize().height;
        backgroundSprite_1->setScale(scaleX, scaleY);

        // ������������ӵ�������
        this->addChild(backgroundSprite_1, 0); // 0 ��ʾ�㼶��ȷ����������ײ�
    }

    // ����һ����ʱ�����ӳ�һ��ʱ����л�����һ������
    this->scheduleOnce(CC_SCHEDULE_SELECTOR(Transition::switchToNextScene), 2.0f); // 2.0���ӳ�
    return true;
}
void Transition::switchToNextScene(float dt)
{
    // ������һ������
    auto newScene = StartScene::create();
    // �л�����һ��������ʹ�õ���Ч��
    Director::getInstance()->replaceScene(TransitionFade::create(1.0, newScene, Color3B(255, 255, 240)));
}


