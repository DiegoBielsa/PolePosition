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
  FloatRect carLocalBounds;
  bool isGoal;
  Sprite sprite;
  int sprite_type; // 0 valla, 1 coche ia, 2 meta, 3 charco
  int last_sprite_type;
  Sprite cars[8];
  float carsX[8];
  float carsYPos[8];
  float carsXPos[8];
  bool carExplosion[8];

  Line() { 
    spriteX = curve = x = y = z = 0; 
    isGoal = false; 
    for(int i = 0; i < 8; i++){
      carExplosion[i] = 0;
    }
  }

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

    if(!std::isnan(s.getGlobalBounds().height) && !std::isnan(s.getGlobalBounds().width)
      && !std::isnan(s.getGlobalBounds().left) && !std::isnan(s.getGlobalBounds().top)  ){
      localBounds = s.getGlobalBounds();
    }
    
    //std::cout<<"drw"<<localBounds.height<<std::endl;
    app.draw(s);
  }

    void drawCars(RenderWindow &app, int i) {
      float spriteXToDraw = carsX[i];
      int w = cars[i].getTextureRect().width;
      int h = cars[i].getTextureRect().height;

      float destW = w * W / 266;
      float destH = h * W / 266;

      float destX = X + scale * spriteXToDraw * width / 2;
      float destY = Y + 4;
      destX += destW * spriteXToDraw + 3; //offsetX
                        //destY += destH *(-1) - 20;   
      destY += destH *(-1);    //offsetY

      float clipH = destY + destH - clip;
      if (clipH<0) clipH = 0;


      destX = X + (W * spriteXToDraw);
      if (clipH >= destH) return;

      carsYPos[i] = destY;
      carsXPos[i] = destX;
      //std::cout << carsYPos[i] << std::endl;

      //cars[i].setTextureRect(IntRect(0, 0, car_width, car_height));
      cars[i].setScale(destW*1.6 / w, destH*1.6 / h);
      if(carExplosion[i]){
        cars[i].setPosition(destX -160,destY -65);
      }else{
        cars[i].setPosition(destX, destY);
      }

      if(!std::isnan(cars[i].getGlobalBounds().height) && !std::isnan(cars[i].getGlobalBounds().width)
      && !std::isnan(cars[i].getGlobalBounds().left) && !std::isnan(cars[i].getGlobalBounds().top)  ){
        carLocalBounds = cars[i].getGlobalBounds();
      }

      app.draw(cars[i]);
	  }

    
};