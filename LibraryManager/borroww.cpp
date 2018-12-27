#include "borroww.h"
#include "ui_borroww.h"

BorrowW::BorrowW(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BorrowW)
{
    ui->setupUi(this);
}

BorrowW::~BorrowW()
{
    delete ui;
}
