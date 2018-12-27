#include "bookinw.h"
#include "ui_bookinw.h"

BookInW::BookInW(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BookInW)
{
    ui->setupUi(this);
}

BookInW::~BookInW()
{
    delete ui;
}
