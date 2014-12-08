#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_connectButton_clicked()
{
    sf::TcpSocket socket;
    sf::Socket::Status status = socket.connect("127.0.0.1", 1488);
    if (status != sf::Socket::Done)
    {
    socket.send(hero_position);
    }
}
