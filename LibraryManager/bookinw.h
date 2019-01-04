#ifndef BOOKINW_H
#define BOOKINW_H

#include <QMainWindow>
#include "bookdata.h"

namespace Ui {
class BookInW;
}

class BookInW : public QMainWindow
{
    Q_OBJECT

public:
    explicit BookInW(QWidget *parent = nullptr);
    ~BookInW();

private slots:
    void on_pushButton_released();

    void on_button_search_book_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();
    void paintEvent(QPaintEvent *event);


private:
    Ui::BookInW *ui;
    BookDetailD *target_book = NULL;

};

#endif // BOOKINW_H
