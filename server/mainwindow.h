#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <QTcpSocket>
#include <QObject>
#include <QByteArray>
#include <QDebug>
#include <SFML/Network.hpp>
#include <QMap>

namespace Ui {
class MainWindow;
}

class QTcpServer;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    struct hero_position {
        float x,y;
    };
    QMap<int, hero_position> list_her_pos;
    //QMapIterator<int, hero_position> i(list_her_pos);
private slots:
    void on_start_clicked();
    void on_stop_clicked();
    void new_user();
    void slotReadClient();
    void hero_move();
    void sendPositions();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QTcpServer *tcpServer;
    int server_status;
    QMap<int, QTcpSocket *> SClients;
    QTcpSocket clientSocket;

};

#endif // MAINWINDOW_H
