#ifndef COMPANY_H
#define COMPANY_H

#include <QSqlDatabase>
#include <QWidget>

namespace Ui {
class company;
}

class company : public QWidget
{
    Q_OBJECT

public:
    explicit company(QSqlDatabase dbconn, QWidget *parent = nullptr);
    ~company();

private:
    Ui::company *ui;
    QSqlDatabase dbconn;

private slots:
    void btnSelectAll();
    void btnBack();
    void btnAdd();
    void btnDelete();
    void btnUpdate();
    void btnSearch();
    void on_twCompany_cellClicked(int row, int column);
   // void on_bntUpdate_clicked();
};

#endif // COMPANY_H
