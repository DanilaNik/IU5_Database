#include "comanies.h"
#include "ui_comanies.h"

comanies::comanies(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::comanies)
{
    ui->setupUi(this);
}

comanies::~comanies()
{
    delete ui;
}
