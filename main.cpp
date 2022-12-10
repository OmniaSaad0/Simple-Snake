#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include <time.h>
#include <string>
using namespace sf;
using namespace std;

int main()
{
    // Create the main window
    RenderWindow app(VideoMode(1920, 1080), "Final Game");
    app.setFramerateLimit(60);
    app.setKeyRepeatEnabled(false);


    //font
    Font comix;
    comix.loadFromFile("Data/ALGER.TTF");

    int i = 0;
    Texture  GameOverBG;
    GameOverBG.loadFromFile("Data/GOBackGround.png");
    //HomePage texture
    Texture fStart, fExit,fmiddle,fRMiddle,fLMiddle,fName,fInfo,fSound,bHomePage;
    fLMiddle.loadFromFile("Data/RA.png");
    fRMiddle.loadFromFile("Data/LA.png");
    fInfo.loadFromFile("Data/InfoPage.png");
    fSound.loadFromFile("Data/528061.png");
    bHomePage.loadFromFile("Data/5.png");
    fName.loadFromFile("Data/Name.png");
    fStart.loadFromFile("Data/Play.png");
    fExit.loadFromFile("Data/Exit.png");


    //SnakeChoose
    Texture rSnake,bSnake,gSnake;
    rSnake.loadFromFile("Data/6988764.png");
    gSnake.loadFromFile("Data/3196026.png");
    bSnake.loadFromFile("Data/2276815.png");

    //HomePage temps
    RectangleShape middle,rMiddle,lMiddle,bStart,bExit,bName,bSound,bInfo,bInfoPage,tInfo,backgroundStartPage,scoreBG;

    scoreBG.setSize(Vector2f(1920,1080));
    scoreBG.setTexture(&GameOverBG);

    backgroundStartPage.setSize(Vector2f(1920,1080));
    backgroundStartPage.setTexture(&bHomePage);

    bName.setSize(Vector2f(780,120));
    bName.setPosition(560,70);
    bName.setTexture(&fName);

    middle.setSize(Vector2f(320,320));
    middle.setPosition(800,325);
    middle.setTexture(&rSnake);

    rMiddle.setSize(Vector2f(160,160));
    rMiddle.setPosition(1280,405);
    rMiddle.setTexture(&fRMiddle);

    lMiddle.setSize(Vector2f(160,160));
    lMiddle.setPosition(480,405);
    lMiddle.setTexture(&fLMiddle);

    bStart.setSize(Vector2f(640,65));
    bStart.setPosition(640,710);
    bStart.setTexture(&fStart);

    bExit.setSize(Vector2f(640,65));
    bExit.setPosition(640,840);
    bExit.setTexture(&fExit);

    bInfo.setSize(Vector2f(80,80));
    bInfo.setPosition(1800,960);
    bInfo.setTexture(&fInfo);

    tInfo.setSize(Vector2f(400,225));
    tInfo.setPosition(1440,775);

    bSound.setSize(Vector2f(80,80));
    bSound.setPosition(40,960);
    bSound.setTexture(&fSound);


    //Information page
    Texture fInfoPage,fODC,fCreativa,fThanxLetter,fTeamInfo,fBackgroungInfoPage,fTeam;
    fBackgroungInfoPage.loadFromFile("Data/Back10.jpg");
    fInfoPage.loadFromFile("Data/x.png");
    fCreativa.loadFromFile("Data/logo.png");
    fODC.loadFromFile("Data/ODC.jfif");
    fTeam.loadFromFile("Data/Artboard 1.png");
    fThanxLetter.loadFromFile("Data/2.png");

    RectangleShape teamInfo,bTeamInfo, ODC,Creativa,thanxLetter,backgroungInfoPage;

    backgroungInfoPage.setSize(Vector2f(1920,1080));
    backgroungInfoPage.setTexture(&fBackgroungInfoPage);

    teamInfo.setSize(Vector2f(1600,470));
    teamInfo.setPosition(160,70);
    teamInfo.setTexture(&fTeam);


    bTeamInfo.setSize(Vector2f(1920,470));
    bTeamInfo.setPosition(0,70);
    bTeamInfo.setFillColor(Color(0,0,0,50));

    thanxLetter.setSize(Vector2f(960,250));
    thanxLetter.setPosition(480,610);
    thanxLetter.setTexture(&fThanxLetter);

    ODC.setSize(Vector2f(135,135));
    ODC.setPosition(1040,945);
    ODC.setTexture(&fODC);

    Creativa.setSize(Vector2f(135,135));
    Creativa.setPosition(745,945);
    Creativa.setTexture(&fCreativa);

    bInfoPage.setSize(Vector2f(80,80));
    bInfoPage.setPosition(1800,960);
    bInfoPage.setTexture(&fInfoPage);

begining :

    //define HomePage variables
    bool HomePage = 1,rMov = 0,lMov = 0,start = 0,exit = 0,info = 0,sound = 1,infoPage = 0,gameOver = 0 ;

    //game variables
    bool moveRight=0,moveLeft=0,moveUp=0,moveDown=0;
    int score=0,pos=0;

    // sound load
    SoundBuffer buffer;
    buffer.loadFromFile("Data/bg.wav");
    Sound BG;
    BG.setBuffer(buffer);

    //score
    Text scoreText;
    scoreText.setFont(comix);
    scoreText.setPosition(10,10);
    scoreText.setCharacterSize(20);
    scoreText.setFillColor(Color::White);
    scoreText.setString("Score : " + to_string(score));

    // game temps
    vector<CircleShape>snak;
    CircleShape head;
    int x=960,y=525;
    head.setPosition(x,y);
    head.setRadius(10);
    for(int i=0; i<5; i++)
    {
        snak.push_back(head);
    }
    int tempx=960;
    for(int i=1; i<5; i++)
    {
        tempx-=30;
        snak[i].setPosition(tempx,y);

    }

    // food
    sf::CircleShape food[10];
    for(int i=0; i<2; i++)
        food[i].setRadius(10);
    pair<int,int>foodPosition[10];
    for(int i=0; i<2; i++)
    {
        foodPosition[i].first=rand()%1880+30;
        foodPosition[i].second=rand()%1040+30;
        food[i].setPosition(foodPosition[i].first,foodPosition[i].second);
    }

    //sound on
    if(sound)
        BG.play();


    // Start the game loop
    while (!exit)
    {
        Event event;
        while (app.pollEvent(event))
        {
            if (event.type == Event::Closed)
                app.close();

            if(!start)
            {
                //rMiddle
                if(Mouse::getPosition().x>=1280 && Mouse::getPosition().x<1440
                        &&Mouse::getPosition().y>405 && Mouse::getPosition().y<565
                        &&event.type==sf::Event::MouseButtonPressed&&event.mouseButton.button==sf::Mouse::Left)
                {
                    rMov=true;
                    if(i<2)
                        i++;
                }
                //lMiddle
                if(Mouse::getPosition().x>=480 && Mouse::getPosition().x<=640
                        &&Mouse::getPosition().y>=405 && Mouse::getPosition().y<=565
                        &&event.type==sf::Event::MouseButtonPressed&&event.mouseButton.button==sf::Mouse::Left)
                {
                    lMov=true;
                    if(i>0)
                        i--;
                }

                //bStart
                if(Mouse::getPosition().x>=640 && Mouse::getPosition().x<=1280
                        &&Mouse::getPosition().y>=710 && Mouse::getPosition().y<=775
                        &&event.type==sf::Event::MouseButtonPressed&&event.mouseButton.button==sf::Mouse::Left)
                {
                    start = true;
                    HomePage = 0;
                    if(i==0)
                    {
                        head.setFillColor(Color::Red);
                        for(int k=0;k<snak.size();k++)
                            snak[k].setFillColor(Color::Red);
                    }
                    else if(i==1)
                    {
                         head.setFillColor(Color::Green);
                        for(int k=0;k<snak.size();k++)
                            snak[k].setFillColor(Color::Green);
                    }
                    else
                    {
                         head.setFillColor(Color::Yellow);
                        for(int k=0;k<snak.size();k++)
                            snak[k].setFillColor(Color::Yellow);
                    }
                }

                //bExit
                if(Mouse::getPosition().x>=640 && Mouse::getPosition().x<=1280
                        &&Mouse::getPosition().y>=840 && Mouse::getPosition().y<=905
                        &&event.type==sf::Event::MouseButtonPressed&&event.mouseButton.button==sf::Mouse::Left)
                {
                    exit = true;
                }

                //bSound
                if(Mouse::getPosition().x>=40 && Mouse::getPosition().x<=120
                        &&Mouse::getPosition().y>=960 && Mouse::getPosition().y<=1040
                        &&event.type==sf::Event::MouseButtonPressed&&event.mouseButton.button==sf::Mouse::Left)
                    sound = !sound;
                //bInfo
                if(Mouse::getPosition().x>=1800 && Mouse::getPosition().x<=1880
                        &&Mouse::getPosition().y>=960 && Mouse::getPosition().y<=1040
                        &&event.type==sf::Event::MouseButtonPressed&&event.mouseButton.button==sf::Mouse::Left)
                {
                    infoPage=!infoPage;
                    HomePage = !HomePage;
                }

            }

            //Game Events
            if(event.type==Event::KeyPressed&&event.key.code==sf::Keyboard::Up)
            {
                moveUp=true;
                moveDown=moveLeft=moveRight=false;
            }
            if(event.type==sf::Event::KeyPressed&&event.key.code==sf::Keyboard::Down)
            {
                moveDown=true;
                moveUp=moveLeft=moveRight=false;
            }
            if(event.type==sf::Event::KeyPressed&&event.key.code==sf::Keyboard::Right)
            {
                moveRight=true;
                moveDown=moveLeft=moveUp=false;
            }
            if(event.type==sf::Event::KeyPressed&&event.key.code==sf::Keyboard::Left)
            {
                moveLeft=true;
                moveDown=moveRight=moveUp=false;
            }



        }

        if(HomePage)
        {
            app.clear();
            app.draw(backgroundStartPage);
            app.draw(bName);
            app.draw(middle);
            app.draw(rMiddle);
            app.draw(lMiddle);
            app.draw(bStart);
            app.draw(bExit);
            app.draw(bSound);
            app.draw(bInfo);
            if(i==0)
                middle.setTexture(&rSnake);
            if(i==1)
                middle.setTexture(&gSnake);
            if(i==2)
                middle.setTexture(&bSnake);
            app.display();
        }
        else if(infoPage)
        {
            app.clear();

            app.draw(backgroungInfoPage);

            app.draw(bInfoPage);
            app.draw(teamInfo);
            app.draw(Creativa);
            app.draw(ODC);
            app.draw(thanxLetter);
            app.display();
        }
        else if(start)
        {
            //play the game
            app.clear();
            if(moveUp)
            {
                app.clear();
                y-=10;
                x=((x%1920)+1920)%1920;
                y=((y%1080)+1080)%1080;
                for(int i=snak.size()-1; i>=0; i--)
                {
                    int xn=snak[i-1].getPosition().x;
                    int yn=snak[i-1].getPosition().y;
                    snak[i].setPosition(xn,yn);

                }
                snak[0].setPosition(x,y);
                for(int i=0; i<snak.size(); i++)
                {
                    app.draw(snak[i]);
                }

            }
            else if(moveDown)
            {
                app.clear();
                y+=10;
                x=((x%1920)+1920)%1920;
                y=((y%1080)+1080)%1080;
                for(int i=snak.size()-1; i>=0; i--)
                {
                    int xn=snak[i-1].getPosition().x;
                    int yn=snak[i-1].getPosition().y;
                    snak[i].setPosition(xn,yn);

                }
                snak[0].setPosition(x,y);
                for(int i=0; i<snak.size(); i++)
                {
                    app.draw(snak[i]);
                }
            }
            else if(moveLeft)
            {
                app.clear();
                x-=10;
                x=((x%1920)+1920)%1920;
                y=((y%1080)+1080)%1080;
                for(int i=snak.size()-1; i>=0; i--)
                {
                    int xn=snak[i-1].getPosition().x;
                    int yn=snak[i-1].getPosition().y;
                    snak[i].setPosition(xn,yn);

                }
                snak[0].setPosition(x,y);
                for(int i=0; i<snak.size(); i++)
                {
                    app.draw(snak[i]);
                }

            }
            else if(moveRight)
            {
                app.clear();
                x+=10;
                x=((x%1920)+1920)%1920;
                y=((y%1080)+1080)%1080;
                for(int i=snak.size()-1; i>=0; i--)
                {
                    int xn=snak[i-1].getPosition().x;
                    int yn=snak[i-1].getPosition().y;
                    snak[i].setPosition(xn,yn);

                }
                snak[0].setPosition(x,y);
                for(int i=0; i<snak.size(); i++)
                {
                    app.draw(snak[i]);
                }
            }
            for(int i=0; i<2; i++)
            {
                app.draw(food[i]);
                if(snak[0].getGlobalBounds().intersects(food[i].getGlobalBounds()))
                {
                    score += 5;
                    scoreText.setString("Score : " + to_string(score));
                    foodPosition[i].first=rand()%1880+30;
                    foodPosition[i].second=rand()%1040+50;
                    food[i].setPosition(foodPosition[i].first,foodPosition[i].second);
                    int xn=snak[snak.size()-1].getPosition().x;
                    int yn=snak[snak.size()-1].getPosition().y;

                    for(int i=0; i<3; i++)
                    {
                        head.setPosition(xn+10,yn);
                        snak.push_back(head);
                        app.draw(head);
                        xn=snak[snak.size()-1].getPosition().x;
                        yn=snak[snak.size()-1].getPosition().y;

                    }

                }
            }

            for(int i=1; i<snak.size(); i++)
            {
                if(snak[0].getPosition().x==snak[i].getPosition().x&&snak[0].getPosition().y==snak[i].getPosition().y)
                {
                    BG.stop();

                    sleep(milliseconds(5000));
                    gameOver=1;
                    start=0;
                }
            }
            app.draw(scoreText);
            app.display();

        }
        else if(gameOver)
        {
            //Game Over
            //score
            app.clear();
            app.draw(scoreBG);
            scoreText.setCharacterSize(50);
            scoreText.setPosition(850,750);
            scoreText.setFillColor(Color::Yellow);
            app.draw(scoreText);
            app.display();
            sleep(milliseconds(5000));

            gameOver=0;
            HomePage=1;
            score=0;
            goto begining;

        }
    }
    return EXIT_SUCCESS;
}

