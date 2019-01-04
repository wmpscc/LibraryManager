#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qpainter.h>
#include <QDateTime>
#include <QMessageBox>
#include <QCloseEvent>
#include "cglobal.h"
#include<stdio.h>
#include <stdlib.h>
#include <string.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButton->setFlat(true);
    ui->pushButton->setIcon(QIcon(":/icon/图书检索.png"));
    ui->pushButton->setIconSize(QSize(142,142));

    ui->pushButton_2->setFlat(true);
    ui->pushButton_2->setIcon(QIcon(":/icon/书籍入库.png"));
    ui->pushButton_2->setIconSize(QSize(142,142));

    ui->pushButton_4->setFlat(true);
    ui->pushButton_4->setIcon(QIcon(":/icon/图书借阅.png"));
    ui->pushButton_4->setIconSize(QSize(142,142));

    ui->pushButton_3->setFlat(true);
    ui->pushButton_3->setIcon(QIcon(":/icon/读者信息录入.png"));
    ui->pushButton_3->setIconSize(QSize(142,142));

    ui->pushButton_5->setFlat(true);
    ui->pushButton_5->setIcon(QIcon(":/icon/图书归还.png"));
    ui->pushButton_5->setIconSize(QSize(142,142));
//    restore_book_csv("book_info.csv");
}

MainWindow::~MainWindow()
{
    delete ui;
}

char *toChar(QString str){
    QByteArray ba = str.toLocal8Bit();
    return ba.data();
}

void MainWindow::save_book_csv(char *filename){


    FILE *fp;
    fp = fopen(filename, "w");

    fwrite(toChar(tr("书号,")), sizeof(char), strlen("书号,"), fp);
    fwrite(toChar(tr("书名,")), sizeof(char), strlen("书名,"), fp);
    fwrite(toChar(tr("作者,")), sizeof(char), strlen("作者,"), fp);
    fwrite(toChar(tr("索取号,")), sizeof(char), strlen("索取号,"), fp);
    fwrite(toChar(tr("现存量,")), sizeof(char), strlen("现存量,"), fp);
    fwrite(toChar(tr("总库存,")), sizeof(char), strlen("总库存,"), fp);
    fwrite(toChar(tr("出版社,")), sizeof(char), strlen("出版社,"), fp);
    fwrite(toChar(tr("出版日期,")), sizeof(char), strlen("出版日期,"), fp);
    fwrite(toChar(tr("页数,")), sizeof(char), strlen("页数,"), fp);
    fwrite(toChar(tr("标准码")), sizeof(char), strlen("标准码"), fp);
    fwrite("\n", 1, strlen("\n"), fp);
    BookDetailD *p = bd_head_s;
    char temp[100];
    while(p){

//        QString str = tr("%1,%2,%3,%4,%5,%6,%7,%8,%9,%10\n").arg(p->bookID).arg(p->bookName)
//                .arg(p->authorName).arg(p->accessNumber).arg(p->currStorage).arg(p->totalStorage)
//                .arg(p->pressName).arg(p->pressDate).arg(p->pagesNumber).arg(p->standardCode);
//        fwrite(str.toLocal8Bit(), 8, sizeof (str.toLocal8Bit()), fp);
//        QByteArray ba = str.toStdString();
//        fwrite(ba.data(), sizeof(ba.data()), 1, fp);

        sprintf(temp, "%ld", p->bookID);
        fwrite(temp, sizeof(char), stringLength(temp), fp);
        fwrite(",", sizeof(char), sizeof (","), fp);


        fwrite(p->bookName, 1, stringLength(p->bookName), fp);
        fwrite(",", sizeof(char), sizeof (","), fp);

        fwrite(p->authorName, 1, stringLength(p->authorName), fp);
        fwrite(",", sizeof(char), sizeof (","), fp);

        fwrite(p->accessNumber, 1, stringLength(p->accessNumber), fp);
        fwrite(",", sizeof(char), sizeof (","), fp);

        sprintf(temp, "%d", p->currStorage);
        fwrite(temp, sizeof(char), stringLength(temp), fp);
        fwrite(",", sizeof(char), sizeof (","), fp);

        sprintf(temp, "%d", p->totalStorage);
        fwrite(temp, sizeof(char), stringLength(temp), fp);
        fwrite(",", sizeof(char), sizeof (","), fp);

        fwrite(p->pressName, 1, stringLength(p->pressName), fp);
        fwrite(",", sizeof(char), sizeof (","), fp);

        sprintf(temp, "%ld", p->pressDate);
        fwrite(temp, sizeof(char), stringLength(temp), fp);
        fwrite(",", sizeof(char), sizeof (","), fp);

        sprintf(temp, "%d", p->pagesNumber);
        fwrite(temp, sizeof(char), stringLength(temp), fp);
        fwrite(",", sizeof(char), sizeof (","), fp);

        fwrite(p->standardCode, 1, stringLength(p->standardCode), fp);
        fwrite("\n", sizeof(char), sizeof ("\n"), fp);

        p = p->next;
    }


}

void MainWindow::restore_book_csv(char *filename){
    FILE *fp;
    fp = fopen(filename, "r");
    if(!fp){
        return;
    }
    QMessageBox::information(this, "提示", "正在从文件恢复数据!");
    char line[300];
    char *result = NULL;
    BookDetailD *bookDetail, *p;
    int i;  // 当前列数
    fgets(line, sizeof(line), fp);
    while(fgets(line, sizeof(line), fp) != NULL){
        result = strtok(line, ",");
        bookDetail = (BookDetailD *)malloc(sizeof(BookDetailD));
        i = 0;
        while (result != NULL) {
            switch (i++) {
            case 0:
                bookDetail->bookID = atol(result);
                if(bookDetail->bookID > book_id_s)
                    book_id_s = bookDetail->bookID;
                break;
            case 1:
//                QString s = QString::fromLatin1(stringCopy(result));
//                QByteArray ba = s.toLocal8Bit();
//                bookDetail->bookName = ba.data();
                break;
            case 2:
                bookDetail->authorName = stringCopy(result);
                break;
            case 3:
                bookDetail->accessNumber = stringCopy(result);
                break;
            case 4:
                bookDetail->currStorage = atoi(result);
                break;
            case 5:
                bookDetail->totalStorage = atoi(result);
                break;
            case 6:
                bookDetail->pressName = stringCopy(result);
                break;
            case 7:
                bookDetail->pressDate = atol(result);
                break;
            case 8:
                bookDetail->pagesNumber = atoi(result);
                break;
            case 9:
                bookDetail->standardCode = stringCopy(result);
                break;
            }
            result = strtok(NULL, ",");
        }

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
    }

}
void MainWindow::closeEvent(QCloseEvent *event){
    event->ignore();

//    save_book_csv("book_info.csv");
    event->accept();


}

void MainWindow::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.drawPixmap(0,0,width(), height(), QPixmap(":/icon/b1.png"));
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



void MainWindow::on_pushButton_5_clicked()
{
    bookBackWindow = new BookBackW();
    bookBackWindow->show();
}

void MainWindow::on_pushButton_3_clicked()
{
    readerInfoWindow = new ReaderInfoW();
    readerInfoWindow->show();
}

