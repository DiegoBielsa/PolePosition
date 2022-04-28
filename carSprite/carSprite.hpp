#include "../globals/globals.hpp"
#include <iostream>

using namespace sf;

//Control sprite coche
struct carSprite{
  int car_status; //-1 atras 0 quieto 1 alante
  int car_dir; //-1 izq 0 recto 1 dcha
  int spriteN; //Numero de sprite (columna)[0-7]
  bool car_inv; //false normal, true invertido
  bool colision; //colision detectada
  Texture tex;
  IntRect rectSrcSprite; 
  Sprite sprite;
  Clock clock;

  void init(IntRect rect, Texture t){
    car_status = 0;
    car_dir = 0;
    spriteN = 0;
    car_inv = false;
    colision = false;
    rectSrcSprite = rect;
    tex = t;
    sprite.setTexture(tex);
    sprite.setTextureRect(rectSrcSprite);
    sprite.setPosition(width/2-car_width*1.5,600);
    sprite.setScale(3,3);
  }
  void reinit(){
    car_width = 56;
    car_height = 33;
    car_status = 0;
    car_dir = 0;
    spriteN = 0;
    car_inv = false;
    colision = false;
    rectSrcSprite = IntRect(0, 0, car_width, car_height);
    sprite.setTexture(tex);
    sprite.setTextureRect(rectSrcSprite);
    sprite.setPosition(width/2-car_width*1.5,600);
    sprite.setScale(3,3);
  }
  void updateCarSprite(){
    /*float vel_refresco;
    if(car_status == 0)
      vel_refresco = 1.0f;
    else
      vel_refresco = 0.3f;*/
    if(clock.getElapsedTime().asSeconds() > 0.03f){
      if(colision){
        if(rectSrcSprite.top < 3*car_height){
          car_width = 61;
          rectSrcSprite = IntRect(0,3*car_height, car_width, car_height);
          spriteN = 0;
        }
        else if(spriteN < 2){
          rectSrcSprite.left += 3+car_width;
          spriteN++;
        }
        else if(spriteN == 2){
          rectSrcSprite.left += 5+car_width;
          spriteN++;
        }
        else if(spriteN == 3){
          rectSrcSprite.left += car_width;
          car_width = 54;
          rectSrcSprite.width = car_width;
          spriteN++;
        }
        else if(spriteN == 4){
          rectSrcSprite.left += car_width;
          spriteN++;
        }else if(spriteN == 5){
          rectSrcSprite.left += car_width;
          car_width = 58;
          rectSrcSprite.width = car_width;
          spriteN++;
        }else if(spriteN == 6){
          rectSrcSprite.left += car_width;
          car_width = 68;
          rectSrcSprite.width = car_width;
          spriteN++;
        }
        /*else{
          car_width = 61;
          rectSrcSprite.width = car_width;
          rectSrcSprite.left = 0;
          spriteN = 0;
        }*/
      }
      else{
        if(car_status == 0){
          //Quieto
          if(car_dir == 1){
            //Movimiento dcha
            if(car_inv){
              //Recuperando direccion del coche
              if(rectSrcSprite.left == car_width){
                car_inv = false;
                rectSrcSprite.left -= rectSrcSprite.width;
                rectSrcSprite.width = -rectSrcSprite.width;
              }
              else
                rectSrcSprite.left -= car_width;
            }else{
              //Giro a dcha
              if(rectSrcSprite.left < 7*car_width)
                rectSrcSprite.left += car_width;
            }
          }
          if(car_dir == -1){
            //Movimiento a izq
            if(!car_inv){
              //Recuperando direccion del coche
              if(rectSrcSprite.left == 0){
                car_inv = true;
                rectSrcSprite.left += car_width;
                rectSrcSprite.width = -rectSrcSprite.width;
              }
              else
                rectSrcSprite.left -= car_width; 
            }else{
              //Giro a izq
              if(rectSrcSprite.left < 7*car_width)
              rectSrcSprite.left += car_width;
            }
          }
        }
        if(car_status == 1){
          //Acelerando
          if(car_dir == 0){
            //Movimiento recto
            if(rectSrcSprite.left >= car_width){
              if(car_inv){
                //Recuperando direccion del coche
                if(rectSrcSprite.left == car_width){
                car_inv = false;
                rectSrcSprite.left -= rectSrcSprite.width;
                rectSrcSprite.width = -rectSrcSprite.width;
                }
              }
              rectSrcSprite.left -= car_width;
            }
            else
              rectSrcSprite.left += car_width;
          }
          if(car_dir == 1){
            //Movimiento dcha
            if(car_inv){
              //Recuperando direccion del coche
             if(rectSrcSprite.left == car_width){
                car_inv = false;
                rectSrcSprite.left -= rectSrcSprite.width;
                rectSrcSprite.width = -rectSrcSprite.width;
              }
              else
                rectSrcSprite.left -= car_width;
            }else{
              
              if(rectSrcSprite.left < 7*car_width){
                rectSrcSprite.left += car_width;
              }
              else{
                rectSrcSprite.left = 6*car_width;
              }
            } 
          }
          if(car_dir == -1){
            //Movimiento a izq
            if(!car_inv){
              //Recuperando direccion del coche
              if(rectSrcSprite.left == 0){
                car_inv = true;
                rectSrcSprite.left += rectSrcSprite.width;
                rectSrcSprite.width = -rectSrcSprite.width;
              }
              else
                rectSrcSprite.left -= car_width;
            }else{
              if(rectSrcSprite.left < 8*car_width)
                rectSrcSprite.left += car_width;
              else
                rectSrcSprite.left = 7*car_width;
            }
            
          }
        }
      }
      clock.restart();
      sprite.setTextureRect(rectSrcSprite);
    }
  }
};


