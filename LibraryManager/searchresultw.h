#ifndef SEARCHRESULTW_H
#define SEARCHRESULTW_H

#include <QMainWindow>
#include<bookdata.h>
#include<QStandardItemModel>
namespace Ui {
class SearchResultW;
}

class SearchResultW : public QMainWindow
{
    Q_OBJECT


public:
    explicit SearchResultW(QWidget *parent = nullptr);
    ~SearchResultW();


private slots:
    void receiveData(QString data, int command);
    void paintEvent(QPaintEvent *event);



    void on_pushButton_2_clicked();

private:
    Ui::SearchResultW *ui;
    QStandardItemModel *model;
    QStandardItem *item;
    int row = 0;
    static TrieBookDetail *nameTrieRoot;
    char traWord[30];
    int pos = 0;
    void searchByBookNameFirstLetter(QString name);
    void TraverseTrieTree(TrieBookDetail *ptrRoot, char *pstr);
    void SearchTrie(TrieBookDetail *pRoot, char *s);
    void InsertTrie(TrieBookDetail* &ptrRoot, char *s, BookDetailD *data);
    void searchByPressFirstLetter(QString name);
    void searchByAuthorFirstLetter(QString name);
    TrieBookDetail *CreateTrieNode();
    void notifyTabView();
    void searchByBookId(long bookid);


};

#endif // SEARCHRESULTW_H
