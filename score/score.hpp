#pragma once
#include "../globals/globals.hpp"
#include "../loopControl/loopControl.hpp"
sf::Vector2f scaleToFit( const sf::Vector2f& in, const sf::Vector2f& clip );

void leerPuntuaciones(string puntuaciones[],int numero,int iaMode);

String inttostring(int entero);
int stringtoint(string s);

void leerLimite(int &limite, int numero);

void drawLetters(RenderWindow& app, string puntuaciones[], int velocidad, int puntu, Time& elapsed, int &limite,bool &gameOver);

void drawGameOver(RenderWindow& app);

sf::View getLetterboxView(sf::View view, int windowWidth, int windowHeight);
void calcularScore(int& score, int velocidad, int lim, int limite, bool gameOver);

void escribirPuntuaciones(string puntuaciones[], int puntuacion,int numero,int& posicionPuntuacion, int iaMode);
void leerNombres(string nombres[], int numero, int iaMode);
void escribirNombres(string nombres[], int numero, int iaMode);