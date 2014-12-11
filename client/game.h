#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include <QDebug>
#include <QTcpSocket>
#include <iostream>
#include <SFML/Network.hpp>

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
    void move(int route);
    void connect();
    void sendPosition();
    void readUnitPositions();

private:
    struct units_positions{
        float x;
        float y;
    };
    sf::TcpSocket *socket;
    std::vector<units_positions> v_units_positions;
    units_positions u_pos;
    sf::Clock clock;
    sf::String path_to_resources;
    sf::Vector2i framesWindow;
    sf::Time TimePerFrame, timeSinceLastUpdate;
    int index_Menu, animation_pos, animation_pos_timer;
    enum game_state {MAIN_MENU, GAME};
    int port;
    //sf::TcpSocket socket;
    game_state state;
    sf::Vector2f background_position, object_position;
    int window_height, window_width;
    sf::RenderWindow mainWindow;
    std::vector<sf::Text> m_options;
    std::vector<sf::Sprite> sprites;
    std::vector<sf::Texture> textures;
    //====================
    sf::Texture hero;
    sf::Sprite hero_sprite;
    sf::Vector2f hero_position;
    //====================
    sf::Text playOption, exitOption;
    sf::Font mainFont;

private:
    int count_users;
};

#endif // GAME_H
