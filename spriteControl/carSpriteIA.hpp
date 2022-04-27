#include "../globals/globals.hpp"
#include "carSprite.hpp"

using namespace sf;

//Control sprite coche
struct carSpriteIA{
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
    //WIP control con la IA

    //WIP Checkeo de distancia
    if (distancia){
        //cambio a sprites pequeños
    }
  }

  bool distancia(carSprite player){
      //definir margen
      double margen = 50.0;
      Vector2f aux = sprite.getPosition()-player.sprite.getPosition();
      return abs(aux.x)+abs(aux.y) > margen;
  }
};