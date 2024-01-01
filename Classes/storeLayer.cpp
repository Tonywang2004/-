#include <random>
#include "cocos2d.h"
#include <string>
#include "playerScene.h"

extern chessboardSeat seat1;
extern preparationSeat seat2;
extern Vector<Hero *> allMyHeroes;    // �ҷ�����Ӣ��
extern Vector<Hero *> allEnemyHeroes; // �з�����Ӣ��

// �ȼ������
const int exp_level_up[6] = {0, 0, 4, 8, 16, 36};
// exp_level_up[i]��ʾ��i-1������i����Ҫ�ľ���
const int MAX_LEVEL = 5; // ��ߵȼ�

storeLayer *storeLayer::createLayer()
{
    return storeLayer::create();
}

bool storeLayer::init()
{
    // ������δ��ʼ��
    if (!Layer::init())
    {
        return false;
    }

    gold = 50; // ��ʼ�������
    exp = 0;   // ��ʼ����ֵ
    level = 1; // ��ʼ�ȼ�

    // ��ȡ��ǰ��Ļ�ĳߴ��ԭ��λ��
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // �����̵�
    auto store = Sprite::create("store.jpg");
    if (store != NULL)
    {
        // ���ñ��������λ��
        store->setPosition(Vec2(visibleSize.width * 0.5 + origin.x, visibleSize.height * 0.05 + origin.y));
        store->setScale(0.4);

        // ������������ӵ�������
        this->addChild(store, 0);
        /*���ϳ�����Ϊʾ���������*/
    }

    // �̵�������ť
    auto lockStore = ui::CheckBox::create("lockStore.jpg", "lockStore_click.jpg");
    lockStore->setPosition(Vec2(origin.x + visibleSize.width * 0.715, origin.y + visibleSize.height * 0.09));
    lockStore->setScale(0.6f);

    // ���ø�ѡ��״̬�ı�
    lockStore->addEventListener([=](Ref *sender, ui::CheckBox::EventType type)
                                {
        if (type == ui::CheckBox::EventType::SELECTED) {

        }
        else if (type == ui::CheckBox::EventType::UNSELECTED) {

        } });
    this->addChild(lockStore);

    // ������ҡ��ȼ���ǩ
    goldLabel = Label::createWithTTF("Gold: " + std::to_string(gold), "fonts/arial.ttf", 30);
    levelLabel = Label::createWithTTF("Degree: " + std::to_string(level), "fonts/arial.ttf", 30);
    goldLabel->setPosition(origin.x + visibleSize.width * 0.25, origin.y + visibleSize.height * 0.03);
    levelLabel->setPosition(origin.x + visibleSize.width * 0.25, origin.y + visibleSize.height * 0.09);
    this->addChild(goldLabel, 3);
    this->addChild(levelLabel, 3);

    // ����������
    expBar = ui::LoadingBar::create("LoadingBarFile.png");
    expBar->setDirection(ui::LoadingBar::Direction::LEFT);
    expBar->setPosition(Point(0, 0));
    this->addChild(expBar);

    // ����������ť
    upgradeButton = MenuItemImage::create("refreshExperience.jpg", "refreshExperience_click.jpg",
                                          CC_CALLBACK_1(storeLayer::onUpgradeButtonClicked, this));

    // ���5��
    this->schedule([this](float dt)
                   {
        if (level == 5) {
            upgradeButton->setEnabled(false);  //������������
            this->unschedule("cutupgrade");
        } },
                   "cutupgrade");

    // ����ˢ�°�ť
    auto refreshButton = MenuItemImage::create("buyGold.jpg", "buyGold_click.jpg",
                                               CC_CALLBACK_1(storeLayer::onRefreshButtonClicked, this));
    auto storeMenu = Menu::create(upgradeButton, refreshButton, nullptr);
    storeMenu->setPosition(origin.x + visibleSize.width * 0.09, origin.y - visibleSize.height * 0.188); // �ڳ����еĲ���
    storeMenu->alignItemsVerticallyWithPadding(0);                                                      // ���ô�ֱ����
    storeMenu->setScale(0.53);
    this->addChild(storeMenu);

    createHeroButtons();

    updateUI(); // ��ʼ��UI��ʾ

    return true;
}

void storeLayer::updateUI()
{
    // ���½�ҡ��ȼ���ǩ�;�������ʾ
    goldLabel->setString("Gold: " + std::to_string(gold));
    levelLabel->setString("Level: " + std::to_string(level));
    if (level < MAX_LEVEL)
        expBar->setPercent(100 * (double(exp) / exp_level_up[level + 1]));
    else
        expBar->setPercent(100);
}

void storeLayer::upgrade()
{
    // �����������
    if (gold >= 4)
    {
        gold -= 4;
        exp += 4;
        if (level < MAX_LEVEL && exp >= exp_level_up[level + 1])
        {
            exp -= exp_level_up[level + 1];
            level++;
        }
        updateUI(); // ����UI��ʾ
    }
}

