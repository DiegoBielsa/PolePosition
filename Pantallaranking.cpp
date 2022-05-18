#include "Pantallaranking.hpp"

void selectName(string name[], string key[], int& letra, int& iterador, bool& terminar, bool& haCambiado, Clock & clock) {

    if (clock.getElapsedTime().asSeconds() > 0.1f) { //sin esto se pasa de "estados"
        clock.restart();
        if (Keyboard::isKeyPressed(Keyboard::Up)) {
            if (letra != 0) {
                letra = letra - 1;
                haCambiado = 1;
            }


        }
        if (Keyboard::isKeyPressed(Keyboard::Down)) {
            if (letra != 25) {
                letra = letra + 1;
                haCambiado = 1;
            }

        }
        if (Keyboard::isKeyPressed(Keyboard::Enter)) {

            if (iterador < 2) {
                iterador = iterador + 1;
            }
            else {
                terminar = true;
            }
        }
        name[iterador] = key[letra];
    }

}


void drawRanking(RenderWindow& app, string puntuaciones[], string nombres[], int& lim, int& scoreentero, int& posicionPuntuacion, int& color) {
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
    string puntu = inttostring(scoreentero);
    scorenumber.setString(puntu);

    string loamarillo = inttostring(lim);
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


    for (int i = 0; i < 6; i++) {
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
        n.setString(nombres[i]);

        j.setCharacterSize(50);
        s.setCharacterSize(50);
        t.setCharacterSize(50);
        n.setCharacterSize(50);

        int altura = 250 + (i * 60);
        j.setPosition(75, altura);
        s.setPosition(215, altura);
        t.setPosition(425, altura);
        n.setPosition(630, altura);

        // set the color
        if (i != posicionPuntuacion) {
            j.setFillColor(sf::Color::White);
            s.setFillColor(sf::Color::White);
            t.setFillColor(sf::Color::White);
            n.setFillColor(sf::Color::White);
        }
        else if (i == posicionPuntuacion && (color == 0 || color == 1)) {
            j.setFillColor(sf::Color::Yellow);
            s.setFillColor(sf::Color::Yellow);
            t.setFillColor(sf::Color::Yellow);
            n.setFillColor(sf::Color::Yellow);
            color++;
        }
        else if (i == posicionPuntuacion && (color == 2)) {
            j.setFillColor(sf::Color::Red);
            s.setFillColor(sf::Color::Red);
            t.setFillColor(sf::Color::Red);
            n.setFillColor(sf::Color::Red);
            color++;
        }
        else if (i == posicionPuntuacion && (color == 3 || color == 4)) {
            j.setFillColor(sf::Color::White);
            s.setFillColor(sf::Color::White);
            t.setFillColor(sf::Color::White);
            n.setFillColor(sf::Color::White);
            if (color == 4) {
                color = 0;
            }
            else { color++; }
        }


        app.draw(j);
        app.draw(s);
        app.draw(t);
        app.draw(n);
    }
}


void drawInicio(RenderWindow& app, int& color) {
    Texture titulo;
    Texture nan;
    Texture letrai;
    titulo.loadFromFile("images/titulo.png");
    nan.loadFromFile("images/falonsoedition.png");
    letrai.loadFromFile("images/letrasinicio.png");

    Sprite tit(titulo);
    Sprite nano(nan);
    Sprite letra(letrai);

    if (color == 0 || color == 1) {
        tit.setColor(sf::Color::Red);
        nano.setColor(sf::Color::Red);
        color++;
    }

    else if (color == 2 || color == 3) {
        tit.setColor(sf::Color::Yellow);
        nano.setColor(sf::Color::Blue);
        color++;
    }
    else if (color == 4 || color == 5) {
        tit.setColor(sf::Color::White);
        nano.setColor(sf::Color::White);
        color++;
    }
    else { //azul
        color = 0;
    }



    tit.setPosition(20, 0);
    nano.setScale(1.25, 1.25);
    nano.setPosition(355, 350);
    letra.setPosition(220, 500);
    app.draw(tit);
    app.draw(nano);
    app.draw(letra);

}

void drawPrepare(RenderWindow& app, Sprite object[], bool& prepare) {
    object[16].move(sf::Vector2f(-16, 0));

    if (object[16].getPosition().x > -1000) {
        app.draw(object[16]);
    }
    else {
        prepare = false;
    }
    //app.draw(globo);

}



void drawSemaphore(RenderWindow& app, Sprite object[], int& contadorSem) {
    contadorSem++;
    if (contadorSem < 50) {
        app.draw(object[18]);
    }
    else if (contadorSem >= 50 && contadorSem < 65) {
        app.draw(object[18]);
    }
    else if (contadorSem >= 65 && contadorSem < 130) {
        app.draw(object[19]);
    }
    else if (contadorSem >= 130 && contadorSem < 200) {
        app.draw(object[20]);
    }
    else {
        app.draw(object[21]);
    }
}


void manageKeysCircuito(int& mapa, bool& terminar, bool& atras, Event& e) {

    if (atras == true) {
        if (e.type == sf::Event::KeyPressed) {
            if (e.key.code == sf::Keyboard::Down) {
                mapa = 1;
                atras = false;
            }
            if (e.key.code == sf::Keyboard::Enter) {
                terminar = true;
            }
        }
    }
    else {
        if (mapa == 0) {//test
            if (e.type == sf::Event::KeyPressed) {
                if (e.key.code == sf::Keyboard::Right) {
                    mapa = 0;

                }
                if (e.key.code == sf::Keyboard::Left) {
                    mapa = 1;

                }
                if (e.key.code == sf::Keyboard::Up) {
                    mapa = 0;
                    atras = true;

                }
                if (e.key.code == sf::Keyboard::Down) {
                    mapa = 2;

                }
                if (e.key.code == sf::Keyboard::Enter) {
                    terminar = true;
                }
            }
        }
        else if (mapa == 1) {//fuji
            if (e.type == sf::Event::KeyPressed) {
                if (e.key.code == sf::Keyboard::Right) {
                    mapa = 0; //test
                }
                if (e.key.code == sf::Keyboard::Left) {
                    mapa = 1;

                }
                if (e.key.code == sf::Keyboard::Up) {
                    mapa = 1;
                    atras = true;


                }
                if (e.key.code == sf::Keyboard::Down) {
                    mapa = 3;
                }
                if (e.key.code == sf::Keyboard::Enter) {
                    terminar = true;
                }
            }
        }
        else if (mapa == 3) {//suzuka
            if (e.type == sf::Event::KeyPressed) {
                if (e.key.code == sf::Keyboard::Right) {
                    mapa = 2;

                }
                if (e.key.code == sf::Keyboard::Left) {
                    mapa = 3;

                }
                if (e.key.code == sf::Keyboard::Up) {
                    mapa = 1;

                }
                if (e.key.code == sf::Keyboard::Down) {
                    mapa = 3;

                }
                if (e.key.code == sf::Keyboard::Enter) {
                    terminar = true;

                }
            }
        }
        else if (mapa == 2) {//seaside
            if (e.type == sf::Event::KeyPressed) {
                if (e.key.code == sf::Keyboard::Right) {
                    mapa = 2;

                }
                if (e.key.code == sf::Keyboard::Left) {
                    mapa = 3;

                }
                if (e.key.code == sf::Keyboard::Up) {
                    mapa = 0;

                }
                if (e.key.code == sf::Keyboard::Down) {
                    mapa = 2;

                }
                if (e.key.code == sf::Keyboard::Enter) {
                    terminar = true;

                }
            }
        }
    }


}

