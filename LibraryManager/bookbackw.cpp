#include "bookbackw.h"
#include "ui_bookbackw.h"

BookBackW::BookBackW(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BookBackW)
{
    ui->setupUi(this);
}

BookBackW::~BookBackW()
{
    delete ui;
}
