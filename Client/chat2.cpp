#include "chat2.h"
#include "ui_chat2.h"

chat2::chat(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::chat2)
{
    ui->setupUi(this);
}

chat2::~chat2()
{
    delete ui;
}
