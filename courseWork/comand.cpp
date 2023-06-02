#include "comand.h"
#include "ui_comand.h"
#include "adminpanel.h"
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <iostream>

comand::comand(QSqlDatabase dbconn, QWidget *parent):
    QWidget(parent),
    ui(new Ui::comand)
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

    ui->twComand->setColumnCount(3);
    // Возможность прокрутки
    ui->twComand->setAutoScroll(true);
    // Режим выделения ячеек - только одна строка
    ui->twComand->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->twComand->setSelectionBehavior(QAbstractItemView::SelectRows);
    // Заголовки таблицы
//    ui->twComand->setHorizontalHeaderItem(0,new QTableWidgetItem("ID отдела"));
    ui->twComand->setHorizontalHeaderItem(0,new QTableWidgetItem("Название отдела"));
    ui->twComand->setHorizontalHeaderItem(1,new QTableWidgetItem("Общий Email отдела"));
    ui->twComand->setHorizontalHeaderItem(2,new QTableWidgetItem("Название компании заказчика"));
    // Последний столбец растягивается при изменении размера формы
    ui->twComand->horizontalHeader()->setStretchLastSection(true);
    // Разрешаем сортировку пользователю
    ui->twComand->setSortingEnabled(true);
    ui->twComand->sortByColumn(3);
    // Запрет на изменение ячеек таблицы при отображении
    ui->twComand->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

comand::~comand()
{
    delete ui;
}

void comand::btnSelectAll(){
    ui->twComand->clearContents();

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
        ui->twComand->setRowCount(query.size());
    } else {
        ui->twComand->setRowCount(0);
    }
    ui->teComand->append(QString("Read %1 rows").arg(query.size()));
    // Прочитать в цикле все строки результата (курсора)
        // и вывести их в компонент таблицы
    int i=0;
    while(query.next()) {
//        ui->twComand->setItem(i,0,new
//        QTableWidgetItem(query.value("ID отдела").toString()));

        ui->twComand->setItem(i,0,new
        QTableWidgetItem(query.value("Name").toString()));

        ui->twComand->setItem(i,1,new
        QTableWidgetItem(query.value("Comand_Email").toString()));

        ui->twComand->setItem(i,2,new
        QTableWidgetItem(query.value("Company_name").toString()));

        i++;
     }

     return;
}

void comand::btnAdd() {
    if(!dbconn.isOpen()) {
        QMessageBox::critical(this,"Error",dbconn.lastError().text());
        return;
        }
    QSqlQuery query(dbconn);
    QSqlQuery help_select_query1(dbconn);
    QSqlQuery help_update_query1(dbconn);
    // Создать строку запроса
    QString sqlstr = "INSERT INTO comands (Name,Comand_Email) values(?,?)";
    QString help_select_sqlstr1 = "select company.comand_id from company where company.name = '" + ui->leCompanyName->text() + "'";
    QString help_update_sqlstr1 = "UPDATE company SET comand_id = (SELECT MAX(comands.id) from comands) WHERE name = '"+ui->leCompanyName->text()+"'";
    query.prepare(sqlstr);
    help_select_query1.prepare(help_select_sqlstr1);
    help_update_query1.prepare(help_update_sqlstr1);
    // Передать параметры из полей ввода в запрос
    query.bindValue(0,ui->leComandName->text());
    query.bindValue(1,ui->leComandEmail->text());
    //help_select_query1.bindValue(0,ui->leCompanyName->text());
    //query.bindValue(3,ui->leFIOLead->text());
    if(!help_select_query1.exec()) {
        QMessageBox::critical(this,"Error", help_select_query1.lastError().text());
        return;
    }
   if (help_select_query1.next()){
       int a = 0;
   }
   if(help_select_query1.size() == 0){
        QMessageBox::critical(this,"Error", "Введенной вами компании нет в БД");
        return;
    }
    if(!help_select_query1.value("Comand_ID").isNull()){
        QMessageBox::critical(this,"Error", "С введенной вами компанией работает другой отдел");
        return;
    }
   // Выполнить запрос
   if(!query.exec()) {
        ui->teComand->append(query.lastQuery());
        QMessageBox::critical(this,"Error",query.lastError().text());
        return;
   }
   if(!help_update_query1.exec()) {
        ui->teComand->append(query.lastQuery());
        QMessageBox::critical(this,"Error",query.lastError().text());
        return;
   }
   // Если запрос выполнен, то вывести сообщение одобавлении строки
    ui->teComand->append( QString("AddRead %1 rows").arg(query.numRowsAffected()));
    // и обновить записи в компоненте таблицы
    btnSelectAll();
}

