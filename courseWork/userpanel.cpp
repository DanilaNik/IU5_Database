#include "userpanel.h"
#include "ui_userpanel.h"
#include "mainwindow.h"
#include "comandu.h"
#include "razrabu.h"
#include "productu.h"
#include "companyu.h"
#include "versionu.h"


userpanel::userpanel(QSqlDatabase dbconn, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::userpanel)
{
    this->dbconn = dbconn;
    ui->setupUi(this);
    QPixmap bkgnd("/home/nikulin_danila/Документы/CourseDB/db.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
    connect(ui->btnChangeUserU, SIGNAL(clicked(bool)), this, SLOT(btnChangeUser()));
    connect(ui->btnComandU, SIGNAL(clicked(bool)), this, SLOT(btnComand()));
    connect(ui->btnCompanyU, SIGNAL(clicked(bool)), this, SLOT(btnCompany()));
    connect(ui->btnProductU, SIGNAL(clicked(bool)), this, SLOT(btnProduct()));
    connect(ui->btnRazrabU, SIGNAL(clicked(bool)), this, SLOT(btnRazrab()));
    //connect(ui->btnVersion, SIGNAL(clicked(bool)), this, SLOT(btnVersion()));
}

userpanel::~userpanel()
{
    delete ui;
}

void userpanel::btnChangeUser(){
    this->close();
    MainWindow *auth = new MainWindow();
    auth->show();
    return;
}

void userpanel::btnComand(){
    this->close();
    comandU *com= new comandU(dbconn);
    com->show();
    return;
}

void userpanel::btnCompany(){
    companyu *comp= new companyu(dbconn);
    this->close();
    comp->show();
    return;
}

void userpanel::btnProduct(){
    productu *prod = new productu(dbconn);
    this->close();
    prod->show();
    return;
}

void userpanel::btnRazrab(){
    razrabU *razrab = new razrabU(dbconn);
    this->close();
    razrab->show();
    return;
}

//void userpanel::btnVersion(){
    versionu *vers = new versionu(dbconn);
    this->close();
    vers->show();
    return;
}
