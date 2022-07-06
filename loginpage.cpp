#include <QMessageBox>
#include <iostream>
#include<QAbstractButton>


#include "Auth.h"
#include "Filemanager.h"
#include "loginpage.h"
#include "studentmainmenu.h"
#include "adminmainmenu.h"
#include "teachermainmenu.h"
// for hash class
#include <functional>

#include "ui_loginpage.h"

using std::hash;

LoginPage::LoginPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginPage)
{
    ui->setupUi(this);
    this->ui->forgotPass->setStyleSheet("background-color:transparent");
    this->ui->Loginbtn->setStyleSheet("background-color:transparent");

    ui->passLine->setEchoMode(QLineEdit::Password);
    connect(ui->showPass, SIGNAL(clicked(bool)), this, SLOT(on_showPass_clicked(bool)));

    StudentMainMenu smm(this);

    smm.set_username("65564");

    smm.load();

    smm.addTerm();

    for(auto& i : smm.getAverages())
        qDebug() << i;

}

LoginPage::~LoginPage()
{
    delete ui;
}

void LoginPage::on_showPass_clicked(bool checked)
{
    if (checked==true){
        ui->passLine->setEchoMode(QLineEdit::Normal);
    }

    else{
        ui->passLine->setEchoMode(QLineEdit::Password);
    }
}


void LoginPage::on_forgotPass_clicked(bool checked)
{
    ForgotPassPage* fpg = new ForgotPassPage;
    fpg->show();
    close();
}

int LoginPage::isUserValid()
{
    hash<QString> passHasher;

    QString username = ui->userLine->text();
    QString password = QString::number(passHasher(ui->passLine->text()));

    return Auth::canLogin(username, password);
}

void LoginPage::on_Loginbtn_clicked()
{
    int userIndex=  isUserValid();


    if(userIndex == -1)
    {
        QMessageBox* loginStatus = new QMessageBox(
            QMessageBox::Critical,
            "Can't Login",
            "Username or password is wrong, please enter valid information.",
            QMessageBox::Ok
            );


        loginStatus->show();
        connect(loginStatus ,
                &QMessageBox::buttonClicked ,
                loginStatus ,
                &QMessageBox::deleteLater
                );
        return;
    }

    FileManager userFile;

    userFile.create();

    userFile.loadData();

    QString wantedUser = userFile.getRecord(userIndex);

    auto parsedUser = userFile.parse(wantedUser);

    QString userType = parsedUser[parsedUser.size() - 1];

    if(userType == "Admin")
    {
        AdminMainMenu* amm = new AdminMainMenu;
        amm->set_username(ui->userLine->text());
        amm->set_password(ui->passLine->text());
        amm->show();
    }
    else if(userType == "Teacher")
    {
        TeacherMainMenu* tmm = new TeacherMainMenu;
        tmm->set_username(ui->userLine->text());
        tmm->set_password(ui->passLine->text());
        tmm->show();

    }
    else if (userType == "Student")
    {
        StudentMainMenu* smm = new StudentMainMenu;
        smm->set_username(ui->userLine->text());
        smm->set_password(ui->passLine->text());
        smm->show();
    }
//    else


    close();
}