void manageKeysIa(int& iaMode, bool& terminar, bool& atras, Event& e) {

    if (atras == true) {
        if (e.type == sf::Event::KeyPressed) {
            if (e.key.code == sf::Keyboard::Down) {
                iaMode = 0;
                atras = false;
            }
            if (e.key.code == sf::Keyboard::Enter) {
                terminar = true;
            }

        }
    }
    else {
        if (iaMode == 0) {//facil
            if (e.type == sf::Event::KeyPressed) {
                if (e.key.code == sf::Keyboard::Up) {
                    iaMode = 2;
                    atras = true;
                }
                if (e.key.code == sf::Keyboard::Down) {
                    iaMode = 1;

                }
                if (e.key.code == sf::Keyboard::Enter) {
                    terminar = true;
                }
            }
        }
        else if (iaMode == 1) {//medio
            if (e.type == sf::Event::KeyPressed) {
                if (e.key.code == sf::Keyboard::Up) {
                    iaMode = 0;

                }
                if (e.key.code == sf::Keyboard::Down) {
                    iaMode = 2;

                }
                if (e.key.code == sf::Keyboard::Enter) {
                    terminar = true;
                }
            }
        }
        else if (iaMode == 2) {//dificil
            if (e.type == sf::Event::KeyPressed) {
                if (e.key.code == sf::Keyboard::Up) {
                    iaMode = 1;

                }
                if (e.key.code == sf::Keyboard::Down) {
                    iaMode = 0;

                }
                if (e.key.code == sf::Keyboard::Enter) {
                    terminar = true;
                }
            }
        }
    }



}

void drawCircuito(RenderWindow& app, int& color, int mapa, bool atras) {
    sf::Text texto1;
    sf::Text texto2;
    sf::Text texto3;
    sf::Text texto4;
    sf::Text titulo;
    Vector2f tamayo(40, 30);
    RectangleShape botonatras(tamayo);
    botonatras.setPosition(10, 10);
    botonatras.setFillColor(Color::White);
    botonatras.setOutlineThickness(1.5);

    Texture atr;

    atr.loadFromFile("images/flechaatras.png");

    const sf::Texture* pTexture = &atr;
    botonatras.setTexture(pTexture);


    sf::Font font;
    font.loadFromFile("letra.ttf");

    // select the font
    texto1.setFont(font); // font is a sf::Font
    texto2.setFont(font);
    texto3.setFont(font);
    texto4.setFont(font);
    titulo.setFont(font);

    texto1.setString("-FUJI-");
    texto2.setString("-TEST-");
    texto3.setString("-SUZUKA-");
    texto4.setString("-SEASIDE-");
    titulo.setString("SELECT CIRCUIT");


    texto1.setFillColor(Color(219, 224, 142));
    texto2.setFillColor(Color(219, 224, 142));
    texto3.setFillColor(Color(219, 224, 142));
    texto4.setFillColor(Color(219, 224, 142));


    texto1.setCharacterSize(55);
    texto2.setCharacterSize(55);
    texto3.setCharacterSize(55);
    texto4.setCharacterSize(55);
    titulo.setCharacterSize(60);

    texto1.setPosition(227, 145);
    texto2.setPosition(630, 145);
    texto3.setPosition(200, 360);
    texto4.setPosition(595, 360);
    titulo.setPosition(300, 30);


    Texture fuj;
    Texture suzuka;
    Texture tes;
    Texture seaside;

    fuj.loadFromFile("images/fuji2.png");
    suzuka.loadFromFile("images/suzuka.png");
    tes.loadFromFile("images/test.png");
    seaside.loadFromFile("images/seaside.png");

    Sprite fuji(fuj);
    Sprite suzu(suzuka);
    Sprite test(tes);
    Sprite sea(seaside);
    if (atras == true) {
        if (color == 0 || color == 1) {
            botonatras.setOutlineColor(sf::Color::Blue);
            color++;
        }

        else if (color == 2 || color == 3) {
            botonatras.setOutlineColor(sf::Color::Yellow);
            color++;
        }
        else if (color == 4 || color == 5 || color == 6) {
            botonatras.setOutlineColor(sf::Color::Red);
            color++;
        }
        else { //blanco
            botonatras.setOutlineColor(sf::Color::White);
            color = 0;
        }

    }
    else {
        if (mapa == 0) {//test
            if (color == 0 || color == 1) {
                test.setColor(sf::Color::Blue);
                color++;
            }

            else if (color == 2 || color == 3) {
                test.setColor(sf::Color::Yellow);
                color++;
            }
            else if (color == 4 || color == 5 || color == 6) {
                test.setColor(sf::Color::White);
                color++;
            }
            else { //rojo
                color = 0;
            }
        }
        else if (mapa == 1) {//fuji
            if (color == 0 || color == 1) {
                fuji.setColor(sf::Color::Blue);
                color++;
            }

            else if (color == 2 || color == 3) {
                fuji.setColor(sf::Color::Yellow);
                color++;
            }
            else if (color == 4 || color == 5 || color == 6) {
                fuji.setColor(sf::Color::White);
                color++;
            }
            else { //rojo
                color = 0;
            }
        }
        else if (mapa == 3) {//suzuka
            if (color == 0 || color == 1) {
                suzu.setColor(sf::Color::Blue);

                color++;
            }

            else if (color == 2 || color == 3) {
                suzu.setColor(sf::Color::Yellow);
                color++;
            }
            else if (color == 4 || color == 5 || color == 6) {
                suzu.setColor(sf::Color::White);
                color++;
            }
            else { //rojo
                color = 0;
            }
        }
        else if (mapa == 2) {//seaside
            if (color == 0 || color == 1) {
                sea.setColor(sf::Color::Blue);
                color++;
            }

            else if (color == 2 || color == 3) {
                sea.setColor(sf::Color::Yellow);
                color++;
            }
            else if (color == 4 || color == 5 || color == 6) {
                sea.setColor(sf::Color::White);
                color++;
            }
            else { //rojo
                color = 0;
            }
        }
    }


    fuji.setPosition(120, 180);
    test.setPosition(490, 190);
    suzu.setPosition(120, 370);
    sea.setScale(0.4, 0.4);
    sea.setPosition(555, 430);


    app.draw(fuji);
    app.draw(test);
    app.draw(suzu);
    app.draw(sea);
    app.draw(texto1);
    app.draw(texto2);
    app.draw(texto3);
    app.draw(texto4);
    app.draw(titulo);
    app.draw(botonatras);
}


