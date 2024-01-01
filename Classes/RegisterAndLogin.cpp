#include "RegisterAndLogin.h"
#include "transitionScene.h"
#include "settingScene.h"
#include "AudioControl.h"
#include "ui/CocosGUI.h" //ʹ��UI���
#include "audio/include/AudioEngine.h"//��Ƶͷ�ļ�
#include <iostream>
#include <string>

USING_NS_CC;
using namespace cocos2d::ui;
using namespace std;

Scene* RegisterAndLogin::createScene()
{
    return RegisterAndLogin::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool RegisterAndLogin::init()
{
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    // ��ȡ��ǰ��Ļ�ĳߴ��ԭ��λ��
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // add a "close" icon to exit the progress. it's an autorelease object
    //�˳���Ϸ��ť
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(RegisterAndLogin::menuCloseCallback, this));

    if (closeItem == NULL ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }

    // create menu, it's an autorelease object
    auto menu0 = Menu::create(closeItem, NULL);
    menu0->setPosition(Vec2::ZERO);
    this->addChild(menu0, 1);

    // ������������
    auto backgroundSprite = Sprite::create("bg.png");
    if (backgroundSprite != NULL)
    {
        // ���ñ��������λ��
        backgroundSprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
       
        // ���ű����������Ļ
        float scaleX = visibleSize.width / backgroundSprite->getContentSize().width;
        float scaleY = visibleSize.height / backgroundSprite->getContentSize().height;
        backgroundSprite->setScale(scaleX, scaleY);

        // ������������ӵ�������
        this->addChild(backgroundSprite, 0); //ȷ����������ײ�
    }
    //����ͬ�ô�ѧlogo
    auto tj_sprite = Sprite::create("tju.jpg");
    tj_sprite->setScale(0.5); 
    if (tj_sprite != NULL)
    {
        // position the sprite on the center of the screen
        Size visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();
        tj_sprite->setPosition(Vec2(float(origin.x + visibleSize.width * 0.85 + 3), origin.y + visibleSize.height * 0.72));
        // add the sprite as a child to this layer
        this->addChild(tj_sprite, 1);
    }

    // add "password" splash screen"
   auto sprite = Sprite::create("password.jpg");
   sprite->setScale(2.5);  //����
    if (sprite != NULL)
    {
        // position the sprite on the center of the screen
        Size visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();
        sprite->setPosition(Vec2(float(origin.x + visibleSize.width * 0.85 + 3), origin.y + visibleSize.height * 0.45));
      
        // add the sprite as a child to this layer
        this->addChild(sprite, 1);
    }

    // ���ô�����¼����ĺ���
    this->createLogin();

    //�������ð�ť
    auto setting = createButton("setting_icon.png", "setting_icon_click.png", Vec2(origin.x + visibleSize.width * 0.95, origin.y + visibleSize.height * 0.95),
        2.5, [=](Ref* sender, ui::Widget::TouchEventType type) {
            if (type == ui::Widget::TouchEventType::ENDED) {
                // ���ŵ����Ч
                AudioControl::getInstance()->playClickSoundEffect();
                // ������һ������
                auto newScene = SettingScene::create();
                 //�л�����һ������
                cocos2d::Director::getInstance()->pushScene(TransitionFade::create(1.0, newScene, Color3B(255, 255, 240)));
            }
        });

    return true;
}

//���������
ui::EditBox* RegisterAndLogin::createInputBox(const Size& size, const Vec2& position, bool isPassword) {
    auto inputBox = ui::EditBox::create(size, ui::Scale9Sprite::create("button1.png"));
    inputBox->setPosition(position);
    if (isPassword) {
        inputBox->setInputFlag(ui::EditBox::InputFlag::PASSWORD);
    }
    this->addChild(inputBox, 2);
    return inputBox;
}

//������ť
ui::Button* RegisterAndLogin::createButton(const string& normalImage, const string& selectedImage, const Vec2& position,
    const float& scale, const std::function<void(Ref*, ui::Widget::TouchEventType)>& callback) {
    auto button = ui::Button::create(normalImage, selectedImage);
    button->setPosition(position);
    button->setScale(scale);
    button->addTouchEventListener(callback);
    this->addChild(button, 2);
    return button;
}

