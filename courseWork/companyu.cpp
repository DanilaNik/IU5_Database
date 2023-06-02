#include "companyu.h"
#include "ui_companyu.h"
#include "userpanel.h"
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>

companyu::companyu(QSqlDatabase dbconn, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::companyu)
{
    this->dbconn = dbconn;
    ui->setupUi(this);
    QPixmap bkgnd("/home/nikulin_danila/Документы/CourseDB/db4.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
    connect(ui->btnSearch, SIGNAL(clicked(bool)), this, SLOT(btnSearch()));
    connect(ui->btnBack, SIGNAL(clicked(bool)), this, SLOT(btnBack()));
    connect(ui->btnSelectAll, SIGNAL(clicked(bool)), this, SLOT(btnSelectAll()));

    ui->twCompanyU->setColumnCount(2);
    // Возможность прокрутки
    ui->twCompanyU->setAutoScroll(true);
    // Режим выделения ячеек - только одна строка
    ui->twCompanyU->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->twCompanyU->setSelectionBehavior(QAbstractItemView::SelectRows);
    // Заголовки таблицы
//    ui->twComand->setHorizontalHeaderItem(0,new QTableWidgetItem("ID отдела"));
    ui->twCompanyU->setHorizontalHeaderItem(0,new QTableWidgetItem("Название компании"));
    ui->twCompanyU->setHorizontalHeaderItem(1,new QTableWidgetItem("Email"));

    // Последний столбец растягивается при изменении размера формы
    ui->twCompanyU->horizontalHeader()->setStretchLastSection(true);
    // Разрешаем сортировку пользователю
    ui->twCompanyU->setSortingEnabled(true);
    ui->twCompanyU->sortByColumn(2);
    // Запрет на изменение ячеек таблицы при отображении
    ui->twCompanyU->setEditTriggers(QAbstractItemView::NoEditTriggers);
    btnSelectAll();
}

companyu::~companyu()
{
    delete ui;
}

void companyu::btnBack() {
    this->close();
    userpanel *userp = new userpanel(dbconn);
    userp->show();
    return;
}

void companyu::btnSelectAll(){
    ui->twCompanyU->clearContents();

    if(!dbconn.isOpen()){
        QMessageBox::critical(this,"Error",dbconn.lastError().text());
        return;
    }

    QSqlQuery query(dbconn);

    QString sqlstr = "SELECT name, company_email from company";

    if( !query.exec(sqlstr)) {
        QMessageBox::critical(this,"Error", query.lastError().text());
        return;
    }

    if(query.isActive()) {
        ui->twCompanyU->setRowCount(query.size());
    } else {
        ui->twCompanyU->setRowCount(0);
    }
    ui->teCompanyU->append(QString("Read %1 rows").arg(query.size()));
    // Прочитать в цикле все строки результата (курсора)
        // и вывести их в компонент таблицы
    int i=0;
    while(query.next()) {
//        ui->twComand->setItem(i,0,new
//        QTableWidgetItem(query.value("ID отдела").toString()));

        ui->twCompanyU->setItem(i,0,new
        QTableWidgetItem(query.value("name").toString()));

        ui->twCompanyU->setItem(i,1,new
        QTableWidgetItem(query.value("company_email").toString()));

        i++;
     }

     return;
}

void companyu::btnSearch() {
    ui->twCompanyU->clearContents();

    if (!dbconn.isOpen()) {
        QMessageBox::critical(this,"Error",dbconn.lastError().text());
        return;
    }

    QSqlQuery query(dbconn);

    QString sqlstr = "select name, company_email from company where name = '" + ui->leCompanyNameSearch->text() + "'";

    if(!query.exec(sqlstr)) {
        QMessageBox::critical(this,"Error", query.lastError().text());
        return;
    }


    if(query.isActive()) {
        ui->twCompanyU->setRowCount( query.size());
    } else {
        ui->twCompanyU->setRowCount(0);
    }
    ui->teCompanyU->append(QString("Read %1 rows").arg(query.size()));

    // Прочитать в цикле все строки результата (курсора)
    // и вывести их в компонент таблицы
    int i=0;
    while(query.next()) {
//        ui->twComand->setItem(i,0,new
//        QTableWidgetItem(query.value("ID отдела").toString()));

        ui->twCompanyU->setItem(i,0,new
        QTableWidgetItem(query.value("name").toString()));

        ui->twCompanyU->setItem(i,1,new
        QTableWidgetItem(query.value("company_email").toString()));

        i++;
    }

    return;
}

