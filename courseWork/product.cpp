#include "product.h"
#include "ui_product.h"
#include "adminpanel.h"
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QString>

product::product(QSqlDatabase dbconn, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::product)
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

    ui->twProduct->setColumnCount(4);
    // Возможность прокрутки
    ui->twProduct->setAutoScroll(true);
    // Режим выделения ячеек - только одна строка
    ui->twProduct->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->twProduct->setSelectionBehavior(QAbstractItemView::SelectRows);
    // Заголовки таблицы
//    ui->twComand->setHorizontalHeaderItem(0,new QTableWidgetItem("ID IT продукта"));
    ui->twProduct->setHorizontalHeaderItem(0,new QTableWidgetItem("Название проекта"));
    ui->twProduct->setHorizontalHeaderItem(1,new QTableWidgetItem("Название отдела"));
    ui->twProduct->setHorizontalHeaderItem(2,new QTableWidgetItem("Название компании зачазчика"));
    ui->twProduct->setHorizontalHeaderItem(3,new QTableWidgetItem("Последняя версия"));
    // Последний столбец растягивается при изменении размера формы
    ui->twProduct->horizontalHeader()->setStretchLastSection(true);
    // Разрешаем сортировку пользователю
    ui->twProduct->setSortingEnabled(true);
    ui->twProduct->sortByColumn(4);
    // Запрет на изменение ячеек таблицы при отображении
    ui->twProduct->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

product::~product()
{
    delete ui;
}

void product::btnSelectAll(){
    ui->twProduct->clearContents();

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
        ui->twProduct->setRowCount(query.size());
    } else {
        ui->twProduct->setRowCount(0);
    }
    ui->teProduct->append(QString("Read %1 rows").arg(query.size()));
    // Прочитать в цикле все строки результата (курсора)
        // и вывести их в компонент таблицы
    int i=0;
    while(query.next()) {
//        ui->twComand->setItem(i,0,new
//        QTableWidgetItem(query.value("ID_IT_продукта").toString()));

        ui->twProduct->setItem(i,0,new
        QTableWidgetItem(query.value("name").toString()));

        ui->twProduct->setItem(i,1,new
        QTableWidgetItem(query.value("Comand_name").toString()));

        ui->twProduct->setItem(i,2,new
        QTableWidgetItem(query.value("Company_name").toString()));

        ui->twProduct->setItem(i,3,new
        QTableWidgetItem(query.value("Version_name").toString()));

        i++;
     }

     return;
}

void product::btnAdd() {
    if(!dbconn.isOpen()) {
        QMessageBox::critical(this,"Error",dbconn.lastError().text());
        return;
        }
    QSqlQuery query(dbconn);
    QSqlQuery help_query1(dbconn);
    QSqlQuery help_query2(dbconn);
    QSqlQuery help_query3(dbconn);
    // Создать строку запроса
    QString sqlstr = "insert into products (name, comand_id, company_id) values(?,?,?)";
    QString help_sqlstr1 = "select company.id AS Company_id, c.id AS Comand_id, c.name AS Comand_name from company JOIN comands c on company.comand_id = c.id WHERE company.name = '"+ui->leCompanyNameProduct->text()+"'";
    QString help_sqlstr2 = "select comands.id as Comand_id from comands WHERE comands.name = '"+ui->leComandNameProduct->text()+"'";
    QString help_sqlstr3 = "insert into versions (name, version_date, product_id) values ('0.0.1', current_date,(select MAX(products.id) from products))";
    // Подготовить запрос
    query.prepare(sqlstr);
    help_query1.prepare(help_sqlstr1);
    if( !help_query1.exec(help_sqlstr1)) {
        QMessageBox::critical(this,"Error", help_query1.lastError().text());
        return;
    }
    help_query2.prepare(help_sqlstr2);
    if( !help_query2.exec(help_sqlstr2)) {
        QMessageBox::critical(this,"Error", help_query2.lastError().text());
        return;
    }
    if(help_query1.next()){
        int a = 2;
    }
    if(help_query2.next()){
        int b = 2;
    }
    if(help_query1.value("Comand_id").toInt() != help_query2.value("Comand_id").toInt()){
        QMessageBox::critical(this,"Error", "Выбранная вами компания работает c отделом" + help_query1.value("Comand_name").toString() );
        return;
    }

    // Передать параметры из полей ввода в запрос
    if(!help_query1.value("Comand_id").isNull() && !help_query1.value("Company_id").isNull()){
    query.bindValue(0,ui->leNameProduct->text());
    query.bindValue(1,help_query1.value("Comand_id").toInt());
    query.bindValue(2,help_query1.value("Company_id").toInt());
    }
    else{
        QMessageBox::critical(this,"Error","Некорректные данные");
        return;
    }

    // Выполнить запрос
    if(!query.exec()) {
        ui->teProduct->append(query.lastQuery());
        QMessageBox::critical(this,"Error",query.lastError().text());
        return;
    }

    help_query3.prepare(help_sqlstr3);
    if(!help_query3.exec()) {
        ui->teProduct->append(help_query3.lastQuery());
        QMessageBox::critical(this,"Error",help_query3.lastError().text());
        return;
    }
    // Если запрос выполнен, то вывести сообщение одобавлении строки
    ui->teProduct->append( QString("AddRead %1 rows").arg(query.numRowsAffected()));
    // и обновить записи в компоненте таблицы
    btnSelectAll();
}

