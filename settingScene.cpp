#include "SettingScene.h"
#include "StartScene.h"
#include "RegisterAndLogin.h"
#include "AudioControl.h"
#include "cocos2d.h"
#include "audio/include/AudioEngine.h"

USING_NS_CC;

SettingScene::SettingScene() : clickSoundEnabled(true) {}  // ��ʼ��



Scene* SettingScene::createScene()
{
    return SettingScene::create();
}

bool SettingScene::init()
{
    if (!Scene::init()) {
        return false;
    }

    //���ñ���
    createSettingBackground("set0.jpg");
    //�����ť����
    createMenuButtons_set();

    return true;
}

//������������
void SettingScene::createSettingBackground(const string& picName)
{
    // ��ȡ��ǰ��Ļ�ĳߴ��ԭ��λ��
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // ������������
    auto backgroundSprite = Sprite::create(picName);

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
}


//������Ļ�ֱ��ʺ���
MenuItemImage* SettingScene::createResolutionButton(const std::string& title, int width, int height) {
    auto button = MenuItemImage::create(
        "button1.png",    // ����״̬��ͼƬ
        "button2.jpg",   // ѡ��״̬��ͼƬ
        [this, width, height](Ref* sender) {
            this->setResolution(width, height);
        });

    // ����һ����ǩ���ڰ�ť��
    auto label = Label::createWithTTF(title, "fonts/Marker Felt.ttf", 8);
    if (label != nullptr) {
        label->setPosition(button->getContentSize() / 2);
        button->addChild(label);
    }
    button->setScale(1.2f);

    return button;
}

//�ֱ��ʵ�������
void SettingScene::setResolution(int width, int height) {
    Director::getInstance()->getOpenGLView()->setFrameSize(width, height);
}

//�ֱ��ʵ��ú���
void SettingScene::conductSetResolution(){
    // ��ȡ��Ļ��ʵ�ʳߴ�
    Size screenSize = Director::getInstance()->getOpenGLView()->getFrameSize();

    // ʹ��ͨ�ú��������ֱ������ð�ť
    auto button1280x720 = createResolutionButton("1280x720", 1280, 720);
    auto button1920x1080 = createResolutionButton("1920x1080", 1920, 1080);
    auto button2560x1440 = createResolutionButton("2560x1440", 2560, 1440);
    auto button2880x1800 = createResolutionButton("2880x1800", 2880, 1800);
    auto button3840x2160 = createResolutionButton("3840x2160", 3840, 2160);

    // ����ť��ӵ��˵�
    auto menu = Menu::create(button1280x720, button1920x1080, button2560x1440, button2880x1800, button3840x2160, nullptr);
    menu->alignItemsVertically();// ��ֱ���а�ť
    this->addChild(menu);

    //�˳����ý���
    exitTheScene();
}

//�ص������溯��
void SettingScene::goToMainMenu() {
    auto mainMenuScene = StartScene::create(); 
    Director::getInstance()->replaceScene(TransitionFade::create(0.5, mainMenuScene));
}

//�˳���ǰ���水ť����
void SettingScene::exitTheScene() {
    // �����˳���ť
    auto exitButton = MenuItemImage::create(
        "exit_button.jpg",  // ����״̬��ͼƬ
        "exit_button_click.jpg", // ѡ��״̬��ͼƬ
        CC_CALLBACK_0(SettingScene::goToMainMenu, this));
    exitButton->setScale(1.5f);
    // ��ȡ��ͼ�Ĵ�С��ԭ��
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // ���ð�ťλ��Ϊ���½�
    exitButton->setPosition(Vec2(origin.x + visibleSize.width - exitButton->getContentSize().width / 2 - 30,
        origin.y + exitButton->getContentSize().height / 2 + 10));

    // �����˵�����Ӱ�ť
    auto menu = Menu::create(exitButton, nullptr);
    menu->setPosition(Vec2::ZERO);  // ���ò˵���λ��
    this->addChild(menu);
}

// ��������������¼�
void SettingScene::volumeSliderEvent(Ref* sender, Slider::EventType type) {
    if (type == Slider::EventType::ON_PERCENTAGE_CHANGED) {
        Slider* slider = dynamic_cast<Slider*>(sender);//�����ƶ�
        int volume = static_cast<Slider*>(sender)->getPercent(); // �����µ�����ֵ
        AudioControl::getInstance()->setVolume(volume); // ��������
    }
}

// �л���Ч����״̬
void SettingScene::muteEffects() {
    clickSoundEnabled = !clickSoundEnabled;  // �л�״̬
    AudioControl::getInstance()->setClickSoundEnabled(clickSoundEnabled);
}

//�������ú���
void SettingScene::conductSetMusic() {
    // ��ȡ��ǰ��Ļ�ĳߴ��ԭ��λ��
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // �����������ƻ���
    auto volumeSlider = Slider::create();
    volumeSlider->loadBarTexture("sliderTrack.png"); // �������
    volumeSlider->loadSlidBallTextures("sliderThumb.png", "sliderThumb.png", ""); // �����˵�
    volumeSlider->loadProgressBarTexture("sliderProgress.png"); // ����������
    volumeSlider->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 + 40));
    volumeSlider->setPercent(AudioControl::getInstance()->getVolume());// ���û���ĳ�ʼ����
    volumeSlider->addEventListener(CC_CALLBACK_2(SettingScene::volumeSliderEvent, this));
    this->addChild(volumeSlider);

    muteSoundCheckBox();//��������
    muteEffectCheckBox();//�ر���Ч����

    //�˳����ý���
    exitTheScene();
}

