#include "comandu.h"
#include "ui_comandu.h"
#include "userpanel.h"
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>

comandU::comandU(QSqlDatabase dbconn, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::comandU)
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

    ui->twComandU->setColumnCount(3);
    // Возможность прокрутки
    ui->twComandU->setAutoScroll(true);
    // Режим выделения ячеек - только одна строка
    ui->twComandU->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->twComandU->setSelectionBehavior(QAbstractItemView::SelectRows);
    // Заголовки таблицы
//    ui->twComand->setHorizontalHeaderItem(0,new QTableWidgetItem("ID отдела"));
    ui->twComandU->setHorizontalHeaderItem(0,new QTableWidgetItem("Название отдела"));
    ui->twComandU->setHorizontalHeaderItem(1,new QTableWidgetItem("Общий Email отдела"));
    ui->twComandU->setHorizontalHeaderItem(2,new QTableWidgetItem("Название компании заказчика"));
    // Последний столбец растягивается при изменении размера формы
    ui->twComandU->horizontalHeader()->setStretchLastSection(true);
    // Разрешаем сортировку пользователю
    ui->twComandU->setSortingEnabled(true);
    ui->twComandU->sortByColumn(3);
    // Запрет на изменение ячеек таблицы при отображении
    ui->twComandU->setEditTriggers(QAbstractItemView::NoEditTriggers);
    btnSelectAll();
}

comandU::~comandU()
{
    delete ui;
}

void comandU::btnSelectAll(){
    ui->twComandU->clearContents();

    if(!dbconn.isOpen()){
        QMessageBox::critical(this,"Error",dbconn.lastError().text());
        return;
    }

    QSqlQuery query(dbconn);

    QString sqlstr = "SELECT comands.name, comands.comand_email, c.name AS Company_name from comands join company c on comands.id = c.comand_id ORDER BY comands.name";

    if( !query.exec(sqlstr)) {
        QMessageBox::critical(this,"Error", query.lastError().text());
        return;
    }

    if(query.isActive()) {
        ui->twComandU->setRowCount(query.size());
    } else {
        ui->twComandU->setRowCount(0);
    }
    ui->teComandU->append(QString("Read %1 rows").arg(query.size()));
    // Прочитать в цикле все строки результата (курсора)
        // и вывести их в компонент таблицы
    int i=0;
    while(query.next()) {
//        ui->twComand->setItem(i,0,new
//        QTableWidgetItem(query.value("ID отдела").toString()));

        ui->twComandU->setItem(i,0,new
        QTableWidgetItem(query.value("Name").toString()));

        ui->twComandU->setItem(i,1,new
        QTableWidgetItem(query.value("Comand_Email").toString()));

        ui->twComandU->setItem(i,2,new
        QTableWidgetItem(query.value("Company_name").toString()));

        i++;
     }

     return;
}

void comandU::btnBack() {
    this->close();
    userpanel *userp = new userpanel(dbconn);
    userp->show();
    return;
}

void comandU::btnSearch() {
    ui->twComandU->clearContents();

    if (!dbconn.isOpen()) {
        QMessageBox::critical(this,"Error",dbconn.lastError().text());
        return;
    }

    QSqlQuery query(dbconn);

    QString sqlstr = "select comands.name, comands.comand_email, c.name AS Company_name from comands join company c on comands.id = c.comand_id where c.name = '" + ui->leComandNameSearch->text() + "'";

    if(!query.exec(sqlstr)) {
        QMessageBox::critical(this,"Error", query.lastError().text());
        return;
    }


    if(query.isActive()) {
        ui->twComandU->setRowCount( query.size());
    } else {
        ui->twComandU->setRowCount(0);
    }
    ui->teComandU->append(QString("Read %1 rows").arg(query.size()));

    // Прочитать в цикле все строки результата (курсора)
    // и вывести их в компонент таблицы
    int i=0;
    while(query.next()) {
//        ui->twComand->setItem(i,0,new
//        QTableWidgetItem(query.value("ID отдела").toString()));

        ui->twComandU->setItem(i,0,new
        QTableWidgetItem(query.value("name").toString()));

        ui->twComandU->setItem(i,1,new
        QTableWidgetItem(query.value("comand_email").toString()));

        ui->twComandU->setItem(i,2,new
        QTableWidgetItem(query.value("Company_name").toString()));

        i++;
    }

    return;
}

