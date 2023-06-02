#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QMessageBox>
#include <QDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap bkgnd("/home/nikulin_danila/Документы/CourseDB/db3.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
    connect(ui->btnLogin, SIGNAL(clicked(bool)), this, SLOT(btnLogin()));
    m_errorLabel = new QLabel();
    m_errorLabel->setStyleSheet("QLabel { color : red; }");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::btnLogin() {
    if (!dbconn.isOpen()) {
        dbconn=QSqlDatabase::addDatabase("QPSQL");
        // Установить параметры соединения: имя БД, адрес хоста, логин и пароль
        dbconn.setDatabaseName(/*"DB name"*/);
        dbconn.setHostName(/*"DB host"*/);
        dbconn.setUserName(/*"DB user"*/);
        dbconn.setPassword(/*"DB password"*/);
        // Открыть соединениe и результат вывести в окно вывода
        if(!dbconn.open()) {
            QMessageBox::warning(this,"Ошибка","Сервер в данное время не доступен");
            return;
        }
    } else {
        // Если соединение уже открыто, то сообщить об этом
        m_errorLabel->setText("Connect is already open...");
    }
    QString login = ui->comboBox->currentText();
    QString password = ui->lePassword->text();
    if (login == "admin" && password == "qwerty") {
        AP = new adminpanel(dbconn);
        this->close();
        AP->show();
    } else if (login == "user" && password == "12345") {
        UP = new userpanel(dbconn);
        this->close();
        UP->show();
    } else {
        QMessageBox::warning(this,"Ошибка","Неверный логин или пароль");
    }

    return;
}