void storeLayer::refresh()
{
    // ˢ�²���
    if (gold >= 2)
    {
        gold -= 2;
        // ʵ��ˢ���߼��������Ϊ������������
        createHeroButtons();
        updateUI(); // ����UI��ʾ
    }
}

void storeLayer::onUpgradeButtonClicked(Ref *sender)
{
    // ������ť����¼�
    upgrade();
}

void storeLayer::onRefreshButtonClicked(Ref *sender)
{
    // ˢ�°�ť����¼�
    refresh();
}

// ���Ӣ�۰���
void storeLayer::createHeroButtons()
{

    // ��ȡ��ǰ��Ļ�ĳߴ��ԭ��λ��
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    srand(std::time(0));

    // ��һ����ť
    if (heroButton1 != nullptr)
        heroButton1->removeFromParent();
    int randnum = rand() % 6 + 1;
    if (randnum == 1)
        heroButton1 = ui::Button::create("soldier.png");
    else if (randnum == 2)
        heroButton1 = ui::Button::create("supersoldier.png");
    else if (randnum == 3)
        heroButton1 = ui::Button::create("Demonsoldier.png");
    else if (randnum == 4)
        heroButton1 = ui::Button::create("shooter.png");
    else if (randnum == 5)
        heroButton1 = ui::Button::create("supershooter.png");
    else if (randnum == 6)
        heroButton1 = ui::Button::create("demonshooter.png");
    heroButton1->setPosition(Point(origin.x + visibleSize.width * 0.39, origin.y + visibleSize.height * 0.05));
    // ���ñ�׼�ߴ�
    auto originalSize = heroButton1->getContentSize();

    // ��������������ʹ�����С��Ϊ20x20����
    float scaleX = 150.0f / originalSize.width;
    float scaleY = 150.0f / originalSize.height;

    // ���þ��������
    heroButton1->setScale(scaleX, scaleY);
    heroButton1->addClickEventListener(CC_CALLBACK_1(storeLayer::onHeroButtonClicked, this, 0));
    this->addChild(heroButton1);
    herotype[0] = randnum;

    // �ڶ�����ť
    if (heroButton2 != nullptr)
        heroButton2->removeFromParent();
    randnum = rand() % 6 + 1;
    if (randnum == 1)
        heroButton1 = ui::Button::create("soldier.png");
    else if (randnum == 2)
        heroButton1 = ui::Button::create("supersoldier.png");
    else if (randnum == 3)
        heroButton1 = ui::Button::create("Demonsoldier.png");
    else if (randnum == 4)
        heroButton1 = ui::Button::create("shooter.png");
    else if (randnum == 5)
        heroButton1 = ui::Button::create("supershooter.png");
    else if (randnum == 6)
        heroButton1 = ui::Button::create("demonshooter.png");
    heroButton2->setPosition(Point(origin.x + visibleSize.width * 0.39 + 1 * visibleSize.width * 0.07, origin.y + visibleSize.height * 0.05));
    // ���ñ�׼�ߴ�
    originalSize = heroButton2->getContentSize();

    // ��������������ʹ�����С��Ϊ20x20����
    scaleX = 150.0f / originalSize.width;
    scaleY = 150.0f / originalSize.height;

    // ���þ��������
    heroButton2->setScale(scaleX, scaleY);
    heroButton2->addClickEventListener(CC_CALLBACK_1(storeLayer::onHeroButtonClicked, this, 1));
    this->addChild(heroButton2);
    herotype[1] = randnum;

    // ��������ť
    if (heroButton3 != nullptr)
        heroButton3->removeFromParent();
    randnum = rand() % 6 + 1;
    if (randnum == 1)
        heroButton1 = ui::Button::create("soldier.png");
    else if (randnum == 2)
        heroButton1 = ui::Button::create("supersoldier.png");
    else if (randnum == 3)
        heroButton1 = ui::Button::create("Demonsoldier.png");
    else if (randnum == 4)
        heroButton1 = ui::Button::create("shooter.png");
    else if (randnum == 5)
        heroButton1 = ui::Button::create("supershooter.png");
    else if (randnum == 6)
        heroButton1 = ui::Button::create("demonshooter.png");
    heroButton3->setPosition(Point(origin.x + visibleSize.width * 0.39 + 2 * visibleSize.width * 0.07, origin.y + visibleSize.height * 0.05));
    // ���ñ�׼�ߴ�
    originalSize = heroButton3->getContentSize();

    // ��������������ʹ�����С��Ϊ20x20����
    scaleX = 150.0f / originalSize.width;
    scaleY = 150.0f / originalSize.height;

    // ���þ��������
    heroButton3->setScale(scaleX, scaleY);
    heroButton3->addClickEventListener(CC_CALLBACK_1(storeLayer::onHeroButtonClicked, this, 2));
    this->addChild(heroButton3);
    herotype[2] = randnum;

    // ���ĸ���ť
    if (heroButton4 != nullptr)
        heroButton4->removeFromParent();
    randnum = rand() % 6 + 1;
    if (randnum == 1)
        heroButton1 = ui::Button::create("soldier.png");
    else if (randnum == 2)
        heroButton1 = ui::Button::create("supersoldier.png");
    else if (randnum == 3)
        heroButton1 = ui::Button::create("Demonsoldier.png");
    else if (randnum == 4)
        heroButton1 = ui::Button::create("shooter.png");
    else if (randnum == 5)
        heroButton1 = ui::Button::create("supershooter.png");
    else if (randnum == 6)
        heroButton1 = ui::Button::create("demonshooter.png");
    heroButton4->setPosition(Point(origin.x + visibleSize.width * 0.39 + 3 * visibleSize.width * 0.07, origin.y + visibleSize.height * 0.05));
    // ���ñ�׼�ߴ�
    originalSize = heroButton4->getContentSize();

    // ��������������ʹ�����С��Ϊ20x20����
    scaleX = 150.0f / originalSize.width;
    scaleY = 150.0f / originalSize.height;

    // ���þ��������
    heroButton4->setScale(scaleX, scaleY);
    heroButton4->addClickEventListener(CC_CALLBACK_1(storeLayer::onHeroButtonClicked, this, 3));
    this->addChild(heroButton4);
    herotype[3] = randnum;

    // �������ť
    if (heroButton5 != nullptr)
        heroButton5->removeFromParent();
    randnum = rand() % 6 + 1;
    if (randnum == 1)
        heroButton1 = ui::Button::create("soldier.png");
    else if (randnum == 2)
        heroButton1 = ui::Button::create("supersoldier.png");
    else if (randnum == 3)
        heroButton1 = ui::Button::create("Demonsoldier.png");
    else if (randnum == 4)
        heroButton1 = ui::Button::create("shooter.png");
    else if (randnum == 5)
        heroButton1 = ui::Button::create("supershooter.png");
    else if (randnum == 6)
        heroButton1 = ui::Button::create("demonshooter.png");
    heroButton5->setPosition(Point(origin.x + visibleSize.width * 0.39 + 4 * visibleSize.width * 0.07, origin.y + visibleSize.height * 0.05));
    // ���ñ�׼�ߴ�
    originalSize = heroButton5->getContentSize();

    // ��������������ʹ�����С��Ϊ20x20����
    scaleX = 150.0f / originalSize.width;
    scaleY = 150.0f / originalSize.height;

    // ���þ��������
    heroButton5->setScale(scaleX, scaleY);
    heroButton5->addClickEventListener(CC_CALLBACK_1(storeLayer::onHeroButtonClicked, this, 4));
    this->addChild(heroButton5);
    herotype[4] = randnum;
}

