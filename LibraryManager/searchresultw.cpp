#include "searchresultw.h"
#include "ui_searchresultw.h"
#include "bookdata.h"
#include <QMessageBox>
#include <QTextCodec>
#include <stdlib.h>
#include<cglobal.h>
#include<string.h>
#include <qpainter.h>
#include <QStandardItemModel>

SearchResultW::SearchResultW(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SearchResultW)
{
    ui->setupUi(this);
    ui->pushButton_2->setFlat(true);
    ui->pushButton_2->setIcon(QIcon(":/icon/仅显示可借图书.png"));
    ui->pushButton_2->setIconSize(QSize(200,50));

}

SearchResultW::~SearchResultW()
{
    delete ui;
}

void SearchResultW::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.drawPixmap(0,0,width(), height(), QPixmap(":/icon/b7.png"));
}

// ****************取中文拼音首字母****************
bool between(int min, int max, int value){
    if(value <= max && value > min)
        return true;
    else
        return false;
}

char gbk2char(int h_ch){
    if  (between(0xB0A1,0xB0C4,h_ch))  return  'a';
    if  (between(0XB0C5,0XB2C0,h_ch))  return  'b';
    if  (between(0xB2C1,0xB4ED,h_ch))  return  'c';
    if  (between(0xB4EE,0xB6E9,h_ch))  return  'd';
    if  (between(0xB6EA,0xB7A1,h_ch))  return  'e';
    if  (between(0xB7A2,0xB8c0,h_ch))  return  'f';
    if  (between(0xB8C1,0xB9FD,h_ch))  return  'g';
    if  (between(0xB9FE,0xBBF6,h_ch))  return  'h';
    if  (between(0xBBF7,0xBFA5,h_ch))  return  'j';
    if  (between(0xBFA6,0xC0AB,h_ch))  return  'k';
    if  (between(0xC0AC,0xC2E7,h_ch))  return  'l';
    if  (between(0xC2E8,0xC4C2,h_ch))  return  'm';
    if  (between(0xC4C3,0xC5B5,h_ch))  return  'n';
    if  (between(0xC5B6,0xC5BD,h_ch))  return  'o';
    if  (between(0xC5BE,0xC6D9,h_ch))  return  'p';
    if  (between(0xC6DA,0xC8BA,h_ch))  return  'q';
    if  (between(0xC8BB,0xC8F5,h_ch))  return  'r';
    if  (between(0xC8F6,0xCBF0,h_ch))  return  's';
    if  (between(0xCBFA,0xCDD9,h_ch))  return  't';
    if  (between(0xCDDA,0xCEF3,h_ch))  return  'w';
    if  (between(0xCEF4,0xD188,h_ch))  return  'x';
    if  (between(0xD1B9,0xD4D0,h_ch))  return  'y';
    if  (between(0xD4D1,0xD7F9,h_ch))  return  'z';
    return  '\0';
}

int get_pinyin_first_letter(char input[], int len, char outLetter[]) {
    int end = 0;
    int h_ch = 0;
    uint8_t gbk_ch[2];
    for (int i = 0; i < len; i++) {
        if (isascii(input[i])) {
            outLetter[end] = input[i];
            end++;
        } else {
            gbk_ch[0] = input[i];
            gbk_ch[1] = input[++i];
            h_ch = (gbk_ch[0] & 0xff) * 0x100 + (gbk_ch[1] & 0xff);
            outLetter[end] = gbk2char(h_ch);
            end++;
        }
    }
    outLetter[end] = '\0';
    return end;
}

// ****************字符串工具函数****************
//int stringLength(char *s) {
//    int i = 0;
//    while (s[i++] != '\0');
//    return i;
//}

//char *stringConcat(char *a, char *b) {
//    char *c = (char *) malloc(stringLength(a) + stringLength(b) + 1);
//    if (c == NULL)exit(1);
//    char *head = c; // 首地址
//    while (*a != '\0')
//        *c++ = *a++;
//    while ((*c++ = *b++) != '\0');
//    return head;
//}

// ****************搜索算法****************

TrieBookDetail* SearchResultW::CreateTrieNode() {
    TrieBookDetail *p;
    p = (TrieBookDetail *) malloc(sizeof(TrieBookDetail));
    p->nCount = 1;
    for (int i = 0; i < SUBTRIE; ++i) {
        p->nextTree[i] = NULL;
    }
    return p;
}


void SearchResultW::TraverseTrieTree(TrieBookDetail *ptrRoot, char *pstr) {
    char *title;
    BookDetailD *temp;
    if (ptrRoot == NULL)
        return;
    for (int i = 0; i < SUBTRIE; ++i) {
        if (ptrRoot->nextTree[i] == NULL)
            continue;
        traWord[pos++] = i + 'a';
        if ((ptrRoot->nextTree[i]->isnData == false)&&(ptrRoot->nextTree[i]->data != NULL)) {
            traWord[pos] = '\0';
            title = stringConcat(pstr, traWord);
            temp = ptrRoot->nextTree[i]->data;
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
            row++;
        }
        TraverseTrieTree(ptrRoot->nextTree[i], pstr);
        pos--;
    }
    ui->tableView->setModel(model);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setShowGrid(true);
}


void SearchResultW::SearchTrie(TrieBookDetail *pRoot, char *s) {
    TrieBookDetail *p;
    int i, k;
    if (!(p = pRoot))
        return;
    i = 0;
    while (s[i]) {
        k = s[i++] - 'a';
        if (p->nextTree[k] == NULL)
            return; //未找到
        p = p->nextTree[k];
    }
    // 找到了表中存在的字符最后一个节点
    s[i + 1] = '\0';
    TraverseTrieTree(p, s);

}