//��¼����
void RegisterAndLogin::createLogin() {
    // ��ȡ��ǰ��Ļ�ĳߴ��ԭ��λ��
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // �����Ҳ�λ��
    float rightSideX = float(origin.x + visibleSize.width * 0.85 + 6);

    // �����˺�������������ô�С��λ�ã�ͬʱ�����˺�
    auto accountBox = createInputBox(Size(420, 60), Vec2(rightSideX, origin.y + visibleSize.height * 0.5), false);
    auto passwordBox = createInputBox(Size(420, 60), Vec2(rightSideX, origin.y + visibleSize.height * 0.421), true);
    //������¼��ť
    auto loginButton = createButton("button_qd_00.png", "button_qd_01.png",
        Vec2(rightSideX * 0.93, origin.y + visibleSize.height * 0.3), 2.0, [=](Ref* sender, ui::Widget::TouchEventType type) {
            if (type == ui::Widget::TouchEventType::ENDED) {
                // ���ŵ����Ч
                AudioControl::getInstance()->playClickSoundEffect();
                string account = accountBox->getText();
                string password = passwordBox->getText();

                // �ӱ��ش洢�л�ȡ���˺Ŷ�Ӧ������
                string storedPassword = UserDefault::getInstance()->getStringForKey(account.c_str(), "");

                // ����˺�����
                if (!storedPassword.empty() && password == storedPassword) {
                    // �˺�������ȷ,������һ������
                    auto newScene = Transition::createScene();
                    // �л�����һ������
                    Director::getInstance()->replaceScene(TransitionFade::create(1.0, newScene, Color3B(255, 255, 240)));
                }
                else {
                    //�˺����������������
                    accountBox->setText("");
                    passwordBox->setText("");
                    // ����һ�����������ʾ
                    auto registerButton = ui::Button::create("wrongInput2.jpg", "wrongInput2.jpg");
                    registerButton->setScale(float(0.15));  //��С
                    registerButton->setPosition(Vec2(rightSideX - 3, origin.y + visibleSize.height * 0.3));
                    this->addChild(registerButton, 2);
                }
            }
        });

    //����ȡ����ť
    auto exitButton = createButton("button_qx_00.png", "button_qx_01.png", Vec2(rightSideX*1.05, origin.y + visibleSize.height * 0.3),
        2.0, [=](Ref* sender, ui::Widget::TouchEventType type) {
            if (type == ui::Widget::TouchEventType::ENDED) {
                // ���ŵ����Ч
                AudioControl::getInstance()->playClickSoundEffect();
                // ����˺ź����������
                accountBox->setText("");
                passwordBox->setText("");
            }
        });

    //����ע��
    // ����һ��ע������л���ť
    auto registerButton = createButton("rigister.jpg", "rigister.jpg", Vec2(rightSideX - 5, origin.y + visibleSize.height*0.2),
        0.2, [=](Ref* sender, ui::Widget::TouchEventType type) {
            if (type == ui::Widget::TouchEventType::ENDED) {
                // ���ŵ����Ч
                AudioControl::getInstance()->playClickSoundEffect();
                //����ע�ắ��
                this->createRegistration();
            }
        });
}

//ע�ắ��
void RegisterAndLogin::createRegistration() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    // ��������е������ӽڵ㣬��׼���µĽ���
    this->removeAllChildren();

    //�����±���
    auto registerBackground = Sprite::create("reg.png");
    registerBackground->setScale(4);
    registerBackground->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 20));
    this->addChild(registerBackground, 0);


    // ����һ���˺�����������˺�
    auto accountInput = ui::EditBox::create(Size(420, 60), ui::Scale9Sprite::create("button1.png"));
    accountInput->setScale(float(2.0));
    accountInput->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 1.6));
    // ������������ʾ�ı�
    accountInput->setPlaceHolder("ACCOUNT");
    this->addChild(accountInput, 1);

    // ����һ������������������룬�˴�û��ʹ���벻�ɼ�
    auto passwordInput = ui::EditBox::create(Size(420, 60), ui::Scale9Sprite::create("button1.png"));
    passwordInput->setScale(float(2.0));
    passwordInput->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2.4));
    // ����������������ʾ�ı�
    passwordInput->setPlaceHolder("PASSWORD");
    this->addChild(passwordInput, 1);

    // ����ȷ�ϰ�ť
    auto loginButton_1 = createButton("button_qd_00.png", "button_qd_01.png", Vec2(float(visibleSize.width * 0.38), visibleSize.height * 0.25)
        , 2.5, [=](Ref* sender, ui::Widget::TouchEventType type) {
            if (type == ui::Widget::TouchEventType::ENDED) {
                // ���ŵ����Ч
                AudioControl::getInstance()->playClickSoundEffect();
                // ��ȡ������û���������
                string username = accountInput->getText();
                string password = passwordInput->getText();

                // ���û��������뱣�浽���ش洢
                UserDefault::getInstance()->setStringForKey(username.c_str(), password);

                if (type == ui::Widget::TouchEventType::ENDED) {
                    //�����ǰ����
                    this->removeAllChildren();
                    //���ص�¼����
                    this->init();
                }
            }
        });

    // ����ȡ����ť
    auto exitButton_1 = createButton("button_qx_00.png", "button_qx_01.png", Vec2(float(visibleSize.width*0.6), visibleSize.height*0.25)
        , 2.5, [=](Ref* sender, ui::Widget::TouchEventType type) {
            if (type == ui::Widget::TouchEventType::ENDED) {
                // ���ŵ����Ч
                AudioControl::getInstance()->playClickSoundEffect();
                //�����ǰ���棬���ص�¼����
                //this->removeAllChildren();
                //this->init();
                // ����˺ź����������
                accountInput->setText("");
                passwordInput->setText("");
            }
        });

    // �����˳���ť
    auto exitButton_2 = createButton("return.png", "return_h.png", Vec2(origin.x + visibleSize.width * 0.92, visibleSize.height*0.08)
        , 3.6, [=](Ref* sender, ui::Widget::TouchEventType type) {
            if (type == ui::Widget::TouchEventType::ENDED) {
                // ���ŵ����Ч
                AudioControl::getInstance()->playClickSoundEffect();
                //�����ǰ���棬���ص�¼����
                this->removeAllChildren();
                this->init();
            }
        });
}

//�˵��ص�
void RegisterAndLogin::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();
}

//�л�����
void RegisterAndLogin::menuPlayCut(Ref* pSender)
{
    // ������һ������
    auto newScene = Transition::create();
    // �л�����һ������
    Director::getInstance()->replaceScene(newScene);
}

void  RegisterAndLogin::onEnter() {
    Scene::onEnter();
    // ����Ƿ��ھ���״̬
    if (!AudioControl::getInstance()->isMuted()) {
        // ���û�о��������¿�ʼ���ű�������
        AudioControl::getInstance()->playBackgroundMusic("27Y.mp3", true);
    }
}

void  RegisterAndLogin::onExit() {
    Scene::onExit();
}


