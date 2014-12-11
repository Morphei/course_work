#include "game.h"


using namespace sf;

//0 - background
//1 - flower
//2 - tree 1 position
//3 - tree 1 position (transparent)
//4 - tree 2 position
//5 - tree 2 position (transparent)
//6 - road
int scene[10][14] {  2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 2,
                    -1,-1, 0, 0,-1,-1, 0, 2,-1,-1, 0, 0, 0,-1,
                     2, 0, 0, 0, 0, 0, 0,-1,-1, 1, 2, 0, 0, 0,
                    -1,-1, 0, 1, 0, 0, 0, 0, 0, 0,-1, 2, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1,-1, 0,
                     0, 0, 0, 2, 0, 2, 2, 0, 2, 2, 0, 0, 0, 0,
                     0, 0, 2, 2, 2, 2, 2, 2, 2,-1,-1, 0, 0, 0,
                     0, 0,-1,-1,-1,-1,-1, 2, 0, 2, 0, 2, 0, 0,
                     0, 0, 2, 0, 2, 0, 2,-1,-1,-1,-1,-1,-1, 0,
                     2, 0,-1,-1,-1,-1,-1,-1, 0, 0, 0, 0, 0, 1
//                     0,0,0,0,0,0,0,0,0,0,0,0,0,0,
//                     0,0,0,0,0,0,0,0,0,0,0,0,0,0,
//                     0,0,0,0,0,0,0,0,0,0,0,0,0,0,
//                     0,0,0,0,0,0,0,0,0,0,0,0,0,0,
//                     0,0,0,0,0,0,0,0,0,0,0,0,0,0,
//                     0,0,0,0,0,0,0,0,0,0,0,0,0,0,
//                     0,0,0,0,0,0,0,0,0,0,0,0,0,0,
//                     0,0,0,0,0,0,0,0,0,0,0,0,0,0,
//                     0,0,0,0,0,0,0,0,0,0,0,0,0,0,
//                     0,0,0,0,0,0,0,0,0,0,0,0,0,0
                                                };

game::game(bool g_state)
    : mainWindow(VideoMode(/*1024,768*/896,640), "Greenwood v.0.01")
{
    port = 1488;
    animation_pos_timer=0;
    animation_pos = 2;
//    path_to_resources = "/home/hkitty/course_work/resources/";
    path_to_resources = "/home/morphei/course_work/course_work/client/resources/";
    framesWindow.x = 10;
    framesWindow.y = 14;
    TimePerFrame = seconds(1.f/60.f);
    hero_position.x = 128;
    hero_position.y = 128;

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
    timeSinceLastUpdate = sf::Time::Zero;
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
            mainWindow.setKeyRepeatEnabled(false);
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
    //readUnitPositions();
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
    int x,y;
    y = hero_position.x/64;
    x = hero_position.y/64;
    //qDebug()<< x << "-" << y << "scene:" << scene[x][y];
        //Drawing background
        for(int i = 0; i < window_height; i++)
            for(int j = 0; j < window_width; j++)
            {
                background_position.x=0+i*128;
                background_position.y=0+j*128;
                sprites.at(0).setPosition(background_position);
                mainWindow.draw(sprites.at(0));
            }
        for(int i = 0; i < framesWindow.x; i++)
            for(int j = 0; j < framesWindow.y; j++)
            {
                if(scene[i][j]!=2&&scene[i][j]!=-1&&scene[i][j]!=0)
                {
                object_position.x = 0 + j*64;
                object_position.y = 0 + i*64;
                sprites.at(scene[i][j]).setPosition(object_position);
                mainWindow.draw(sprites.at(scene[i][j]));
                }

            }
        //Drawing hero

        hero_sprite.setPosition(hero_position.x, hero_position.y);
        mainWindow.draw(hero_sprite);

        for(int i = 0; i < count_users; i++){
            hero_position.x = v_units_positions.at(i).x;
            //hero_position.x /= 64;
            hero_position.y = v_units_positions.at(i).y;
            //hero_position.y /= 64;
            hero_sprite.setPosition(hero_position);
            mainWindow.draw(hero_sprite);
        }
        //Drawing objects
        for(int i = 0; i < framesWindow.x; i++)
            for(int j = 0; j < framesWindow.y; j++)
            {
                if(scene[i][j]==2)
                {
                object_position.x = 0 + j*64;
                object_position.y = 0 + i*64;   
                sprites.at(animation_pos).setPosition(object_position);
                mainWindow.draw(sprites.at(animation_pos));
                animation_pos_timer++;
                if(animation_pos_timer==1000)
                {
                    animation_pos++;
                    animation_pos_timer=0;
                }
                if(animation_pos==4)
                {
                animation_pos=2;
                }
                //qDebug() << timeSinceLastUpdate.asSeconds() << "  ";
                //qDebug() << animation_pos;
                }
            }

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
        Texture tree,road,flower, tree_2, tree_tr, tree_2_tr;
        textures.at(0).loadFromFile(path_to_resources+"grass_background.jpg");
        flower.loadFromFile(path_to_resources+"obj_01.png");
        tree.loadFromFile(path_to_resources+"obj_03.png");
        road.loadFromFile(path_to_resources+"obj_04.png");
        tree_2.loadFromFile(path_to_resources+"obj_03_01.png");
        tree_tr.loadFromFile(path_to_resources+"obj_03_tr.png");
        tree_2_tr.loadFromFile(path_to_resources+"obj_03_01_tr.png");
        textures.push_back(flower);
        textures.push_back(tree);
        textures.push_back(tree_tr);
        textures.push_back(tree_2);
        textures.push_back(tree_2_tr);
        textures.push_back(road);
        Sprite tree_sp,way_sp,flower_sp, tree_sp_2, tree_sp_tr, tree_sp_2_tr;
        sprites.at(0).setTexture(textures.at(0));
        flower_sp.setTexture(textures.at(1));
        tree_sp.setTexture(textures.at(2));
        tree_sp_tr.setTexture(textures.at(3));
        tree_sp_2.setTexture(textures.at(4));
        tree_sp_2_tr.setTexture(textures.at(5));
        way_sp.setTexture(textures.at(6));
        sprites.push_back(flower_sp);
        sprites.push_back(tree_sp);
        sprites.push_back(tree_sp_2);
        sprites.push_back(tree_sp_tr);
        sprites.push_back(tree_sp_2_tr);
        sprites.push_back(way_sp);
        hero.loadFromFile(path_to_resources+"Bomzh_02.png");
        hero_sprite.setTexture(hero);
    }
}