void SearchResultW::InsertTrie(TrieBookDetail* &ptrRoot, char *s, BookDetailD *data) {
    int i, k;
    TrieBookDetail *p;
    if (!(p = ptrRoot)) {
        p = CreateTrieNode();
        ptrRoot = p;
    }
    i = 0;
    while (s[i]) {
        k = s[i++] - 'a';
        if (!(p->nextTree[k])){
            p->nextTree[k] = CreateTrieNode();
            p->nextTree[k]->data = NULL;
        }
        p = p->nextTree[k];
    }
    p->isnData = false;
    p->data = data;

}



// ****************逻辑函数****************

void SearchResultW::searchByBookId(long bookid){
    // command:0
    int total = 0;
    BookDetailD *p = bd_head_s;
    while(p){
        total++;
        p = p->next;
    }
    BookDetailD * *r = (BookDetailD* *)malloc(sizeof (BookDetailD) * total);
    p = bd_head_s;
    for(int i = 0; i < total; ++i){
        r[i] = p;
        p = p->next;
    }
    int result = fibonacciSearch(r, total, bookid);
    if(result == -1){
        QMessageBox::information(this, "错误", "未找到该成员！");
        return;
    }

    item = new QStandardItem(tr("%1").arg(r[result]->bookID));
    model->setItem(0, 0, item);
    item = new QStandardItem(QString::fromLocal8Bit(r[result]->bookName));
    model->setItem(0, 1, item);
    item = new QStandardItem(QString::fromLocal8Bit(r[result]->authorName));
    model->setItem(0, 2, item);
    item = new QStandardItem(tr("%1").arg(r[result]->pagesNumber));
    model->setItem(0, 3, item);
    item = new QStandardItem(tr("%1").arg(r[result]->accessNumber));
    model->setItem(0, 4, item);
    item = new QStandardItem(QString::fromLocal8Bit(r[result]->pressName));
    model->setItem(0, 5, item);
    item = new QStandardItem(tr("%1").arg(r[result]->pressDate));
    model->setItem(0, 6, item);
    item = new QStandardItem(tr("%1").arg(r[result]->standardCode));
    model->setItem(0, 7, item);
    item = new QStandardItem(tr("%1").arg(r[result]->currStorage));
    model->setItem(0, 8, item);
    item = new QStandardItem(tr("%1").arg(r[result]->totalStorage));
    model->setItem(0, 9, item);
    ui->tableView->setModel(model);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setShowGrid(true);
}

void SearchResultW::searchByBookNameFirstLetter(QString name){
    // command:1
    QByteArray ba = name.toLatin1();
    char *target = ba.data();
    char pinyinFirstLetter[30];

    BookDetailD *p = bd_head_s;
    while(p != NULL){
        get_pinyin_first_letter(p->bookName, stringLength(p->bookName), pinyinFirstLetter);
        InsertTrie(trieNameRoot, pinyinFirstLetter, p);
        p = p->next;
    }
    SearchTrie(trieNameRoot, target);
}

void SearchResultW::searchByPressFirstLetter(QString name){
    // command:2
    QByteArray ba = name.toLatin1();
    char *target = ba.data();
    char pinyinFirstLetter[30];
    BookDetailD *p = bd_head_s;
    while(p != NULL){
        get_pinyin_first_letter(p->pressName, stringLength(p->pressName), pinyinFirstLetter);
        InsertTrie(triePressRoot, pinyinFirstLetter, p);
        p = p->next;
    }
    SearchTrie(triePressRoot, target);
}

void SearchResultW::searchByAuthorFirstLetter(QString name){
    // command:3
    QByteArray ba = name.toLatin1();
    char *target = ba.data();
    char pinyinFirstLetter[30];
    BookDetailD *p = bd_head_s;
    while(p != NULL){
        get_pinyin_first_letter(p->authorName, stringLength(p->authorName), pinyinFirstLetter);
        InsertTrie(trieAuthorRoot, pinyinFirstLetter, p);
        p = p->next;
    }
    SearchTrie(trieAuthorRoot, target);

}


void SearchResultW::notifyTabView(){
    ui->tableView->verticalHeader()->hide();

    model = new QStandardItemModel();
    model->setColumnCount(10);
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
}


void SearchResultW::receiveData(QString data, int command){
    notifyTabView();
    switch (command) {
    case 0:
        searchByBookId(data.toLong());
        break;
    case 1:
        searchByBookNameFirstLetter(data);
        break;
    case 2:
        searchByPressFirstLetter(data);
        break;
    case 3:
        searchByAuthorFirstLetter(data);
        break;
    }

    ui->label->setText(tr("共找到 %1 条记录").arg(ui->tableView->model()->rowCount()));
    ui->tableView->setColumnWidth(0, 80);
    ui->tableView->setColumnWidth(1, 200);
    ui->tableView->setColumnWidth(2, 150);
    ui->tableView->setColumnWidth(3, 80);
    ui->tableView->setColumnWidth(4, 100);
    ui->tableView->setColumnWidth(5, 150);
    ui->tableView->setColumnWidth(6, 150);
    ui->tableView->setColumnWidth(7, 150);
    ui->tableView->setColumnWidth(8, 80);
    ui->tableView->setColumnWidth(9, 90);
}





void SearchResultW::on_pushButton_2_clicked()
{

    for(int i = 0; i < ui->tableView->model()->rowCount(); i++){
        QModelIndex index = ui->tableView->model()->index(i,8, QModelIndex());
        if(index.data().toString() == tr("0")){
            ui->tableView->hideRow(i);
        }
    }

}
