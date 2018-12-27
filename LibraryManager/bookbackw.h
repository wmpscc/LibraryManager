#ifndef BOOKBACKW_H
#define BOOKBACKW_H

#include <QMainWindow>

namespace Ui {
class BookBackW;
}

class BookBackW : public QMainWindow
{
    Q_OBJECT

public:
    explicit BookBackW(QWidget *parent = nullptr);
    ~BookBackW();

private:
    Ui::BookBackW *ui;
};

#endif // BOOKBACKW_H
