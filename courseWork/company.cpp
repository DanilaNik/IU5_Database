#include "company.h"
#include "ui_company.h"
#include "adminpanel.h"
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <iostream>

company::company(QSqlDatabase dbconn, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::company)
{
    this->dbconn = dbconn;
    ui->setupUi(this);
    QPixmap bkgnd("/home/nikulin_danila/Документы/CourseDB/db3.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
    connect(ui->btnSelectAll, SIGNAL(clicked(bool)), this, SLOT(btnSelectAll()));
    connect(ui->btnAdd, SIGNAL(clicked(bool)), this, SLOT(btnAdd()));
    connect(ui->btnDelete, SIGNAL(clicked(bool)), this, SLOT(btnDelete()));
    connect(ui->btnUpdate, SIGNAL(clicked(bool)), this, SLOT(btnUpdate()));
    connect(ui->btnBack, SIGNAL(clicked(bool)), this, SLOT(btnBack()));
    connect(ui->btnSearch, SIGNAL(clicked(bool)), this, SLOT(btnSearch()));


    ui->twCompany->setColumnCount(2);
    // Возможность прокрутки
    ui->twCompany->setAutoScroll(true);
    // Режим выделения ячеек - только одна строка
    ui->twCompany->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->twCompany->setSelectionBehavior(QAbstractItemView::SelectRows);
    // Заголовки таблицы
//    ui->twComand->setHorizontalHeaderItem(0,new QTableWidgetItem("ID отдела"));
    ui->twCompany->setHorizontalHeaderItem(0,new QTableWidgetItem("Название компании"));
    ui->twCompany->setHorizontalHeaderItem(1,new QTableWidgetItem("Email"));

    // Последний столбец растягивается при изменении размера формы
    ui->twCompany->horizontalHeader()->setStretchLastSection(true);
    // Разрешаем сортировку пользователю
    ui->twCompany->setSortingEnabled(true);
    ui->twCompany->sortByColumn(2);
    // Запрет на изменение ячеек таблицы при отображении
    ui->twCompany->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

company::~company()
{
    delete ui;
}

void company::btnBack() {
    this->close();
    adminpanel *adminp = new adminpanel(dbconn);
    adminp->show();
    return;
}

void company::btnSelectAll(){
    ui->twCompany->clearContents();

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
        ui->twCompany->setRowCount(query.size());
    } else {
        ui->twCompany->setRowCount(0);
    }
    ui->teCompany->append(QString("Read %1 rows").arg(query.size()));
    // Прочитать в цикле все строки результата (курсора)
        // и вывести их в компонент таблицы
    int i=0;
    while(query.next()) {
//        ui->twComand->setItem(i,0,new
//        QTableWidgetItem(query.value("ID отдела").toString()));

        ui->twCompany->setItem(i,0,new
        QTableWidgetItem(query.value("name").toString()));

        ui->twCompany->setItem(i,1,new
        QTableWidgetItem(query.value("company_email").toString()));

        i++;
     }

     return;
}

void company::btnDelete() {
    if(!dbconn.isOpen()) {
        QMessageBox::critical(this,"Error",dbconn.lastError().text());
        return;
    }
    // Получить номер выбранной строки в компоненте таблицы
    int currow = ui->twCompany->currentRow();
    // Если он меньше 0 (строка не выбрана), то
    // сообщение об ошибке и выход из функции
    if(currow < 0) {
        QMessageBox::critical(this,"Error","Not selected row!");
        return;
    }
    // Спросить у пользователя подтверждение удаления записи
    // Используется статический метод QMessageBox::question
    // для задания вопроса, который возвращает код нажатой кнопки
    if( QMessageBox::question(this,"Delete","Delete row?",
    QMessageBox::Cancel,QMessageBox::Ok)==QMessageBox::Cancel)
    return;
    // Создать объект запроса
    QSqlQuery query(dbconn);
    QSqlQuery help_select_query1(dbconn);
    QSqlQuery help_update_query1(dbconn);
    QSqlQuery help_delete_query1(dbconn);
    // Создать строку запроса.
    // Вместо подготовки запроса и передачи параметров значение параметра
    // конкатенируется со строкой запроса
    // Обратите,что строковое значение помещается в одинарные кавычки
    // Значение выбирается из компонента таблицы методом item(row,col)
    QString select_comand_id;
    QString help_select_sqlstr1 = "SELECT id FROM company WHERE name = '"+ ui->twCompany->item(currow,0)->text()+"' AND comands.name = '"+ui->twCompany->item(currow,0)->text()+"' AND comands.comand_email = '"+ui->twCompany->item(currow,1)->text()+"'";

    // Находим id для удаления
    if(!help_select_query1.exec(help_select_sqlstr1)) {
        ui->teCompany->append(help_select_query1.lastQuery());
        QMessageBox::critical(this,"Error",help_select_query1.lastError().text());
        return;
    }
    if(help_select_query1.next()){
        select_comand_id = help_select_query1.value("id").toString();
    }
    QString help_delete_sqlstr1 = "delete from products where comapny_id = " + select_comand_id;
    if(!help_delete_query1.exec(help_delete_sqlstr1)) {
        ui->teCompany->append(help_delete_query1.lastQuery());
        QMessageBox::critical(this,"Error",help_delete_query1.lastError().text());
        return;
    }
    // Удаляем значение из таблицы Comands
    QString sqlstr = "delete from comands where id = " + select_comand_id;
    if(!query.exec(sqlstr)) {
        ui->teCompany->append(query.lastQuery());
        QMessageBox::critical(this,"Error",query.lastError().text());
        return;
    }
    // Вывести сообщение об удалении строки
    ui->teCompany->append( QString("Del %1 rows").arg(query.numRowsAffected()) );
    // Обновить содержимое компонента таблицы
    btnSelectAll();
    return;
}

void company::btnUpdate() {
    if(!dbconn.isOpen()) {
        QMessageBox::critical(this,"Error",dbconn.lastError().text());
        return;
    }
    // Получить номер выбранной строки в компоненте таблицы
    int currow = ui->twCompany->currentRow();
    // Если он меньше 0 (строка не выбрана), то
    // сообщение об ошибке и выход из функции
    if(currow < 0) {
        QMessageBox::critical(this,"Error","Not selected row!");
        return;
    }

    if( QMessageBox::question(this,"Update","Update row?",
    QMessageBox::Cancel,QMessageBox::Ok)==QMessageBox::Cancel)
    return;

    QSqlQuery help_select_query1(dbconn);
    QString select_company_id;
    QString help_select_sqlstr1 = "SELECT id FROM company where name = '"+ui->twCompany->item(currow,0)->text()+"' AND email = '" + ui->twCompany->item(currow,1)->text() + "'" ;
    // Находим id для update
    if(!help_select_query1.exec(help_select_sqlstr1)) {
        ui->teCompany->append(help_select_query1.lastQuery());
        QMessageBox::critical(this,"Error",help_select_query1.lastError().text());
        return;
    }
    if(help_select_query1.next()){
        select_company_id = help_select_query1.value("id").toString();
    }
    //
    QSqlQuery query(dbconn);
    if (ui->leNameCompany->text() != "") {
        QString sqlstr = "update company set name = '" + ui->leNameCompany->text() + "' where id = " + select_company_id;
        if(!query.exec(sqlstr)) {
            ui->teCompany->append(query.lastQuery());
            QMessageBox::critical(this,"Error",query.lastError().text());
            return;
        }
    }

    if (ui->leEmailCompany->text() != "") {
        QString sqlstr = "update company set company_email = '" + ui->leEmailCompany->text() + "' where id = " + select_company_id;
        if(!query.exec(sqlstr)) {
            ui->teCompany->append(query.lastQuery());
            QMessageBox::critical(this,"Error",query.lastError().text());
            return;
        }
    }


    ui->teCompany->append(QString("Updated %1 rows").arg(query.numRowsAffected()));
    btnSelectAll();
    return;
}

void company::btnAdd() {
    if(!dbconn.isOpen()) {
        QMessageBox::critical(this,"Error",dbconn.lastError().text());
        return;
        }
    QSqlQuery query(dbconn);
    QSqlQuery help_select_query1(dbconn);
    QSqlQuery help_update_query1(dbconn);
    // Создать строку запроса
    QString sqlstr = "INSERT INTO company (name, comand_email) values(?,?)";
//    QString help_select_sqlstr1 = "select name, c from company where company.name = '" + ui->leCompanyName->text() + "'";
//    QString help_update_sqlstr1 = "UPDATE company SET comand_id = (SELECT MAX(comands.id) from comands) WHERE name = '"+ui->leCompanyName->text()+"'";
//    query.prepare(sqlstr);
//    help_select_query1.prepare(help_select_sqlstr1);
//    help_update_query1.prepare(help_update_sqlstr1);
    // Передать параметры из полей ввода в запрос
    query.bindValue(0,ui->leNameCompany->text());
    query.bindValue(1,ui->leEmailCompany->text());
    //help_select_query1.bindValue(0,ui->leCompanyName->text());
    //query.bindValue(3,ui->leFIOLead->text());
//    if(!help_select_query1.exec()) {
//        QMessageBox::critical(this,"Error", help_select_query1.lastError().text());
//        return;
//    }
//   if (help_select_query1.next()){
//       int a = 0;
//   }
//   if(help_select_query1.size() == 0){
//        QMessageBox::critical(this,"Error", "Введенной вами компании нет в БД");
//        return;
//    }
//    if(!help_select_query1.value("Comand_ID").isNull()){
//        QMessageBox::critical(this,"Error", "С введенной вами компанией работает другой отдел");
//        return;
//}
   // Выполнить запрос
   if(!query.exec()) {
        ui->teCompany->append(query.lastQuery());
        QMessageBox::critical(this,"Error",query.lastError().text());
        return;
   }
//   if(!help_update_query1.exec()) {
//        ui->teCompany->append(query.lastQuery());
//        QMessageBox::critical(this,"Error",query.lastError().text());
//        return;
//   }
   // Если запрос выполнен, то вывести сообщение одобавлении строки
    ui->teCompany->append( QString("AddRead %1 rows").arg(query.numRowsAffected()));
    // и обновить записи в компоненте таблицы
    btnSelectAll();
}

void company::btnSearch() {
    ui->twCompany->clearContents();

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
        ui->twCompany->setRowCount( query.size());
    } else {
        ui->twCompany->setRowCount(0);
    }
    ui->teCompany->append(QString("Read %1 rows").arg(query.size()));

    // Прочитать в цикле все строки результата (курсора)
    // и вывести их в компонент таблицы
    int i=0;
    while(query.next()) {
//        ui->twComand->setItem(i,0,new
//        QTableWidgetItem(query.value("ID отдела").toString()));

        ui->twCompany->setItem(i,0,new
        QTableWidgetItem(query.value("name").toString()));

        ui->twCompany->setItem(i,1,new
        QTableWidgetItem(query.value("company_email").toString()));

        i++;
    }

    return;
}


void company::on_twCompany_cellClicked(int row, int column)
{
    ui->leNameCompany->setText(ui->twCompany->item(row,0)->text());
    ui->leEmailCompany->setText(ui->twCompany->item(row,1)->text());
}
