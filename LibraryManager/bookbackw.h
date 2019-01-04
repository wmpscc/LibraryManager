#ifndef BOOKBACKW_H
#define BOOKBACKW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include"bookdata.h"
namespace Ui {
class BookBackW;
}

class BookBackW : public QMainWindow
{
    Q_OBJECT

public:
    explicit BookBackW(QWidget *parent = nullptr);
    ~BookBackW();

private slots:
    void on_button_search_reader_info_clicked();

    void on_button_search_book_info_clicked();

    void on_pushButton_2_clicked();
    void paintEvent(QPaintEvent *event);


private:
    Ui::BookBackW *ui;
    QStandardItemModel *model;
    QStandardItem *item;
    ReaderInfoD *user = NULL;
    BookDetailD *target_book = NULL;
    void update_lend_history(ReaderInfoD *p);
};

#endif // BOOKBACKW_H
