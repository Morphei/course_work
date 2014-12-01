#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>

class game
{
public:
    game(bool g_state);
    void run();

private:
    void processEvents();
    void update(sf::Time TimePerFrame);
    void render();
    void loadResources();
    void handlePlayerInput(sf::Keyboard::Key key,bool isPressed);

private:
    sf::Time TimePerFrame;
    int index_Menu;
    enum game_state {MAIN_MENU, GAME};
    game_state state;
    sf::Vector2f background_position;
    int window_height, window_width;
    sf::RenderWindow mainWindow;
    sf::Texture background;
    sf::Sprite background_sprite;
    std::vector<sf::Text> m_options;
    sf::Text playOption, exitOption;
    sf::Font mainFont;
};

#endif // GAME_H
