#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cmath>
#include <iostream>
#include "RectangularBoundaryCollision.hpp"
#include <fstream>
#include <string>
#include <sstream>#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cmath>
#include <iostream>
#include "RectangularBoundaryCollision.hpp"
#include <fstream>
#include <string>
#include <sstream>

using namespace sf;
using namespace std;

#define charco 0
#define spriteColisión 1

int width = 1024;
int height = 768;
int roadW = 2000;
int segL = 200;    // segment length
float camD = 0.84; // camera depth
float draw_distance = 300; // empiezan a aparecer en pantalla en el 8
int car_width = 56;
int car_height = 50;
float off_road_allowed = 700;
float road_limit = 700;
float turn_power = 0.1;
float draft_power = 0.02;
int speed = 0;
bool marchaBaja = true;
bool pressed = false;
int maxSpeed = 600;
bool enHierba = false;
int NumCircuitos = 5;
bool gameOver = false;



// in = ( scenew, sceneh ); clip = ( windoww, windowh )
sf::Vector2f scaleToFit(const sf::Vector2f& in, const sf::Vector2f& clip)
{
    sf::Vector2f ret(in);
    if ((clip.y * in.x) / in.y >= clip.x)
    {
        ret.y = (clip.x * in.y) / in.x;
        ret.x = clip.x;
    }
    else if ((clip.x * in.y) / in.x >= clip.y)
    {
        ret.x = (clip.y * in.x) / in.y;
        ret.y = clip.y;
    }
    else
        ret = clip;
    return ret;
}


void drawRanking(RenderWindow& app) {
    sf::Text score;
    sf::Text scorenumber;
    sf::Text timenumber;
    sf::Text texto1;
    sf::Text texto2;
    sf::Text NOcol;
    sf::Text scorecol;
    sf::Text timecol;
    sf::Text namecol;
    sf::Text speed;
    sf::Text speednumber;


    sf::Font font;
    font.loadFromFile("letra.ttf");
    // select the font
    texto1.setFont(font); // font is a sf::Font
    texto2.setFont(font);
     scorecol.setFont(font);
     timecol.setFont(font);
     namecol.setFont(font);
     NOcol.setFont(font);
    score.setFont(font);
    scorenumber.setFont(font);
    timenumber.setFont(font);
    speed.setFont(font);
    speednumber.setFont(font);



    // set the string to display
    texto1.setString("THE PAST 6 GAMES RECORD");
    texto2.setString("PRIZE WINNERS");
    NOcol.setString("NO''");
    scorecol.setString("SCORE");
    timecol.setString("TIME");
    namecol.setString("NAME");

    score.setString("SCORE");
    scorenumber.setString("00000");

        timenumber.setString("0");
    
    speed.setString("SPEED");
    int s = 1;
    speednumber.setString("0 km");
    //int width = 1024;
  //int height = 768;


    score.setPosition(35, 0);
    scorenumber.setPosition(200, 0);

    timenumber.setPosition(500, 0);
    speednumber.setPosition(870, 0);
    speed.setPosition(700, 0);
    texto1.setPosition(120, 60);
    texto2.setPosition(215, 120);

    NOcol.setPosition(70, 180);
    scorecol.setPosition(215, 180);
    timecol.setPosition(400, 180);
    namecol.setPosition(630, 180);





    // set the character size
    NOcol.setCharacterSize(50); // in pixels, not points!
    texto1.setCharacterSize(50);
    texto2.setCharacterSize(50);
    scorecol.setCharacterSize(50);
    timecol.setCharacterSize(50);
    namecol.setCharacterSize(50);
    score.setCharacterSize(50);
    scorenumber.setCharacterSize(50);
    timenumber.setCharacterSize(50);
    speed.setCharacterSize(50);
    speednumber.setCharacterSize(50);

    // set the color
    NOcol.setFillColor(sf::Color::White);
    scorecol.setFillColor(sf::Color::White);
    timecol.setFillColor(sf::Color::White);
    timenumber.setFillColor(sf::Color::Yellow);
    namecol.setFillColor(sf::Color::White);
    score.setFillColor(sf::Color::White);
    scorenumber.setFillColor(sf::Color::White);
    speed.setFillColor(sf::Color::White);
    speednumber.setFillColor(sf::Color::White);
    // set the text style




        // inside the main loop, between window.clear() and window.display()
    app.draw(texto1);
    app.draw(texto2);
    app.draw(NOcol);
    app.draw(scorecol);
    app.draw(timecol);
    app.draw(timenumber);
    app.draw(namecol);

    app.draw(score);
    app.draw(scorenumber);
    app.draw(speed);
    app.draw(speednumber);


    for (int i = 1;i < 7;i++) {
        sf::Text j;
        sf::Text s;
        sf::Text t;
        sf::Text n;
        j.setFont(font);
        s.setFont(font);
        t.setFont(font);
        n.setFont(font);

        j.setString("1");
        s.setString("00000");
        t.setString("0");
        n.setString("Juan");

        j.setCharacterSize(50);
        s.setCharacterSize(50);
        t.setCharacterSize(50);
        n.setCharacterSize(50);

        int altura = 200 + (i * 60);
        j.setPosition(75, altura );
        s.setPosition(215, altura);
        t.setPosition(425, altura);
        n.setPosition(630, altura);

        // set the color
        j.setFillColor(sf::Color::White);
        s.setFillColor(sf::Color::White);
        t.setFillColor(sf::Color::White);
        n.setFillColor(sf::Color::White);


        app.draw(j);
        app.draw(s);
        app.draw(t);
        app.draw(n);
    }
}


/*------------------------------- FIN FUNCIONES DE CONTROL DEL BUCLE PRINCIPAL -------------------------------*/


int main()
{
    RenderWindow app(VideoMode(width, height), "Pole Position");
    while (app.isOpen()) {
        Event e;
        while (app.pollEvent(e)) {
            if (e.type == Event::Closed)
                app.close();
        }

        // catch the resize events
        if (e.type == sf::Event::Resized)
        {
            sf::View v(sf::FloatRect(0, 0, (float)e.size.width, (float)e.size.height));
            sf::FloatRect viewport(sf::Vector2f(0, 0), scaleToFit(sf::Vector2f((float)e.size.width, (float)e.size.height), sf::Vector2f((float)e.size.width, (float)e.size.height)));
            viewport.width = viewport.width / width;
            viewport.height = viewport.height / height;
            viewport.left = (1.0 - viewport.width) * 0.5;
            viewport.top = (1.0 - viewport.height) * 0.5;
            v.setViewport(viewport);
            app.setView(v);
            // update the view to the new size of the window
            //sf::FloatRect visibleArea(0, 0, e.size.width, e.size.width*(4/3));
                //app.setView(sf::View(app.getView().getCenter(), sf::Vector2f((float)e.size.width, (float)e.size.height)));
        }


        app.clear(Color(0, 0, 180));

        drawRanking(app);

        app.display();

    }
    return 0;
}