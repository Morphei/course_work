#include "server.h"
#include "iostream"
#include <QDebug>

Server::Server()
{
}

void Server::start()
{
    listener.listen(1488);
    selector.add(listener);
    started = true;
    int i = 0;
    while(started)
    {
        qDebug() << "Entered";
        if(selector.wait())
        {
            qDebug() << "Entered wait";
            if(selector.isReady(listener))
            {
                sf::TcpSocket* client = new sf::TcpSocket;
                if (listener.accept(*client) == sf::Socket::Done)
               {
               // Add the new client to the clients list
               clients.push_back(client);
               // Add the new client to the selector so that we will
               // be notified when he sends something
               selector.add(*client);
               }
               else
               {
               // Error, we won't get a new connection, delete the socket
               delete client;
               }
            qDebug() << "Entered isReady";
            }
            else
            {
           // The listener socket is not ready, test all other sockets (the clients)
                qDebug() << "Test all other sockets";
               for (std::list<sf::TcpSocket*>::iterator it = clients.begin(); it != clients.end(); ++it)
               {
                   sf::TcpSocket& client = **it;
                   if (selector.isReady(client))
                   {
                       // The client has sent some data, we can receive it
                       sf::Packet packet;
                       if (client.receive(packet) == sf::Socket::Done)
                           {
                           //...
                           }
                   }
               }
           }
        }
    i++;
    std::cout << i;
    }
}

void Server::stop()
{
    started = 0;
    listener.close();
    selector.clear();
    for (std::list<sf::TcpSocket*>::iterator it = clients.begin(); it != clients.end(); ++it)
    {
        sf::TcpSocket& client = **it;
        client.disconnect();
    }
}
