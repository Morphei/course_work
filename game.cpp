#include "game.h"

using namespace sf;
game::game()
    : mainWindow(VideoMode(800,600), "GameName")
{

}

void game::run()
{
    while(mainWindow.isOpen())
    {
        processEvents();
        update();
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
    }
}

void game::update()
{

}

void game::render()
{

}
