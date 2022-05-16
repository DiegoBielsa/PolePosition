#pragma once

#include "../score/score.hpp"

void drawRanking(RenderWindow& app, string puntuaciones[], string nombres[], int& lim, int& scoreentero, int& posicionPuntuacion, int& color);
void drawInicio(RenderWindow& app,int& color);
void drawPrepare(RenderWindow& app,Sprite object[], bool& prepare);
void drawSemaphore(RenderWindow& app,Sprite object[],  int& contadorSem);
void manageKeysCircuito(int& mapa,bool& terminar, bool& atras,Clock& clock);
void drawCircuito(RenderWindow& app, int& color, int mapa,bool atras);
void manageKeysIa(int& iaMode, bool& terminar, Clock& clock, bool& atras);
void drawIa(RenderWindow& app, int& color, int iaMode, bool atras);
void selectName(string name[], string key[], int& letra, int& iterador, bool& terminar, bool& haCambiado, Clock& clock);
void drawResultadosClas(RenderWindow& app, Time tiempo, int& posicionSalida, int& bon, int& color,int parpadeo);
