#include "razrabu.h"
#include "ui_razrabu.h"
#include "userpanel.h"
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>

razrabU::razrabU(QSqlDatabase dbconn, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::razrabU)
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

    ui->twRazrabU->setColumnCount(6);
    // Возможность прокрутки
    ui->twRazrabU->setAutoScroll(true);
    // Режим выделения ячеек - только одна строка
    ui->twRazrabU->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->twRazrabU->setSelectionBehavior(QAbstractItemView::SelectRows);
    // Заголовки таблицы
//    ui->twComand->setHorizontalHeaderItem(0,new QTableWidgetItem("ID_разработчика"));
    ui->twRazrabU->setHorizontalHeaderItem(0,new QTableWidgetItem("ФИО"));
    ui->twRazrabU->setHorizontalHeaderItem(1,new QTableWidgetItem("Email"));
    ui->twRazrabU->setHorizontalHeaderItem(2,new QTableWidgetItem("Номер телефона"));
    ui->twRazrabU->setHorizontalHeaderItem(3,new QTableWidgetItem("Должность"));
    ui->twRazrabU->setHorizontalHeaderItem(4,new QTableWidgetItem("Отдел"));
    ui->twRazrabU->setHorizontalHeaderItem(5,new QTableWidgetItem("Режим работы"));
    // Последний столбец растягивается при изменении размера формы
    ui->twRazrabU->horizontalHeader()->setStretchLastSection(true);
    // Разрешаем сортировку пользователю
    ui->twRazrabU->setSortingEnabled(true);
    ui->twRazrabU->sortByColumn(6);
    // Запрет на изменение ячеек таблицы при отображении
    ui->twRazrabU->setEditTriggers(QAbstractItemView::NoEditTriggers);
    btnSelectAll();
}

razrabU::~razrabU()
{
    delete ui;
}

void razrabU::btnSelectAll(){
    ui->twRazrabU->clearContents();

    if(!dbconn.isOpen()){
        QMessageBox::critical(this,"Error",dbconn.lastError().text());
        return;
    }

    QSqlQuery query(dbconn);

    QString sqlstr = "select developers.fio, developers.email, developers.phone, developers.post, c.name AS comand_name, developers.working_mode from developers JOIN comands c on c.id = developers.comand_id";

    if( !query.exec(sqlstr)) {
        QMessageBox::critical(this,"Error", query.lastError().text());
        return;
    }

    if(query.isActive()) {
        ui->twRazrabU->setRowCount(query.size());
    } else {
        ui->twRazrabU->setRowCount(0);
    }
    ui->teRazrabU->append(QString("Read %1 rows").arg(query.size()));
    // Прочитать в цикле все строки результата (курсора)
        // и вывести их в компонент таблицы
    int i=0;
    while(query.next()) {
//        ui->twComand->setItem(i,0,new
//        QTableWidgetItem(query.value("ID разработчика").toString()));

        ui->twRazrabU->setItem(i,0,new
        QTableWidgetItem(query.value("fio").toString()));

        ui->twRazrabU->setItem(i,1,new
        QTableWidgetItem(query.value("email").toString()));

        ui->twRazrabU->setItem(i,2,new
        QTableWidgetItem(query.value("phone").toString()));

        ui->twRazrabU->setItem(i,3,new
        QTableWidgetItem(query.value("post").toString()));

        ui->twRazrabU->setItem(i,4,new
        QTableWidgetItem(query.value("comand_name").toString()));

        ui->twRazrabU->setItem(i,5,new
        QTableWidgetItem(query.value("working_mode").toString()));
        i++;
     }

     return;
}

void razrabU::btnBack() {
    this->close();
    userpanel *userp = new userpanel(dbconn);
    userp->show();
    return;
}

void razrabU::btnSearch() {
    ui->twRazrabU->clearContents();

    if (!dbconn.isOpen()) {
        QMessageBox::critical(this,"Error",dbconn.lastError().text());
        return;
    }

    QSqlQuery query(dbconn);

    QString sqlstr = "select developers.fio, developers.email, developers.phone, developers.post, c.name AS comand_name, developers.working_mode from developers JOIN comands c on c.id = developers.comand_id where developers.fio = '" + ui->leRazrabNameSearch->text()+"'";

    if(!query.exec(sqlstr)) {
        QMessageBox::critical(this,"Error", query.lastError().text());
        return;
    }


    if(query.isActive()) {
        ui->twRazrabU->setRowCount( query.size());
    } else {
        ui->twRazrabU->setRowCount(0);
    }
    ui->teRazrabU->append(QString("Read %1 rows").arg(query.size()));

    // Прочитать в цикле все строки результата (курсора)
    // и вывести их в компонент таблицы
    int i=0;
    while(query.next()) {
//        ui->twComand->setItem(i,0,new
//        QTableWidgetItem(query.value("ID_разработчика").toString()));

        ui->twRazrabU->setItem(i,0,new
        QTableWidgetItem(query.value("fio").toString()));

        ui->twRazrabU->setItem(i,1,new
        QTableWidgetItem(query.value("email").toString()));

        ui->twRazrabU->setItem(i,2,new
        QTableWidgetItem(query.value("phone").toString()));

        ui->twRazrabU->setItem(i,3,new
        QTableWidgetItem(query.value("post").toString()));

        ui->twRazrabU->setItem(i,4,new
        QTableWidgetItem(query.value("comand_name").toString()));

        ui->twRazrabU->setItem(i,5,new
        QTableWidgetItem(query.value("working_mode").toString()));
        i++;
    }
    return;
}
