#ifndef COMANDU_H
#define COMANDU_H

#include <QSqlDatabase>
#include <QWidget>

namespace Ui {
    class comandU;
}

class comandU : public QWidget
{
    Q_OBJECT
public:
     explicit comandU(QSqlDatabase dbconn, QWidget *parent = nullptr);
    ~comandU();

private:
    Ui::comandU *ui;
    QSqlDatabase dbconn;

private slots:
    void btnSelectAll();
    //void SelectAllU();
    void btnBack();
    void btnSearch();
};

#endif // COMANDU_H
