#include "studentmainmenu.h"
#include "ui_studentmainmenu.h"
#include <QMessageBox>
#include <QAbstractButton>
#include <QPushButton>
#include "loginpage.h"
#include "studentprofile.h"

StudentMainMenu::StudentMainMenu(QWidget *parent) :
//    QWidget(parent),
    ui(new Ui::StudentMainMenu)
{
    ui->setupUi(this);
    this->ui->pushButton->setStyleSheet("background-color:transparent");
    this->ui->pushButton_2->setStyleSheet("background-color:transparent");
    this->ui->pushButton_3->setStyleSheet("background-color:transparent");
    this->ui->pushButton_4->setStyleSheet("background-color:transparent");
    this->ui->pushButton_5->setStyleSheet("background-color:transparent");
    this->ui->label_8->setStyleSheet("background-color: #f0f0f0; border-radius: 20px;");

}

StudentMainMenu::~StudentMainMenu()
{
    delete ui;
}

void StudentMainMenu::surveyOfTeachers(QString lesson, int result )
{
    for (auto i = this->teachers.begin() ; i!=this->teachers.end() ; i++ )
    {
        if (lesson == i.key())
        {

        }
    }
}





void StudentMainMenu::on_pushButton_5_clicked()
{
    QMessageBox* exit = new QMessageBox(QMessageBox::Warning,"Close Window","Do you want to close this window?");
    exit->setStandardButtons(QMessageBox::Yes);
    exit->addButton(QMessageBox::No);
    exit->setDefaultButton(QMessageBox::No);
    exit->show();
    if(exit->exec() == QMessageBox::Yes){
        LoginPage* lg = new LoginPage;
        lg->show();
        exit->close();
        close();
    }
    else{
        exit->close();
    }
}


void StudentMainMenu::on_pushButton_clicked()
{
    StudentProfile* sp = new StudentProfile;
    sp->show();
    close();
}

