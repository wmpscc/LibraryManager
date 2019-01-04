#include "readerinfow.h"
#include "ui_readerinfow.h"
#include "bookdata.h"
#include "cglobal.h"
#include <qpainter.h>
#include <QMessageBox>

ReaderInfoW::ReaderInfoW(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ReaderInfoW)
{
    ui->setupUi(this);
    ui->pushButton->setFlat(true);
    ui->pushButton->setIcon(QIcon(":/icon/保存.png"));
    ui->pushButton->setIconSize(QSize(250,60));

}

ReaderInfoW::~ReaderInfoW()
{
    delete ui;
}
void ReaderInfoW::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.drawPixmap(0,0,width(), height(), QPixmap(":/icon/b5.png"));
}

void ReaderInfoW::on_pushButton_released()
{

    ui->le_reader_id->setText(tr("%1").arg(reader_id++));
    ReaderInfoD *readerInfo = (ReaderInfoD *)malloc(sizeof (ReaderInfoD));
    readerInfo->allowBookNum = ui->le_allow_book_num->text().toInt();
    readerInfo->createDate = ui->le_create_date->text().toLong();
    readerInfo->hasLentBookNum = ui->le_has_lent_num->text().toInt();
    readerInfo->phoneNum = ui->le_phone_number->text().toLong();
    readerInfo->readerID = ui->le_reader_id->text().toLong();
    readerInfo->readerName = stringCopy(ui->le_reader_name->text());
    readerInfo->readerRole = stringCopy(ui->le_reader_role->text());
    readerInfo->borrowRecord = NULL;

    ReaderInfoD *p = readerIndoHead;
    if(p == NULL){
        readerIndoHead = readerInfo;
        p = readerIndoHead;
        p->next = NULL;
    }else{
        while (p->next != NULL) {
            p = p->next;
        }
        p->next = readerInfo;
        p = p->next;
        p->next = NULL;
    }

    QMessageBox::information(this, "成功", tr("姓名：%1\n%2").arg(QString::fromLocal8Bit(p->readerName)).arg("成功写入!"));

}

