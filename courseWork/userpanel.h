#ifndef USERPANEL_H
#define USERPANEL_H

#include <QWidget>
#include <QSqlDatabase>

namespace Ui {
    class userpanel;
}

class userpanel : public QWidget
{
    Q_OBJECT

public:
    explicit userpanel(QSqlDatabase dbconn, QWidget *parent = nullptr);
    ~userpanel();

private:
    Ui::userpanel *ui;
    QSqlDatabase dbconn;

private slots:
    void btnChangeUser();
    void btnComand();
    void btnCompany();
    void btnProduct();
    void btnRazrab();
   // void btnVersion();
};

#endif // USERPANEL_H
