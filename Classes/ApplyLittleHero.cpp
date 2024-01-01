#include "ApplyLittleHero.h"
#include "MoveLittleHero.h"
#include "cocos2d.h"
#include"hero.h"
USING_NS_CC;
Player my_hero;
Player enemy_hero;
Scene* ApplyLittleHero::createScene()
{
    return  ApplyLittleHero::create();
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
    auto backgroundSprite = Sprite::create("GameBack.jpg");
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


    /*���ϳ�����Ϊʾ���������*/
    /*����ΪССӢ���ƶ�����*/

    // ����ССӢ��
    auto hero = littleHero::create("LittlePlayer_4_0.png");
    if (hero) {
        hero->setPosition(Vec2(visibleSize.width / 2.8 + origin.x, visibleSize.height / 2.8 + origin.y)); // ����Ӣ�۵�λ��
        hero->setScale(0.5);
        this->addChild(hero); // ��Ӣ����ӵ�������
    }
    hero->enableMouseControl(true);
    // ����Ϸ׼���׶Σ��ر�ССӢ���ƶ�
    this->schedule([=](float dt) {
        
        }, 1.0f, "time");
    //hero->enableMouseControl(false);
    Hero hero1(1, 1, this),hero2(2,1,this);
    hero1.mine->setPosition(200, 200);
    hero2.mine->setPosition(300, 300);
    this->addChild(hero1.mine);
    this->addChild(hero2.mine);
    my_hero.hero_on_board.push_back(&hero1);
    enemy_hero.hero_on_board.push_back(&hero2);
    hero1.attack(hero1.gettarget(enemy_hero),this,enemy_hero);
    hero2.attack(hero2.gettarget(my_hero), this, my_hero);
    return true;
}

