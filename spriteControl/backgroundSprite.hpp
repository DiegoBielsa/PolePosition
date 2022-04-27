#include "../globals/globals.hpp"

using namespace sf;

//Control sprite coche
struct backgroundSprite{
  Texture tex;
  IntRect rectSrcSprite; 
  Sprite sprite;
  Clock clock;

  void init(IntRect rect, Texture t, int x, int y, int scale){
    rectSrcSprite = rect;
    tex = t;
    sprite.setTexture(tex);
    sprite.setTextureRect(rectSrcSprite);
    sprite.setPosition(x,y);
    sprite.setScale(scale,scale);
  }

  void setSprite(IntRect rect, int x, int y, int scale){
    rectSrcSprite = rect;
    sprite.setTexture(tex);
    sprite.setTextureRect(rectSrcSprite);
    sprite.setPosition(x,y);
    sprite.setScale(scale,scale);
  }
    
};