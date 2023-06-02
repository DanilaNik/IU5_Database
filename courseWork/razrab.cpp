#include "razrab.h"
#include "ui_razrab.h"
#include "adminpanel.h"
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>

razrab::razrab(QSqlDatabase dbconn, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::razrab)
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

    ui->twRazrab->setColumnCount(6);
    // Возможность прокрутки
    ui->twRazrab->setAutoScroll(true);
    // Режим выделения ячеек - только одна строка
    ui->twRazrab->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->twRazrab->setSelectionBehavior(QAbstractItemView::SelectRows);
    // Заголовки таблицы
//    ui->twComand->setHorizontalHeaderItem(0,new QTableWidgetItem("ID_разработчика"));
    ui->twRazrab->setHorizontalHeaderItem(0,new QTableWidgetItem("ФИО"));
    ui->twRazrab->setHorizontalHeaderItem(1,new QTableWidgetItem("Email"));
    ui->twRazrab->setHorizontalHeaderItem(2,new QTableWidgetItem("Номер телефона"));
    ui->twRazrab->setHorizontalHeaderItem(3,new QTableWidgetItem("Должность"));
    ui->twRazrab->setHorizontalHeaderItem(4,new QTableWidgetItem("Отдел"));
    ui->twRazrab->setHorizontalHeaderItem(5,new QTableWidgetItem("Режим работы"));
    // Последний столбец растягивается при изменении размера формы
    ui->twRazrab->horizontalHeader()->setStretchLastSection(true);
    // Разрешаем сортировку пользователю
    ui->twRazrab->setSortingEnabled(true);
    ui->twRazrab->sortByColumn(6);
    // Запрет на изменение ячеек таблицы при отображении
    ui->twRazrab->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

razrab::~razrab()
{
    delete ui;
}

void razrab::btnSelectAll(){
    ui->twRazrab->clearContents();

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
        ui->twRazrab->setRowCount(query.size());
    } else {
        ui->twRazrab->setRowCount(0);
    }
    ui->teRazrab->append(QString("Read %1 rows").arg(query.size()));
    // Прочитать в цикле все строки результата (курсора)
        // и вывести их в компонент таблицы
    int i=0;
    while(query.next()) {
//        ui->twComand->setItem(i,0,new
//        QTableWidgetItem(query.value("ID разработчика").toString()));

        ui->twRazrab->setItem(i,0,new
        QTableWidgetItem(query.value("fio").toString()));

        ui->twRazrab->setItem(i,1,new
        QTableWidgetItem(query.value("email").toString()));

        ui->twRazrab->setItem(i,2,new
        QTableWidgetItem(query.value("phone").toString()));

        ui->twRazrab->setItem(i,3,new
        QTableWidgetItem(query.value("post").toString()));

        ui->twRazrab->setItem(i,4,new
        QTableWidgetItem(query.value("comand_name").toString()));

        ui->twRazrab->setItem(i,5,new
        QTableWidgetItem(query.value("working_mode").toString()));
        i++;
     }

     return;
}

void razrab::btnAdd() {
    if(!dbconn.isOpen()) {
        QMessageBox::critical(this,"Error",dbconn.lastError().text());
        return;
        }
    QSqlQuery query(dbconn);
    QSqlQuery help_select_query1(dbconn);
    // Создать строку запроса
    int selected_comand_id;
    QString sqlstr = "insert into developers (fio,email,phone,post, comand_id, working_mode) values(?,?,?,?,?,?)";
    QString help_select_sqlstr1 = "select comands.id from comands where comands.name = '"+ ui->leComandRazrab->text()+"'";
    // Подготовить запрос
    //query.prepare(sqlstr);
    help_select_query1.prepare(help_select_sqlstr1);
    if(!help_select_query1.exec()) {
        QMessageBox::critical(this,"Error", help_select_query1.lastError().text());
        return;
    }
   if (help_select_query1.next()){
       selected_comand_id = help_select_query1.value("id").toInt();
   }
   if(help_select_query1.size() == 0){
        QMessageBox::critical(this,"Error", "Введенного вами отдела нет в БД");
        return;
    }
    // Передать параметры из полей ввода в запрос
    query.bindValue(0,ui->leFIORazrab->text());
    query.bindValue(1,ui->leEmailRazrab->text());
    query.bindValue(2,ui->lePhoneRazrab->text());
    query.bindValue(3,ui->lePostRazrab->text());
    query.bindValue(4,help_select_query1.value("id").toInt());


    if (ui->radOffice->isChecked()) {
        query.bindValue(5,"Full-time");
    } else {
        query.bindValue(5,"Part-time");
    }
    query.prepare(sqlstr);
    // Выполнить запрос
    if(!query.exec(sqlstr)) {
        ui->teRazrab->append(query.lastQuery());
        QMessageBox::critical(this,"Error",query.lastError().text());
        return;
    }
    // Если запрос выполнен, то вывести сообщение одобавлении строки
    ui->teRazrab->append( QString("AddRead %1 rows").arg(query.numRowsAffected()));
    // и обновить записи в компоненте таблицы
    btnSelectAll();
}

void razrab::btnBack() {
    this->close();
    adminpanel *adminp = new adminpanel(dbconn);
    adminp->show();
    return;
}