void product::btnBack() {
    this->close();
    adminpanel *adminp = new adminpanel(dbconn);
    adminp->show();
    return;
}

void product::btnDelete() {
    if(!dbconn.isOpen()) {
        QMessageBox::critical(this,"Error",dbconn.lastError().text());
        return;
    }
    // Получить номер выбранной строки в компоненте таблицы
    int currow = ui->twProduct->currentRow();
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
    QSqlQuery help_delete_query1(dbconn);
    // Создать строку запроса.
    // Вместо подготовки запроса и передачи параметров значение параметра
    // конкатенируется со строкой запроса
    // Обратите,что строковое значение помещается в одинарные кавычки
    // Значение выбирается из компонента таблицы методом item(row,col)
    QString select_product_id;
    QString help_select_sqlstr1 = "SELECT products.id FROM products JOIN comands c on products.comand_id = c.id JOIN company c2 on products.company_id = c2.id WHERE products.name = '"+ui->twProduct->item(currow,0)->text()+"' AND c.id = (SELECT comands.id from comands WHERE comands.name ='"+ui->twProduct->item(currow,1)->text()+"') AND c2.id = (SELECT company.id from company WHERE company.name ='"+ui->twProduct->item(currow,2)->text()+"')" ;
    if(!help_select_query1.exec(help_select_sqlstr1)) {
        ui->teProduct->append(help_select_query1.lastQuery());
        QMessageBox::critical(this,"Error",help_select_query1.lastError().text());
        return;
    }
    if(help_select_query1.next()){
        select_product_id = help_select_query1.value("id").toString();
    }

    QString sqlstr = "delete from products where id = " + select_product_id;
    // Удаляем записи из versions
    QString help_delete_sqlstr1 = "DELETE FROM versions WHERE product_id = " + select_product_id;
    if(!help_delete_query1.exec(help_delete_sqlstr1)) {
        ui->teProduct->append(help_delete_query1.lastQuery());
        QMessageBox::critical(this,"Error",help_delete_query1.lastError().text());
        return;
    }

    // Выполнить строку запроса и проверить его успешность
    if(!query.exec(sqlstr)) {
        ui->teProduct->append(query.lastQuery());
        QMessageBox::critical(this,"Error",query.lastError().text());
        return;
    }

    // Вывести сообщение об удалении строки
    ui->teProduct->append( QString("Del %1 rows").arg(query.numRowsAffected()) );
    // Обновить содержимое компонента таблицы
    btnSelectAll();
    return;
}