void comand::btnBack() {
    this->close();
    adminpanel *adminp = new adminpanel(dbconn);
    adminp->show();
    return;
}

void comand::btnDelete() {
    if(!dbconn.isOpen()) {
        QMessageBox::critical(this,"Error",dbconn.lastError().text());
        return;
    }
    // Получить номер выбранной строки в компоненте таблицы
    int currow = ui->twComand->currentRow();
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
    // Создать строку запроса.
    // Вместо подготовки запроса и передачи параметров значение параметра
    // конкатенируется со строкой запроса
    // Обратите,что строковое значение помещается в одинарные кавычки
    // Значение выбирается из компонента таблицы методом item(row,col)
    QString select_comand_id;
    QString help_select_sqlstr1 = "SELECT comands.id FROM comands JOIN company c on comands.id = c.comand_id WHERE c.name = '"+ ui->twComand->item(currow,2)->text()+"' AND comands.name = '"+ui->twComand->item(currow,0)->text()+"' AND comands.comand_email = '"+ui->twComand->item(currow,1)->text()+"'";
    // Находим id для удаления
    if(!help_select_query1.exec(help_select_sqlstr1)) {
        ui->teComand->append(help_select_query1.lastQuery());
        QMessageBox::critical(this,"Error",help_select_query1.lastError().text());
        return;
    }
    if(help_select_query1.next()){
        select_comand_id = help_select_query1.value("id").toString();
    }

    // Удаляем значение из таблицы Company
    QString help_update_sqlstr1 = "UPDATE company SET Comand_ID = NULL WHERE Comand_ID = " + select_comand_id;
    if(!help_update_query1.exec(help_update_sqlstr1)) {
        ui->teComand->append(help_update_query1.lastQuery());
        QMessageBox::critical(this,"Error",help_update_query1.lastError().text());
        return;
    }
    // Удаляем значение из таблицы Comands
    QString sqlstr = "delete from comands where id = " + select_comand_id;
    if(!query.exec(sqlstr)) {
        ui->teComand->append(query.lastQuery());
        QMessageBox::critical(this,"Error",query.lastError().text());
        return;
    }
    // Вывести сообщение об удалении строки
    ui->teComand->append( QString("Del %1 rows").arg(query.numRowsAffected()) );
    // Обновить содержимое компонента таблицы
    btnSelectAll();
    return;
}

