#include "playerScene.h"
#include"hero.h"
#include"AudioControl.h"
#include"SettingScene.h"
#include"MoveLittleHero.h"
#include<vector>
#include"endScene.h"
USING_NS_CC;

#define STORETAG   462

std::vector<Sprite*>MySeat;  //��СΪ14


int enemyType = 1;  // ��һ������

chessboardSeat seat1(1);   //����λ��
preparationSeat seat2(1);   //��սϯλ��

chessboardSeat seat3(0);   //�з�����λ��
preparationSeat seat4(0);   //�з���սϯλ��

extern Vector<Hero*> allMyHeroes;//�ҷ�����Ӣ��
extern Vector<Hero*> allEnemyHeroes;//�з�����Ӣ��

extern int fight;  //�׶��л�

playerScene* playerScene::createScene() {
	return playerScene::create();
}

bool playerScene::init() {

	if (!Scene::create()) {
		return 0;
	}

	// ��ȡ��ǰ��Ļ�ĳߴ��ԭ��λ��
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// ������������
	auto background = Sprite::create("pink_1.jpg");
	if (background != NULL)
	{
		// ���ñ��������λ��
		background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

		// ���ű����������Ļ
		float scaleX = visibleSize.width / background->getContentSize().width;
		float scaleY = visibleSize.height / background->getContentSize().height;
		background->setScale(scaleX, scaleY);

		// ������������ӵ�������
		this->addChild(background, 0); // 0 ��ʾ�㼶��ȷ����������ײ�
	}


	// ����ССӢ��
	auto hero = littleHero::create("LittlePlayer_1_0.png");
	if (hero) {
		hero->setPosition(Vec2(visibleSize.width / 4.5 + origin.x, visibleSize.height / 3.8 + origin.y)); // ����Ӣ�۵�λ��
		hero->setScale(0.8);
		this->addChild(hero); // ��Ӣ����ӵ�������
	}
	hero->enableMouseControl(true);

	//�������ð�ť
	auto setting = createButton("setting_icon.png", "setting_icon_click.png", Vec2(origin.x + visibleSize.width * 0.95, origin.y + visibleSize.height * 0.9),
		2.5, [=](Ref* sender, ui::Widget::TouchEventType type) {
			if (type == ui::Widget::TouchEventType::ENDED) {
				// ���ŵ����Ч
				AudioControl::getInstance()->playClickSoundEffect();
				// ������һ������
				auto newScene = SettingScene::create();
				//�л�����һ������
				cocos2d::Director::getInstance()->pushScene(TransitionFade::create(1.0, newScene, Color3B(255, 255, 240)));
			}
		});



	// �ҷ��ĳ�ʼӢ��
	auto hero1 = Hero::creatHero(1, Vec2(seat1.seats[0].x + 70, seat1.seats[0].y + 50), 1);
	seat1.seats[0].state = 1;
	this->addChild(hero1, 2);
	hero1->enterboard();
	hero1->setIndex(0);


	//Ӣ��λ���ƶ�
	auto changePosListener = EventListenerTouchOneByOne::create();
	changePosListener->setSwallowTouches(true);   
	//Ӣ�۵���ж�
	changePosListener->onTouchBegan = [this](Touch* t, Event* e)->bool {
		//ս������ֻ�ܶԱ�սϯ��Ӣ�۵����Ч
		if (fight) {
			for (Hero* hero : allMyHeroes) {
				if (!hero->isonboard()) {  //����ս��ϯ��
					Vec2 myclick = t->getLocation();
					myclick = hero->convertToNodeSpace(myclick);
					Rect spriteBoundingBox = Rect(0, 0, hero->getContentSize().width, hero->getContentSize().height);
					if (spriteBoundingBox.containsPoint(myclick)) {
						hero->setclick(1);
						return true;
					}
				}
			}
			return false;  //��û�е������սϯ���κ�Ӣ��
		}
		else {  //��ս�����ڶ����м���Ӣ�۵������Ч
			for (Hero* hero : allMyHeroes) {
				Vec2 myTurn = t->getLocation();
				myTurn = hero->convertToNodeSpace(myTurn);
				Rect spriteBoundingBox = Rect(0, 0, hero->getContentSize().width, hero->getContentSize().height);
				if (spriteBoundingBox.containsPoint(myTurn)) {
					hero->setclick(1);
					return true;
				}
			}
			return false;  //û�е�����κ�Ӣ��
		}

	};
	//Ӣ�۵��ƶ�
	changePosListener->onTouchMoved = [](Touch* t, Event* e)->void {
		for (Hero* hero : allMyHeroes) {
			if (hero->getclick()) {
				hero->setPosition(hero->getPosition() + t->getDelta());
				break;
			}
		}
	};
	//Ӣ�۷���
	changePosListener->onTouchEnded = [this](Touch* t, Event* e)->void {
		if (fight) {  //������ֻ�����Ƿ����ڱ�սϯ��
			int i;
			for (i = 5; i < 14; i++) {
				Vec2 clickEnd = t->getLocation();
				clickEnd = MySeat[i]->convertToNodeSpace(clickEnd);
				Rect spriteBoundingBox = Rect(0, 0, MySeat[i]->getContentSize().width, MySeat[i]->getContentSize().height);
				if (spriteBoundingBox.containsPoint(clickEnd)) {
					int index = i - 5;  //��սϯλ���±�
					
					//�жϸ�λ���Ƿ�Ϊ��
					if (seat2.seats[index].state == 0) {  //��λ��
						for (Hero* hero : allMyHeroes) {
							if (hero->getclick()) {  //�ҵ��������Ӣ��
								seat2.seats[hero->getindex()].Removesprite();  //ԭλ����Ϊ��
								hero->setIndex(index);  //Ӣ�۴洢���±�
								hero->setPosition(seat2.seats[index].x + 70, seat2.seats[index].y + 50);
								seat2.seats[index].Setsprite();
								hero->setclick(0);  //���õ��
								break;
							}
						}
					}
					else {   //�ǿ�λ��
						for (Hero* hero1 : allMyHeroes) {
							if (hero1->getclick()) {  //�ҵ��������Ӣ��
								for (Hero* hero2 : allMyHeroes) {
									if (!hero2->isonboard() && hero2->getindex() == index) {
										//����λ��
										hero2->setIndex(hero1->getindex());
										hero1->setIndex(index);
										hero1->setPosition(seat2.seats[hero1->getindex()].x + 70, seat2.seats[hero1->getindex()].y + 50);
										hero2->setPosition(seat2.seats[hero2->getindex()].x + 70, seat2.seats[hero2->getindex()].y + 50);
										hero1->setclick(0);
										break;
									}
								}
								break;
							}
						}
					}
					break;  //�˳�����������սϯλ��
				}
			}
			if (i == 14) {  //�ص�ԭ��
				for (Hero* hero : allMyHeroes) {
					if (hero->getclick()) {
						hero->setPosition(seat2.seats[hero->getindex()].x + 70, seat2.seats[hero->getindex()].y + 50);
						hero->setclick(0);
						break;
					}
				}
			}
		}
		else {   //�����㿼�����е�λ
			int i;
			for (i = 0; i < 14; i++) {
				Vec2 clickEnd = t->getLocation();
				clickEnd = MySeat[i]->convertToNodeSpace(clickEnd);
				Rect spriteBoundingBox = Rect(0, 0, MySeat[i]->getContentSize().width, MySeat[i]->getContentSize().height);
				if (spriteBoundingBox.containsPoint(clickEnd)) {  //ͣ������ĳ��λ��
					if (i >= 5) {  //ͣ����λ���Ǳ�սϯ
						int index = i - 5;  //��սϯλ���±�

						//�жϸ�λ���Ƿ�Ϊ��
						if (seat2.seats[index].state == 0) {  //��λ��
							for (Hero* hero : allMyHeroes) {
								if (hero->getclick()) {  //�ҵ��������Ӣ��
									if (hero->isonboard()) {  //ԭλ����ս��ϯ
										seat1.seats[hero->getindex()].Removesprite();  //ԭλ����Ϊ��
									}
									else {   //ԭλ���ڱ�սϯ
										seat2.seats[hero->getindex()].Removesprite();  //ԭλ����Ϊ��
									}
									
									hero->setIndex(index);  //Ӣ�۴洢���±�
									hero->setPosition(seat2.seats[index].x + 70, seat2.seats[index].y + 50);
									seat2.seats[index].Setsprite();
									hero->outboard();  //�ص���սϯ
									hero->setclick(0);  //���õ��
									break;
								}
							}
						}
						else {   //�ǿ�λ��
							for (Hero* hero1 : allMyHeroes) {
								if (hero1->getclick()) {  //�ҵ��������Ӣ��
									for (Hero* hero2 : allMyHeroes) {
										if (!hero2->isonboard() && hero2->getindex() == index) {
											//����λ��
											hero2->setIndex(hero1->getindex());
											hero1->setIndex(index);
											hero1->setPosition(seat2.seats[hero1->getindex()].x + 70, seat2.seats[hero1->getindex()].y + 50);
											if (!hero1->isonboard())
											{
												hero2->setPosition(seat2.seats[hero2->getindex()].x + 70, seat2.seats[hero2->getindex()].y + 50);
											}
											else {
												hero2->setPosition(seat1.seats[hero2->getindex()].x + 70, seat1.seats[hero2->getindex()].y + 50);
											}
											hero1->setclick(0);
											hero2->setboard(hero1->isonboard());
											hero1->outboard();
											break;
										}
									}

									break;
								}
							}
						}
					}
					else {   //ͣ����λ����ս��ϯ
						int index = i;
						if (seat1.seats[index].state == 0) {  //��λ��
							int hero_in_board = 0;
							for (Hero* hero : allMyHeroes) {
								if (hero->isonboard()) {
									hero_in_board++;
								}
							}
							for (Hero* hero : allMyHeroes) {
								if (hero->getclick()) {  //�ҵ��������Ӣ��
									if (hero->isonboard()) {  //ԭλ����ս��ϯ
										seat1.seats[hero->getindex()].Removesprite();  //ԭλ����Ϊ��
										hero->setIndex(index);  //Ӣ�۴洢���±�
										hero->setPosition(seat1.seats[index].x + 70, seat1.seats[index].y + 50);
										seat1.seats[index].Setsprite();
										hero->enterboard();  //��ս��
										hero->setclick(0);  //���õ��
									}
									else {   //ԭλ���ڱ�սϯ
										if (hero_in_board >= store->level)  //��������
										{
											hero->setPosition(seat2.seats[hero->getindex()].x + 70, seat2.seats[hero->getindex()].y + 50);
										}
										else {
											seat2.seats[hero->getindex()].Removesprite();  //ԭλ����Ϊ��
											hero->setIndex(index);  //Ӣ�۴洢���±�
											hero->setPosition(seat1.seats[index].x + 70, seat1.seats[index].y + 50);
											seat1.seats[index].Setsprite();
											hero->enterboard();  //��ս��
											hero->setclick(0);  //���õ��
										}
									}
									break;
								}
							}
						}
						else {   //�ǿ�λ��
							for (Hero* hero1 : allMyHeroes) {
								if (hero1->getclick()) {  //�ҵ��������Ӣ��
									for (Hero* hero2 : allMyHeroes) {
										if (hero2->isonboard() && hero2->getindex() == index) {
											//����λ��
											hero2->setIndex(hero1->getindex());
											hero1->setIndex(index);
											hero1->setPosition(seat1.seats[hero1->getindex()].x + 70, seat1.seats[hero1->getindex()].y + 50);
											if(!hero1->isonboard())
											{
												hero2->setPosition(seat2.seats[hero2->getindex()].x + 70, seat2.seats[hero2->getindex()].y + 50);
											}
											else {
												hero2->setPosition(seat1.seats[hero2->getindex()].x + 70, seat1.seats[hero2->getindex()].y + 50);
											}
											hero1->setclick(0);
											hero2->setboard(hero1->isonboard());
											hero1->enterboard();
											break;
										}
									}

									break;
								}
							}
						}
					}

					break;  //�˳�����������սϯλ��
				}
			}
			if (i == 14) {  //�ص�ԭ��
				for (Hero* hero : allMyHeroes) {
					if (hero->getclick()) {
						if(!hero->isonboard())
						{
							hero->setPosition(seat2.seats[hero->getindex()].x + 70, seat2.seats[hero->getindex()].y + 50);
						}
						else {
							hero->setPosition(seat1.seats[hero->getindex()].x + 70, seat1.seats[hero->getindex()].y + 50);
						}
						hero->setclick(0);
						break;
					}
				}
			}
		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(changePosListener, this);


	//ÿһ֡����Ӣ�۵�Ѫ��������
	this->schedule([this](float dt) {
		//�����ҷ�Ӣ��Ѫ��������
		for (Hero* hero : allMyHeroes) {
			hero->updatebloodandmagic();
		}
        //���µз�Ӣ�۵�Ѫ��������
	    for (Hero* hero : allEnemyHeroes) {
		    hero->updatebloodandmagic();
	    }
	}, "updateherobar");


	//ÿһ֡����
	this->schedule([this](float dt) {
		float mypercentage = myrole->cur_blood / myrole->max_blood * 100.0f;
	    myrole->healthBar->setPercentage(mypercentage);
		if (enemyType == 2)
		{
			float enemypercentage = enemyrole1->cur_blood / enemyrole1->max_blood * 100.0f;
			enemyrole1->healthBar->setPercentage(enemypercentage);
		}
		else {
			float enemypercentage = enemyrole2->cur_blood / enemyrole2->max_blood * 100.0f;
			enemyrole2->healthBar->setPercentage(enemypercentage);
		}

		if (myrole->cur_blood == 0 && (enemyrole1->cur_blood != 0 || enemyrole2->cur_blood != 0)) {  //�ҷ�ʧ��
			auto delayAction = DelayTime::create(1.0f); // ͣ��1��
			auto callback = CallFunc::create([]() {
				auto endscene = endScene::createScene(0);
			    Director::getInstance()->replaceScene(endscene);
			});
			auto sequence = Sequence::create(delayAction, callback, nullptr);
			this->runAction(sequence);
		}
		if (myrole->cur_blood != 0 && enemyrole1->cur_blood == 0 && enemyrole2->cur_blood == 0) {  //�з�ʧ��
			auto delayAction = DelayTime::create(1.0f); // ͣ��1��
			auto callback = CallFunc::create([]() {
				auto endscene = endScene::createScene(1);
			    Director::getInstance()->replaceScene(endscene);
			});
			auto sequence = Sequence::create(delayAction, callback, nullptr);
			this->runAction(sequence);
		}
		if (myrole->cur_blood == 0 && enemyrole1->cur_blood == 0 && enemyrole2->cur_blood == 0) {  //ƽ��
			auto delayAction = DelayTime::create(1.0f); // ͣ��1��
			auto callback = CallFunc::create([]() {
				auto endscene = endScene::createScene(2);
			    Director::getInstance()->replaceScene(endscene);
			});
			auto sequence = Sequence::create(delayAction, callback, nullptr);
			this->runAction(sequence);
		}
	}, "updaterolebar");

	//����������
	progress0 = Sprite::create("progress0.png");
	progress1 = ProgressTimer::create(Sprite::create("progress1.png"));
	progress0->setPosition(955, 1000);
	progress1->setPosition(955, 1000);
	this->addChild(progress0, 5);
	this->addChild(progress1, 6);
	progress1->setType(ProgressTimer::Type::BAR);
	progress1->setMidpoint(Vec2(0, 0.5)); // ������
	progress1->setBarChangeRate(Vec2(1, 0)); // ��ˮƽ����ı�


	//��Ϸ��ѭ���Ļص�����
	this->schedule(CC_SCHEDULE_SELECTOR(playerScene::startGame), 1.0f);


	/*�ҷ�λ��ͼ�����ʾ(����ʾ�ҷ�)*/
//λ��ͼ���ʼ��
	for (int i = 0; i < 14; i++) {
		MySeat.push_back(Sprite::create("seats.png"));
	}
	//ͼ����ʾ
	for (int i = 0; i < 5; i++) {
		MySeat[i]->setScale(0.25);
		MySeat[i]->setPosition(seat1.seats[i].x + 70, seat1.seats[i].y + 50);
		this->addChild(MySeat[i], 1);
	}
	for (int i = 0; i < 9; i++) {
		MySeat[i + 5]->setScale(0.25);
		MySeat[i + 5]->setPosition(seat2.seats[i].x + 70, seat2.seats[i].y + 50);
		this->addChild(MySeat[i + 5], 1);
	}




	//Ӣ������
	auto sellheroListener = EventListenerMouse::create();
	sellheroListener->onMouseDown = [this](EventMouse* event)->void {
		if (event->getMouseButton() == EventMouse::MouseButton::BUTTON_RIGHT) {
			//��ս������ֻ������սϯ�ϵ�Ӣ��
			if (fight) {
				for (Hero* hero : allMyHeroes) {
					if (!hero->isonboard()) {  //����ս��ϯ��
						Vec2 touchLocation = Vec2(event->getCursorX(), event->getCursorY());
						touchLocation = hero->convertToNodeSpace(touchLocation);
						Rect spriteBoundingBox = Rect(0, 0, hero->getContentSize().width, hero->getContentSize().height);
						if (spriteBoundingBox.containsPoint(touchLocation)) {
							//�̵��Ǯ��Ҫ��ʾˢ��
							store->gold += (store->herocost[hero->getNo()]) * pow(3, (hero->getlevel()) - 1);
							store->updateUI();

							//Ӣ����ʧ
							seat2.seats[hero->getindex()].Removesprite();
							allMyHeroes.eraseObject(hero);
							hero->removeFromParent();
							break;
						}
					}
				}
			}
			else {  //��ս�����ڣ����Ե������Ӣ��
				for (Hero* hero : allMyHeroes) {
					Vec2 touchLocation = Vec2(event->getCursorX(), event->getCursorY());
					touchLocation = hero->convertToNodeSpace(touchLocation);
					Rect spriteBoundingBox = Rect(0, 0, hero->getContentSize().width, hero->getContentSize().height);
					
					if (spriteBoundingBox.containsPoint(touchLocation)) {
						//ˢ�����
						store->gold += (store->herocost[hero->getNo()]) * pow(3, (hero->getlevel()) - 1);
						store->updateUI();

						//ȥ��������Ӣ��
						if (hero->isonboard()) {
							seat1.seats[hero->getindex()].Removesprite();
						}
						else {
							seat2.seats[hero->getindex()].Removesprite();
						}
						allMyHeroes.eraseObject(hero);
						hero->removeFromParent();
						break;
					}
				}
			}
		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(sellheroListener, this);


	//ССӢ��
	myrole = playerroleLayer::createLayer(0);
	this->addChild(myrole, 3, ROLETAG);
	enemyrole1= playerroleLayer::createLayer(1);
	this->addChild(enemyrole1, 3);
	enemyrole2 = playerroleLayer::createLayer(2);
	this->addChild(enemyrole2, 3);

	/* �˻�1 */
	auto enemy11 = Sprite::create("enemy11.png");
	auto enemy12 = Sprite::create("enemy12.png");
	auto enemy13 = Sprite::create("enemy13.png");
	seeEnemy1 = MenuItemSprite::create(enemy11, enemy12, enemy13,
		CC_CALLBACK_1(playerScene::seeEnemy1_callback, this));
	auto see_enemy1 = Menu::create(seeEnemy1, NULL);
	this->addChild(see_enemy1, 4);
	see_enemy1->setScale(0.7);
	see_enemy1->setPosition(1400, 700);
	
	/* �˻�2 */
	auto enemy21 = Sprite::create("enemy21.png");
	auto enemy22 = Sprite::create("enemy22.png");
	auto enemy23 = Sprite::create("enemy23.png");
	seeEnemy2 = MenuItemSprite::create(enemy21, enemy22, enemy23,
		CC_CALLBACK_1(playerScene::seeEnemy2_callback, this));
	auto see_enemy2 = Menu::create(seeEnemy2, NULL);
	this->addChild(see_enemy2, 4);
	see_enemy2->setScale(0.7);
	see_enemy2->setPosition(1400, 600);

	/* ���ذ��� */
	auto goback1 = Sprite::create("goback1.png");
	auto goback2 = Sprite::create("goback2.png");
	goback = MenuItemSprite::create(goback1, goback2,
		CC_CALLBACK_1(playerScene::goback_callback, this));
	auto go_back = Menu::create(goback, NULL);
	this->addChild(go_back, 4);
	go_back->setScale(0.7);
	go_back->setPosition(1400, 500);
	goback->setVisible(false);

	//�̵�
	store = storeLayer::createLayer();   
	this->addChild(store, 4);


	//ССӢ�۵��ƶ�
	auto roleMoveListener = EventListenerTouchOneByOne::create();
	roleMoveListener->setSwallowTouches(true);
	roleMoveListener->onTouchBegan = [background, this](Touch* t, Event* e)-> bool {
		Vec2 pos = background->convertTouchToNodeSpace(t);
		if (pos.x > 323 && pos.x < 1247 && pos.y>327 && pos.y < 839)  //ССӢ���ƶ���Χ
		{
			myrole->cur_position = Vec2(pos.x + 70, pos.y + 50);
			auto role = this->myrole->getChildByTag(ROLETAG);
			role->stopAllActions();
			role->runAction(MoveTo::create(0.3, Vec2(pos.x + 55.25, pos.y + 46.875)));
			return true;   //�¼����ٴ��ݸ�����������
		}
		else {
			return false;  //�¼����Լ�������
		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(roleMoveListener, this);
	


	// �˻�ССӢ�۵�����ƶ�
	this->schedule(CC_SCHEDULE_SELECTOR(playerScene::enemyMove), 10.0f); // 10���ʱ����
	//���з�Ӣ�۵��ƶ�
	this->schedule([this](float dt) {
		enemyrole1->getChildByTag(ROLETAG)->stopAllActions();
	enemyrole1->getChildByTag(ROLETAG)->runAction(MoveTo::create(0.3f, Vec2(enemyrole1->cur_position.x - 14.75, enemyrole1->cur_position.y - 3.125)));
	enemyrole2->getChildByTag(ROLETAG)->stopAllActions();
	enemyrole2->getChildByTag(ROLETAG)->runAction(MoveTo::create(0.3f, Vec2(enemyrole2->cur_position.x - 14.75, enemyrole2->cur_position.y - 3.125)));
		}, 0.3, "enemymove");
	return 1;
}

//��ʾ����Ӣ��
void playerScene::ShowHeroes(int turn) {
	if (turn == 0) {  //�ҷ�
		for (Hero* hero : allMyHeroes) {
			if (hero->isonboard()) {  //��ս����
				hero->setPosition(seat1.seats[hero->getindex()].x + 70, seat1.seats[hero->getindex()].y + 50);
			}
			else {  //�ڱ�սϯ��
				hero->setPosition(seat2.seats[hero->getindex()].x + 70, seat2.seats[hero->getindex()].y + 50);
			}
			hero->sethp(hero->gethpmax());   //���ó�ʼ��Ѫ
			hero->setmp(hero->getmpstart());  //���ó�ʼ����
			hero->setVisible(true);   //������ʾ
			if (hero->getdie()) {   //����Die��־
				hero->setdie(0);
			}
		}
	}
	else{  //����enemyrole1��Ӣ��
		//ɾ��ԭ����Ӣ��
		Vector<Hero*>heroToDelete;
		for (Hero* hero : allEnemyHeroes) {
			heroToDelete.pushBack(hero);
		}
		for (Hero* hero : heroToDelete) {
			allEnemyHeroes.eraseObject(hero);
			hero->removeFromParent();
		}

		//����seat3��stateΪ0
		for (int i = 0; i < 5; i++) {
			seat3.seats[i].state = 0;
		}

		int myPriority[5] = { 1,6,5,3,4 };  //Ӣ�����͵����ȼ�
		int enemyPriority[5] = { 3,6,1,4,5 };
		int i = 0;  
		for (Hero* myhero : allMyHeroes) {
			if (myhero->isonboard()) {
				Hero* enemy;
				if (turn == 1)
				{
					enemy = Hero::creatHero(myPriority[i], Vec2(0, 0), 0);
				}
				else if (turn == 2) {
					enemy = Hero::creatHero(enemyPriority[i], Vec2(0, 0), 0);
				}
				enemy->setIndex(myhero->getindex());    //�����±�
				enemy->enterboard();    
				this->addChild(enemy, 2);   
				enemy->setVisible(false);  
				seat3.seats[myhero->getindex()].state = 1;   
				enemy->upgrade(myhero->getlevel());  //����Ϊ��ͬ���Ǽ�
				i++;
			}
		}

		//��ʾ�з�Ӣ��
		for (Hero* hero : allEnemyHeroes) {
			if (hero->isonboard()) {  //��ս����
				hero->setPosition(seat3.seats[hero->getindex()].x + 70, seat3.seats[hero->getindex()].y + 50);
			}
			else {  //�ڱ�սϯ��
				hero->setPosition(seat4.seats[hero->getindex()].x + 70, seat4.seats[hero->getindex()].y + 50);
			}
			hero->sethp(hero->gethpmax());
			hero->setmp(hero->getmpstart());
			hero->setVisible(true);
			if (hero->getdie()) {
				hero->setdie(0);
			}
		}
	}
	Hero::mergeHeroes();
}


//��������Ӣ��
void playerScene::CoverHeroes(int tag) {
	if (tag == 0) {
		for (Hero* hero : allMyHeroes) {
			hero->setVisible(false);
		}
	}
	else {
		for (Hero* hero : allEnemyHeroes) {
			hero->setVisible(false);
		}
	}
}


//�˻�1������
void playerScene::seeEnemy1_callback(Ref* pSender) {
	seeEnemy1->setEnabled(false); 
	seeEnemy2->setEnabled(false);  
	goback->setVisible(true);  //���ذ���

	//��ʾ�з�
	CoverHeroes(0);
	store->setVisible(false);
	ShowHeroes(1);
}


//�˻�2������
void playerScene::seeEnemy2_callback(Ref* pSender) {
	seeEnemy1->setEnabled(false); 
	seeEnemy2->setEnabled(false);  
	goback->setVisible(true);  //���ذ���

	// ��ʾ�з�
	CoverHeroes(0);
	store->setVisible(false);
	ShowHeroes(2);
}


// ����
void playerScene::goback_callback(Ref* pSender) {
	goback->setVisible(false);
	seeEnemy1->setEnabled(true);
	seeEnemy2->setEnabled(true);

	//��ȥ�з�Ӣ�ۣ���ʾ�ҷ�Ӣ�ۺ��̵�
	CoverHeroes(1);
	ShowHeroes(0);
	store->setVisible(true);
}


// �˻�������ƶ�
void playerScene::enemyMove(float dt) {
	// ��ȡʵ�ʷֱ���
	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

	// ��д�˴�����ʱ�ķֱ���Ϊ 2560*1440
	cocos2d::Size designSize = cocos2d::Size(2560, 1440);

	// ����ʵ�ʷֱ�������Ʒֱ��ʵ����ű���
	float scaleX = visibleSize.width / designSize.width;
	float scaleY = visibleSize.height / designSize.height;

	// ��������Ʒֱ����µ�λ�úʹ�С
	cocos2d::Rect designBoardRect(400, 250, 1880, 1080);
	srand(time(0));
	int x = rand() % 540 + 400;
	int y = rand() % 430 + 250;
	// �˻�1��λ�����ݱ仯 
	enemyrole1->cur_position = Vec2(x + 70, y + 50);

	x = rand() % 540 + 400;
	y = rand() % 430 + 250;
	// �˻�2��λ�����ݱ仯 
	enemyrole1->cur_position = Vec2(x + 70, y + 50);
}

//������ť
ui::Button* playerScene::createButton(const string& normalImage, const string& selectedImage, const Vec2& position,
	const float& scale, const std::function<void(Ref*, ui::Widget::TouchEventType)>& callback) {
	auto button = ui::Button::create(normalImage, selectedImage);
	button->setPosition(position);
	button->setScale(scale);
	button->addTouchEventListener(callback);
	this->addChild(button, 2);
	return button;
}


void  playerScene::onEnter() {
	Scene::onEnter();
	// ����Ƿ��ھ���״̬
	if (!AudioControl::getInstance()->isMuted()) {
		// ���û�о��������¿�ʼ���ű�������
		AudioControl::getInstance()->playBackgroundMusic("BM.mp3", true);
	}
}

void  playerScene::onExit() {
	Scene::onExit();
}