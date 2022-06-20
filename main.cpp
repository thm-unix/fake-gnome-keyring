#include "setup.h"
#include "unlock.h"

#include <QApplication>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    QString homeDirectory = getenv("HOME");
    if (QFile::exists(homeDirectory + "/.config/fake-gnome-keyring/config.json")) {
        Unlock* u = new Unlock;
        u->show();

        a.exec();
        u->quit();
    }

    else {
        Setup* s = new Setup;
        s->show();

        a.exec();
    }
}