void drawIa(RenderWindow& app, int& color, int iaMode, bool atras) {

    sf::Text texto1;
    sf::Text texto2;
    sf::Text texto3;
    sf::Text titulo;
    Vector2f tamayo(40, 30);
    RectangleShape botonatras(tamayo);
    botonatras.setPosition(10, 10);
    botonatras.setFillColor(Color::White);
    botonatras.setOutlineThickness(1.5);

    Texture atr;

    atr.loadFromFile("images/flechaatras.png");

    const sf::Texture* pTexture = &atr;
    botonatras.setTexture(pTexture);

    sf::Font font;
    font.loadFromFile("letra.ttf");
    sf::Font font2;
    font2.loadFromFile("retro.ttf");
    // select the font
    texto1.setFont(font2); // font is a sf::Font
    texto2.setFont(font2);
    texto3.setFont(font2);
    titulo.setFont(font);

    texto1.setString("-EASY-");
    texto2.setString("-MEDIUM-");
    texto3.setString("-HARD-");
    titulo.setString("SELECT IA");



    texto1.setCharacterSize(55);
    texto2.setCharacterSize(55);
    texto3.setCharacterSize(55);
    titulo.setCharacterSize(80);

    texto1.setPosition(400, 200);
    texto2.setPosition(380, 350);
    texto3.setPosition(400, 500);
    titulo.setPosition(290, 30);


    if (atras == true) {
        if (color == 0 || color == 1) {
            botonatras.setOutlineColor(sf::Color::Blue);
            color++;
        }

        else if (color == 2 || color == 3) {
            botonatras.setOutlineColor(sf::Color::Yellow);
            color++;
        }
        else if (color == 4 || color == 5 || color == 6) {
            botonatras.setOutlineColor(sf::Color::Red);
            color++;
        }
        else { //blanco
            botonatras.setOutlineColor(sf::Color::White);
            color = 0;
        }

    }
    else {
        if (iaMode == 0) {//test
            if (color == 0 || color == 1) {
                texto1.setFillColor(sf::Color::Blue);
                color++;
            }

            else if (color == 2 || color == 3) {
                texto1.setFillColor(sf::Color::Yellow);
                color++;
            }
            else if (color == 4 || color == 5 || color == 6) {
                texto1.setFillColor(sf::Color::Red);
                color++;
            }
            else { //blanco
                color = 0;
            }
        }
        else  if (iaMode == 1) {//medium
            if (color == 0 || color == 1) {
                texto2.setFillColor(sf::Color::Blue);
                color++;
            }

            else if (color == 2 || color == 3) {
                texto2.setFillColor(sf::Color::Yellow);
                color++;
            }
            else if (color == 4 || color == 5 || color == 6) {
                texto2.setFillColor(sf::Color::Red);
                color++;
            }
            else { //blanco
                color = 0;
            }
        }
        else  if (iaMode == 2) {//hard
            if (color == 0 || color == 1) {
                texto3.setFillColor(sf::Color::Blue);
                color++;
            }

            else if (color == 2 || color == 3) {
                texto3.setFillColor(sf::Color::Yellow);
                color++;
            }
            else if (color == 4 || color == 5 || color == 6) {
                texto3.setFillColor(sf::Color::Red);
                color++;
            }
            else { //blanco
                color = 0;
            }
        }
    }




    app.draw(texto1);
    app.draw(texto2);
    app.draw(texto3);
    app.draw(titulo);
    app.draw(botonatras);


}

