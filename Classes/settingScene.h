#pragma once
#ifndef __SRTTING_SCENE_H__
#define __SETTING_SCENE_H__
#include "ui/CocosGUI.h"
#include "audio/include/AudioEngine.h"//��Ƶͷ�ļ�
#include "cocos2d.h"

USING_NS_CC;
using namespace cocos2d::ui;
using namespace std;

class SettingScene : public cocos2d::Scene
{
    friend class StartScene;
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    SettingScene();
    //������������
    void createSettingBackground(const string& picName);
    // �����ֱ������ð�ť��ͨ�ú���
    MenuItemImage* SettingScene::createResolutionButton(const std::string& title, int width, int height);

    // ͨ�÷ֱ��ʵ�������
    void setResolution(int width, int height);

    //�ֱ��ʵ��ú���
    void SettingScene::conductSetResolution();



    //�ص�������
    void SettingScene::goToMainMenu();

    //�˳���ǰ����
    void SettingScene::exitTheScene();

    // �������ƺ���
    void volumeSliderEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
    void muteAllSounds();
    void muteEffects();
    //�������ú���
    void conductSetMusic();

    //�����ť������һ����
    void createMenuButtons_set();
    void createAndAddButton_set(const string& normalImage, const string& selectedImage, const Vec2& position, float scale, const function<void()>& callback);

    //������ѡ����
    void muteSoundCheckBox();
    //�ر���Ч��ѡ����
    void muteEffectCheckBox();

    //����
    void SettingScene::otherSetScene();
    // implement the "static create()" method manually
    CREATE_FUNC(SettingScene);

private:
    int backgroundMusicID; // �������ֵ���ƵID
    bool clickSoundEnabled;  // ���ڸ��ٵ����Ч��״̬

};

#endif 