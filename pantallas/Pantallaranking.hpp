#pragma once

#include "../score/score.hpp"

void drawRanking(RenderWindow& app, string puntuaciones[], int lim, int scoreentero);
void drawInicio(RenderWindow& app,int& color);
void manageKeysCircuito(int& mapa,bool& terminar);
void drawCircuito(RenderWindow& app, int& color, int mapa);
void manageKeysIa(int& iaMode, bool& terminar, Clock& clock);
void drawIa(RenderWindow& app, int& color, int iaMode);
