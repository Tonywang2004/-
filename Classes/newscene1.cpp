#pragma once
#include "newscene1.h"
#include "ui/CocosGUI.h"
#include "openScene.h"
#include "ui/UITextField.h"
#include <iostream>
#include "Roommanager.h"
#include "playerScene.h"
USING_NS_CC;
using namespace cocos2d::ui;
int room_number;//��ʾ�û�����ķ����
Scene* newscene1::createScene()//��������
{
    return newscene1::create();
}

// �������
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// ��ʼ��
bool newscene1::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();//��ȡ�ɼ���С
    Vec2 origin = Director::getInstance()->getVisibleOrigin();//��ȡopengl���
    //������ǩ��Please input room numbers
    auto label = Label::createWithTTF("Please input room numbers", "fonts/Marker Felt.ttf", 24);//����һ����ǩ�����ݡ����塢�ֺţ�
    if (label == nullptr)//������
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // ���õ����м�
        label->setPosition(Vec2(origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height - label->getContentSize().height));

        // ��ӵ���ǰͼ��
        this->addChild(label, 1);
    }
    // �����˳���ť
    auto exitButton = MenuItemImage::create(
        "return.png",  // ����״̬��ͼƬ
        "return_h.png", // ѡ��״̬��ͼƬ
        CC_CALLBACK_0(newscene1::goToMainMenu, this));
    exitButton->setScale(3.0f);

    // ���ð�ťλ��Ϊ���½�
    exitButton->setPosition(Vec2(origin.x + visibleSize.width - exitButton->getContentSize().width / 0.5,
        origin.y + exitButton->getContentSize().height + 8));

    // �����˵�����Ӱ�ť
    auto menu = Menu::create(exitButton, nullptr);
    menu->setPosition(Vec2::ZERO);  // ���ò˵���λ��
    this->addChild(menu);
    
    // ���������
    auto editBoxSize = cocos2d::Size(200, 40);
    roomNumberInput = cocos2d::ui::EditBox::create(editBoxSize, cocos2d::ui::Scale9Sprite::create("roomID.png"));
    roomNumberInput->setPosition(cocos2d::Vec2(1000, 700));
    roomNumberInput->setScale(4);
    roomNumberInput->setFontColor(cocos2d::Color3B::BLACK);
    roomNumberInput->setPlaceHolder("Room Number:");
    roomNumberInput->setMaxLength(10);
    roomNumberInput->setInputMode(cocos2d::ui::EditBox::InputMode::NUMERIC);
    this->addChild(roomNumberInput);

    // ������ť
    auto enterRoomButton = cocos2d::ui::Button::create();
    enterRoomButton->setTitleText("Create Room");
    enterRoomButton->setScale(4);
    enterRoomButton->setPosition(cocos2d::Vec2(1000, 500));
    enterRoomButton->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
        if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
            this->onEnterRoomButtonClicked();//���õ����ť֮��Ĳ���
        }
        });
    this->addChild(enterRoomButton);
    return true;
}
void newscene1::onEnterRoomButtonClicked() {
    //�����������������
    const std::string roomNumberString = roomNumberInput->getText();
    // ��������ַ���ת��Ϊint����
    room_number = std::atoi(roomNumberString.c_str());
    //��ʼ�����������
    RoomManager manager;
    // Ѱ�ҷ���
    Room* foundroom = manager.getRoom(room_number);

    if (foundroom == nullptr) {//δ�ҵ��򴴽�����
        auto room= manager.createRoom(room_number);
        room->addPlayer(Player0(1, "Player1"));//������
        
    }
    else {
        foundroom->addPlayer(Player0(1, "Player1"));//������
    }
    //�л�����Ϸ����
    auto scene = playerScene::createScene();
    Director::getInstance()->replaceScene(scene);
    
}


//�ص������溯��
void newscene1::goToMainMenu() {
    auto mainMenuScene = StartScene::create();
    Director::getInstance()->replaceScene(TransitionFade::create(0.5, mainMenuScene));
}


void newscene1::menuCloseCallback(Ref* pSender)//�˳�����
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}