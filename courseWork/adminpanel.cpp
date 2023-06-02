#include "adminpanel.h"
#include "ui_adminpanel.h"
#include "mainwindow.h"
#include "comand.h"
#include "razrab.h"
#include "product.h"
#include "company.h"
#include "version.h"


adminpanel::adminpanel(QSqlDatabase dbconn, QWidget *parent):
    QWidget(parent),
    ui(new Ui::adminpanel)
{
    this->dbconn = dbconn;
    ui->setupUi(this);
    QPixmap bkgnd("/home/nikulin_danila/Документы/CourseDB/db2.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
    connect(ui->btnChangeUserA, SIGNAL(clicked(bool)), this, SLOT(btnChangeUser()));
    connect(ui->btnComandA, SIGNAL(clicked(bool)), this, SLOT(btnComand()));
    connect(ui->btnCompanyA, SIGNAL(clicked(bool)), this, SLOT(btnCompany()));
    connect(ui->btnProductA, SIGNAL(clicked(bool)), this, SLOT(btnProduct()));
    connect(ui->btnRazrabA, SIGNAL(clicked(bool)), this, SLOT(btnRazrab()));
    //connect(ui->btnVersion, SIGNAL(clicked(bool)), this, SLOT(btnVersion()));
}

adminpanel::~adminpanel()
{
    delete ui;
}

void adminpanel::btnChangeUser(){
    MainWindow *auth = new MainWindow();
    this->close();
    auth->show();
    return;
}

void adminpanel::btnComand(){
    comand *com= new comand(dbconn);
    this->close();
    com->show();
    return;
}

void adminpanel::btnCompany(){
    company *comp= new company(dbconn);
    this->close();
    comp->show();
    return;
}

void adminpanel::btnProduct(){
    product *prod = new product(dbconn);
    this->close();
    prod->show();
    return;
}

void adminpanel::btnRazrab(){
    razrab *raz = new razrab(dbconn);
    this->close();
    raz->show();
    return;
}

//void adminpanel::btnVersion(){
//    version *vers = new version(dbconn);
//    this->close();
//    vers->show();
//    return;
//}