void colorear(sf::Text& texto, int& color) {
    if (color == 0 || color == 1) {
        texto.setFillColor(sf::Color::Blue);
        color++;
    }

    else if (color == 2 || color == 3) {
        texto.setFillColor(sf::Color::Yellow);
        color++;
    }
    else if (color == 4 || color == 5 || color == 6) {
        texto.setFillColor(sf::Color::Red);
        color++;
    }
    else { //blanco
        color = 0;
    }

}
void drawResultadosClas(RenderWindow& app, Time tiempo, int& posicionSalida, int& bon, int& color, int parpadeo) {
    sf::Text lapnumber;
    sf::Text position;
    sf::Text uno;
    sf::Text dos;
    sf::Text tres;
    sf::Text cuatro;
    sf::Text cinco;
    sf::Text seis;
    sf::Text siete;
    sf::Text ocho;
    sf::Text bonus;


    sf::Font font;
    font.loadFromFile("letra.ttf");
    // select the font

    lapnumber.setFont(font);
    position.setFont(font);
    uno.setFont(font);
    dos.setFont(font);
    tres.setFont(font);
    cuatro.setFont(font);
    cinco.setFont(font);
    seis.setFont(font);
    siete.setFont(font);
    ocho.setFont(font);
    bonus.setFont(font);


    int seconds2 = tiempo.asSeconds();
    int mili = tiempo.asMilliseconds();
    while (mili > 1000) {
        mili = mili - 1000;
    }

    String minu = inttostring(mili);
    String sec = inttostring(seconds2);
    lapnumber.setString("LAP TIME " + sec + ". " + minu);

    position.setString("POSITION");
    uno.setString("1");
    dos.setString("2");
    tres.setString("3");
    cuatro.setString("4");
    cinco.setString("5");
    seis.setString("6");
    siete.setString("7");
    ocho.setString("8");

    String puntu = inttostring(bon);
    bonus.setString("BONUS " + puntu);


    if (parpadeo == 0) {
        colorear(lapnumber, color);
    }
    else if (parpadeo == 1) {
        colorear(position, color);
        if (posicionSalida == 0) {
            colorear(uno, color);
        }
        else if (posicionSalida == 1) {
            colorear(dos, color);
        }
        else if (posicionSalida == 2) {
            colorear(tres, color);
        }
        else if (posicionSalida == 3) {
            colorear(cuatro, color);
        }
        else if (posicionSalida == 4) {
            colorear(cinco, color);
        }
        else if (posicionSalida == 5) {
            colorear(seis, color);
        }
        else if (posicionSalida == 6) {
            colorear(siete, color);
        }
        else if (posicionSalida == 7) {
            colorear(ocho, color);
        }

    }
    else if (parpadeo == 2) {
        colorear(bonus, color);
    }






    lapnumber.setCharacterSize(50);
    position.setCharacterSize(50);
    uno.setCharacterSize(50);
    dos.setCharacterSize(50);
    tres.setCharacterSize(50);
    cuatro.setCharacterSize(50);
    cinco.setCharacterSize(50);
    seis.setCharacterSize(50);
    siete.setCharacterSize(50);
    ocho.setCharacterSize(50);
    bonus.setCharacterSize(50);


    lapnumber.setPosition(350, 450);
    position.setPosition(230, 500);
    uno.setPosition(440, 500);
    dos.setPosition(485, 500);
    tres.setPosition(530, 500);
    cuatro.setPosition(575, 500);
    cinco.setPosition(620, 500);
    seis.setPosition(665, 500);
    siete.setPosition(710, 500);
    ocho.setPosition(755, 500);
    bonus.setPosition(400, 550);



    app.draw(lapnumber);
    app.draw(position);
    app.draw(uno);
    app.draw(dos);
    app.draw(tres);
    app.draw(cuatro);
    app.draw(cinco);
    app.draw(seis);
    app.draw(siete);
    app.draw(ocho);
    app.draw(bonus);
}
void manageKeysMenu(bool& terminar, Event& e, int& posicionMenu) {

    if (posicionMenu == 0) {//clasificacion
        if (e.type == sf::Event::KeyPressed) {
            if (e.key.code == sf::Keyboard::Up) {
                posicionMenu = 2;


            }
            if (e.key.code == sf::Keyboard::Down) {
                posicionMenu = 1;

            }
            if (e.key.code == sf::Keyboard::Enter) {
                terminar = true;
            }
        }
    }
    else if (posicionMenu == 1) {//options
        if (e.type == sf::Event::KeyPressed) {
            if (e.key.code == sf::Keyboard::Up) {
                posicionMenu = 0;

            }
            if (e.key.code == sf::Keyboard::Down) {
                posicionMenu = 2;

            }
            if (e.key.code == sf::Keyboard::Enter) {
                terminar = true;
            }
        }
    }
    else if (posicionMenu == 2) {//exit
        if (e.type == sf::Event::KeyPressed) {
            if (e.key.code == sf::Keyboard::Up) {
                posicionMenu = 1;

            }
            if (e.key.code == sf::Keyboard::Down) {
                posicionMenu = 0;

            }
            if (e.key.code == sf::Keyboard::Enter) {
                terminar = true;
            }
        }
    }

}


void drawMenu(RenderWindow& app, int& color, int posicionMenu) {

    sf::Text texto1;
    sf::Text texto2;
    sf::Text texto3;
    sf::Texture fa;
    fa.loadFromFile("images/falonsoedition.png");

    Sprite nano(fa);

    Vector2f tamayo(200, 100);
    Vector2f tamayo2(350, 500);
    RectangleShape botonplay(tamayo);
    RectangleShape botonopts(tamayo);
    RectangleShape botonexit(tamayo);
    RectangleShape fondo(tamayo2);


    botonplay.setPosition(380, 220);
    botonplay.setFillColor(Color(200, 127, 107));
    botonplay.setOutlineThickness(3.5);

    botonopts.setPosition(380, 370);
    botonopts.setFillColor(Color(200, 127, 107));
    botonopts.setOutlineThickness(3.5);

    botonexit.setPosition(380, 520);
    botonexit.setFillColor(Color(200, 127, 107));
    botonexit.setOutlineThickness(3.5);

    fondo.setPosition(310, 180);
    fondo.setFillColor(Color(255, 187, 157));
    fondo.setOutlineThickness(2);

    sf::Font font;
    font.loadFromFile("letra.ttf");
    sf::Font font2;
    font2.loadFromFile("retro.ttf");
    // select the font
    texto1.setFont(font2); // font is a sf::Font
    texto2.setFont(font2);
    texto3.setFont(font2);

    texto1.setString("PLAY");
    texto2.setString("OPTIONS");
    texto3.setString("EXIT");

    texto1.setFillColor(sf::Color::Black);
    texto2.setFillColor(sf::Color::Black);
    texto3.setFillColor(sf::Color::Black);



    texto1.setCharacterSize(55);
    texto2.setCharacterSize(55);
    texto3.setCharacterSize(55);

    texto1.setPosition(430, 240);
    texto2.setPosition(390, 390);
    texto3.setPosition(430, 540);
    nano.setScale(1.5, 1.5);
    nano.setPosition(290, 50);



    if (posicionMenu == 0) {//test
        if (color == 0 || color == 1) {
            botonplay.setOutlineColor(sf::Color::Blue);
            color++;
        }

        else if (color == 2 || color == 3) {
            botonplay.setOutlineColor(sf::Color::Yellow);
            color++;
        }
        else if (color == 4 || color == 5 || color == 6) {
            botonplay.setOutlineColor(sf::Color::Red);
            color++;
        }
        else { //blanco
            color = 0;
        }
    }
    else  if (posicionMenu == 1) {//medium
        if (color == 0 || color == 1) {
            botonopts.setOutlineColor(sf::Color::Blue);
            color++;
        }

        else if (color == 2 || color == 3) {
            botonopts.setOutlineColor(sf::Color::Yellow);
            color++;
        }
        else if (color == 4 || color == 5 || color == 6) {
            botonopts.setOutlineColor(sf::Color::Red);
            color++;
        }
        else { //blanco
            color = 0;
        }
    }
    else  if (posicionMenu == 2) {//hard
        if (color == 0 || color == 1) {
            botonexit.setOutlineColor(sf::Color::Blue);
            color++;
        }

        else if (color == 2 || color == 3) {
            botonexit.setOutlineColor(sf::Color::Yellow);
            color++;
        }
        else if (color == 4 || color == 5 || color == 6) {
            botonexit.setOutlineColor(sf::Color::Red);
            color++;
        }
        else { //blanco
            color = 0;
        }
    }



    app.draw(fondo);
    app.draw(botonplay);
    app.draw(botonopts);
    app.draw(botonexit);
    app.draw(texto1);
    app.draw(texto2);
    app.draw(texto3);
    app.draw(nano);


}




