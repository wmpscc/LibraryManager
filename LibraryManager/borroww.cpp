#include "borroww.h"
#include "ui_borroww.h"
#include"cglobal.h"
#include"bookdata.h"
#include <qpainter.h>
#include <QDateTime>
#include <QMessageBox>
#include <QStandardItemModel>
BorrowW::BorrowW(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BorrowW)
{
    ui->setupUi(this);
    ui->button_search_reader_id->setFlat(true);
    ui->button_search_reader_id->setIcon(QIcon(":/icon/查找长.png"));
    ui->button_search_reader_id->setIconSize(QSize(250,30));

    ui->button_search_book_id->setFlat(true);
    ui->button_search_book_id->setIcon(QIcon(":/icon/查找中.png"));
    ui->button_search_book_id->setIconSize(QSize(75,30));

    ui->pushButton_2->setFlat(true);
    ui->pushButton_2->setIcon(QIcon(":/icon/借出.png"));
    ui->pushButton_2->setIconSize(QSize(210,79));

}

BorrowW::~BorrowW()
{
    delete ui;
}
void BorrowW::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.drawPixmap(0,0,width(), height(), QPixmap(":/icon/b4.png"));
}

void BorrowW::update_lend_history(ReaderInfoD *p){
    ui->tableView->verticalHeader()->hide();
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
    ui->tableView->setModel(model);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setShowGrid(true);

}

void BorrowW::on_button_search_reader_id_clicked()
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
    user = r[result];   // 为其他函数准备

    ui->label_reader_name->setText(QString::fromLocal8Bit(r[result]->readerName));
    ui->label_reader_phone_num->setText(tr("%1").arg(r[result]->phoneNum));
    ui->label_reader_role->setText(QString::fromLocal8Bit(r[result]->readerRole));
    ui->label_create_date->setText(tr("%1").arg(r[result]->createDate));
    ui->label_allow_num->setText(tr("%1").arg(r[result]->allowBookNum));
    ui->label_lend_num->setText(tr("%1").arg(r[result]->hasLentBookNum));

    update_lend_history(r[result]);
}



void BorrowW::on_button_search_book_id_clicked()
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
    ui->label_book_seek_num->setText(QString::fromLocal8Bit(r[result]->accessNumber));
    ui->label_press_name->setText(QString::fromLocal8Bit(r[result]->pressName));
    ui->label_current_storage->setText(tr("%1").arg(r[result]->currStorage));
    ui->label_total_storage->setText(tr("%1").arg(r[result]->totalStorage));

}

bool check_overdue(BorrowRecord *p){
    long currTime = 0;
    QDateTime time = QDateTime::currentDateTime();   //获取当前时间
    currTime = time.toString("yyyyMMdd").toLong();   //将当前时间转为时间戳(年月日)
    while(p){
        if(p->rebackDate < 0){  // 还未归还
            if(currTime - p->lendDate > 30) //借书时间超过一个月
                return true;
        }
        p = p->next;
    }
    return false;
}

void BorrowW::on_pushButton_2_clicked()
{
    // 判断是否已经查找了信息
    if(user == NULL){
        QMessageBox::information(this, "错误", "请先查找读者信息，再操作");
        return;
    }
    if(target_book == NULL){
        QMessageBox::information(this, "错误", "请先查找图书信息，再操作");
        return;
    }
    // 判断是否允许借出
    if(user->allowBookNum - user->hasLentBookNum <= 0){
        QMessageBox::information(this, "错误", "已达到最大借书量，请归还图书再操作");
        return;
    }
    if(target_book->currStorage <= 0){
        QMessageBox::information(this, "错误", "该书暂时已全部借出，现存量为0");
        return;
    }
    if(check_overdue(user->borrowRecord)){
        QMessageBox::information(this, "错误", "请归还过期图书再操作！");
        return;
    }
    // 借出操作

    BorrowRecord *temp = (BorrowRecord *)malloc(sizeof(BorrowRecord));
    QDateTime time = QDateTime::currentDateTime();   //获取当前时间
    temp->lendDate = time.toString("yyyyMMdd").toLong();
    temp->bookDetail = target_book;
    temp->next = NULL;
    temp->rebackDate = -1;

    BorrowRecord *br = user->borrowRecord;
    if(br == NULL){
        user->borrowRecord = temp;
    }else{
        while(br->next)
            br = br->next;
        br->next = temp;
    }
    target_book->currStorage--;
    user->hasLentBookNum++;
    QMessageBox::information(this, "成功", tr("读者ID：%1，成功借出《%2》").arg(user->readerID).arg(QString::fromLocal8Bit(target_book->bookName)));
}