//Control sprite coche
struct carSpriteIA{
  int car_dir; //-1 izq 0 recto 1 dcha
  int spriteN; //Numero de sprite (columna)[0-7]
  bool car_inv; //false normal, true invertido
  bool colision; //colision detectada
  Texture tex;
  IntRect rectSrcSprite; 
  Sprite sprite;
  Clock clock;

  void init(IntRect rect, Texture t){
    car_dir = 0;
    spriteN = 0;
    car_inv = false;
    colision = false;
    rectSrcSprite = rect;
    tex = t;
    sprite.setTexture(tex);
    sprite.setTextureRect(rectSrcSprite);
    sprite.setPosition(width/2-car_width*1.5,600);
    sprite.setScale(3,3);
  }
  void reinit(){
    car_width = 56;
    car_height = 33;
    car_dir = 0;
    spriteN = 0;
    car_inv = false;
    colision = false;
    rectSrcSprite = IntRect(0, 0, car_width, car_height);
    sprite.setTexture(tex);
    sprite.setTextureRect(rectSrcSprite);
    sprite.setPosition(width/2-car_width*1.5,600);
    sprite.setScale(3,3);
  }
  void updateCarSprite(){
    if(clock.getElapsedTime().asSeconds() > 0.03f){
      if(colision){
        if(rectSrcSprite.top < 3*car_height){
          car_width = 61;
          rectSrcSprite = IntRect(0,3*car_height, car_width, car_height);
          spriteN = 0;
        }
        else if(spriteN < 2){
          rectSrcSprite.left += 3+car_width;
          spriteN++;
        }
        else if(spriteN == 2){
          rectSrcSprite.left += 5+car_width;
          spriteN++;
        }
        else if(spriteN == 3){
          rectSrcSprite.left += car_width;
          car_width = 54;
          rectSrcSprite.width = car_width;
          spriteN++;
        }
        else if(spriteN == 4){
          rectSrcSprite.left += car_width;
          spriteN++;
        }else if(spriteN == 5){
          rectSrcSprite.left += car_width;
          car_width = 58;
          rectSrcSprite.width = car_width;
          spriteN++;
        }else if(spriteN == 6){
          rectSrcSprite.left += car_width;
          car_width = 68;
          rectSrcSprite.width = car_width;
          spriteN++;
        }
      }
      else{
          //Acelerando
          if(car_dir == 0){
            //Movimiento recto
            if(rectSrcSprite.left >= car_width){
              if(car_inv){
                //Recuperando direccion del coche
                if(rectSrcSprite.left == car_width){
                car_inv = false;
                rectSrcSprite.left -= rectSrcSprite.width;
                rectSrcSprite.width = -rectSrcSprite.width;
                }
              }
              rectSrcSprite.left -= car_width;
            }
            else
              rectSrcSprite.left += car_width;
          }
          if(car_dir == 1){
            //Movimiento dcha
            if(car_inv){
              //Recuperando direccion del coche
             if(rectSrcSprite.left == car_width){
                car_inv = false;
                rectSrcSprite.left -= rectSrcSprite.width;
                rectSrcSprite.width = -rectSrcSprite.width;
              }
              else
                rectSrcSprite.left -= car_width;
            }else{
              
              if(rectSrcSprite.left < 7*car_width){
                rectSrcSprite.left += car_width;
              }
              else{
                rectSrcSprite.left = 6*car_width;
              }
            } 
          }
          if(car_dir == -1){
            //Movimiento a izq
            if(!car_inv){
              //Recuperando direccion del coche
              if(rectSrcSprite.left == 0){
                car_inv = true;
                rectSrcSprite.left += rectSrcSprite.width;
                rectSrcSprite.width = -rectSrcSprite.width;
              }
              else
                rectSrcSprite.left -= car_width;
            }else{
              if(rectSrcSprite.left < 8*car_width)
                rectSrcSprite.left += car_width;
              else
                rectSrcSprite.left = 7*car_width;
            }
            
          }
        
      }
      clock.restart();
      sprite.setTextureRect(rectSrcSprite);
    }
  }
};