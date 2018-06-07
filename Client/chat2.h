#ifndef CHAT2_H
#define CHAT2_H

#include <QWidget>

namespace Ui {
class chat2;
}

class chat2 : public QWidget
{
    Q_OBJECT

public:
    explicit chat2(QWidget *parent = 0);
    ~chat2();

private:
    Ui::chat2 *ui;
};

#endif // CHAT2_H
