#ifndef SEARCHRESULTW_H
#define SEARCHRESULTW_H

#include <QMainWindow>

namespace Ui {
class SearchResultW;
}

class SearchResultW : public QMainWindow
{
    Q_OBJECT

public:
    explicit SearchResultW(QWidget *parent = nullptr);
    ~SearchResultW();

private:
    Ui::SearchResultW *ui;
};

#endif // SEARCHRESULTW_H
