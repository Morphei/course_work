#ifndef SERVER_H
#define SERVER_H
#include <stdlib.h>
#include <SFML/Network.hpp>
#include <QList>

class Server
{
public:
    Server();
    void start();
    void stop();

public:
    bool started;
    sf::TcpListener listener;
    std::list<sf::TcpSocket*> clients;
    sf::SocketSelector selector;

};

#endif // SERVER_H
