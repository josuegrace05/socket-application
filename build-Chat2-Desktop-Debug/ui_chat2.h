/********************************************************************************
** Form generated from reading UI file 'chat2.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHAT2_H
#define UI_CHAT2_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QTextEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_chat2
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *serveurIP;
    QLabel *label_2;
    QSpinBox *serveurPort;
    QPushButton *connetionButton;
    QPushButton *disconnectButton;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout;
    QLabel *label_5;
    QLabel *label_6;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_7;
    QLineEdit *usernameValue;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *updateButton;
    QHBoxLayout *horizontalLayout_3;
    QTextEdit *logText;
    QTextEdit *listMessages;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QLineEdit *userIp;
    QLabel *label_4;
    QLineEdit *messageText;
    QPushButton *boutonEnvoyer;

    void setupUi(QWidget *chat2)
    {
        if (chat2->objectName().isEmpty())
            chat2->setObjectName(QString::fromUtf8("chat2"));
        chat2->resize(802, 526);
        QIcon icon;
        icon.addFile(QString::fromUtf8("chat.png"), QSize(), QIcon::Normal, QIcon::Off);
        chat2->setWindowIcon(icon);
        verticalLayout_2 = new QVBoxLayout(chat2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(chat2);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        serveurIP = new QLineEdit(chat2);
        serveurIP->setObjectName(QString::fromUtf8("serveurIP"));
        serveurIP->setMaximumSize(QSize(150, 16777215));

        horizontalLayout->addWidget(serveurIP);

        label_2 = new QLabel(chat2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        serveurPort = new QSpinBox(chat2);
        serveurPort->setObjectName(QString::fromUtf8("serveurPort"));
        serveurPort->setMinimumSize(QSize(60, 0));
        serveurPort->setMinimum(1024);
        serveurPort->setMaximum(65535);
        serveurPort->setValue(50885);

        horizontalLayout->addWidget(serveurPort);

        connetionButton = new QPushButton(chat2);
        connetionButton->setObjectName(QString::fromUtf8("connetionButton"));

        horizontalLayout->addWidget(connetionButton);

        disconnectButton = new QPushButton(chat2);
        disconnectButton->setObjectName(QString::fromUtf8("disconnectButton"));

        horizontalLayout->addWidget(disconnectButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_5 = new QLabel(chat2);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setPixmap(QPixmap(QString::fromUtf8("chat.png")));

        verticalLayout->addWidget(label_5);

        label_6 = new QLabel(chat2);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        QFont font;
        font.setPointSize(11);
        font.setBold(false);
        font.setWeight(50);
        label_6->setFont(font);
        label_6->setLayoutDirection(Qt::LeftToRight);
        label_6->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_6);


        horizontalLayout->addLayout(verticalLayout);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_7 = new QLabel(chat2);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout_4->addWidget(label_7);

        usernameValue = new QLineEdit(chat2);
        usernameValue->setObjectName(QString::fromUtf8("usernameValue"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(usernameValue->sizePolicy().hasHeightForWidth());
        usernameValue->setSizePolicy(sizePolicy);
        usernameValue->setMaximumSize(QSize(200, 16777215));
        usernameValue->setLayoutDirection(Qt::RightToLeft);

        horizontalLayout_4->addWidget(usernameValue);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);

        updateButton = new QPushButton(chat2);
        updateButton->setObjectName(QString::fromUtf8("updateButton"));

        horizontalLayout_4->addWidget(updateButton);


        verticalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        logText = new QTextEdit(chat2);
        logText->setObjectName(QString::fromUtf8("logText"));

        horizontalLayout_3->addWidget(logText);

        listMessages = new QTextEdit(chat2);
        listMessages->setObjectName(QString::fromUtf8("listMessages"));
        listMessages->setReadOnly(true);

        horizontalLayout_3->addWidget(listMessages);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_3 = new QLabel(chat2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_2->addWidget(label_3);

        userIp = new QLineEdit(chat2);
        userIp->setObjectName(QString::fromUtf8("userIp"));
        userIp->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_2->addWidget(userIp);

        label_4 = new QLabel(chat2);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_2->addWidget(label_4);

        messageText = new QLineEdit(chat2);
        messageText->setObjectName(QString::fromUtf8("messageText"));

        horizontalLayout_2->addWidget(messageText);

        boutonEnvoyer = new QPushButton(chat2);
        boutonEnvoyer->setObjectName(QString::fromUtf8("boutonEnvoyer"));
        boutonEnvoyer->setIcon(icon);

        horizontalLayout_2->addWidget(boutonEnvoyer);


        verticalLayout_2->addLayout(horizontalLayout_2);


        retranslateUi(chat2);

        QMetaObject::connectSlotsByName(chat2);
    } // setupUi

    void retranslateUi(QWidget *chat2)
    {
        chat2->setWindowTitle(QApplication::translate("chat2", "XareChat", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("chat2", "<html><head/><body><p>IP do servidor :</p></body></html>", 0, QApplication::UnicodeUTF8));
        serveurIP->setText(QApplication::translate("chat2", "127.0.0.1", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("chat2", "<html><head/><body><p>Porta do servidor :</p></body></html>", 0, QApplication::UnicodeUTF8));
        connetionButton->setText(QApplication::translate("chat2", "Connectar", 0, QApplication::UnicodeUTF8));
        disconnectButton->setText(QApplication::translate("chat2", "Desconnectar", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("chat2", "<html><head/><body><p><span style=\" font-weight:600;\">XareChat</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("chat2", "<html><head/><body><p>Username:</p></body></html>", 0, QApplication::UnicodeUTF8));
        updateButton->setText(QApplication::translate("chat2", "Conectados", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("chat2", "<html><head/><body><p>IP do usuario :</p></body></html>", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("chat2", "<html><head/><body><p>Mensagem :</p></body></html>", 0, QApplication::UnicodeUTF8));
        boutonEnvoyer->setText(QApplication::translate("chat2", "Mandar", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class chat2: public Ui_chat2 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHAT2_H
