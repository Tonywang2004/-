//#include "cocos2d.h"
//#include"heroAction.h"
//USING_NS_CC;
//ImageSwitcher::ImageSwitcher(string filename1,string filename2,Hero* hero)
//{
//    _imageA = Sprite::create(filename1);
//    _imageB = Sprite::create(filename2);
//    _imageA->setContentSize(hero->mine->getContentSize());
//    _imageA->setPosition(hero->mine->getPosition());
//    _imageB->setContentSize(hero->mine->getContentSize());
//    _imageB->setPosition(hero->mine->getPosition());
//    addChild(_imageA); 
//
//    // 使用Scheduler每隔1秒触发切换操作
//    schedule(CC_SCHEDULE_SELECTOR(ImageSwitcher::switchImage), hero->as);
//}
//void ImageSwitcher::switchImage(float dt)
//{
//    if (_imageA->getParent() != nullptr)
//    {
//        addChild(_imageB);
//        _imageA->removeFromParent();
//    }
//    else
//    {
//        addChild(_imageA);
//        _imageB->removeFromParent();
//    }
//}