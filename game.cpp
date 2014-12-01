#include "game.h"
#include <QDebug>
using namespace sf;
game::game(bool g_state)
    : mainWindow(VideoMode(/*1024,768*/800,600), "GameName")
{
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

    if(!m_options.empty())
    {
        for(int i = 0; i <= m_options.size()-1; i++)
        {
            m_options.at(i).setColor(Color::Black);
            m_options.at(i).setScale(5,4);
        }
        m_options.operator [](index_Menu).setColor(Color::Red);
        m_options.operator [](index_Menu).setScale(6,4);
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

        background_sprite.setPosition(background_position);
        mainWindow.draw(background_sprite);
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
                background_position.x=0+j*128;
                background_position.y=0+i*128;
                background_sprite.setPosition(background_position);
                mainWindow.draw(background_sprite);
            }

    }
    mainWindow.display();
}

void game::loadResources()
{
    if(state == MAIN_MENU)
    {
        background.loadFromFile("/home/hkitty/Projects/Test/course_work/resources/main_background_800x600.jpg");
        //background.loadFromFile(":/Images/main_background_800x600.jpg");
        background_sprite.setTexture(background);
        mainFont.loadFromFile("/home/hkitty/Projects/Test/course_work/resources/GoodDog.otf");
        playOption.setFont(mainFont);
        playOption.setString("Play");
        playOption.setPosition(50,mainWindow.getSize().y/1.8);
        playOption.setScale(5,4);
        m_options.push_back(playOption);
        exitOption.setFont(mainFont);
        exitOption.setString("ExiT");
        exitOption.setPosition(50,mainWindow.getSize().y/1.8+120);
        exitOption.setScale(5,4);
        m_options.push_back(exitOption);
    }
    if(state == GAME)
    {
        window_height=mainWindow.getSize().x/128;
        window_width=mainWindow.getSize().y/128+3;
        background.loadFromFile("/home/hkitty/Projects/Test/course_work/resources/grass_background.jpg");
        background_sprite.setTexture(background);
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

        }

}
