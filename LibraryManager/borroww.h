#ifndef BORROWW_H
#define BORROWW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include"bookdata.h"
namespace Ui {
class BorrowW;
}

class BorrowW : public QMainWindow
{
    Q_OBJECT

public:
    explicit BorrowW(QWidget *parent = nullptr);
    ~BorrowW();

private slots:
    void on_button_search_reader_id_clicked();

    void on_button_search_book_id_clicked();

    void on_pushButton_2_clicked();
    void paintEvent(QPaintEvent *event);
private:
    Ui::BorrowW *ui;
    QStandardItemModel *model;
    QStandardItem *item;
    ReaderInfoD *user = NULL;
    BookDetailD *target_book = NULL;
    void update_lend_history(ReaderInfoD *p);
};

#endif // BORROWW_H
