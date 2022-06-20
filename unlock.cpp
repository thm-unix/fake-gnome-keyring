#include "unlock.h"
#include "ui_unlock.h"

#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QCryptographicHash>
#include <QProcess>

QJsonObject unlockConfig;
bool unlocked = false;


void Unlock::alarm() {
    QProcess* p = new QProcess;
    p->start(unlockConfig["command"].toString());
}

void Unlock::quit() {
    Unlock::~Unlock();
    exit(0);
}

Unlock::Unlock(QWidget *parent) : QWidget(parent), ui(new Ui::Unlock) {
    ui->setupUi(this);

    QString homeDirectory = getenv("HOME");
    QFile file;
    QString data;

    file.setFileName(homeDirectory + "/.config/fake-gnome-keyring/config.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    data = file.readAll();
    file.close();
    unlockConfig = QJsonDocument::fromJson(data.toUtf8()).object();


    this->connect(ui->unlockPushButton, &QPushButton::clicked, this,
                  [this]() {
        QString realMD5 = unlockConfig["pwdHash"].toString();
        QString userMD5 = QCryptographicHash::hash(ui->pwdLineEdit->text().toLatin1(), QCryptographicHash::Md5).toHex();

        if (userMD5 == realMD5) {
            unlocked = true;
        }

        quit();
    });

    this->connect(ui->cancelPushButton, &QPushButton::clicked, this,
                  [this]() {
        quit();
    });
}

Unlock::~Unlock() {
    if (!unlocked) {
        alarm();
    }
    delete ui;
}
