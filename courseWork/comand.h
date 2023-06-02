#ifndef COMAND_H
#define COMAND_H

#include <QSqlDatabase>
#include <QWidget>

namespace Ui {
    class comand;
}

class comand : public QWidget
{
    Q_OBJECT
public:
     explicit comand(QSqlDatabase dbconn, QWidget *parent = nullptr);
    ~comand();

private:
    Ui::comand *ui;
    QSqlDatabase dbconn;

private slots:
    void btnSelectAll();
    void btnBack();
    void btnAdd();
    void btnDelete();
    void btnUpdate();
    void btnSearch();
    void on_twComand_cellClicked(int row, int column);
   // void on_bntUpdate_clicked();
};

#endif // COMAND_H
