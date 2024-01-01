#pragma once
#ifndef __START_SCENE_H__
#define __START_SCENE_H__
#include "ui/CocosGUI.h"
#include "audio/include/AudioEngine.h"//��Ƶͷ�ļ�
#include "cocos2d.h"

USING_NS_CC;
using namespace cocos2d::ui;

using namespace std;

class StartScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();

    //��������
    void createBackground();

    //�����˵���ť
    void createMenuButtons();

    //���������ť
    void createAndAddButton(const string& normalImage, const string& selectedImage, const Vec2& position, float scale, const function<void()>& callback);

    // ��д onEnter �� onExit 
    virtual void onEnter() override;
    virtual void onExit() override;

    // implement the "static create()" method manually
    CREATE_FUNC(StartScene);

};

#endif // __MY_NEW_SCENE_H__
