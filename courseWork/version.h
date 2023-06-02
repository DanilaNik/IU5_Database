#ifndef VERSION_H
#define VERSION_H

#include <QSqlDatabase>
#include <QWidget>

namespace Ui {
class version;
}

class version : public QWidget
{
    Q_OBJECT

public:
    explicit version(QSqlDatabase dbconn,QWidget *parent = nullptr);
    ~version();

private:
    Ui::version *ui;
    QSqlDatabase dbconn;
private slots:
    //void btnSelectAll();
    //void btnBack();
    //void btnSearch();
};

#endif // VERSION_H
