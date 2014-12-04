#include "game.h"
#include <QDebug>
using namespace sf;

int scene[10][14] { 0,0,0,0,0, 0, 0,0,0,0,0,0,0,0,
                    0,0,0,0,0, 0, 0,0,0,0,0,0,0,0,
                    0,0,0,0,0, 0, 0,0,0,0,0,0,0,0,
                    0,0,0,1,0, 0, 0,0,0,0,0,0,0,0,
                    0,0,0,1,0, 0, 0,0,0,0,0,0,0,0,
                    0,0,0,0,0, 0, 0,0,0,0,0,0,0,0,
                    0,0,0,0,0, 2,-1,0,0,0,0,0,0,0,
                    0,0,0,0,0,-1,-1,0,0,0,0,0,0,0,
                    0,0,0,0,0,-1,-1,0,0,0,0,0,0,0,
                    0,0,0,0,0, 0, 0,0,0,0,0,0,0,0
                                                };

game::game(bool g_state)
    : mainWindow(VideoMode(/*1024,768*/896,640), "GameName")
{
    path_to_resources = "/home/morphei/course_work/course_work/resources/";
    framesWindow.x = 14;
    framesWindow.y = 10;
    TimePerFrame = seconds(1.f/60.f);
    if(g_state == 0)
    {
        state = MAIN_MENU;
        index_Menu=0;
    }
    else
        state = GAME;
    loadResources();
    run();
}

void game::run()
{

    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    mainWindow.setVerticalSyncEnabled(true);
    while(mainWindow.isOpen())
    {
        processEvents();
        timeSinceLastUpdate += clock.restart();
        while (timeSinceLastUpdate > TimePerFrame)
        {
        timeSinceLastUpdate -= TimePerFrame;
        processEvents();
        update(TimePerFrame);
        }
        render();
    }
}

void game::processEvents()
{
    Event event;
    while (mainWindow.pollEvent(event))
    {
        if(event.type == Event::Closed)
            mainWindow.close();
        if(event.type == Event::KeyPressed)
        {
            handlePlayerInput(event.key.code,true);
        }
        if(event.type == Event::KeyReleased)
        {
            handlePlayerInput(event.key.code,false);
        }
    }
}

void game::update(Time TimePerFrame)
{

if(state == MAIN_MENU)
{

    Color color;
    if(!m_options.empty())
    {
        color.r = 77;//
        color.g = 49;//>Brown
        color.b = 2; //
        for(int i = 0; i <= m_options.size()-1; i++)
        {

            m_options.at(i).setColor(color);
            m_options.at(i).setScale(5,4);
        }
        color.r = 14; //
        color.g = 142;//>Green
        color.b = 2;  //
        m_options.at(index_Menu).setColor(color);
        m_options.at(index_Menu).setScale(6,4);
    }

}
if(state == GAME)
{


}

}

void game::render()
{
//----------------------RENDERING MAIN MENU--------------------------------------------------------------------------------------------
if(state == MAIN_MENU)
    {
        sprites.at(0).setPosition(background_position);
        mainWindow.draw(sprites.at(0));
        //--
        for(int i = 0; i <= m_options.size()-1; i++)
            mainWindow.draw(m_options.at(i));
        mainWindow.display();
    }
//----------------------RENDERING GAME-------------------------------------------------------------------------------------------------
if(state == GAME)
    {

        //Drawing background
        for(int i = 0; i < window_height; i++)
            for(int j = 0; j < window_width; j++)
            {
                background_position.x=0+i*128;
                background_position.y=0+j*128;
                sprites.at(0).setPosition(background_position);
                mainWindow.draw(sprites.at(0));
            }
        //Drawing objects
        for(int i = 0; i <= framesWindow.y; i++)
            for(int j = 0; j <= framesWindow.x; j++)
            {
                if(scene[i][j]!=0&&scene[i][j]!=-1)
                {
                object_position.x = 0 + j*64;
                object_position.y = 0 + i*64;
                sprites.at(scene[i][j]).setPosition(object_position);
                mainWindow.draw(sprites.at(scene[i][j]));
                }
            }
        hero_sprite.setPosition(hero_position);
        int x,y;
        x = hero_position.y/64;
        y = hero_position.x/64;
        if(scene[x][y]!=-1)
        mainWindow.draw(hero_sprite);

    }
    mainWindow.display();
}

