#include "versionu.h"
#include "ui_versionu.h"

versionu::versionu(QSqlDatabase dbconn,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::versionu)
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

    ui->twVersionU->setColumnCount(4);
    // Возможность прокрутки
    ui->twVersionU->setAutoScroll(true);
    // Режим выделения ячеек - только одна строка
    ui->twVersionU->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->twVersionU->setSelectionBehavior(QAbstractItemView::SelectRows);
    // Заголовки таблицы
//    ui->twComand->setHorizontalHeaderItem(0,new QTableWidgetItem("ID_разработчика"));
    ui->twVersionU->setHorizontalHeaderItem(0,new QTableWidgetItem("Название версии"));
    ui->twVersionU->setHorizontalHeaderItem(1,new QTableWidgetItem("Дата версии"));
    ui->twVersionU->setHorizontalHeaderItem(2,new QTableWidgetItem("Название проета"));
    ui->twVersionU->setHorizontalHeaderItem(3,new QTableWidgetItem("Дней с первого релиза"));
    /*ui->twVersion->setHorizontalHeaderItem(4,new QTableWidgetItem("Отдел"));
    ui->twRazrab->setHorizontalHeaderItem(5,new QTableWidgetItem("Режим работы"));*/
    // Последний столбец растягивается при изменении размера формы
    ui->twVersionU->horizontalHeader()->setStretchLastSection(true);
    // Разрешаем сортировку пользователю
    ui->twVersionU->setSortingEnabled(true);
    ui->twVersionU->sortByColumn(4);
    // Запрет на изменение ячеек таблицы при отображении
    ui->twVersionU->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

versionu::~versionu()
{
    delete ui;
}
