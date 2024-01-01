#ifndef __NEWSCENE1_SCENE_H__
#define __NEWSCENE1_SCENE_H__
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "ui/UITextField.h"
//�ṩ�˴�����ʹ���û�����Ԫ�ص���ͺ���
USING_NS_CC;

class newscene1 : public cocos2d::Scene//�̳�
{
public:
    static cocos2d::Scene* createScene();//��������

    virtual bool init();//��ʼ��

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);//�˳�����

    void onEnterRoomButtonClicked();//��ť���

    void goToMainMenu();//�ص�������
    // implement the "static create()" method manually
    CREATE_FUNC(newscene1);
    
private:
    cocos2d::ui::EditBox* roomNumberInput;//���������
};

#endif // __NEWSCENE1_SCENE_H__