void product::btnUpdate() {
    if(!dbconn.isOpen()) {
        QMessageBox::critical(this,"Error",dbconn.lastError().text());
        return;
    }
    // Получить номер выбранной строки в компоненте таблицы
    int currow = ui->twProduct->currentRow();
    // Если он меньше 0 (строка не выбрана), то
    // сообщение об ошибке и выход из функции
    if(currow < 0) {
        QMessageBox::critical(this,"Error","Not selected row!");
        return;
    }

    if( QMessageBox::question(this,"Update","Update row?",
    QMessageBox::Cancel,QMessageBox::Ok)==QMessageBox::Cancel)
    return;

//    QSqlQuery query(dbconn);
    QSqlQuery help_select_query1(dbconn);
    QString select_product_id;
    QString select_comand_id;
    QString help_select_sqlstr1 = "SELECT products.id FROM products JOIN comands c on products.comand_id = c.id JOIN company c2 on products.company_id = c2.id WHERE products.name = '"+ui->twProduct->item(currow,0)->text()+"' AND c.id = (SELECT comands.id from comands WHERE comands.name ='"+ui->twProduct->item(currow,1)->text()+"') AND c2.id = (SELECT company.id from company WHERE company.name ='"+ui->twProduct->item(currow,2)->text()+"')" ;
    // Находим id для update
    if(!help_select_query1.exec(help_select_sqlstr1)) {
        ui->teProduct->append(help_select_query1.lastQuery());
        QMessageBox::critical(this,"Error",help_select_query1.lastError().text());
        return;
    }
    if(help_select_query1.next()){
        select_product_id = help_select_query1.value("id").toString();
    }
    //
    QSqlQuery query(dbconn);
    if (ui->leNameProduct->text() != "") {
        QString sqlstr = "update products set name = '" + ui->leNameProduct->text() + "'where id = " + select_product_id;
        if(!query.exec(sqlstr)) {
            ui->teProduct->append(query.lastQuery());
            QMessageBox::critical(this,"Error",query.lastError().text());
            return;
        }
    }

    if (ui->leComandNameProduct->text() != "") {
        QSqlQuery help_select_query2(dbconn);
        QSqlQuery help_select_query3(dbconn);
        QSqlQuery help_update_query2(dbconn);
        QString help_sqlstr2 = "select comands.id from comands WHERE comands.name = '"+ ui->leComandNameProduct->text() + "'";

        help_select_query2.prepare(help_sqlstr2);
        if( !help_select_query2.exec(help_sqlstr2)) {
            QMessageBox::critical(this,"Error", help_select_query2.lastError().text());
            return;
        }
        if (help_select_query2.next()){
             select_product_id = help_select_query2.value("id").toString();
        }
        QString help_sqlstr3 = "select company.id from company JOIN comands c on company.comand_id = c.id WHERE c.id = "+ select_product_id;
        help_select_query3.prepare(help_sqlstr3);
        if( !help_select_query3.exec(help_sqlstr3)) {
            QMessageBox::critical(this,"Error", help_select_query3.lastError().text());
            return;
        }
        if (help_select_query3.next()){
            select_comand_id = help_select_query3.value("id").toString();
        }
        if(help_select_query2.size() == 0){
             QMessageBox::critical(this,"Error", "Введенного вами отдела нет в БД");
             return;
         }
         if(!help_select_query3.value("id").isNull()){
             QMessageBox::critical(this,"Error", "Введенной вами отдел работает с другой компанией");
             return;
         }
        QString sqlstr = "update products SET comand_id = " + select_product_id + "WHERE product_id = " + select_comand_id;
        if(!query.exec(sqlstr)) {
            ui->teProduct->append(query.lastQuery());
            QMessageBox::critical(this,"Error",query.lastError().text());
            return;
        }
    }

    if (ui->leCompanyNameProduct->text() != "") {
        QSqlQuery help_select_query2(dbconn);
        QSqlQuery help_select_query3(dbconn);
        QSqlQuery help_update_query2(dbconn);
        QString help_sqlstr2 = "select company.id from company WHERE company.name = '"+ ui->leCompanyNameProduct->text() + "'";
        help_select_query2.prepare(help_sqlstr2);
        if( !help_select_query2.exec(help_sqlstr2)) {
            QMessageBox::critical(this,"Error", help_select_query2.lastError().text());
            return;
        }
        if (help_select_query2.next()){
             select_product_id = help_select_query2.value("id").toString();
        }
        QString help_sqlstr3 = "select comands.id from comands JOIN company c on comands.id = c.comand_id WHERE c.id = " + select_product_id;
        help_select_query3.prepare(help_sqlstr3);
        if( !help_select_query3.exec(help_sqlstr3)) {
            QMessageBox::critical(this,"Error", help_select_query3.lastError().text());
            return;
        }
        if (help_select_query3.next()){
            select_comand_id = help_select_query3.value("id").toString();
        }
        if(help_select_query2.size() == 0){
             QMessageBox::critical(this,"Error", "Введенной вами компании нет в БД");
             return;
         }
         if(!help_select_query3.value("id").isNull()){
             QMessageBox::critical(this,"Error", "С введенной вами компанией работает другой отдел");
             return;
         }
        QString sqlstr = "update products SET company_id = " + select_product_id + "WHERE comand_id = " + select_comand_id;
        if(!query.exec(sqlstr)) {
            ui->teProduct->append(query.lastQuery());
            QMessageBox::critical(this,"Error",query.lastError().text());
            return;
        }
    }

    ui->teProduct->append(QString("Updated %1 rows").arg(query.numRowsAffected()));
    btnSelectAll();
    return;
}


void product::btnSearch() {
    ui->twProduct->clearContents();

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
        ui->twProduct->setRowCount( query.size());
    } else {
        ui->twProduct->setRowCount(0);
    }
    ui->teProduct->append(QString("Read %1 rows").arg(query.size()));

    // Прочитать в цикле все строки результата (курсора)
    // и вывести их в компонент таблицы
    int i=0;
    while(query.next()) {
//        ui->twComand->setItem(i,0,new
//        QTableWidgetItem(query.value("ID_разработчика").toString()));

        ui->twProduct->setItem(i,0,new
        QTableWidgetItem(query.value("name").toString()));

        ui->twProduct->setItem(i,1,new
        QTableWidgetItem(query.value("Comand_name").toString()));

        ui->twProduct->setItem(i,2,new
        QTableWidgetItem(query.value("Company_name").toString()));

        ui->twProduct->setItem(i,3,new
        QTableWidgetItem(query.value("Version_name").toString()));

        i++;
    }

    return;
}

void product::on_twProduct_cellClicked(int row, int column)
{
    ui->leNameProduct->setText(ui->twProduct->item(row,0)->text());
    ui->leComandNameProduct->setText(ui->twProduct->item(row,1)->text());
    ui->leCompanyNameProduct->setText(ui->twProduct->item(row,2)->text());
    ui->leVersionProduct->setText(ui->twProduct->item(row,3)->text());
}
