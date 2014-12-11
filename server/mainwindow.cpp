#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <server.h>

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

void MainWindow::on_pushButton_clicked()
{
    server.start();
    ui->textBrowser->append("Server started");
}

void MainWindow::on_pushButton_2_clicked()
{
    server.started = 0;
    server.stop();
}
