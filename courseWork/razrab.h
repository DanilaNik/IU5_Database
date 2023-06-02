#ifndef RAZRAB_H
#define RAZRAB_H

#include <QSqlDatabase>
#include <QWidget>

namespace Ui {
class razrab;
}

class razrab : public QWidget
{
    Q_OBJECT

public:
    explicit razrab(QSqlDatabase dbconn, QWidget *parent = nullptr);
    ~razrab();

private:
    Ui::razrab *ui;
    QSqlDatabase dbconn;

private slots:
    void btnSelectAll();
    void btnBack();
    void btnAdd();
    void btnDelete();
    void btnUpdate();
    void btnSearch();
    void on_twRazrab_cellClicked(int row, int column);
};

#endif // RAZRAB_H