//������ѡ��
void SettingScene::muteSoundCheckBox() {
    // ��ȡ��ǰ��Ļ�ĳߴ��ԭ��λ��
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //����������ʾ
    auto mute_sound1 = Sprite::create("SMM1.jpg");
    mute_sound1->setScale(0.4);
    if (mute_sound1 != NULL)
    {
        Size visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();
        mute_sound1->setPosition(Vec2(origin.x + visibleSize.width / 2.2, origin.y + visibleSize.height / 2 + 15));
        this->addChild(mute_sound1);
    }

    // ����ȫ�־�����ѡ��
    auto muteAllCheckBox = ui::CheckBox::create("check_box1.png", "check_box2.png");
    muteAllCheckBox->setSelected(AudioControl::getInstance()->isMuted());
    muteAllCheckBox->setPosition(Vec2(origin.x + visibleSize.width / 1.75, origin.y + visibleSize.height / 2 + 15));
    muteAllCheckBox->setScale(1.2f);

    // ���ø�ѡ��״̬�ı�
    muteAllCheckBox->addEventListener([=](Ref* sender, ui::CheckBox::EventType type) {
        if (type == ui::CheckBox::EventType::SELECTED) {
            // ����ѡ��ѡ��ʱ
            if (!AudioControl::getInstance()->isMuted()) {
                AudioControl::getInstance()->muteAllSounds(); // ����
            }
        }
        else if (type == ui::CheckBox::EventType::UNSELECTED) {
            // ����ѡ��δ��ѡ��ʱ
            if (AudioControl::getInstance()->isMuted()) {
                AudioControl::getInstance()->unmuteAllSounds(); // ȡ������
            }
        }
        });
    this->addChild(muteAllCheckBox);

}

//�ر���Ч��ѡ��
void SettingScene::muteEffectCheckBox() {
    // ��ȡ��ǰ��Ļ�ĳߴ��ԭ��λ��
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //�����ر���Ч��ʾ
    auto mute_sound2 = Sprite::create("SMM2.jpg");
    mute_sound2->setScale(0.4);
    if (mute_sound2 != NULL)
    {
        Size visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();
        mute_sound2->setPosition(Vec2(origin.x + visibleSize.width / 2.2, origin.y + visibleSize.height / 2 - 20));
        this->addChild(mute_sound2);
    }
    // ������Ч��ѡ��
    auto muteEffectsCheckBox = ui::CheckBox::create("check_box1.png", "check_box2.png");
    muteEffectsCheckBox->setSelected(AudioControl::getInstance()->isClickSoundEnabled());
    muteEffectsCheckBox->setPosition(Vec2(origin.x + visibleSize.width / 1.75, origin.y + visibleSize.height / 2 - 20));
    muteEffectsCheckBox->setScale(1.2f);

    // ���ø�ѡ��״̬�ı�
    muteEffectsCheckBox->addEventListener([=](Ref* sender, ui::CheckBox::EventType type) {
        if (type == ui::CheckBox::EventType::SELECTED) {
            // ����ѡ��ѡ��ʱ
            clickSoundEnabled = !clickSoundEnabled;  // �л�״̬
            AudioControl::getInstance()->setClickSoundEnabled(clickSoundEnabled);
        }
        else if (type == ui::CheckBox::EventType::UNSELECTED) {
            // ����ѡ��δ��ѡ��ʱ
            clickSoundEnabled = !clickSoundEnabled;  // �л�״̬
            AudioControl::getInstance()->setClickSoundEnabled(clickSoundEnabled);
        }
        });

    this->addChild(muteEffectsCheckBox);
}

//�������ú���
void SettingScene::otherSetScene() {
    // ��ȡ��ǰ��Ļ�ĳߴ��ԭ��λ��
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //�˳����ý���
    exitTheScene();

    // �����˳���½��ť
    auto exitLoginButton = ui::Button::create("exit_login1.jpg", "exit_login2.jpg");
    exitLoginButton->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 + 15));
    exitLoginButton->setScale(2.0f);
    addChild(exitLoginButton);

    exitLoginButton->addTouchEventListener([=](Ref* sender, Widget::TouchEventType type) {
        if (type == Widget::TouchEventType::ENDED) {
            auto initScene = RegisterAndLogin::create();
            Director::getInstance()->replaceScene(TransitionFade::create(0.5, initScene));
        }
        });
}

//���������ť
void SettingScene::createAndAddButton_set(const string& normalImage, const string& selectedImage, const Vec2& position, float scale, const function<void()>& callback)
{
    auto button = ui::Button::create(normalImage, selectedImage);
    button->setScale(scale);
    //button->setPosition(Vec2(getContentSize().width * position.x, getContentSize().height * position.y));
    button->setPosition(position);
    addChild(button, 3);

    button->addTouchEventListener([=](Ref* sender, Widget::TouchEventType type) {
        if (type == Widget::TouchEventType::ENDED) {
            // ���ŵ����Ч
            AudioControl::getInstance()->playClickSoundEffect();
            callback();
        }
        });
}

//�����ť������һ����
void SettingScene::createMenuButtons_set()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    createAndAddButton_set("setA1.jpg", "", Vec2(origin.x + visibleSize.width * 0.218, origin.y + visibleSize.height * 0.708), 0.9, [this]() {
        this->createSettingBackground("set1.jpg");
        // �ֱ�������
       this->conductSetResolution();
        });

    createAndAddButton_set("setA2.jpg", "", Vec2(origin.x + visibleSize.width * 0.218, origin.y + visibleSize.height * 0.526), 0.7, [this]() {
        this->createSettingBackground("set2.jpg");
        // ��������
        conductSetMusic();
        });

    createAndAddButton_set("setA3.jpg", "", Vec2(origin.x + visibleSize.width * 0.225, origin.y + visibleSize.height * 0.385), 1.0, [this]() {
        this->createSettingBackground("set3.jpg");
        //��������
        otherSetScene();
        });
}

