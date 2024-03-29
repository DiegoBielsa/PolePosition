#pragma once

#include "../score/score.hpp"

void drawRanking(RenderWindow& app, string puntuaciones[], string nombres[], int& lim, int& scoreentero, int& posicionPuntuacion, int& color);
void drawInicio(RenderWindow& app, int& color);
void drawPrepare(RenderWindow& app, Sprite object[], bool& prepare);
void drawSemaphore(RenderWindow& app, Sprite object[], int& contadorSem);
void manageKeysCircuito(int& mapa, bool& terminar, bool& atras, Event& e);
void drawCircuito(RenderWindow& app, int& color, int mapa, bool atras);
void manageKeysIa(int& iaMode, bool& terminar, bool& atras, Event& e);
void drawIa(RenderWindow& app, int& color, int iaMode, bool atras);
void selectName(string name[], string key[], int& letra, int& iterador, bool& terminar, bool& haCambiado, Clock& clock);
void drawResultadosClas(RenderWindow& app, Time tiempo, int& posicionSalida, int& bon, int& color, int parpadeo);
void manageKeysMenu(bool& terminar, Event& e, int& posicionMenu);
void drawMenu(RenderWindow& app, int& color, int posicionMenu);

void drawMenuOpciones(RenderWindow& app, int& color, int posicionMenu, bool atras);
void manageKeysOptions(int& posicionMenuOpciones, bool& terminar, Event& e, bool& atras);

void  drawMenuteclas(RenderWindow& app, int& color, int posicionMenu, bool atras);

void elegirTeamNano(int& teamNano, bool& terminar, bool& atras, Event& e);
void drawNano(RenderWindow& app, int& color, int teamNano, bool atras);

void drawVol(RenderWindow& app, int& color, int posicionVolumen, bool atras);

void elegirVolumen(int& posicionVolumen, bool& terminar, Event& e, bool& atras);