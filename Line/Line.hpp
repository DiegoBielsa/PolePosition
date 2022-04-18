#include "../globals/globals.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <cmath>
#include <iostream>

using namespace sf;

struct Line {
  float x, y, z; // 3d center of line
  float X, Y, W; // screen coord
  float curve, spriteX, clip, scale;
  FloatRect localBounds;
  bool isGoal;
  Sprite sprite;
  int sprite_type;

  Line() { spriteX = curve = x = y = z = 0; isGoal = false; }

  // decide las screen cord dependiendo de dónde está la cámara
  void project(int camX, int camY, int camZ) {
    scale = camD / (z - camZ);
    X = (1 + scale * (x - camX)) * width / 2;
    Y = (1 - scale * (y - camY)) * height / 2;
    W = scale * roadW * width / 2;
  }

  void drawSprite(RenderWindow &app) {
    Sprite s = sprite;
    int w = s.getTextureRect().width;
    int h = s.getTextureRect().height;

    float destX = X + scale * spriteX * width / 2;
    float destY = Y + 4;
    float destW = w * W / 266;
    float destH = h * W / 266;

    destX += destW * spriteX; // offsetX
    destY += destH * (-1);    // offsetY

    float clipH = destY + destH - clip;
    if (clipH < 0)
      clipH = 0;

    if (clipH >= destH)
      return;
    s.setTextureRect(IntRect(0, 0, w, h - h * clipH / destH));
    s.setScale(destW / w, destH / h);
    s.setPosition(destX, destY);

    if(!std::isnan(s.getGlobalBounds().height)){
      localBounds = s.getGlobalBounds();
    }
    
    //std::cout<<"drw"<<localBounds.height<<std::endl;
    app.draw(s);
  }
};