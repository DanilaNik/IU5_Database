#ifndef ADMINPANEL_H
#define ADMINPANEL_H

#include <QWidget>
#include <QSqlDatabase>

namespace Ui {
    class adminpanel;
}

class adminpanel : public QWidget
{
    Q_OBJECT

public:
    explicit adminpanel(QSqlDatabase dbconn, QWidget *parent = nullptr);
    ~adminpanel();

private:
    Ui::adminpanel *ui;
    QSqlDatabase dbconn;

private slots:
    void btnChangeUser();
    void btnComand();
    void btnCompany();
    void btnProduct();
    void btnRazrab();
    //void btnVersion();
};

#endif // ADMINPANEL_H