void razrab::btnDelete() {
    if(!dbconn.isOpen()) {
        QMessageBox::critical(this,"Error",dbconn.lastError().text());
        return;
    }
    // Получить номер выбранной строки в компоненте таблицы
    int currow = ui->twRazrab->currentRow();
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
    // Создать строку запроса.
    // Вместо подготовки запроса и передачи параметров значение параметра
    // конкатенируется со строкой запроса
    // Обратите,что строковое значение помещается в одинарные кавычки
    // Значение выбирается из компонента таблицы методом item(row,col)
    QString sqlstr = "delete from developers where id = "
    + ui->twRazrab->item(currow,0)->text();
    // Выполнить строку запроса и проверить его успешность
    if(!query.exec(sqlstr)) {
        ui->teRazrab->append(query.lastQuery());
        QMessageBox::critical(this,"Error",query.lastError().text());
        return;
    }
    // Вывести сообщение об удалении строки
    ui->teRazrab->append( QString("Del %1 rows").arg(query.numRowsAffected()) );
    // Обновить содержимое компонента таблицы
    btnSelectAll();
    return;
}

void razrab::btnUpdate() {
    if(!dbconn.isOpen()) {
        QMessageBox::critical(this,"Error",dbconn.lastError().text());
        return;
    }
    // Получить номер выбранной строки в компоненте таблицы
    int currow = ui->twRazrab->currentRow();
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
    QSqlQuery query(dbconn);
    QString select_developers_id;
    QString help_select_sqlstr1 = "select developers.id from developers where developers.fio = '" + ui->twRazrab->item(currow,0)->text() +"' and developers.email = '" + ui->twRazrab->item(currow,1)->text() + "'";
    if(!help_select_query1.exec(help_select_sqlstr1)) {
        ui->teRazrab->append(help_select_query1.lastQuery());
        QMessageBox::critical(this,"Error",help_select_query1.lastError().text());
        return;
    }
    if(help_select_query1.next()){
        select_developers_id = help_select_query1.value("id").toString();
    }

    if (ui->leFIORazrab->text() != "") {
        QString sqlstr = "update developers set fio = '"
        + ui->leFIORazrab->text() + "' where id = " + select_developers_id;
        if(!query.exec(sqlstr)) {
            ui->teRazrab->append(query.lastQuery());
            QMessageBox::critical(this,"Error",query.lastError().text());
            return;
        }
    }

    if (ui->leEmailRazrab->text() != "") {
        QString sqlstr = "update developers set email = '"
        + ui->leEmailRazrab->text() + "' where id = " + select_developers_id;
        if(!query.exec(sqlstr)) {
            ui->teRazrab->append(query.lastQuery());
            QMessageBox::critical(this,"Error",query.lastError().text());
            return;
        }
    }

    if (ui->lePhoneRazrab->text() != "") {
        QString sqlstr = "update developers set phone = '"
        + ui->lePhoneRazrab->text() + "' where id = " + select_developers_id;
        if(!query.exec(sqlstr)) {
            ui->teRazrab->append(query.lastQuery());
            QMessageBox::critical(this,"Error",query.lastError().text());
            return;
        }
    }

    if (ui->lePostRazrab->text() != "") {
        QString sqlstr = "update developers set post = '"
        + ui->lePostRazrab->text() + "' where id = " + select_developers_id;
        if(!query.exec(sqlstr)) {
            ui->teRazrab->append(query.lastQuery());
            QMessageBox::critical(this,"Error",query.lastError().text());
            return;
        }
    }

    if (ui->radOffice->isChecked()) {
        QString sqlstr = "update developers set working_mode = 'Full-time' where id = " + select_developers_id;
        if(!query.exec(sqlstr)) {
            QMessageBox::critical(this,"Error",query.lastError().text());
            return;
        }
    } else {
        QString sqlstr = "update developers set working_mode = 'Part-time' where id = " + select_developers_id;
        if(!query.exec(sqlstr)) {
            QMessageBox::critical(this,"Error",query.lastError().text());
            return;
        }
    }

    ui->teRazrab->append(QString("Updated %1 rows").arg(query.numRowsAffected()));
    btnSelectAll();
    return;
}

void razrab::btnSearch() {
    ui->twRazrab->clearContents();

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
        ui->twRazrab->setRowCount( query.size());
    } else {
        ui->twRazrab->setRowCount(0);
    }
    ui->teRazrab->append(QString("Read %1 rows").arg(query.size()));

    // Прочитать в цикле все строки результата (курсора)
    // и вывести их в компонент таблицы
    int i=0;
    while(query.next()) {
//        ui->twComand->setItem(i,0,new
//        QTableWidgetItem(query.value("ID_разработчика").toString()));

        ui->twRazrab->setItem(i,0,new
        QTableWidgetItem(query.value("fio").toString()));

        ui->twRazrab->setItem(i,1,new
        QTableWidgetItem(query.value("email").toString()));

        ui->twRazrab->setItem(i,2,new
        QTableWidgetItem(query.value("phone").toString()));

        ui->twRazrab->setItem(i,3,new
        QTableWidgetItem(query.value("post").toString()));

        ui->twRazrab->setItem(i,4,new
        QTableWidgetItem(query.value("comand_name").toString()));

        ui->twRazrab->setItem(i,5,new
        QTableWidgetItem(query.value("working_mode").toString()));
        i++;
    }

    return;
}

void razrab::on_twRazrab_cellClicked(int row, int column)
{
    ui->leFIORazrab->setText(ui->twRazrab->item(row,0)->text());
    ui->leEmailRazrab->setText(ui->twRazrab->item(row,1)->text());
    ui->lePhoneRazrab->setText(ui->twRazrab->item(row,2)->text());
    ui->lePostRazrab->setText(ui->twRazrab->item(row,3)->text());
    ui->leComandRazrab->setText(ui->twRazrab->item(row,4)->text());
    ui->radOffice->setText(ui->twRazrab->item(row,5)->text());
}
