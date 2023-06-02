#ifndef PRODUCTU_H
#define PRODUCTU_H

#include <QSqlDatabase>
#include <QWidget>

namespace Ui {
class productu;
}

class productu : public QWidget
{
    Q_OBJECT

public:
    explicit productu(QSqlDatabase dbconn, QWidget *parent = nullptr);
    ~productu();

private:
    Ui::productu *ui;
    QSqlDatabase dbconn;

private slots:
    void btnSelectAll();
    void btnBack();
    void btnSearch();
};

#endif // PRODUCTU_H
