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
    server_status = 0;
}


void MainWindow::on_start_clicked() {
    tcpServer = new QTcpServer(this);
    connect(tcpServer, SIGNAL(newConnection()), this, SLOT (new_user()));
    if(!tcpServer->listen(QHostAddress::LocalHost, 1488) && server_status == 0) {
        qDebug() << QObject::tr("Unnable to start the server: %1.").arg(tcpServer->errorString());
        ui->textBrowser->append(tcpServer->errorString());
    }
    else {
        server_status = 1;
        qDebug() << tcpServer->isListening() << "TCPSocket listen on port";
        ui->textBrowser->append("Server started");
        qDebug() << "Server started";
    }
}

void MainWindow::on_stop_clicked(){
    if(server_status == 1){
        foreach (int i, SClients.keys()) {
            QTextStream os(SClients[i]);
            os.setAutoDetectUnicode(true);
            os << QDate::currentDate().toString() << "\n";
            SClients[i]->close();
            SClients.remove(i);
        }
    }
    tcpServer->close();
    ui->textBrowser->append("Server stoped");
    qDebug() << "Server stoped";
    server_status = 0;
}

void MainWindow::new_user(){
    if (server_status == 1){

        qDebug() << "New connection";
        ui->textBrowser->append("New connection");
        QTcpSocket* clientSocket = tcpServer->nextPendingConnection();
        int ID_user_socket = clientSocket->socketDescriptor();
        SClients[ID_user_socket] = clientSocket;
        connect(SClients[ID_user_socket], SIGNAL(readyRead()), this, SLOT(slotReadClient()));
    }

}

void MainWindow::slotReadClient(){
    QTcpSocket* clientSocket = (QTcpSocket*) sender();
    int ID_user_socket = clientSocket->socketDescriptor();
    //ui->textBrowser->append(QString::fromUtf8("Read clien: "+clientSocket->readAll()+"\r\n"));
    QByteArray position = clientSocket->readAll();
    QDataStream in(&position, QIODevice::ReadOnly);
    float position_x, position_y;
    in >> position_x >> position_y;
    qDebug() << position_y << " " << position_x;
    hero_position her;
    her.x = position_x;
    her.y = position_y;
    list_her_pos.insert(ID_user_socket, her);
//    qDebug() << list_her_pos.lastKey();
//    ui->textBrowser->append(position_x);

}

void MainWindow::hero_move(){

}

void MainWindow::sendPositions()
{
    QByteArray unit_positions;
    QDataStream out(&unit_positions, QIODevice::WriteOnly);
    out << (int)list_her_pos.count();
    QMap<int, hero_position>::const_iterator i = list_her_pos.constBegin();
    while (i != list_her_pos.constEnd()) {
        out << (float)i.value().x << (float)i.value().y;
        //qDebug() << i.value().x;
        i++;
    }
    QMap<int, QTcpSocket*>::const_iterator j = SClients.constBegin();
    while (j != SClients.constEnd()) {
        j.value()->write(unit_positions);
        //qDebug() << "jkey: " << j.key();
        j++;
    }
    clientSocket.waitForBytesWritten();
}

void MainWindow::on_pushButton_clicked()
{
    QMap<int, hero_position>::const_iterator i = list_her_pos.constBegin();
    while (i != list_her_pos.constEnd()) {
//        qDebug() << i.key() << ":" << i.value().x << " " << i.value().y;
        i++;
    }
    qDebug() << SClients.count();
//    sendPositions();
//    for(int i =0; i < list_her_pos.size(); i++){
//        qDebug() << list_her_pos.operator [](list_her_pos.firstKey()+i);
//    }
}