void manageKeysOptions(int& posicionMenuOpciones, bool& terminar, Event& e, bool& atras) {

    if (atras == true) {
        if (e.type == sf::Event::KeyPressed) {
            if (e.key.code == sf::Keyboard::Down) {
                posicionMenuOpciones = 0;
                atras = false;
            }
            if (e.key.code == sf::Keyboard::Enter) {
                terminar = true;
            }
        }

    }
    else {
        if (posicionMenuOpciones == 0) {//options
            if (e.type == sf::Event::KeyPressed) {
                if (e.key.code == sf::Keyboard::Up) {
                    posicionMenuOpciones = 0;
                    atras = true;


                }
                if (e.key.code == sf::Keyboard::Down) {
                    posicionMenuOpciones = 1;

                }
                if (e.key.code == sf::Keyboard::Enter) {
                    terminar = true;
                }
            }
        }
        else if (posicionMenuOpciones == 1) {//nano
            if (e.type == sf::Event::KeyPressed) {
                if (e.key.code == sf::Keyboard::Up) {
                    posicionMenuOpciones = 0;

                }
                if (e.key.code == sf::Keyboard::Down) {
                    posicionMenuOpciones = 2;

                }
                if (e.key.code == sf::Keyboard::Enter) {
                    terminar = true;
                }
            }
        }
        else if (posicionMenuOpciones == 2) {//volumen
            if (e.type == sf::Event::KeyPressed) {
                if (e.key.code == sf::Keyboard::Up) {
                    posicionMenuOpciones = 1;

                }
                if (e.key.code == sf::Keyboard::Down) {
                    posicionMenuOpciones = 2;

                }
                if (e.key.code == sf::Keyboard::Enter) {
                    terminar = true;
                }
            }
        }
    }



}








void drawMenuOpciones(RenderWindow& app, int& color, int posicionMenu, bool atras) {

    sf::Text texto1;
    sf::Text texto2;
    sf::Text texto3;
    sf::Text titulo;
    Vector2f tamayo3(40, 30);
    RectangleShape botonatras(tamayo3);
    botonatras.setPosition(10, 10);
    botonatras.setFillColor(Color::White);
    botonatras.setOutlineThickness(1.5);

    Texture atr;

    atr.loadFromFile("images/flechaatras.png");

    const sf::Texture* pTexture = &atr;
    botonatras.setTexture(pTexture);

    sf::Font font;
    font.loadFromFile("letra.ttf");
    titulo.setFont(font);
    titulo.setString("OPTIONS");
    titulo.setCharacterSize(80);
    titulo.setPosition(350, 30);

    Vector2f tamayo(200, 100);
    Vector2f tamayo2(350, 500);
    RectangleShape botonkeys(tamayo);
    RectangleShape botonopts(tamayo);
    RectangleShape botonvol(tamayo);
    RectangleShape fondo(tamayo2);


    botonkeys.setPosition(380, 220);
    botonkeys.setFillColor(Color(200, 127, 107));
    botonkeys.setOutlineThickness(3.5);

    botonopts.setPosition(380, 370);
    botonopts.setFillColor(Color(200, 127, 107));
    botonopts.setOutlineThickness(3.5);

    botonvol.setPosition(380, 520);
    botonvol.setFillColor(Color(200, 127, 107));
    botonvol.setOutlineThickness(3.5);


    fondo.setPosition(310, 180);
    fondo.setFillColor(Color(255, 187, 157));
    fondo.setOutlineThickness(2);

    sf::Font font2;
    font2.loadFromFile("retro.ttf");
    // select the font
    texto1.setFont(font2); // font is a sf::Font
    texto2.setFont(font2);
    texto3.setFont(font2);

    texto1.setString("KEYS");
    texto2.setString("NANO");
    texto3.setString("AUDIO");


    texto1.setFillColor(sf::Color::Black);
    texto2.setFillColor(sf::Color::Black);
    texto3.setFillColor(sf::Color::Black);




    texto1.setCharacterSize(55);
    texto2.setCharacterSize(55);
    texto3.setCharacterSize(55);


    texto1.setPosition(430, 240);
    texto2.setPosition(430, 390);
    texto3.setPosition(420, 540);




    if (atras == true) {
        if (color == 0 || color == 1) {
            botonatras.setOutlineColor(sf::Color::Blue);
            color++;
        }

        else if (color == 2 || color == 3) {
            botonatras.setOutlineColor(sf::Color::Yellow);
            color++;
        }
        else if (color == 4 || color == 5 || color == 6) {
            botonatras.setOutlineColor(sf::Color::Red);
            color++;
        }
        else { //blanco
            botonatras.setOutlineColor(sf::Color::White);
            color = 0;
        }

    }
    else {
        if (posicionMenu == 0) {//test
            if (color == 0 || color == 1) {
                botonkeys.setOutlineColor(sf::Color::Blue);
                color++;
            }

            else if (color == 2 || color == 3) {
                botonkeys.setOutlineColor(sf::Color::Yellow);
                color++;
            }
            else if (color == 4 || color == 5 || color == 6) {
                botonkeys.setOutlineColor(sf::Color::Red);
                color++;
            }
            else { //blanco
                color = 0;
            }
        }
        else  if (posicionMenu == 1) {//medium
            if (color == 0 || color == 1) {
                botonopts.setOutlineColor(sf::Color::Blue);
                color++;
            }

            else if (color == 2 || color == 3) {
                botonopts.setOutlineColor(sf::Color::Yellow);
                color++;
            }
            else if (color == 4 || color == 5 || color == 6) {
                botonopts.setOutlineColor(sf::Color::Red);
                color++;
            }
            else { //blanco
                color = 0;
            }
        }
        else  if (posicionMenu == 2) {//medium
            if (color == 0 || color == 1) {
                botonvol.setOutlineColor(sf::Color::Blue);
                color++;
            }

            else if (color == 2 || color == 3) {
                botonvol.setOutlineColor(sf::Color::Yellow);
                color++;
            }
            else if (color == 4 || color == 5 || color == 6) {
                botonvol.setOutlineColor(sf::Color::Red);
                color++;
            }
            else { //blanco
                color = 0;
            }
        }
    }




    app.draw(fondo);
    app.draw(botonkeys);
    app.draw(botonopts);
    app.draw(botonvol);
    app.draw(texto1);
    app.draw(texto2);
    app.draw(texto3);

    app.draw(botonatras);
    app.draw(titulo);


}



