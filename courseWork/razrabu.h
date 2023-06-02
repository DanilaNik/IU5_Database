#ifndef RAZRABU_H
#define RAZRABU_H

#include <QSqlDatabase>
#include <QWidget>

namespace Ui {
class razrabU;
}

class razrabU : public QWidget
{
    Q_OBJECT

public:
    explicit razrabU(QSqlDatabase dbconn, QWidget *parent = nullptr);
    ~razrabU();

private:
    Ui::razrabU *ui;
    QSqlDatabase dbconn;

private slots:
    void btnSelectAll();
    void btnBack();
    void btnSearch();
};

#endif // RAZRABU_H
