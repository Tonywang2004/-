#include "openScene.h"
#include "settingScene.h"
#include "profile.h"
#include "newscene1.h"
#include "AudioControl.h"
#include "ui/CocosGUI.h"
#include "audio/include/AudioEngine.h"//��Ƶͷ�ļ�

#include"playerScene.h"
USING_NS_CC;
using namespace cocos2d::ui;
using namespace std;

bool StartScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    // ��ȡ��ǰ��Ļ�ĳߴ��ԭ��λ��
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //������ʼ���汳��
    createBackground();
    //�����ť����
    createMenuButtons();

    return true;
}

//������������
void StartScene::createBackground()
{
    // ��ȡ��ǰ��Ļ�ĳߴ��ԭ��λ��
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // ������������
    auto backgroundSprite_1 = Sprite::create("SSS.jpg");
    if (backgroundSprite_1 != NULL)
    {
        // ���ñ��������λ��
        backgroundSprite_1->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

        // ���ű����������Ļ
        float scaleX = visibleSize.width / backgroundSprite_1->getContentSize().width;
        float scaleY = visibleSize.height / backgroundSprite_1->getContentSize().height;
        backgroundSprite_1->setScale(scaleX, scaleY);

        // ������������ӵ�������
        this->addChild(backgroundSprite_1, 0);
    }
}

//������Ӧ

//�����ť������һ����
void StartScene::createMenuButtons()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    createAndAddButton("t1.png", "t1_click.jpg", Vec2(origin.x + visibleSize.width * 0.5 - 5, origin.y + visibleSize.height * 0.25 - 5), 0.85, []() {
        // ����ʼ��Ϸ��ť����¼�
        auto scene = playerScene::createScene();
    Director::getInstance()->replaceScene(scene);

        });

    createAndAddButton("t3.png", "t3_click.jpg", Vec2(origin.x + visibleSize.width * 0.2, origin.y + visibleSize.height * 0.26), 0.8, []() {
        // ������뷿�䰴ť����¼�
        auto scene = newscene1::createScene();
    Director::getInstance()->replaceScene(scene);
        });

    createAndAddButton("t2.png", "t2_click.jpg", Vec2(origin.x + visibleSize.width * 0.79, origin.y + visibleSize.height * 0.26), 0.8, []() {
        // ���������䰴ť����¼�
        auto scene = newscene1::createScene();
    Director::getInstance()->replaceScene(scene);
        });

    createAndAddButton("setting.png", "setting_click.jpg", Vec2(origin.x + visibleSize.width * 0.067, origin.y + visibleSize.height * 0.882), 0.8, []() {
        // �������ð�ť����¼�
        // ������һ������
        auto settingScene = SettingScene::create();
    // �л�����һ��������ʹ�õ���Ч��
    cocos2d::Director::getInstance()->pushScene(TransitionFade::create(1.0, settingScene, Color3B(255, 255, 240)));
        });

    createAndAddButton("profile.png", "profile_click.jpg", Vec2(origin.x + visibleSize.width * 0.93, origin.y + visibleSize.height * 0.882), 0.8, []() {
        // ����profile��ť����¼�
         // ������һ������
        auto settingScene = Profile::create();
    // �л�����һ��������ʹ�õ���Ч��
    Director::getInstance()->replaceScene(TransitionFade::create(1.0, settingScene, Color3B(255, 255, 240)));
        });
}

//���������ť
void StartScene::createAndAddButton(const string& normalImage, const string& selectedImage, const Vec2& position, float scale, const function<void()>& callback)
{
    //���ð�ť״̬
    auto button = ui::Button::create(normalImage, selectedImage);
    button->setScale(scale);
    button->setPosition(position);
    addChild(button, 1);

    //��������¼�
    button->addTouchEventListener([=](Ref* sender, Widget::TouchEventType type) {
        if (type == Widget::TouchEventType::ENDED) {
            // ���ŵ����Ч
            AudioControl::getInstance()->playClickSoundEffect();
            callback();
        }
        });
}

void StartScene::onEnter() {
    Scene::onEnter();
    // ����Ƿ��ھ���״̬
    if (!AudioControl::getInstance()->isMuted()) {
        // ���û�о��������¿�ʼ���ű�������
        AudioControl::getInstance()->playBackgroundMusic("BM.mp3", true);
    }
}

void StartScene::onExit() {
    Scene::onExit();
}