// ���������
void storeLayer::onHeroButtonClicked(Ref *sender, int buttonIndex)
{

    // ��ȡ��ǰ��Ļ�ĳߴ��ԭ��λ��
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    for (int i = 0; i < 9; i++)
    {
        if (seat2.seats[i].IsEmpty())
        {
            if (gold >= herocost[herotype[buttonIndex]])
            {

                // ��Ҽ���
                gold -= herocost[herotype[buttonIndex]];
                updateUI(); // ˢ��

                // ��սϯ��ʾ
                // auto hero = Hero::creatHero(herotype[buttonIndex], Vec2(origin.x + visibleSize.width * 0.34 + (i - 1) * visibleSize.width * 0.08, origin.y + visibleSize.height * 0.17), 1);
                auto hero = Hero::creatHero(herotype[buttonIndex], Vec2(seat2.seats[i].x + 70, seat2.seats[i].y + 50), 1);
                this->getParent()->addChild(hero, 2);
                seat2.seats[i].Setsprite();
                hero->setIndex(i);

                // ������ʧ
                if (buttonIndex == 0)
                {
                    heroButton1->removeFromParent();
                    delete heroButton1;
                    heroButton1 = nullptr;
                }
                else if (buttonIndex == 1)
                {
                    heroButton2->removeFromParent();
                    delete heroButton2;
                    heroButton2 = nullptr;
                }
                else if (buttonIndex == 2)
                {
                    heroButton3->removeFromParent();
                    delete heroButton3;
                    heroButton3 = nullptr;
                }
                else if (buttonIndex == 3)
                {
                    heroButton4->removeFromParent();
                    delete heroButton4;
                    heroButton4 = nullptr;
                }
                else if (buttonIndex == 4)
                {
                    heroButton5->removeFromParent();
                    delete heroButton5;
                    heroButton5 = nullptr;
                }

                Hero::mergeHeroes();

                break;
            }
        }
    }
}
// ������ť
ui::Button *storeLayer::createButton(const std::string &normalImage, const std::string &selectedImage, const Vec2 &position,
                                     const float &scale, const std::function<void(Ref *, ui::Widget::TouchEventType)> &callback)
{
    auto button = ui::Button::create(normalImage, selectedImage);
    button->setPosition(position);
    button->setScale(scale);
    button->addTouchEventListener(callback);
    this->addChild(button, 2);
    return button;
}
