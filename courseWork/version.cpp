#include "version.h"
#include "ui_version.h"
#include "adminpanel.h"
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>

version::version(QSqlDatabase dbconn, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::version)
{
    ui->setupUi(this);
    this->dbconn = dbconn;
    ui->setupUi(this);
    QPixmap bkgnd("/home/nikulin_danila/Документы/CourseDB/db3.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
//    connect(ui->btnSelectAll, SIGNAL(clicked(bool)), this, SLOT(btnSelectAll()));
//    connect(ui->btnAdd, SIGNAL(clicked(bool)), this, SLOT(btnAdd()));
//    connect(ui->btnDelete, SIGNAL(clicked(bool)), this, SLOT(btnDelete()));
//    connect(ui->btnUpdate, SIGNAL(clicked(bool)), this, SLOT(btnUpdate()));
//    connect(ui->btnBack, SIGNAL(clicked(bool)), this, SLOT(btnBack()));
//    connect(ui->btnSearch, SIGNAL(clicked(bool)), this, SLOT(btnSearch()));

    ui->twVersion->setColumnCount(4);
    // Возможность прокрутки
    ui->twVersion->setAutoScroll(true);
    // Режим выделения ячеек - только одна строка
    ui->twVersion->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->twVersion->setSelectionBehavior(QAbstractItemView::SelectRows);
    // Заголовки таблицы
//    ui->twComand->setHorizontalHeaderItem(0,new QTableWidgetItem("ID_разработчика"));
    ui->twVersion->setHorizontalHeaderItem(0,new QTableWidgetItem("Название версии"));
    ui->twVersion->setHorizontalHeaderItem(1,new QTableWidgetItem("Дата версии"));
    ui->twVersion->setHorizontalHeaderItem(2,new QTableWidgetItem("Название проета"));
    ui->twVersion->setHorizontalHeaderItem(3,new QTableWidgetItem("Дней с первого релиза"));
    /*ui->twVersion->setHorizontalHeaderItem(4,new QTableWidgetItem("Отдел"));
    ui->twRazrab->setHorizontalHeaderItem(5,new QTableWidgetItem("Режим работы"));*/
    // Последний столбец растягивается при изменении размера формы
    ui->twVersion->horizontalHeader()->setStretchLastSection(true);
    // Разрешаем сортировку пользователю
    ui->twVersion->setSortingEnabled(true);
    ui->twVersion->sortByColumn(4);
    // Запрет на изменение ячеек таблицы при отображении
    ui->twVersion->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

version::~version()
{
    delete ui;
}
