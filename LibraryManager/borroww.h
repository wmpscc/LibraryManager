#ifndef BORROWW_H
#define BORROWW_H

#include <QMainWindow>

namespace Ui {
class BorrowW;
}

class BorrowW : public QMainWindow
{
    Q_OBJECT

public:
    explicit BorrowW(QWidget *parent = nullptr);
    ~BorrowW();

private:
    Ui::BorrowW *ui;
};

#endif // BORROWW_H
