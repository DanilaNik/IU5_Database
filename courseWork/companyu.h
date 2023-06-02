#ifndef COMPANYU_H
#define COMPANYU_H

#include <QSqlDatabase>
#include <QWidget>

namespace Ui {
class companyu;
}

class companyu : public QWidget
{
    Q_OBJECT

public:
    explicit companyu(QSqlDatabase dbconn, QWidget *parent = nullptr);
    ~companyu();

private:
    Ui::companyu *ui;
    QSqlDatabase dbconn;
private slots:
    void btnSelectAll();
    void btnBack();
    void btnSearch();
};

#endif // COMPANYU_H
