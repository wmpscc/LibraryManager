#include "searchw.h"
#include "ui_searchw.h"
#include "QMessageBox"
#include <cstring>
#include <QTextCodec>
#include"cglobal.h"
#include <qpainter.h>
#include<searchresultw.h>

SearchW::SearchW(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SearchW)
{
    ui->setupUi(this);
    ui->button_query->setFlat(true);
    ui->button_query->setIcon(QIcon(":/icon/查询.png"));
    ui->button_query->setIconSize(QSize(400,60));


}

SearchW::~SearchW()
{
    delete ui;
}

void SearchW::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.drawPixmap(0,0,width(), height(), QPixmap(":/icon/b6.png"));
}

void SearchW::on_button_query_clicked()
{
    SearchResultW *searchResultWindow = new SearchResultW(this);
    connect(this, SIGNAL(sendData(QString, int)), searchResultWindow, SLOT(receiveData(QString, int)));

    if(!ui->edit_id_search->text().isEmpty()){
        emit sendData(ui->edit_id_search->text(), 0);
    }
    else if(!ui->edit_book_name_first->text().isEmpty())
        emit sendData(ui->edit_book_name_first->text(), 1);
    else if(!ui->edit_press_first->text().isEmpty())
        emit sendData(ui->edit_press_first->text(), 2);
    else if(!ui->edit_author_first->text().isEmpty())
        emit sendData(ui->edit_author_first->text(), 3);

    searchResultWindow->show();

    //    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));
    //    QByteArray ba = searchTitle.toLocal8Bit();
    //    char *ch = ba.data();
    //    char out[20];
    //    get_pinyin_first_letter(ch, strlen(ch), out);

    //    QString str2;
    //    QMessageBox::information(this, "Tips", "end");

}
