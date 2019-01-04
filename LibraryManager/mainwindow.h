#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "searchw.h"
#include "borroww.h"
#include "bookinw.h"
#include "searchresultw.h"
#include "bookbackw.h"
#include "readerinfow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_2_clicked();


    void on_pushButton_5_clicked();


    void on_pushButton_3_clicked();

    void paintEvent(QPaintEvent *event);
    void closeEvent(QCloseEvent  *event);

private:

    Ui::MainWindow *ui;
    SearchW *searchWindow;
    BorrowW *borrowWindow;
    BookInW *bookInStorageWindow;
    SearchResultW *searchResultWindow;
    BookBackW *bookBackWindow;
    ReaderInfoW *readerInfoWindow;
    void save_book_csv(char *filename);
    void restore_book_csv(char *filename);

};

#endif // MAINWINDOW_H
