#include "setup.h"
#include "ui_setup.h"

#include <QJsonObject>
#include <QJsonDocument>
#include <QCryptographicHash>
#include <QFile>
#include <QDir>

QJsonObject setupConfig;


void saveSettings(QString pwd, QString cmd) {
    QString md5 = QCryptographicHash::hash(pwd.toLatin1(), QCryptographicHash::Md5).toHex();
    setupConfig["pwdHash"] = QJsonValue(md5);
    setupConfig["command"] = QJsonValue(cmd);


    QDir dir;
    QString homePath = getenv("HOME");
    dir.mkpath(homePath + "/.config/fake-gnome-keyring");
    QString configPath = homePath + "/.config/fake-gnome-keyring/config.json";

    QJsonDocument doc(setupConfig);
    QFile jsonFile(configPath);
    jsonFile.open(QFile::WriteOnly);
    jsonFile.write(doc.toJson(QJsonDocument::Indented));
    jsonFile.close();
}

Setup::Setup(QWidget *parent) : QWidget(parent), ui(new Ui::Setup) {
    ui->setupUi(this);

    this->connect(ui->cancelPushButton, &QPushButton::clicked, this,
                  []() {
        exit(0);
    });

    this->connect(ui->okPushButton, &QPushButton::clicked, this,
                  [this]() {
        saveSettings(ui->pwdLineEdit->text(), ui->cmdLineEdit->text());
        exit(0);
    });
}

Setup::~Setup() {
    delete ui;
}
