#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "hero.h"
#define __SHOP_LAYER_H__
USING_NS_CC;

/*
����㼶�й���7���˵���
��һ�����ڹ����������
�ڶ�������ˢ���̵�
ʣ�µ�5���ǽ�ɫ��ͼƬ���̵�Ĺؼ���Ŀ��

����ʹ��һ��λ������������4����ɫ��λ��
����ˢ���̵�����ý�ɫ����Ƭ
*/

class storeLayer : public Layer
{
public:
  int herotype[5]; // ������������Ӣ�ۣ�ÿ��׼���׶ζ����Զ�ˢ�£�
  int herocost[7] = {0, 1, 2, 3, 1, 2, 3};
  static storeLayer *createLayer();
  CREATE_FUNC(storeLayer);

  bool init() override;
  int gold;  // �������
  int exp;   // ����ֵ
  int level; // �ȼ�

  cocos2d::ui::LoadingBar *expBar; // ������
  cocos2d::Label *goldLabel;       // ��ʾ��������ı�ǩ
  cocos2d::Label *levelLabel;      // ��ʾ�ȼ��ı�ǩ

  cocos2d::ui::Button *heroButton1;
  cocos2d::ui::Button *heroButton2;
  cocos2d::ui::Button *heroButton3;
  cocos2d::ui::Button *heroButton4;
  cocos2d::ui::Button *heroButton5;

  MenuItemImage *upgradeButton;

  void updateUI(); // ����UI��ʾ
  void upgrade();  // ���������������
  void refresh();  // ˢ���̵����

  void onUpgradeButtonClicked(cocos2d::Ref *sender);
  void onRefreshButtonClicked(cocos2d::Ref *sender);
  void createHeroButtons();                                      // ����Ӣ�۰�ť
  void onHeroButtonClicked(cocos2d::Ref *sender, int heroIndex); // Ӣ�۰�ť����¼�

  ui::Button *createButton(const std::string &normalImage, const std::string &selectedImage, const Vec2 &position,
                           const float &scale, const std::function<void(Ref *, ui::Widget::TouchEventType)> &callback);
};
