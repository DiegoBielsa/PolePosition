#include "../globals/globals.hpp"
#include "../loopControl/loopControl.hpp"

sf::Vector2f scaleToFit( const sf::Vector2f& in, const sf::Vector2f& clip );

void leerPuntuaciones(String puntuaciones[]);

String inttostring(int entero);

void leerLimite(int &limite, int numero);

void drawLetters(RenderWindow& app, String puntuaciones[], int velocidad, int puntu, Time& elapsed, int &limite,bool &gameOver);

void drawGameOver(RenderWindow& app);

sf::View getLetterboxView(sf::View view, int windowWidth, int windowHeight);
void calcularScore(int& score, int velocidad,bool gameOver);