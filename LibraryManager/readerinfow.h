#ifndef READERINFOW_H
#define READERINFOW_H

#include <QMainWindow>

namespace Ui {
class ReaderInfoW;
}

class ReaderInfoW : public QMainWindow
{
    Q_OBJECT

public:
    explicit ReaderInfoW(QWidget *parent = nullptr);
    ~ReaderInfoW();

private slots:
    void on_pushButton_released();
    void paintEvent(QPaintEvent *event);



private:
    Ui::ReaderInfoW *ui;
};

#endif // READERINFOW_H
