#ifndef BOOKINW_H
#define BOOKINW_H

#include <QMainWindow>

namespace Ui {
class BookInW;
}

class BookInW : public QMainWindow
{
    Q_OBJECT

public:
    explicit BookInW(QWidget *parent = nullptr);
    ~BookInW();

private:
    Ui::BookInW *ui;
};

#endif // BOOKINW_H
