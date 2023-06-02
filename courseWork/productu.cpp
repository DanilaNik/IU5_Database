#include "productu.h"
#include "ui_productu.h"
#include "userpanel.h"
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>

productu::productu(QSqlDatabase dbconn, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::productu)
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

    ui->twProductU->setColumnCount(4);
    // Возможность прокрутки
    ui->twProductU->setAutoScroll(true);
    // Режим выделения ячеек - только одна строка
    ui->twProductU->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->twProductU->setSelectionBehavior(QAbstractItemView::SelectRows);
    // Заголовки таблицы
//    ui->twComand->setHorizontalHeaderItem(0,new QTableWidgetItem("ID IT продукта"));
    ui->twProductU->setHorizontalHeaderItem(0,new QTableWidgetItem("Название проекта"));
    ui->twProductU->setHorizontalHeaderItem(1,new QTableWidgetItem("Название отдела"));
    ui->twProductU->setHorizontalHeaderItem(2,new QTableWidgetItem("Название компании зачазчика"));
    ui->twProductU->setHorizontalHeaderItem(3,new QTableWidgetItem("Последняя версия"));
    // Последний столбец растягивается при изменении размера формы
    ui->twProductU->horizontalHeader()->setStretchLastSection(true);
    // Разрешаем сортировку пользователю
    ui->twProductU->setSortingEnabled(true);
    ui->twProductU->sortByColumn(4);
    // Запрет на изменение ячеек таблицы при отображении
    ui->twProductU->setEditTriggers(QAbstractItemView::NoEditTriggers);
    btnSelectAll();
}

productu::~productu()
{
    delete ui;
}

void productu::btnSelectAll(){
    ui->twProductU->clearContents();

    if(!dbconn.isOpen()){
        QMessageBox::critical(this,"Error",dbconn.lastError().text());
        return;
    }

    QSqlQuery query(dbconn);

    QString sqlstr = "select products.name, comands.name AS Comand_name, company.name AS Company_name, versions.name AS Version_name from products JOIN comands ON products.comand_id = comands.id JOIN company ON products.company_id= company.id JOIN (SELECT product_id, MAX(version_date) as max_date FROM versions GROUP BY product_id) v_max ON v_max.product_id = products.id JOIN versions ON products.id = versions.product_id AND v_max.max_date = versions.version_date";

    if( !query.exec(sqlstr)) {
        QMessageBox::critical(this,"Error", query.lastError().text());
        return;
    }

    if(query.isActive()) {
        ui->twProductU->setRowCount(query.size());
    } else {
        ui->twProductU->setRowCount(0);
    }
    ui->teProductU->append(QString("Read %1 rows").arg(query.size()));
    // Прочитать в цикле все строки результата (курсора)
        // и вывести их в компонент таблицы
    int i=0;
    while(query.next()) {
//        ui->twComand->setItem(i,0,new
//        QTableWidgetItem(query.value("ID_IT_продукта").toString()));

        ui->twProductU->setItem(i,0,new
        QTableWidgetItem(query.value("name").toString()));

        ui->twProductU->setItem(i,1,new
        QTableWidgetItem(query.value("Comand_name").toString()));

        ui->twProductU->setItem(i,2,new
        QTableWidgetItem(query.value("Company_name").toString()));

        ui->twProductU->setItem(i,3,new
        QTableWidgetItem(query.value("Version_name").toString()));

        i++;
     }

     return;
}

void productu::btnBack() {
    this->close();
    userpanel *userp = new userpanel(dbconn);
    userp->show();
    return;
}

void productu::btnSearch() {
    ui->twProductU->clearContents();

    if (!dbconn.isOpen()) {
        QMessageBox::critical(this,"Error",dbconn.lastError().text());
        return;
    }
    QSqlQuery query(dbconn);
    QString sqlstr = "select products.name, comands.name AS Comand_name, company.name AS Company_name, versions.name AS Version_name from products JOIN comands ON products.comand_id = comands.id JOIN company ON products.company_id= company.id JOIN (SELECT product_id, MAX(version_date) as max_date FROM versions GROUP BY product_id) v_max ON v_max.product_id = products.id JOIN versions ON products.id = versions.product_id AND v_max.max_date = versions.version_date WHERE products.name ='" + ui->leProductNameSearch->text() + "'";
    //QString sqlstr = "select Название_проекта from IT_продукт where \"Название_проекта\" = '"
    //        + ui->leProductNameSearch->text() + "'";

    if(!query.exec(sqlstr)) {
        QMessageBox::critical(this,"Error", query.lastError().text());
        return;
    }

    if(query.isActive()) {
        ui->twProductU->setRowCount( query.size());
    } else {
        ui->twProductU->setRowCount(0);
    }
    ui->teProductU->append(QString("Read %1 rows").arg(query.size()));

    // Прочитать в цикле все строки результата (курсора)
    // и вывести их в компонент таблицы
    int i=0;
    while(query.next()) {
//        ui->twComand->setItem(i,0,new
//        QTableWidgetItem(query.value("ID_разработчика").toString()));

        ui->twProductU->setItem(i,0,new
        QTableWidgetItem(query.value("name").toString()));

        ui->twProductU->setItem(i,1,new
        QTableWidgetItem(query.value("Comand_name").toString()));

        ui->twProductU->setItem(i,2,new
        QTableWidgetItem(query.value("Company_name").toString()));

        ui->twProductU->setItem(i,3,new
        QTableWidgetItem(query.value("Version_name").toString()));

        i++;
    }

    return;
}
