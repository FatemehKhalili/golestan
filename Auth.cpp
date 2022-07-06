#include <QString>

#include "Filemanager.h"
#include "Auth.h"

// for hashing
#include "Md5Hash.h"

#include <exception>

using std::hash, std::string, std::exception;

Auth::Auth()
{
    return;
}

Auth::~Auth()
{
    return;
}

QString Auth::formUserData(QString username, QString password, QString firstname, QString lastname, QString nationalCode, QString phoneNumber, QString role, bool hashPass)
{
    // just used ternary operator for more simplicity
    QString mergedData = username + '\t' +
                         (hashPass ? QString::fromStdString(md5(password.toStdString())) : password) + '\t' +
                         firstname + '\t' +
                         lastname + '\t' +
                         nationalCode + '\t' +
                         phoneNumber + '\t'
                         + role;

    return mergedData;
}

QString Auth::formUserData(QString teacherusername, QString lesson)
{
    QString mergedData = teacherusername + '\t' +
                         lesson;

    return mergedData;
}
/*
int Auth::validStudent(QString studentusername, QString lesson)
{
    FileManager usersFile;

    usersFile.create("teachers.txt");

    usersFile.loadData();

    auto& dataCopy = usersFile.getData();

    for(int i = 0; i < dataCopy.size(); i++)
    {
        QVector<QString> parsedUser = usersFile.parse(dataCopy.at(i));

        if(parsedUser.at(1) == studentusername && parsedUser.at(2) == lesson)
            return i;
    }

    return -1;
}
*/
int Auth::canLogin(QString username, QString password)
{
    FileManager usersFile;

    usersFile.create("users.txt");

    usersFile.loadData();

    auto& dataCopy = usersFile.getData();

    for(int i = 0; i < dataCopy.size(); i++)
    {
        QVector<QString> parsedUser = usersFile.parse(dataCopy.at(i));

        if(parsedUser.at(0) == username && parsedUser.at(1) == QString::fromStdString(md5(password.toStdString())) )
            return i;
    }

    return -1;
}

int Auth::isHintValid(QString username, QString phoneNumber)
{
    FileManager usersFile;

    usersFile.create();

    usersFile.loadData();

    auto& dataCopy = usersFile.getData();

    for(int i = 0; i < dataCopy.size(); i++)
    {
        QVector<QString> parsedUser = usersFile.parse(dataCopy.at(i));

        // last element in parsed user is hint
        if(parsedUser.at(0) == username && parsedUser.at(5) == phoneNumber)
            return i;
    }

    return -1;
}

void Auth::updateCredential(int rowIndex, int itemIndex, QString newValue, bool shouldHash)
{
    FileManager userFile;

    userFile.create();

    userFile.loadData();

    QVector<QString> parsedUserInfo = userFile.parse(userFile.getRecord(rowIndex));

    parsedUserInfo[itemIndex] = shouldHash ? QString::fromStdString(md5(newValue.toStdString())) : newValue;

    QString modifiedUserInfo = Auth::formUserData(
        parsedUserInfo[0], parsedUserInfo[1],
        parsedUserInfo[2], parsedUserInfo[3],
        parsedUserInfo[4], parsedUserInfo[5],
        parsedUserInfo[6], false
        );

    userFile.update(rowIndex, modifiedUserInfo);

    userFile.write();
}

int Auth::findUser(QString username)
{
    FileManager userFile;

    userFile.create();

    userFile.loadData();

    for(int i = 0; i < userFile.getData().size(); i++)
        return i;

    throw exception("No user found");
}



