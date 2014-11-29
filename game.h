#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>

class game
{
public:
    game();
    void run();

private:
    void processEvents();
    void update();
    void render();

private:
    sf::RenderWindow mainWindow;
};

#endif // GAME_H
