#include "SGSceneHeroSpeakScene.h"
#include "SGGlobalSettings.h"
#include "SGHeroResourceUtils.h"

USING_NS_CC;


Scene* SGSceneHeroSpeakScene::creatScene(const char* hero_name, const char* content, const Vec2& pos)
{
  Scene* scene = Scene::create();

  SGSceneHeroSpeakScene* speak_layer = SGSceneHeroSpeakScene::create();
  Size win_size = Director::getInstance()->getVisibleSize();
  RenderTexture* render_texture = RenderTexture::create(win_size.width, win_size.height);

  render_texture->begin();
  Director::getInstance()->getRunningScene()->visit();
  render_texture->end();
  render_texture->setPosition(Vec2(win_size.width/2, win_size.height/2)); 

  speak_layer->addChild(render_texture);


  // Create the hero speak dialog window

  // step 1: create the dialog window backgound texture;
  Sprite* dialog_win = Sprite::create(DIALOG_WINDOW_BACKGROUND);
  Size dialog_size(win_size.width * 0.666f, win_size.height * 0.1928f);
  dialog_win->setTextureRect(Rect(0, 0, dialog_size.width, dialog_size.height));
  Texture2D::TexParams params = { GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT };
  dialog_win->getTexture()->setTexParameters(params);
  dialog_win->setAnchorPoint(Vec2::ZERO);

  // step 2: create hero face image;
  std::string hero_face_res = SG_HERO_FACE_RES_PATH;
  hero_face_res.append(SGHeroResourceUtils::getInstance()->getHeroResObj(hero_name)->res_name);
  hero_face_res.append(".png");

  std::string hero_face_res_full_path = FileUtils::getInstance()->fullPathForFilename(hero_face_res);
  Sprite* face = Sprite::create(hero_face_res_full_path);
  face->setPosition(Vec2(dialog_size.width * 0.1f ,dialog_size.height/2));
  dialog_win->addChild(face);

  // step 3: create dialog content background
  LayerColor* content_bg_layer = LayerColor::create(Color4B::WHITE, dialog_size.width * 0.75f ,dialog_size.height * 0.6667f);
  content_bg_layer->setPosition(Vec2(dialog_size.width * 0.2333f ,dialog_size.height * 0.0714f));
  dialog_win->addChild(content_bg_layer);

  // step4: create dialog content TTF
  Label* content_ttf = Label::create(content, TEXT_FONT_NAME, TEXT_FONT_SIZE);
  content_ttf->setHorizontalAlignment(TextHAlignment::LEFT);
  content_ttf->setColor(Color3B::BLACK);
  content_ttf->setAnchorPoint(Vec2(0.0f, 1.0f));
  content_ttf->setPosition(Vec2(20.0f, content_bg_layer->getContentSize().height - 10.0f));
  content_bg_layer->addChild(content_ttf);

  // set dialog window position
  Vec2 dialog_win_pos;
  if (pos == Vec2::ZERO) {
    dialog_win_pos = Vec2(win_size.width * 0.0278f, win_size.height * 0.03571f);
  } else {
    dialog_win->setAnchorPoint(Vec2(0.5f, 0.0f));
    dialog_win_pos = pos;
  }
  dialog_win->setPosition(dialog_win_pos);
  

  speak_layer->addChild(dialog_win);
  speak_layer->setName("dialog_layer");
  

  scene->addChild(speak_layer);

  

  return scene;
}


bool SGSceneHeroSpeakScene::init()
{
  if (!Layer::init()) {
    return false;
  }

  auto dispatcher = Director::getInstance()->getEventDispatcher();
  event_listener = EventListenerTouchOneByOne::create();
  event_listener->onTouchBegan = CC_CALLBACK_2(SGSceneHeroSpeakScene::onTouchBegin, this);
  event_listener->setSwallowTouches(true);
  dispatcher->addEventListenerWithSceneGraphPriority(event_listener,this);
  return true;
}

bool SGSceneHeroSpeakScene::onTouchBegin(Touch *touch, Event *unused_event)
{
  notifyObserver();
  Director::getInstance()->getEventDispatcher()->removeEventListener(event_listener);
  Director::getInstance()->popScene();
  return true;
}

