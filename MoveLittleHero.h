#pragma once
#ifndef __LITTLE_HERO_H__ 
#define __LITTLR_HERO_H__

#include "cocos2d.h" 

class littleHero : public cocos2d::Sprite {
public:
    //���캯��
    littleHero();

    // ��̬����ССӢ��
    static littleHero* create(const std::string& filename);

    // ���û�ͣ��������,enabled Ϊ true ʱ���������ƣ�Ϊ false ʱ����
    void enableMouseControl(bool enabled);

    //�ƶ�ССӢ�۵�ָ��λ��
    void moveHeroToLocation(const cocos2d::Vec2& location, const int& numPlayer);

    //������Һ�ССӢ�۵�ͼƬ
    void  preloadWalkingFrames(const int& numPlayer);

    // ֹͣ���߶���
    void stopHeroAction(const int& numPlayer);

    //��ͬ��ҵı��
    int numPlayer;

private:
    //����������ʼ
    cocos2d::EventListenerMouse* _mouseListener = nullptr;

    // ��ʼ������¼�������
    void initMouseListener();

    //��갴��ʱ�Ĳ�������
    void setMouseParameter(cocos2d::Event* event);
};

#endif 