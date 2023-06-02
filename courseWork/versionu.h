#ifndef VERSIONU_H
#define VERSIONU_H

#include <QSqlDatabase>
#include <QWidget>

namespace Ui {
class versionu;
}

class versionu : public QWidget
{
    Q_OBJECT

public:
    explicit versionu(QSqlDatabase dbconn,QWidget *parent = nullptr);
    ~versionu();

private:
    Ui::versionu *ui;
    QSqlDatabase dbconn;

private slots:
    //void btnSelectAll();
    //void btnBack();
    //void btnSearch();
};

#endif // VERSIONU_H
