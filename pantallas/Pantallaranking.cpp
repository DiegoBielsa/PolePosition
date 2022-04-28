#include "Pantallaranking.hpp"



void drawRanking(RenderWindow& app,string puntuaciones[],int lim,int scoreentero) {
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
    string puntu=inttostring(scoreentero);
    scorenumber.setString(puntu);

    string loamarillo=inttostring(lim);
        timenumber.setString(loamarillo);
    
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


    for (int i = 0;i < 6;i++) {
        sf::Text j;
        sf::Text s;
        sf::Text t;
        sf::Text n;
        j.setFont(font);
        s.setFont(font);
        t.setFont(font);
        n.setFont(font);
        string numero = inttostring(i + 1);
        j.setString(numero);
        s.setString(puntuaciones[i]);
        t.setString("0");
        n.setString("Juan");

        j.setCharacterSize(50);
        s.setCharacterSize(50);
        t.setCharacterSize(50);
        n.setCharacterSize(50);

        int altura = 250 + (i * 60);
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


void drawInicio(RenderWindow& app,int& color){
    Texture titulo;
    Texture dos;
    Texture fondodos;
    Texture letrai;
        titulo.loadFromFile("images/titulo.png");
        dos.loadFromFile("images/numero2.png");
        fondodos.loadFromFile("images/fondonumero.png");
        letrai.loadFromFile("images/letrasinicio.png");

        Sprite tit(titulo);
        Sprite numdos(dos);
        Sprite fondonumdos(fondodos);
        Sprite letra(letrai);

        if (color == 0 ||color==1) {
            tit.setColor(sf::Color::Red);
            numdos.setColor(sf::Color::Red);
            color++;
        }
        
        else if (color == 2 || color== 3) {
            tit.setColor(sf::Color::Yellow);
            numdos.setColor(sf::Color::Blue);
            color++;
        }
        else if (color == 4 || color == 5) {
            tit.setColor(sf::Color::White);
            numdos.setColor(sf::Color::White);
            color++;
        }
        else { //azul
            color = 0;
        }
        

        Vector2f tamayo;

    tit.setPosition(20, 0);
    tamayo=numdos.getScale();
    numdos.setScale(0.3, 0.3);
    numdos.setPosition(355, 317);
    fondonumdos.setPosition(420, 325);
    letra.setPosition(220, 500);
    app.draw(tit);
    app.draw(fondonumdos);
    app.draw(numdos);
    app.draw(letra);

}


