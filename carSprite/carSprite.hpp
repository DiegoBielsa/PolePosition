#include "../globals/globals.hpp"
#include <iostream>

using namespace sf;

//Control sprite coche
struct carSpriteIA{
  int car_dir; //-1 izq 0 recto 1 dcha
  int spriteN; //Numero de sprite (columna)[0-7]
  bool car_inv; //false normal, true invertido
  bool colision; //colision detectada
  int colisionSprite;
  Texture texCar[24];
  int actualTex;
  Texture texCarExp[11];
  IntRect rectSrcSprite; 
  Sprite sprite;
  Clock clock;
  int maxTex;
  float updateTime = 0.03;


  void init(){
    maxTex = 23;
    actualTex = 5;
    car_dir = 0;
    spriteN = 0;
    colisionSprite = 0;
    car_inv = false;
    colision = false;
    sprite.setTexture(texCar[actualTex]);
    sprite.setPosition(width/2-car_width*1.5,600);
    sprite.setScale(3,3);
  }
  void reinit(){
    maxTex = 23;
    actualTex = 5;
    car_width = 56;
    car_height = 33;
    car_dir = 0;
    spriteN = 0;
    colisionSprite = 0;
    car_inv = false;
    colision = false;
    sprite.setTexture(texCar[actualTex]);
    sprite.setPosition(width/2-car_width*1.5,600);
    sprite.setScale(3,3);
  }
  void updateCarSprite(){
    //if(clock.getElapsedTime().asSeconds() > updateTime){
      if(colision){
        if(colisionSprite == 0) updateTime = 0.17;
        else updateTime-= 0.005;
        if(colisionSprite < 10){
          colisionSprite++;
        }else{
          colisionSprite = 0;
          colision = false;
        }
      }
      else{
        updateTime = 0.03;
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
      }
      //clock.restart();
      sprite = sf::Sprite();
      if(!colision){
        sprite.setTexture(texCar[actualTex]);
        if(car_inv){
          sprite.setTextureRect(sf::IntRect(texCar[actualTex].getSize().x, 0, -texCar[actualTex].getSize().x, texCar[actualTex].getSize().y));    
        }
        sprite.setPosition(width/2-car_width*1.5,600);
      }else{
        sprite.setTexture(texCarExp[colisionSprite]);
        if(colisionSprite >= 3){
            sprite.setPosition((width/2-car_width) -225,400);
          }else{
            sprite.setPosition(width/2-car_width*1.5,600);
          }
      }
      
      
      sprite.setScale(3,3); 
      
    //}
  }
};


//Control sprite coche
struct carSprite{
  int car_status; //-1 atras 0 quieto 1 alante
  int car_dir; //-1 izq 0 recto 1 dcha
  int colisionSprite; //Numero de sprite (columna)[0-7]
  bool car_inv; //false normal, true invertido
  bool colision; //colision detectada
  int maxTexNoKey = 7;
  int maxTexUsualTurn = 19;
  int maxTexDraft = 23;
  Texture texCar[24]; // los 4 ultimos para el derrape
  int actualTex;
  Texture texCarExp[11];
  IntRect rectSrcSprite; 
  Sprite sprite;
  Clock clock;
  int maxTex;
  float updateTime = 0.03;

  void init(){
    maxTex = maxTexNoKey;
    actualTex = 0;
    car_dir = 0;
    colisionSprite = 0;
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
    colisionSprite = 0;
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
        if(colisionSprite == 0) updateTime = 0.17;
        else updateTime-= 0.005;
        if(colisionSprite < 10){
          colisionSprite++;
        }
      }
      else{
        updateTime = 0.03;
        colisionSprite = 0;
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
      if(!colision){
        sprite.setTexture(texCar[actualTex]);
        if(car_inv){
          sprite.setTextureRect(sf::IntRect(texCar[actualTex].getSize().x, 0, -texCar[actualTex].getSize().x, texCar[actualTex].getSize().y));    
        }
        sprite.setPosition(width/2-car_width*1.5,600);
      }else{
        sprite.setTexture(texCarExp[colisionSprite]);
        if(colisionSprite >= 3){
            sprite.setPosition((width/2-car_width) -225,400);
          }else{
            sprite.setPosition(width/2-car_width*1.5,600);
          }
      }
      
      
      sprite.setScale(3,3); 
    }
  }
};