#include"Auth.h"
#include<QMessageBox>


#include "forgotpasspage.h"
#include "ui_forgotpasspage.h"



ForgotPassPage::ForgotPassPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ForgotPassPage)
{
    ui->setupUi(this);
    this->ui->Confirmbtn->setStyleSheet("background-color:transparent");
}


ForgotPassPage::~ForgotPassPage()
{
    delete ui;
}

void ForgotPassPage::on_Confirmbtn_clicked()
{
    QString phoneNumber = ui->phoneLine->text() ;
    QString username = ui->userLine->text() ;
    if ( Auth::isHintValid(username , phoneNumber) == -1 )
    {
        QMessageBox * msgb = new QMessageBox(QMessageBox::Icon::Critical , "Invalid usernme or phone number" , "the usernme or phone number doesn't match or doesn't exist at all. please check your answers again" , QMessageBox::Button::Ok);
        QObject::connect(msgb , &QMessageBox::buttonClicked , msgb , &QMessageBox::deleteLater);
        return ;
    }




    EntereNewPass* enp = new EntereNewPass;   
    enp->show();
    close();

}