void game::handlePlayerInput(Keyboard::Key key, bool isPressed)
{
    if(state == MAIN_MENU)
        {
        if(isPressed)
            {
            if(key == Keyboard::W||key == Keyboard::Up)
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
                        connect();
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
    if(state == GAME){
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
        hero.loadFromFile(path_to_resources+"Bomzh-back_02.png");
        if (hero_position.y/64>0){
        for (int i = 0; i < 16; i++){
        hero_position.y -= 4;
        render();
        }
        }
        break;

    case 1:
        hero.loadFromFile(path_to_resources+"Bomzh-main_02.png");
        if (hero_position.y/64 < 9){
        for (int i = 0; i < 16; i++){
            hero_position.y += 4;
            render();
        }
        }
        break;

    case 2:
        hero.loadFromFile(path_to_resources+"Bomzh-left_02.png");
        if (hero_position.x/64 > 0){
        for (int i = 0; i < 16; i++){
        hero_position.x -= 4;
        render();
        }
        }
        break;

    case 3:
        hero.loadFromFile(path_to_resources+"Bomzh_02.png");
        if (hero_position.x/64 < 13){
        for (int i = 0; i < 16; i++){
        hero_position.x += 4;
        render();
        }
        }
        break;
    default:
        break;
    }
    qDebug() << hero_position.x << " : " << hero_position.y << "after move";
    sendPosition();
    readUnitPositions();
}

void game::connect(){
    socket = new TcpSocket;
    socket->connect("127.0.0.1", port);
    sendPosition();
    readUnitPositions();

//    out << hero_position.x;
//    QByteArray position_y;
//    socket->write(position_x);
//    socket->waitForBytesWritten();
//    socket->write(position_y);
//    socket->waitForBytesWritten();
    /*sf::Socket::Status status = socket.connect("127.0.0.1", port);
    if (status != sf::Socket::Done)
    {
        //Error
        qDebug() << "not connection";
    }
    std::string sSend = "hkitty";
    sf::Packet Nickname;
    Nickname << "hkitty";
    socket.send(Nickname);
    socket.send("hkitty", NULL);*/


//    sf::Packet packet_boss;
//    packet_boss << "16";
//    packet_boss << hero_position.y;
//    socket->send(packet_boss);
}

void game::sendPosition(){
    QByteArray position;
    QDataStream out(&position, QIODevice::WriteOnly);
    out << (float)hero_position.x;
    out << (float)hero_position.y;

    socket->write(position);
    //qDebug() << hero_position.x;
    socket->waitForBytesWritten();
    qDebug() << hero_position.x << " : " << hero_position.y << "after sending";
}

void game::readUnitPositions()
{
    qDebug() << "Entered read func";
    //socket->state().
    //socket->stateChanged();
    QByteArray unit_positions = socket->readAll();
    QDataStream in(&unit_positions, QIODevice::ReadOnly);
    in >> count_users;
    qDebug() << count_users;
    for (int i = 0;i < 1/*count_users*/; i++){
        in >> u_pos.x;
        in >> u_pos.y;
        v_units_positions.push_back(u_pos);
                qDebug() << u_pos.x << ":" << u_pos.y << "after reading position from server";
    }
}