void  drawMenuteclas(RenderWindow& app, int& color, int posicionMenu, bool atras) {


    sf::Text titulo;
    Vector2f tamayo3(40, 30);
    RectangleShape botonatras(tamayo3);
    botonatras.setPosition(10, 10);
    botonatras.setFillColor(Color::White);
    botonatras.setOutlineThickness(1.5);

    Vector2f tamayo4(50, 50);
    RectangleShape imgder(tamayo4);
    imgder.setPosition(630, 150);
    RectangleShape imgizq(tamayo4);
    imgizq.setPosition(630, 250);
    RectangleShape imggas(tamayo4);
    imggas.setPosition(630, 350);
    RectangleShape imgbrake(tamayo4);
    imgbrake.setPosition(630, 450);
    RectangleShape imggear(tamayo4);
    imggear.setPosition(630, 550);
    RectangleShape imgpause(tamayo4);
    imgpause.setPosition(630, 650);


    Texture atr;
    Texture der;
    Texture izq;
    Texture gas;
    Texture brake;
    Texture gear;
    Texture pause;

    atr.loadFromFile("images/flechaatras.png");
    der.loadFromFile("sprites/coches/DroveCar/tile100.png");
    izq.loadFromFile("images/izquierdaparapantalla.png");
    gas.loadFromFile("sprites/coches/DroveCar/tile00.png");
    brake.loadFromFile("images/cochefrena.png");
    gear.loadFromFile("images/marcha_alta.png");
    pause.loadFromFile("images/pause.png");

    const sf::Texture* pTexture = &atr;
    botonatras.setTexture(pTexture);

    pTexture = &der;
    imgder.setTexture(pTexture);

    pTexture = &izq;
    imgizq.setTexture(pTexture);

    pTexture = &gas;
    imggas.setTexture(pTexture);

    pTexture = &brake;
    imgbrake.setTexture(pTexture);

    pTexture = &gear;
    imggear.setTexture(pTexture);
    pTexture = &pause;
    imgpause.setTexture(pTexture);

    sf::Font font;
    font.loadFromFile("letra.ttf");
    titulo.setFont(font);
    titulo.setString("KEYS");
    titulo.setCharacterSize(80);
    titulo.setPosition(430, 30);

    Vector2f tamayo(450, 50);
    Vector2f tamayo2(350, 500);
    RectangleShape botonGas(tamayo);
    RectangleShape botonBrake(tamayo);
    RectangleShape botonIzq(tamayo);
    RectangleShape botonDer(tamayo);
    RectangleShape botonGear(tamayo);
    RectangleShape botonPause(tamayo);
    RectangleShape fondo(tamayo2);


    botonGas.setPosition(300, 150);
    botonGas.setFillColor(Color(200, 127, 107));
    botonGas.setOutlineThickness(3.5);

    botonBrake.setPosition(300, 250);
    botonBrake.setFillColor(Color(200, 127, 107));
    botonBrake.setOutlineThickness(3.5);

    botonDer.setPosition(300, 350);
    botonDer.setFillColor(Color(200, 127, 107));
    botonDer.setOutlineThickness(3.5);

    botonIzq.setPosition(300, 450);
    botonIzq.setFillColor(Color(200, 127, 107));
    botonIzq.setOutlineThickness(3.5);

    botonGear.setPosition(300, 550);
    botonGear.setFillColor(Color(200, 127, 107));
    botonGear.setOutlineThickness(3.5);

    botonPause.setPosition(300, 650);
    botonPause.setFillColor(Color(200, 127, 107));
    botonPause.setOutlineThickness(3.5);



    sf::Font font2;
    font2.loadFromFile("retro.ttf");
    // select the font







    if (atras == true) {
        if (color == 0 || color == 1) {
            botonatras.setOutlineColor(sf::Color::Blue);
            color++;
        }

        else if (color == 2 || color == 3) {
            botonatras.setOutlineColor(sf::Color::Yellow);
            color++;
        }
        else if (color == 4 || color == 5 || color == 6) {
            botonatras.setOutlineColor(sf::Color::Red);
            color++;
        }
        else { //blanco
            botonatras.setOutlineColor(sf::Color::White);
            color = 0;
        }

    }

    sf::Text texto1;
    sf::Text texto2;
    sf::Text texto3;
    sf::Text texto4;
    sf::Text texto5;
    sf::Text texto6;

    texto1.setFont(font); // font is a sf::Font
    texto2.setFont(font);
    texto3.setFont(font);
    texto4.setFont(font);
    texto5.setFont(font);
    texto6.setFont(font);

    texto1.setString("RIGHT -> RIGHTARROW");
    texto2.setString("LEFT -> LEFTARROW");
    texto3.setString("GAS  -> UPARROW");
    texto4.setString("BRAKE -> DOWNARROW");
    texto5.setString("GEAR -> CONTROL");
    texto6.setString("PAUSE -> ESC");


    texto1.setFillColor(sf::Color::Black);
    texto2.setFillColor(sf::Color::Black);
    texto3.setFillColor(sf::Color::Black);
    texto4.setFillColor(sf::Color::Black);
    texto5.setFillColor(sf::Color::Black);
    texto6.setFillColor(sf::Color::Black);





    texto1.setCharacterSize(30);
    texto2.setCharacterSize(30);
    texto3.setCharacterSize(30);
    texto4.setCharacterSize(30);
    texto5.setCharacterSize(30);
    texto6.setCharacterSize(30);


    texto1.setPosition(320, 150);
    texto2.setPosition(320, 250);
    texto3.setPosition(320, 350);
    texto4.setPosition(320, 450);
    texto5.setPosition(320, 550);
    texto6.setPosition(320, 650);



    app.draw(botonatras);

    app.draw(botonGas);

    app.draw(botonBrake);
    app.draw(botonGear);
    app.draw(botonIzq);
    app.draw(botonDer);
    app.draw(botonPause);

    app.draw(imgder);
    app.draw(imgizq);
    app.draw(imggas);
    app.draw(imgbrake);
    app.draw(imggear);
    app.draw(imgpause);

    app.draw(texto1);
    app.draw(texto2);
    app.draw(texto3);
    app.draw(texto4);
    app.draw(texto5);
    app.draw(texto6);



    app.draw(titulo);


}