void comand::btnUpdate() {
    if(!dbconn.isOpen()) {
        QMessageBox::critical(this,"Error",dbconn.lastError().text());
        return;
    }
    // Получить номер выбранной строки в компоненте таблицы
    int currow = ui->twComand->currentRow();
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
    QString select_comand_id;
    QString help_select_sqlstr1 = "SELECT comands.id FROM comands JOIN company c on comands.id = c.comand_id WHERE c.name = '"+ ui->twComand->item(currow,2)->text()+"' AND comands.name = '"+ui->twComand->item(currow,0)->text()+"' AND comands.comand_email = '"+ui->twComand->item(currow,1)->text()+"'";
    // Находим id для update
    if(!help_select_query1.exec(help_select_sqlstr1)) {
        ui->teComand->append(help_select_query1.lastQuery());
        QMessageBox::critical(this,"Error",help_select_query1.lastError().text());
        return;
    }
    if(help_select_query1.next()){
        select_comand_id = help_select_query1.value("id").toString();
    }
    //
    QSqlQuery query(dbconn);
    if (ui->leComandName->text() != "") {
        QString sqlstr = "update comands set name = '" + ui->leComandName->text() + "' where id = " + select_comand_id;
        if(!query.exec(sqlstr)) {
            ui->teComand->append(query.lastQuery());
            QMessageBox::critical(this,"Error",query.lastError().text());
            return;
        }
    }

    if (ui->leComandEmail->text() != "") {
        QString sqlstr = "update comands set comand_email = '" + ui->leComandEmail->text() + "' where id = " + select_comand_id;
        if(!query.exec(sqlstr)) {
            ui->teComand->append(query.lastQuery());
            QMessageBox::critical(this,"Error",query.lastError().text());
            return;
        }
    }

    if (ui->leCompanyName->text() != "") {
        QSqlQuery help_select_query2(dbconn);
        QSqlQuery help_update_query2(dbconn);
        QString help_select_sqlstr2 = "select company.comand_id from company where company.name = '" + ui->leCompanyName->text() + "'";
        QString help_update_sqlstr2 = "UPDATE company SET comand_id = '"+ select_comand_id +"' WHERE name = '"+ui->leCompanyName->text()+"'";
        if(!help_select_query2.exec(help_select_sqlstr2)) {
            QMessageBox::critical(this,"Error", help_select_query2.lastError().text());
            return;
        }
       if (help_select_query2.next()){
           int a = 0;
       }
       if(help_select_query2.size() == 0){
            QMessageBox::critical(this,"Error", "Введенной вами компании нет в БД");
            return;
        }
        if(!help_select_query2.value("Comand_ID").isNull()){
            QMessageBox::critical(this,"Error", "С введенной вами компанией работает другой отдел");
            return;
        }
        if(!help_update_query2.exec(help_update_sqlstr2)) {
             ui->teComand->append(query.lastQuery());
             QMessageBox::critical(this,"Error",query.lastError().text());
             return;
        }
    }


    ui->teComand->append(QString("Updated %1 rows").arg(query.numRowsAffected()));
    btnSelectAll();
    return;
}

void comand::btnSearch() {
    ui->twComand->clearContents();

    if (!dbconn.isOpen()) {
        QMessageBox::critical(this,"Error",dbconn.lastError().text());
        return;
    }

    QSqlQuery query(dbconn);

    QString sqlstr = "select comands.name, comands.comand_email, c.name AS Company_name from comands join company c on comands.id = c.comand_id where comands.name = '" + ui->leComandNameSearch->text() + "'";

    if(!query.exec(sqlstr)) {
        QMessageBox::critical(this,"Error", query.lastError().text());
        return;
    }


    if(query.isActive()) {
        ui->twComand->setRowCount( query.size());
    } else {
        ui->twComand->setRowCount(0);
    }
    ui->teComand->append(QString("Read %1 rows").arg(query.size()));

    // Прочитать в цикле все строки результата (курсора)
    // и вывести их в компонент таблицы
    int i=0;
    while(query.next()) {
//        ui->twComand->setItem(i,0,new
//        QTableWidgetItem(query.value("ID отдела").toString()));

        ui->twComand->setItem(i,0,new
        QTableWidgetItem(query.value("name").toString()));

        ui->twComand->setItem(i,1,new
        QTableWidgetItem(query.value("comand_email").toString()));

        ui->twComand->setItem(i,2,new
        QTableWidgetItem(query.value("Company_name").toString()));

        i++;
    }

    return;
}


void comand::on_twComand_cellClicked(int row, int column)
{
    ui->leComandName->setText(ui->twComand->item(row,0)->text());
    ui->leComandEmail->setText(ui->twComand->item(row,1)->text());
    ui->leCompanyName->setText(ui->twComand->item(row,2)->text());
}
