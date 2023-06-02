#ifndef COMANIES_H
#define COMANIES_H

#include <QWidget>

namespace Ui {
class comanies;
}

class comanies : public QWidget
{
    Q_OBJECT

public:
    explicit comanies(QWidget *parent = nullptr);
    ~comanies();

private:
    Ui::comanies *ui;
};

#endif // COMANIES_H