void elegirTeamNano(int& teamNano, bool& terminar, bool& atras, Event& e) {

        if (atras == true) {
            if (e.type == sf::Event::KeyPressed) {
                if (e.key.code == sf::Keyboard::Down){
                    teamNano = 1;
                    atras = false;
                 }
            
                if (e.key.code == sf::Keyboard::Enter) {
                terminar = true;
                 }
            }
        }
        else {
            if (teamNano == 0) {//ferrari
                if (e.type == sf::Event::KeyPressed) {
                    if (e.key.code == sf::Keyboard::Right) {
                        teamNano = 0;

                    }
                    if (e.key.code == sf::Keyboard::Left) {
                        teamNano = 1;

                    }
                    if (e.key.code == sf::Keyboard::Up) {
                        teamNano = 0;
                        atras = true;

                    }
                    if (e.key.code == sf::Keyboard::Down) {
                        teamNano = 2;

                    }
                    if (e.key.code == sf::Keyboard::Enter) {
                        terminar = true;
                    }
                }
            }
            else if (teamNano == 1) {//alpine
                if (e.type == sf::Event::KeyPressed) {
                    if (e.key.code == sf::Keyboard::Right) {
                        teamNano = 0; //test
                    }

                    if (e.key.code == sf::Keyboard::Left) {
                         teamNano = 1;
                    }

                    if (e.key.code == sf::Keyboard::Up) {
                          teamNano = 1;
                             atras = true;
                    }
                    if (e.key.code == sf::Keyboard::Down) {
                    teamNano = 3;
                    }
                    if (e.key.code == sf::Keyboard::Enter) {
                    terminar = true;
                    }
                }
            }
            else if (teamNano == 3) {//renault
                if (e.type == sf::Event::KeyPressed) {
                    if (e.key.code == sf::Keyboard::Right) {
                        teamNano = 2;

                    }
                    if (e.key.code == sf::Keyboard::Left) {
                        teamNano = 3;

                    }
                    if (e.key.code == sf::Keyboard::Up) {
                        teamNano = 1;

                    }
                    if (e.key.code == sf::Keyboard::Down) {
                        teamNano = 3;

                    }
                    if (e.key.code == sf::Keyboard::Enter) {
                        terminar = true;

                    }
                }
            }
            else if (teamNano == 2) {//mclaren
                if (e.type == sf::Event::KeyPressed) {
                    if (e.key.code == sf::Keyboard::Right) {
                        teamNano = 2;

                    }
                    if (e.key.code == sf::Keyboard::Left) {
                        teamNano = 3;

                    }
                    if (e.key.code == sf::Keyboard::Up) {
                        teamNano = 0;

                    }
                    if (e.key.code == sf::Keyboard::Down) {
                        teamNano = 2;

                    }
                    if (e.key.code == sf::Keyboard::Enter) {
                        terminar = true;

                    }
                }
            }
        }
    

}



void drawNano(RenderWindow& app, int& color, int teamNano, bool atras) {
    sf::Text texto1;
    sf::Text texto2;
    sf::Text texto3;
    sf::Text texto4;
    sf::Text titulo;
    Vector2f tamayo(40, 30);
    RectangleShape botonatras(tamayo);
    botonatras.setPosition(10, 10);
    botonatras.setFillColor(Color::White);
    botonatras.setOutlineThickness(1.5);


    Vector2f tamayo2(380, 200);
    RectangleShape alpine(tamayo2);
    alpine.setPosition(80, 180);
    alpine.setFillColor(Color::White);
    alpine.setOutlineThickness(2);

    RectangleShape ferrari(tamayo2);
    ferrari.setPosition(550, 180);
    ferrari.setFillColor(Color::White);
    ferrari.setOutlineThickness(2);

    RectangleShape renault(tamayo2);
    renault.setPosition(80, 450);
    renault.setFillColor(Color::White);
    renault.setOutlineThickness(2);

    RectangleShape mclaren(tamayo2);
    mclaren.setPosition(550, 450);
    mclaren.setFillColor(Color::White);
    mclaren.setOutlineThickness(2);

    Texture atr;
    Texture alp;
    Texture rrari;
    Texture renau;
    Texture mc;

    atr.loadFromFile("images/flechaatras.png");
    alp.loadFromFile("images/alpine.png");
    rrari.loadFromFile("images/ferrari.png");
    renau.loadFromFile("images/renault.png");
    mc.loadFromFile("images/mclaren.png");

    const sf::Texture* pTexture = &atr;
    botonatras.setTexture(pTexture);

    pTexture = &alp;
    alpine.setTexture(pTexture);

    pTexture = &rrari;
    ferrari.setTexture(pTexture);


    pTexture = &renau;
    renault.setTexture(pTexture);

    pTexture = &mc;
    mclaren.setTexture(pTexture);





    sf::Font font;
    font.loadFromFile("letra.ttf");


    titulo.setFont(font);


    titulo.setString("NANO'S TEAM");



    titulo.setCharacterSize(60);


    titulo.setPosition(350, 30);



    if (atras == true) {
        if (color == 0 || color == 1) {
            botonatras.setOutlineColor(sf::Color::Blue);
            color++;
        }

        else if (color == 2 || color == 3) {
            botonatras.setOutlineColor(sf::Color::Yellow);
            color++;
        }
        else if (color == 4 || color == 5 || color == 6) {
            botonatras.setOutlineColor(sf::Color::Red);
            color++;
        }
        else { //blanco
            botonatras.setOutlineColor(sf::Color::White);
            color = 0;
        }

    }

    else {
        if (teamNano == 0) {//ferrari
            if (color == 0 || color == 1) {
                ferrari.setOutlineColor(sf::Color::Blue);
                color++;
            }

            else if (color == 2 || color == 3) {
                ferrari.setOutlineColor(sf::Color::Yellow);
                color++;
            }
            else if (color == 4 || color == 5 || color == 6) {
                ferrari.setOutlineColor(sf::Color::Red);
                color++;
            }
            else { //rojo
                color = 0;
            }
        }
        else if (teamNano == 1) {//alpine
            if (color == 0 || color == 1) {
                alpine.setOutlineColor(sf::Color::Blue);
                color++;
            }

            else if (color == 2 || color == 3) {
                alpine.setOutlineColor(sf::Color::Yellow);
                color++;
            }
            else if (color == 4 || color == 5 || color == 6) {
                alpine.setOutlineColor(sf::Color::Red);
                color++;
            }
            else { //rojo
                color = 0;
            }
        }
        else if (teamNano == 3) {//renault
            if (color == 0 || color == 1) {
                renault.setOutlineColor(sf::Color::Blue);

                color++;
            }

            else if (color == 2 || color == 3) {
                renault.setOutlineColor(sf::Color::Yellow);
                color++;
            }
            else if (color == 4 || color == 5 || color == 6) {
                renault.setOutlineColor(sf::Color::Red);
                color++;
            }
            else { //rojo
                color = 0;
            }
        }
        else if (teamNano == 2) {//mclaren
            if (color == 0 || color == 1) {
                mclaren.setOutlineColor(sf::Color::Blue);
                color++;
            }

            else if (color == 2 || color == 3) {
                mclaren.setOutlineColor(sf::Color::Yellow);
                color++;
            }
            else if (color == 4 || color == 5 || color == 6) {
                mclaren.setOutlineColor(sf::Color::Red);
                color++;
            }
            else { //rojo
                color = 0;
            }
        }
    }






    app.draw(titulo);
    app.draw(botonatras);
    app.draw(alpine);
    app.draw(ferrari);
    app.draw(renault);
    app.draw(mclaren);
}

