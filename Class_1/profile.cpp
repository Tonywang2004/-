#include "profile.h"
#include "StartScene.h"
USING_NS_CC;

Scene* Profile::createScene()
{
    return Profile::create();
}

bool Profile::init()
{
    if (!Scene::init())
    {
        return false;
    }
    // ��ȡ��ǰ��Ļ�ĳߴ��ԭ��λ��
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // ������������
    auto backgroundSprite_1 = Sprite::create("reg.png");
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

    // �����˳���ť
    auto exitButton = MenuItemImage::create(
        "exit_button.jpg",  // ����״̬��ͼƬ
        "exit_button_click.jpg", // ѡ��״̬��ͼƬ
        CC_CALLBACK_0(Profile::goToMainMenu, this));
    exitButton->setScale(1.2f);

    // ���ð�ťλ��Ϊ���½�
    exitButton->setPosition(Vec2(origin.x + visibleSize.width - exitButton->getContentSize().width / 2 - 24,
        origin.y + exitButton->getContentSize().height / 2 + 3));

    // �����˵�����Ӱ�ť
    auto menu = Menu::create(exitButton, nullptr);
    menu->setPosition(Vec2::ZERO);  // ���ò˵���λ��
    this->addChild(menu);

    return true;
}
//�ص������溯��
void Profile::goToMainMenu() {
    auto mainMenuScene = StartScene::create();
    Director::getInstance()->replaceScene(TransitionFade::create(0.5, mainMenuScene));
}