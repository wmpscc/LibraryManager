#include "bookbackw.h"
#include "ui_bookbackw.h"
#include "bookdata.h"
#include "cglobal.h"
#include <qpainter.h>
#include <QMessageBox>
#include <QDateTime>
BookBackW::BookBackW(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BookBackW)
{
    ui->setupUi(this);
    ui->button_search_reader_info->setFlat(true);
    ui->button_search_reader_info->setIcon(QIcon(":/icon/查找长.png"));
    ui->button_search_reader_info->setIconSize(QSize(250,30));

    ui->button_search_book_info->setFlat(true);
    ui->button_search_book_info->setIcon(QIcon(":/icon/查找中.png"));
    ui->button_search_book_info->setIconSize(QSize(75,30));

    ui->pushButton_2->setFlat(true);
    ui->pushButton_2->setIcon(QIcon(":/icon/归还.png"));
    ui->pushButton_2->setIconSize(QSize(210,79));

}

BookBackW::~BookBackW()
{
    delete ui;

}
void BookBackW::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.drawPixmap(0,0,width(), height(), QPixmap(":/icon/b3.png"));
}

void BookBackW::update_lend_history(ReaderInfoD *p){
    ui->tableView_2->verticalHeader()->hide();
    model = new QStandardItemModel();
    model->setColumnCount(12);
    model->setHeaderData(0, Qt::Horizontal, QStringLiteral("书号"));
    model->setHeaderData(1, Qt::Horizontal, QStringLiteral("书名"));
    model->setHeaderData(2, Qt::Horizontal, QStringLiteral("作者"));
    model->setHeaderData(3, Qt::Horizontal, QStringLiteral("页数"));
    model->setHeaderData(4, Qt::Horizontal, QStringLiteral("索取码"));
    model->setHeaderData(5, Qt::Horizontal, QStringLiteral("出版社"));
    model->setHeaderData(6, Qt::Horizontal, QStringLiteral("出版日期"));
    model->setHeaderData(7, Qt::Horizontal, QStringLiteral("标准编码"));
    model->setHeaderData(8, Qt::Horizontal, QStringLiteral("现存量"));
    model->setHeaderData(9, Qt::Horizontal, QStringLiteral("总库存"));
    model->setHeaderData(10, Qt::Horizontal, QStringLiteral("借出日期"));
    model->setHeaderData(11, Qt::Horizontal, QStringLiteral("归还日期"));
    BorrowRecord *record = p->borrowRecord;
    BookDetailD *temp;
    int row = 0;
    while(record){
        temp = record->bookDetail;
        item = new QStandardItem(tr("%1").arg(temp->bookID));
        model->setItem(row, 0, item);
        item = new QStandardItem(QString::fromLocal8Bit(temp->bookName));
        model->setItem(row, 1, item);
        item = new QStandardItem(QString::fromLocal8Bit(temp->authorName));
        model->setItem(row, 2, item);
        item = new QStandardItem(tr("%1").arg(temp->pagesNumber));
        model->setItem(row, 3, item);
        item = new QStandardItem(tr("%1").arg(temp->accessNumber));
        model->setItem(row, 4, item);
        item = new QStandardItem(QString::fromLocal8Bit(temp->pressName));
        model->setItem(row, 5, item);
        item = new QStandardItem(tr("%1").arg(temp->pressDate));
        model->setItem(row, 6, item);
        item = new QStandardItem(tr("%1").arg(temp->standardCode));
        model->setItem(row, 7, item);
        item = new QStandardItem(tr("%1").arg(temp->currStorage));
        model->setItem(row, 8, item);
        item = new QStandardItem(tr("%1").arg(temp->totalStorage));
        model->setItem(row, 9, item);

        item = new QStandardItem(tr("%1").arg(record->lendDate));
        model->setItem(row, 10, item);
        item = new QStandardItem(tr("%1").arg(record->rebackDate));
        model->setItem(row, 11, item);
        row++;
        record = record->next;
    }
    ui->tableView_2->setModel(model);
    ui->tableView_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView_2->setShowGrid(true);

}
void BookBackW::on_button_search_reader_info_clicked()
{
    // 查找读者信息
    int total = 0;
    ReaderInfoD *p = readerIndoHead;
    while (p) {
        total++;
        p = p->next;
    }
    ReaderInfoD *(*r) = (ReaderInfoD* *)malloc(sizeof(ReaderInfoD) * total);
    p = readerIndoHead;
    for(int i = 0; i < total; ++i){
        r[i] = p;
        p = p->next;
    }
    int result = BinarySearch(r, total, ui->le_reader_id->text().toLong());
    if(result == -1){
        QMessageBox::information(this, "错误", "未找到该成员！");
        return;
    }
    user = r[result];
    ui->label_reader_name->setText(QString::fromLocal8Bit(r[result]->readerName));
    ui->label_reader_phone_num->setText(tr("%1").arg(r[result]->phoneNum));
    ui->label_reader_role->setText(QString::fromLocal8Bit(r[result]->readerRole));
    ui->label_create_time->setText(tr("%1").arg(r[result]->createDate));
    ui->label_allow_num->setText(tr("%1").arg(r[result]->allowBookNum));
    ui->label_has_lent_num->setText(tr("%1").arg(r[result]->hasLentBookNum));

    update_lend_history(r[result]);
}

void BookBackW::on_button_search_book_info_clicked()
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
    int result = fibonacciSearch(r, total, ui->le_reader_id->text().toLong());
    if(result == -1){
        QMessageBox::information(this, "错误", "未找到该成员！");
        return;
    }
    target_book = r[result];

    ui->label_book_name->setText(QString::fromLocal8Bit(r[result]->bookName));
    ui->label_seek_num->setText(QString::fromLocal8Bit(r[result]->accessNumber));
    ui->label_press_name->setText(QString::fromLocal8Bit(r[result]->pressName));
    ui->label_current_storage->setText(tr("%1").arg(r[result]->currStorage));
    ui->label_total_storage->setText(tr("%1").arg(r[result]->totalStorage));


}

void BookBackW::on_pushButton_2_clicked()
{
    user->hasLentBookNum--;
    target_book->currStorage++;

    BorrowRecord *p = user->borrowRecord;
    QDateTime time = QDateTime::currentDateTime();   //获取当前时间
    while(p){
        if(p->bookDetail->bookID == target_book->bookID){
            p->rebackDate = time.toString("yyyyMMdd").toLong();
        }
        p = p->next;
    }
    QMessageBox::information(this, "提示", "还书成功!");

}