void elegirVolumen(int& posicionVolumen, bool& terminar, Event& e, bool& atras) {

        if (atras == true) {
            if (e.type == sf::Event::KeyPressed) {
                if (e.key.code == sf::Keyboard::Down) {
                    posicionVolumen = 0;
                    atras = false;
                }
                if (e.key.code == sf::Keyboard::Enter) {
                    terminar = true;
                }
            }
        }
        else {
            if (posicionVolumen == 0) {//sonido
                if (e.type == sf::Event::KeyPressed) {
                    if (e.key.code == sf::Keyboard::Up) {
                        posicionVolumen = 0;
                        atras = true;

                    }
                    if (e.key.code == sf::Keyboard::Down) {
                        posicionVolumen = 1;

                    }
                    if (e.key.code == sf::Keyboard::Enter) {
                        terminar = true;
                    }
                }
            }
            else if (posicionVolumen == 1) {//quitarsonido
                if (e.type == sf::Event::KeyPressed) {
                    if (e.key.code == sf::Keyboard::Up) {
                        posicionVolumen = 0;


                    }
                    if (e.key.code == sf::Keyboard::Down) {
                        posicionVolumen = 1;
                    }
                    if (e.key.code == sf::Keyboard::Enter) {
                        terminar = true;
                    }
                }
            }
        }
    
}

void drawVol(RenderWindow& app, int& color, int posicionVolumen, bool atras) {

    sf::Text titulo;
    Vector2f tamayo3(40, 30);
    RectangleShape botonatras(tamayo3);
    botonatras.setPosition(10, 10);
    botonatras.setFillColor(Color::White);
    botonatras.setOutlineThickness(1.5);

    Vector2f tamayo4(50, 50);
    RectangleShape volume(tamayo4);
    volume.setPosition(630, 150);
    
    RectangleShape novolume(tamayo4);
    novolume.setPosition(630, 250);
    

    if (posicionVolumen == 0) {
        volume.setFillColor(Color::Yellow);
        novolume.setFillColor(Color::Red);
    }
    else if (posicionVolumen == 1) {
        novolume.setFillColor(Color::Yellow);
        volume.setFillColor(Color::Red);
    }



    Texture atr;
    Texture vol;
    Texture novol;


    atr.loadFromFile("images/flechaatras.png");
    vol.loadFromFile("images/volumen.png");
    novol.loadFromFile("images/novolume.png");
  
    const sf::Texture* pTexture = &atr;
    botonatras.setTexture(pTexture);

    pTexture = &vol;
    volume.setTexture(pTexture);

    pTexture = &novol;
    novolume.setTexture(pTexture);

  

    sf::Font font;
    font.loadFromFile("letra.ttf");
    titulo.setFont(font);
    titulo.setString("VOLUME");
    titulo.setCharacterSize(80);
    titulo.setPosition(420, 30);

    Vector2f tamayo(450, 50);
    Vector2f tamayo2(350, 500);
    RectangleShape botonVol(tamayo);
    RectangleShape botonnoVol(tamayo);



    botonVol.setPosition(300, 150);
    botonVol.setFillColor(Color(200, 127, 107));
    botonVol.setOutlineThickness(3.5);

    botonnoVol.setPosition(300, 250);
    botonnoVol.setFillColor(Color(200, 127, 107));
    botonnoVol.setOutlineThickness(3.5);



    sf::Font font2;
    font2.loadFromFile("retro.ttf");
    // select the font







    if (atras == true) {
        if (color == 0 || color == 1) {
            botonatras.setOutlineColor(sf::Color::Blue);
            color++;
        }

        else if (color == 2 || color == 3) {
            botonatras.setOutlineColor(sf::Color::Yellow);
            color++;
        }
        else if (color == 4 || color == 5 || color == 6) {
            botonatras.setOutlineColor(sf::Color::Red);
            color++;
        }
        else { //blanco
            botonatras.setOutlineColor(sf::Color::White);
            color = 0;
        }

    }

    else {
        if (posicionVolumen == 0) {//ferrari
            if (color == 0 || color == 1) {
                botonVol.setOutlineColor(sf::Color::Blue);
                color++;
            }

            else if (color == 2 || color == 3) {
                botonVol.setOutlineColor(sf::Color::Yellow);
                color++;
            }
            else if (color == 4 || color == 5 || color == 6) {
                botonVol.setOutlineColor(sf::Color::Red);
                color++;
            }
            else { //rojo
                color = 0;
            }
        }
        else if (posicionVolumen == 1) {//alpine
            if (color == 0 || color == 1) {
                botonnoVol.setOutlineColor(sf::Color::Blue);
                color++;
            }

            else if (color == 2 || color == 3) {
                botonnoVol.setOutlineColor(sf::Color::Yellow);
                color++;
            }
            else if (color == 4 || color == 5 || color == 6) {
                botonnoVol.setOutlineColor(sf::Color::Red);
                color++;
            }
            else { //rojo
                color = 0;
            }
        }
    }

    sf::Text texto1;
    sf::Text texto2;


    texto1.setFont(font); // font is a sf::Font
    texto2.setFont(font);


    texto1.setString("VOLUME -> ON");
    texto2.setString("VOLUME -> OFF");



    texto1.setFillColor(sf::Color::Black);
    texto2.setFillColor(sf::Color::Black);
   




    texto1.setCharacterSize(30);
    texto2.setCharacterSize(30);
    

    texto1.setPosition(320, 150);
    texto2.setPosition(320, 250);
 



    app.draw(botonatras);

    app.draw(botonVol);

    app.draw(botonnoVol);


    app.draw(volume);
    app.draw(novolume);


    app.draw(texto1);
    app.draw(texto2);




    app.draw(titulo);

}