void game::loadResources()
{
    if(state == MAIN_MENU)
    {
        Texture background;
        Sprite background_sp;
        background.loadFromFile(path_to_resources+"main_background_800x600_b.jpg");
        textures.push_back(background);
        sprites.push_back(background_sp);
        sprites.at(0).setTexture(textures.at(0));
        mainFont.loadFromFile(path_to_resources+"GoodDog.otf");
        playOption.setFont(mainFont);
        playOption.setString("Play");
        playOption.setPosition(50,mainWindow.getSize().y/3);
        playOption.setScale(5,4);
        m_options.push_back(playOption);
        exitOption.setFont(mainFont);
        exitOption.setString("ExiT");
        exitOption.setPosition(50,mainWindow.getSize().y/3+120);
        exitOption.setScale(5,4);
        m_options.push_back(exitOption);
    }
    if(state == GAME)
    {
        window_height=mainWindow.getSize().x/128;
        window_width=mainWindow.getSize().y/128+3;
        Texture tree,way,flower;
        textures.at(0).loadFromFile(path_to_resources+"grass_background.jpg");
        flower.loadFromFile(path_to_resources+"obj_01.png");
        tree.loadFromFile(path_to_resources+"obj_02.png");
        //textures.push_back(way);
        textures.push_back(flower);
        textures.push_back(tree);
        Sprite tree_sp,way_sp,flower_sp;
        sprites.at(0).setTexture(textures.at(0));
        //way_sp.setTexture(textures.at(2));
        flower_sp.setTexture(textures.at(1));
        tree_sp.setTexture(textures.at(2));
        sprites.push_back(flower_sp);
        sprites.push_back(tree_sp);
        hero.loadFromFile(path_to_resources+"Bomzh.png");
        hero_sprite.setTexture(hero);
        hero_position.x = 128;
        hero_position.y = 128;
    }
}

void game::handlePlayerInput(Keyboard::Key key, bool isPressed)
{
    if(state == MAIN_MENU)
        {
        if(isPressed)
            {
            if(key == Keyboard::W|key == Keyboard::Up)
                if (index_Menu == 0)
                {
                    index_Menu = m_options.size()-1;
                }
                else
                    index_Menu--;
            if(key == Keyboard::S||key == Keyboard::Down)
                if (index_Menu == m_options.size()-1)
                    index_Menu=0;
                else
                    index_Menu++;
            if(key == Keyboard::Return)
                {
                    if(index_Menu==0)
                    {
                        state=GAME;
                        loadResources();
                    }
                    if(index_Menu==1)
                    {
                        mainWindow.close();
                    }
                }
            }
        }
    if(state == GAME)
        {
        if (isPressed){
            if (key == sf::Keyboard::W || key == sf::Keyboard::Up){
                move(0);
                }
            else if (key == sf::Keyboard::S || key == sf::Keyboard::Down){
                move(1);
                }
            else if (key == sf::Keyboard::A || key == sf::Keyboard::Left){
                move(2);
                }
            else if (key == sf::Keyboard::D || key == sf::Keyboard::Right){
                move(3);
                }
        }

        }

}

void game::move(int route){
    switch (route) {
    case 0:
        hero.loadFromFile(path_to_resources+"Bomzh-back.png");
        for (int i = 0; i < 16; i++){
        hero_position.y -= 4;
        render();
        }
        break;

    case 1:
        hero.loadFromFile(path_to_resources+"Bomzh-main.png");
        for (int i = 0; i < 16; i++){
            hero_position.y += 4;
            render();
        }
        break;

    case 2:
        hero.loadFromFile(path_to_resources+"Bomzh-left.png");
        for (int i = 0; i < 16; i++){
        hero_position.x -= 4;
        render();
        }
        break;

    case 3:
        hero.loadFromFile(path_to_resources+"Bomzh.png");
        for (int i = 0; i < 16; i++){
        hero_position.x += 4;
        render();
        }
        break;
    default:
        break;
    }
}
