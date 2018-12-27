#include "searchw.h"
#include "ui_searchw.h"
#include "QMessageBox"
SearchW::SearchW(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SearchW)
{
    ui->setupUi(this);
}

SearchW::~SearchW()
{
    delete ui;
}

void SearchW::on_button_query_clicked()
{
    QString searchTitle = "";
    if(!ui->edit_id_search->text().isEmpty())
        searchTitle = ui->edit_id_search->text();
    else if(!ui->edit_book_name_first->text().isEmpty())
        searchTitle = ui->edit_book_name_first->text();
    else if(!ui->edit_author_first->text().isEmpty())
        searchTitle = ui->edit_author_first->text();
    else if(!ui->edit_press_first->text().isEmpty())
        searchTitle = ui->edit_press_first->text();
    QMessageBox::information(this, "Tips", searchTitle);

}
