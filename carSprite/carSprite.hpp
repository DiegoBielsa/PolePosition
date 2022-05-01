#include "../globals/globals.hpp"
#include <iostream>

using namespace sf;

//Control sprite coche
struct carSpriteIA{
  int car_dir; //-1 izq 0 recto 1 dcha
  int spriteN; //Numero de sprite (columna)[0-7]
  bool car_inv; //false normal, true invertido
  bool colision; //colision detectada
  Texture texCar[24];
  int actualTex;
  Texture texCarExp[15];
  IntRect rectSrcSprite; 
  Sprite sprite;
  Clock clock;
  int maxTex;

  void init(){
    maxTex = 23;
    actualTex = 0;
    car_dir = 0;
    spriteN = 0;
    car_inv = false;
    colision = false;
    sprite.setTexture(texCar[actualTex]);
    sprite.setPosition(width/2-car_width*1.5,600);
    sprite.setScale(3,3);
  }
  void reinit(){
    maxTex = 23;
    actualTex = 0;
    car_width = 56;
    car_height = 33;
    car_dir = 0;
    spriteN = 0;
    car_inv = false;
    colision = false;
    sprite.setTexture(texCar[actualTex]);
    sprite.setPosition(width/2-car_width*1.5,600);
    sprite.setScale(3,3);
  }
  void updateCarSprite(){
    if(clock.getElapsedTime().asSeconds() > 0.06f){
      if(car_dir == 0){ //Movimiento recto
        if(actualTex > 1){ //si estaba girando recuperamos 
          if(car_inv){ //girando a izquierdas
            if(actualTex - 1 == 1){ // si estamos terminando de girar dejamos de invertir
              car_inv = false;
            }
          }
          actualTex--;
        } // si no estaba girando hacemos que tenga la sensación de acelerar
        else{
          if(actualTex == 1) actualTex = 0;
          else actualTex = 1;
        }
          
      }
      if(car_dir == 1){ //Movimiento dcha
        if(car_inv && actualTex > 1){  //Si estabamos girando a izquierdas tenemos que recuperar
          
          if(actualTex - 1 == 1){
            car_inv = false;
          }
          else
            actualTex--;
        }else{ // si no tenemos que girar a derechas
          
          if(actualTex < maxTex){
            actualTex++;
          }else if(actualTex > maxTex+1){
                actualTex--;
              }
          else{
            actualTex = maxTex-1;
          }
        } 
      }
      if(car_dir == -1){ //Movimiento a izq
        if(!car_inv && actualTex > 1){ //Recuperando direccion del coche
          if(actualTex - 1 == 1){
            car_inv = true;
          }
          else
            actualTex--;
        }else{
          if(actualTex < maxTex){
            if(actualTex == 0) car_inv = true;
            actualTex++;
          }else if(actualTex > maxTex+1){
                actualTex--;
          }
          else
            actualTex = maxTex-1;
        }
        
      }

      clock.restart();
      sprite = sf::Sprite();
      sprite.setTexture(texCar[actualTex]);
      if(car_inv){
        sprite.setTextureRect(sf::IntRect(texCar[actualTex].getSize().x, 0, -texCar[actualTex].getSize().x, texCar[actualTex].getSize().y));    
      }
      sprite.setPosition(width/2-car_width*1.5,600);
      sprite.setScale(3,3); 
      
    }
  }
};


//Control sprite coche
struct carSprite{
  int car_status; //-1 atras 0 quieto 1 alante
  int car_dir; //-1 izq 0 recto 1 dcha
  int spriteN; //Numero de sprite (columna)[0-7]
  bool car_inv; //false normal, true invertido
  bool colision; //colision detectada
  int maxTexNoKey = 7;
  int maxTexUsualTurn = 19;
  int maxTexDraft = 23;
  Texture texCar[24]; // los 4 ultimos para el derrape
  int actualTex;
  Texture texCarExp[15];
  IntRect rectSrcSprite; 
  Sprite sprite;
  Clock clock;
  int maxTex;
  float updateTime = 0.03;

  void init(){
    maxTex = maxTexNoKey;
    actualTex = 0;
    car_dir = 0;
    spriteN = 0;
    car_inv = false;
    colision = false;
    sprite.setTexture(texCar[actualTex]);
    sprite.setPosition(width/2-car_width*1.5,600);
    sprite.setScale(3,3);
  }
  void reinit(){
    maxTex = maxTexNoKey;
    actualTex = 0;
    car_dir = 0;
    spriteN = 0;
    car_inv = false;
    colision = false;
    sprite.setTexture(texCar[actualTex]);
    sprite.setPosition(width/2-car_width*1.5,600);
    sprite.setScale(3,3);
  }
  void updateCarSprite(){
    /*float vel_refresco;
    if(car_status == 0)
      vel_refresco = 1.0f;
    else
      vel_refresco = 0.3f;*/
    if(clock.getElapsedTime().asSeconds() > updateTime){
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
          if(car_dir == 1){ //Movimiento dcha
            if(car_inv && actualTex > 1){  //Si estabamos girando a izquierdas tenemos que recuperar
              
              if(actualTex - 1 == 1){
                car_inv = false;
              }
              else
                actualTex--;
            }else{ // si no tenemos que girar a derechas
              
              if(actualTex < maxTex){
                actualTex++;
              }
            } 
          }
          if(car_dir == -1){ //Movimiento a izq
            if(!car_inv && actualTex > 1){ //Recuperando direccion del coche
              if(actualTex - 1 == 1){
                car_inv = true;
              }
              else
                actualTex--;
            }else{
              if(actualTex < maxTex){
                if(actualTex == 0) car_inv = true;
                actualTex++;
              }
            }
            
          }
        }
        if(car_status == 1){
          //Acelerando
          if(car_dir == 0){ //Movimiento recto
            if(actualTex > 1){ //si estaba girando recuperamos 
              if(car_inv){ //girando a izquierdas
                if(actualTex - 1 == 1){ // si estamos terminando de girar dejamos de invertir
                  car_inv = false;
                }
              }
              actualTex--;
            } // si no estaba girando hacemos que tenga la sensación de acelerar
            else{
              if(actualTex == 1) actualTex = 0;
              else actualTex = 1;
            }
              
          }
          if(car_dir == 1){ //Movimiento dcha
            if(car_inv && actualTex > 1){  //Si estabamos girando a izquierdas tenemos que recuperar
              
              if(actualTex - 1 == 1){
                car_inv = false;
              }
              else
                actualTex--;
            }else{ // si no tenemos que girar a derechas
              
              if(actualTex < maxTex){
                actualTex++;
              }else if(actualTex > maxTex+1){
                actualTex--;
              }
              else{
                actualTex = maxTex-1;
              }
            } 
          }
          if(car_dir == -1){ //Movimiento a izq
            if(!car_inv && actualTex > 1){ //Recuperando direccion del coche
              if(actualTex - 1 == 1){
                car_inv = true;
              }
              else
                actualTex--;
            }else{
              if(actualTex < maxTex){
                if(actualTex == 0) car_inv = true;
                actualTex++;
              }else if(actualTex > maxTex+1){
                actualTex--;
              }
              else{
                actualTex = maxTex-1;
              }
            }
            
          }
        }
      }
      clock.restart();
      sprite = sf::Sprite();
      sprite.setTexture(texCar[actualTex]);
      if(car_inv){
        sprite.setTextureRect(sf::IntRect(texCar[actualTex].getSize().x, 0, -texCar[actualTex].getSize().x, texCar[actualTex].getSize().y));    
      }
      sprite.setPosition(width/2-car_width*1.5,600);
      sprite.setScale(3,3); 
    }
  }
};