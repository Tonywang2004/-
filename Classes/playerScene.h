#pragma once
#include"cocos2d.h"
#include"preparationSeat.h"
#include"chessboardSeat.h"
#include"storeLayer.h"
#include"hero.h"
#include"playerroleLayer.h"
USING_NS_CC;
extern Vector<Hero*> allMyHeroes;//�ҷ�����Ӣ��
extern Vector<Hero*> allEnemyHeroes;//�з�����Ӣ��
extern int fight;
extern int enemyType;

class playerScene : public Scene
{
public:
    playerroleLayer* myrole;
    playerroleLayer* enemyrole1;  //�˻�1
    playerroleLayer* enemyrole2;  //�˻�2

	storeLayer* store;

    Sprite* progress0;
    ProgressTimer* progress1;
    Sequence* to1;
    Sequence* gameprogress;

    float totalTime = 20.0f;
    float currentTime = 0.0f;

    MenuItemSprite* seeEnemy1;
    MenuItemSprite* seeEnemy2;
    MenuItemSprite* goback;

	static playerScene* createScene();
	virtual bool init();
	CREATE_FUNC(playerScene);
	void ShowHeroes(int IsMine);
	void CoverHeroes(int IsMine);

    //��д
    void onEnter();
    void onExit();

    //������ť
    ui::Button* playerScene::createButton(const string& normalImage, const string& selectedImage, const Vec2& position,
        const float& scale, const std::function<void(Ref*, ui::Widget::TouchEventType)>& callback);

    void startattack() {
        schedule(CC_SCHEDULE_SELECTOR(playerScene::attack), 2.0f);
    }

    // ��������
    void attack(float dt)
    {
        bool attacked = 0;

        //�ҷ���������
        for (auto myHero : allMyHeroes)
        {
            if (!myHero->getdie() && myHero->isonboard()) {
                Hero* target;
                bool targetFind = 0;
                long long nearst_distance = 99999999999;
                for (auto enemyHero : allEnemyHeroes) {
                    if (!enemyHero->getdie() && enemyHero->isonboard()) {
                        targetFind = 1;
                        long long x_distance = myHero->getPosition().x - enemyHero->getPosition().x;
                        long long y_distance = myHero->getPosition().y - enemyHero->getPosition().y;
                        long long distance = pow(x_distance, 2) + pow(y_distance, 2);
                        if (distance < nearst_distance) {
                            target = enemyHero;
                            nearst_distance = distance;
                        }
                    }
                }
                if (targetFind) {
                    myHero->attack(target);
                    attacked = 1;
                }
            }
        }
        //�з���������
        for (auto enemyHero : allEnemyHeroes)
        {
            if (!enemyHero->getdie()&&enemyHero->isonboard()) {
                Hero* target;
                bool targetFind = 0;
                long long nearst_distance = 99999999999;
                for (auto myHero : allMyHeroes) {
                    if (!myHero->getdie()&&myHero->isonboard()) {
                        targetFind = 1;
                        long long x_distance = myHero->getPosition().x - enemyHero->getPosition().x;
                        long long y_distance = myHero->getPosition().y - enemyHero->getPosition().y;
                        long long distance = pow(x_distance, 2) + pow(y_distance, 2);
                        if (distance < nearst_distance) {
                            target = myHero;
                            nearst_distance = distance;
                        }
                    }
                }

                if (targetFind) {
                    enemyHero->attack(target);
                    attacked = 1;
                }

            }
        }
        if (!attacked) {
            unschedule(CC_SCHEDULE_SELECTOR(playerScene::attack));
            fight = 0;

            //ССӢ�۵Ĺ��������Զ���Ѫ
            int countUnDead = 0;
            for (Hero* hero : allEnemyHeroes) {
                if (hero->isonboard() && !hero->getdie()) {
                    countUnDead++;
                }
            }
            if (countUnDead == 0) {
                if (enemyType == 1)
                {
                    myrole->attack(enemyrole1);
                }
                else {
                    myrole->attack(enemyrole2);
                }
            }
            countUnDead = 0;
            for (Hero* hero : allMyHeroes) {
                if (hero->isonboard() && !hero->getdie()) {
                    countUnDead++;
                }
            }
            if (countUnDead == 0) {
                if (enemyType == 1)
                {
                    enemyrole1->attack(myrole);
                }
                else {
                    enemyrole2->attack(myrole);
                }
            }
            schedule(CC_SCHEDULE_SELECTOR(playerScene::startGame), 1.0f);
        }
    }

    //ͨ�����fightȫ�ֱ�����ʵ��׼��������ս�����ڵĽ���
    void startGame(float dt) {  
        if (fight == 0) {  //�˳�ս�����ֵ�׼������
            unschedule(CC_SCHEDULE_SELECTOR(playerScene::startGame));  //ֹͣ���ѭ���ص�
            static int count = 0;  //����������ʼ�����̵���ظ�ˢ��
            if (count)
            {
                store->gold += 2;  
                store->refresh();   //�µĻ��ڻ�ˢ���̵�

                //ÿһ�ֵĶ��⽱��
                store->gold += 2;

                // ÿ��10����ҿ��Է���һ����ҵ���Ϣ
                store->gold += store->gold / 10;
                store->updateUI();
            }
            count++;

            seeEnemy1->setEnabled(true);
            seeEnemy2->setEnabled(true);

            //�����ҷ�Ӣ��
            ShowHeroes(0);

            //��ȥ�з�Ӣ��
            CoverHeroes(enemyType);

            // �л�����
            enemyType = 3 - enemyType;             

            //��������ʼ
            progress0->setVisible(true);
            progress1->setVisible(true);
            // ���ö�ʱ������Ƶ��
            this->schedule([this](float dt) {
                currentTime += dt;
            // ���㵱ǰ����
            float progressPercentage = (currentTime / totalTime) * 100.0f;
            // ���½�����
            progress1->setPercentage(progressPercentage);

            // �ж��Ƿ�ﵽ��ʱʱ�䣬����ﵽ��ȡ����ʱ���������������
            if (currentTime >= totalTime) {  //׼��ʱ�����
                this->unschedule("progress");
                currentTime = 0.0f;   //����
                fight = 1;
                progress0->setVisible(false);
                progress1->setVisible(false);
                schedule(CC_SCHEDULE_SELECTOR(playerScene::startGame), 1.0f);
            }
                }, "progress");
        }
        else {
            unschedule(CC_SCHEDULE_SELECTOR(playerScene::startGame));  //ֹͣ���ص�
            //��ʾ�з�Ӣ��
            ShowHeroes(enemyType);
            ShowHeroes(0);
            store->setVisible(true);

            // ���ù۲찴���Ľ���
            goback->setVisible(false);
            seeEnemy1->setEnabled(false);
            seeEnemy2->setEnabled(false);

            //��ʼ�Դ�
            startattack();
        }
    }

    void seeEnemy1_callback(Ref* pSender);  //�۲��˻�1������
    void seeEnemy2_callback(Ref* pSender);  //�۲��˻�2������
    void goback_callback(Ref* pSender);     //����
    void enemyMove(float dt);    //�˻����ƶ�
};

