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

void MainWindow::on_pushButton_clicked()
{
    searchWindow = new SearchW();
    searchWindow->show();
}

void MainWindow::on_pushButton_4_clicked()
{
    borrowWindow = new BorrowW;
    borrowWindow->show();
}

void MainWindow::on_pushButton_2_clicked()
{
    bookInStorageWindow = new BookInW();
    bookInStorageWindow->show();
}

void MainWindow::on_pushButton_6_clicked()
{
    searchResultWindow = new SearchResultW();
    searchResultWindow->show();
}

void MainWindow::on_pushButton_5_clicked()
{
    bookBackWindow = new BookBackW();
    bookBackWindow->show();
}
