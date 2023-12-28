#include "ApplyLittleHero.h"
#include "MoveLittleHero.h"
#include "cocos2d.h"
#include"hero.h"
#include"RegisterAndLogin.h"
#include"settingScene.h"
USING_NS_CC;
using namespace cocos2d::ui;
Player my_hero;
Player enemy_hero;
int isfight=0;
Scene* ApplyLittleHero::createScene()
{
    return  ApplyLittleHero::create();
}
bool fight = 0;
void ApplyLittleHero::update(float delta) {
    // ���µ���ʱ
    //for (int i=0;i<my_hero.hero_on_board.size();i++)
    //{
    //    my_hero.hero_on_board[i];
    //   // hero->attack(hero->gettarget(enemy_hero), this, enemy_hero);
    //}
    //for (int i = 0; i < enemy_hero.hero_on_board.size(); i++) {
    //    Hero* hero = enemy_hero.hero_on_board[i];
    //    hero->attack(hero->gettarget(my_hero), this, my_hero);
    //}
    if (countdown > 0) {
        countdown -= delta;
        timerLabel->setString(std::to_string((int)countdown));
        //�ж�fight�Ƿ�Ϊ1��Ϊ1ʱ���й�����Ϊ0ʱ�����ƶ�
        //if (fight == 1)
        //{
        //    for (Hero* hero : my_hero.hero_on_board)
        //    {
        //        hero->attack(hero->gettarget(enemy_hero), this, enemy_hero);
        //    }
        //    for (Hero* hero : enemy_hero.hero_on_board) {
        //        hero->attack(hero->gettarget(my_hero), this, my_hero);
        //    }
        //}
    }
    else {
        // ����ʱ����ʱִ�еĲ���
        countdown = countdown_max;
        timerLabel->setString(std::to_string((int)countdown));
        // ���磺������Ϸ���ı䳡����
        fight = (fight == 0 ? 1 : 0);
        if (fight == 1)
        {
            //�½�����
            auto newScene = SettingScene::create();
            //Director::getInstance()->pushScene();
            //�˳�����
            //Director::getInstance()->popScene();
        }
    }
}
bool  ApplyLittleHero::init()
{
 

    if (!Scene::init())
    {
        return false;
    }
    // ��ȡ��ǰ��Ļ�ĳߴ��ԭ��λ��
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // ������������
    auto backgroundSprite = Sprite::create("pink_1.jpg");
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
    countdown = 30.0f;
    // ��������ӱ�ǩ
    timerLabel = Label::createWithSystemFont(std::to_string((int)countdown), "Arial", 24);
    timerLabel->setColor(Color3B(255, 100, 0));
    timerLabel->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2,
    Director::getInstance()->getVisibleSize().height));
    //��ӵ���ʱ��ǩ
    this->addChild(timerLabel);

    /*���ϳ�����Ϊʾ���������*/
    /*����ΪССӢ���ƶ�����*/

    // ����ССӢ��
    auto hero = littleHero::create("LittlePlayer_4_0.png");
    if (hero) {
        hero->setPosition(Vec2(visibleSize.width / 4.5 + origin.x, visibleSize.height / 3.8 + origin.y)); // ����Ӣ�۵�λ��
        hero->setScale(0.8);
        this->addChild(hero); // ��Ӣ����ӵ�������
    }
    hero->enableMouseControl(true);
    //����Ϸ׼���׶Σ�ССӢ���ƶ�
	//��ʼӢ��
    Hero so(1, 1, this),so1(1,1,this);
    this->addChild(so.mine);
	this->addChild(so1.mine);
	my_hero.the = this;
	enemy_hero.the = this;
	my_hero.hero_on_board.push_back(&so);
	enemy_hero.hero_on_board.push_back(&so1);
    so.mine->setPosition(30, 30);
	so1.mine->setPosition(100, 100);
	so.enableMouseControl(1,this);
    this->scheduleUpdate();
	//so1.enableMouseControl(1,this);
	/*so.attack(so.gettarget(enemy_hero), this, enemy_hero);
	so1.attack(so1.gettarget(my_hero), this, my_hero);*/
    //������ʼӢ��
    
	//ս������ֻ�ܶԱ�սϯ��Ӣ�۵����Ч

	return true;
}

