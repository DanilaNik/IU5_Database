#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QMainWindow>
#include "adminpanel.h"
#include "userpanel.h"
#include <QSqlDatabase>
#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QMainWindow>
#include <QMessageBox>
#include <QSqlQuery>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    adminpanel *AP;
    userpanel *UP;
    QSqlDatabase dbconn;
    QLabel *m_errorLabel;

public slots:
    void btnLogin();
};
#endif // MAINWINDOW_H
