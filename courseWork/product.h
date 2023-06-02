#ifndef PRODUCT_H
#define PRODUCT_H

#include <QSqlDatabase>
#include <QWidget>

namespace Ui {
class product;
}

class product : public QWidget
{
    Q_OBJECT

public:
    explicit product(QSqlDatabase dbconn, QWidget *parent = nullptr);
    ~product();

private:
    Ui::product *ui;
    QSqlDatabase dbconn;

private slots:
    void btnSelectAll();
    void btnBack();
    void btnAdd();
    void btnDelete();
    void btnUpdate();
    void btnSearch();
    void on_twProduct_cellClicked(int row, int column);
};

#endif // PRODUCT_H
