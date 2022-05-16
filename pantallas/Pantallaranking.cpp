#include "Pantallaranking.hpp"

void selectName(string name[], string key[],int& letra,int& iterador, bool& terminar, bool& haCambiado,Clock& clock) {

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


void drawRanking(RenderWindow& app,string puntuaciones[], string nombres[],int& lim,int& scoreentero, int& posicionPuntuacion,int& color) {
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
        n.setString(nombres[i]);

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
        if (i != posicionPuntuacion) {
            j.setFillColor(sf::Color::White);
            s.setFillColor(sf::Color::White);
            t.setFillColor(sf::Color::White);
            n.setFillColor(sf::Color::White);
        }
        else if(i== posicionPuntuacion &&(color==0 || color ==1)) {
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


void drawInicio(RenderWindow& app,int& color){
    Texture titulo;
    Texture nan;
    Texture letrai;
        titulo.loadFromFile("images/titulo.png");
        nan.loadFromFile("images/falonsoedition.png");
        letrai.loadFromFile("images/letrasinicio.png");

        Sprite tit(titulo);
        Sprite nano(nan);
        Sprite letra(letrai);

        if (color == 0 ||color==1) {
            tit.setColor(sf::Color::Red);
            nano.setColor(sf::Color::Red);
            color++;
        }
        
        else if (color == 2 || color== 3) {
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

void drawPrepare(RenderWindow& app,Sprite object[], bool& prepare){
    object[16].move(sf::Vector2f(-16,0));

    if(object[16].getPosition().x > -1000){
        app.draw(object[16]);
    }else{
        prepare = false;
    }
    //app.draw(globo);

}



void drawSemaphore(RenderWindow& app,Sprite object[],  int& contadorSem){
    contadorSem++;
    if(contadorSem <50){
        app.draw(object[18]);
    }else if(contadorSem >= 50 && contadorSem < 65){
        app.draw(object[18]);
    }else if(contadorSem >= 65 && contadorSem < 130){
        app.draw(object[19]);
    }else if(contadorSem >= 130 && contadorSem < 200){
        app.draw(object[20]);
    }else{
        app.draw(object[21]);
    }
}


void manageKeysCircuito(int& mapa,bool& terminar,bool& atras,Clock& clock) {
    if (clock.getElapsedTime().asSeconds() > 0.1f) { //sin esto se pasa de "estados"
        clock.restart();
        if (atras == true) {
            if (Keyboard::isKeyPressed(Keyboard::Down)) {
                mapa = 1;
            }
            if (Keyboard::isKeyPressed(Keyboard::Enter)) {
                terminar = true;
            }
        }
        else {
            if (mapa == 0) {//test
                if (Keyboard::isKeyPressed(Keyboard::Right)) {
                    mapa = 0;

                }
                if (Keyboard::isKeyPressed(Keyboard::Left)) {
                    mapa = 1;

                }
                if (Keyboard::isKeyPressed(Keyboard::Up)) {
                    mapa = 0;
                    atras = true;

                }
                if (Keyboard::isKeyPressed(Keyboard::Down)) {
                    mapa = 2;

                }
                if (Keyboard::isKeyPressed(Keyboard::Enter)) {
                    terminar = true;
                }
            }
            else if (mapa == 1) {//fuji
                if (Keyboard::isKeyPressed(Keyboard::Right)) {
                    mapa = 0; //test
                }
                if (Keyboard::isKeyPressed(Keyboard::Left)) {
                    mapa = 1;

                }
                if (Keyboard::isKeyPressed(Keyboard::Up)) {
                    mapa = 1;
                    atras = true;


                }
                if (Keyboard::isKeyPressed(Keyboard::Down)) {
                    mapa = 3;
                }
                if (Keyboard::isKeyPressed(Keyboard::Enter)) {
                    terminar = true;
                }
            }
            else if (mapa == 3) {//suzuka
                if (Keyboard::isKeyPressed(Keyboard::Right)) {
                    mapa = 2;

                }
                if (Keyboard::isKeyPressed(Keyboard::Left)) {
                    mapa = 3;

                }
                if (Keyboard::isKeyPressed(Keyboard::Up)) {
                    mapa = 1;

                }
                if (Keyboard::isKeyPressed(Keyboard::Down)) {
                    mapa = 3;

                }
                if (Keyboard::isKeyPressed(Keyboard::Enter)) {
                    terminar = true;

                }
            }
            else if (mapa == 2) {//seaside
                if (Keyboard::isKeyPressed(Keyboard::Right)) {
                    mapa = 2;

                }
                if (Keyboard::isKeyPressed(Keyboard::Left)) {
                    mapa = 3;

                }
                if (Keyboard::isKeyPressed(Keyboard::Up)) {
                    mapa = 0;

                }
                if (Keyboard::isKeyPressed(Keyboard::Down)) {
                    mapa = 2;

                }
                if (Keyboard::isKeyPressed(Keyboard::Enter)) {
                    terminar = true;

                }
            }
        }
    }

}

void manageKeysIa(int& iaMode, bool& terminar, Clock& clock,bool &atras) {
    if (clock.getElapsedTime().asSeconds() > 0.1f) { //sin esto se pasa de "estados"
        clock.restart();
        if (atras == true) {
            if (Keyboard::isKeyPressed(Keyboard::Down)) {
                mapa = 1;
            }
            if (Keyboard::isKeyPressed(Keyboard::Enter)) {
                terminar = true;
            }
        }
        else {
            if (iaMode == 0) {//facil

                if (Keyboard::isKeyPressed(Keyboard::Up)) {
                    iaMode = 2;
                    atras = true;


                }
                if (Keyboard::isKeyPressed(Keyboard::Down)) {
                    iaMode = 1;

                }
                if (Keyboard::isKeyPressed(Keyboard::Enter)) {
                    terminar = true;
                }
            }
            else if (iaMode == 1) {//medio

                if (Keyboard::isKeyPressed(Keyboard::Up)) {
                    iaMode = 0;

                }
                if (Keyboard::isKeyPressed(Keyboard::Down)) {
                    iaMode = 2;

                }
                if (Keyboard::isKeyPressed(Keyboard::Enter)) {
                    terminar = true;
                }
            }
            else if (iaMode == 2) {//dificil

                if (Keyboard::isKeyPressed(Keyboard::Up)) {
                    iaMode = 1;

                }
                if (Keyboard::isKeyPressed(Keyboard::Down)) {
                    iaMode = 0;

                }
                if (Keyboard::isKeyPressed(Keyboard::Enter)) {
                    terminar = true;
                }
            }
        }
    }
    

}

void drawCircuito(RenderWindow& app, int& color, int mapa,bool atras) {
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


    texto1.setFillColor(Color(219,224,142));
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


void drawIa(RenderWindow& app, int& color, int iaMode,bool atras) {

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
    titulo.setString("SELECT LEVEL");



    texto1.setCharacterSize(55);
    texto2.setCharacterSize(55);
    texto3.setCharacterSize(55);
    titulo.setCharacterSize(80);

    texto1.setPosition(400, 200);
    texto2.setPosition(380, 350);
    texto3.setPosition(400, 500);
    titulo.setPosition(280, 30);


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
void drawResultadosClas(RenderWindow& app,Time tiempo, int& posicionSalida,int& bon,int& color,int parpadeo) {
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
    lapnumber.setString("LAP TIME "+sec + ". " + minu);

    position.setString("POSITION");
    uno.setString("1");
    dos.setString("2");
    tres.setString("3");
    cuatro.setString("4");
    cinco.setString("5");
    seis.setString("6");
    siete.setString("7");
    ocho.setString("8");

    String puntu= inttostring(bon);
    bonus.setString("BONUS "+puntu);


    if (parpadeo == 0) {
        colorear(lapnumber, color);
    }
    else if(parpadeo == 1){
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
    else if(parpadeo==2) {
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
