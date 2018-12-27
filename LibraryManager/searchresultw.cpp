#include "searchresultw.h"
#include "ui_searchresultw.h"

SearchResultW::SearchResultW(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SearchResultW)
{
    ui->setupUi(this);

}

SearchResultW::~SearchResultW()
{
    delete ui;
}
