#ifndef SG_DRAMA_SCENE_HERO_H
#define SG_DRAMR_SCENE_HERO_H

#include "cocos2d.h"
USING_NS_CC;

class SGDramaSceneHero : public Sprite 
{
public:
  static SGDramaSceneHero* create(const char* hero_name);

  void moveTo(Vec2 target_pos);

  bool init(const char* hero_name);

  bool initActions();

  void speak(const char* content);

  void actionFinished();
  Animate* animate;
};

#endif