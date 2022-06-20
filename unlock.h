#ifndef UNLOCK_H
#define UNLOCK_H

#include <QWidget>

namespace Ui {
class Unlock;
}

class Unlock : public QWidget
{
    Q_OBJECT

public:
    explicit Unlock(QWidget *parent = nullptr);
    ~Unlock();
    void quit();
    void alarm();

private:
    Ui::Unlock *ui;
};

#endif // UNLOCK_H
