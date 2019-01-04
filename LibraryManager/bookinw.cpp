#include "bookinw.h"
#include "ui_bookinw.h"
#include "bookdata.h"
#include <QMessageBox>
#include <QString>
#include <QTextCodec>
#include "cglobal.h"
#include <qpainter.h>
BookInW::BookInW(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BookInW)
{
    ui->setupUi(this);
    ui->pushButton->setFlat(true);
    ui->pushButton->setIcon(QIcon(":/icon/入库.png"));
    ui->pushButton->setIconSize(QSize(150,50));

    ui->pushButton_2->setFlat(true);
    ui->pushButton_2->setIcon(QIcon(":/icon/修改.png"));
    ui->pushButton_2->setIconSize(QSize(150,50));

    ui->pushButton_3->setFlat(true);
    ui->pushButton_3->setIcon(QIcon(":/icon/删除记录.png"));
    ui->pushButton_3->setIconSize(QSize(150,50));

    ui->button_search_book->setFlat(true);
    ui->button_search_book->setIcon(QIcon(":/icon/搜索.png"));
    ui->button_search_book->setIconSize(QSize(75,30));
}

BookInW::~BookInW()
{
    delete ui;
}
void BookInW::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.drawPixmap(0,0,width(), height(), QPixmap(":/icon/b2.png"));
}


void BookInW::on_pushButton_released()
{
    ui->le_book_id->setText(tr("%1").arg(book_id_s++));

    BookDetailD *bookDetail, *p;
    bookDetail = (BookDetailD *)malloc(sizeof(BookDetailD));
    bookDetail->bookID = ui->le_book_id->text().toLong();

    bookDetail->bookName = stringCopy(ui->le_book_name->text());

    bookDetail->currStorage = ui->le_book_curr_num->text().toInt();
    bookDetail->pagesNumber = ui->le_book_pages_num->text().toInt();

    bookDetail->accessNumber = stringCopy(ui->le_book_seek_number->text());

    bookDetail->standardCode = stringCopy(ui->le_book_std_code->text());
    bookDetail->totalStorage = ui->le_book_total_num->text().toInt();

    bookDetail->authorName =stringCopy(ui->le_book_author->text());
    bookDetail->pressDate = ui->le_book_press_date->text().toLong();

    bookDetail->pressName = stringCopy(ui->le_book_press->text());
    bookDetail->next = NULL;

    p = bd_head_s;
    if(p == NULL){
        bd_head_s = bookDetail;
        p = bd_head_s;
        p->next = NULL;
    }
    else{
        while(p->next != NULL){
            p = p->next;
        }
        p->next = bookDetail;
        p = p->next;
        p->next = NULL;
    }

    QMessageBox::information(this, "成功", tr("《%1》,bookid:%2\n%3").arg(QString::fromLocal8Bit(p->bookName)).arg(p->bookID).arg("成功写入!"));

}

void BookInW::on_button_search_book_clicked()
{
    int total = 0;
    BookDetailD *p = bd_head_s;
    while(p){
        total++;
        p = p->next;
    }
    BookDetailD *(*r) = (BookDetailD* *)malloc(sizeof (BookDetailD) * total);
    p = bd_head_s;
    for(int i = 0; i < total; ++i){
        r[i] = p;
        p = p->next;
    }
    int result = BinarySearch_book(r, total, ui->le_book_id_2->text().toLong());
    if(result == -1){
        QMessageBox::information(this, "错误", "未找到该成员！");
        return;
    }
    target_book = r[result];
    ui->le_book_id->setText(tr("%1").arg(target_book->bookID));
    ui->le_book_name->setText(QString::fromLocal8Bit(target_book->bookName));
    ui->le_book_author->setText(QString::fromLocal8Bit(target_book->authorName));
    ui->le_book_seek_number->setText(tr("%1").arg(target_book->accessNumber));
    ui->le_book_curr_num->setText(tr("%1").arg(target_book->currStorage));
    ui->le_book_total_num->setText(tr("%1").arg(target_book->totalStorage));
    ui->le_book_press->setText(QString::fromLocal8Bit(target_book->pressName));
    ui->le_book_press_date->setText(tr("%1").arg(target_book->pressDate));
    ui->le_book_pages_num->setText(tr("%1").arg(target_book->pagesNumber));
    ui->le_book_std_code->setText(QString::fromLocal8Bit(target_book->standardCode));


}

void BookInW::on_pushButton_2_clicked()
{
    if(target_book == NULL){
        QMessageBox::information(this, "错误", "请先查找记录！");
        return;
    }

    target_book->bookID = ui->le_book_id->text().toLong();

    target_book->bookName = stringCopy(ui->le_book_name->text());

    target_book->currStorage = ui->le_book_curr_num->text().toInt();
    target_book->pagesNumber = ui->le_book_pages_num->text().toInt();

    target_book->accessNumber = stringCopy(ui->le_book_seek_number->text());

    target_book->standardCode = stringCopy(ui->le_book_std_code->text());
    target_book->totalStorage = ui->le_book_total_num->text().toInt();

    target_book->authorName = stringCopy(ui->le_book_author->text());
    target_book->pressDate = ui->le_book_press_date->text().toLong();

    target_book->pressName = stringCopy(ui->le_book_press->text());
    QMessageBox::information(this, "成功", "修改成功!");
}

void BookInW::on_pushButton_3_clicked()
{
    BookDetailD *p = bd_head_s;
    BookDetailD *last = NULL;
    while(p!=target_book){
        last = p;
        p = p->next;
    }
    last->next = p->next;
    free(p);
    QMessageBox::information(this, "成功", "删除成功!");
}
