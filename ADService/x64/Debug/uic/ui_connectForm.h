/********************************************************************************
** Form generated from reading UI file 'connectForm.ui'
**
** Created by: Qt User Interface Compiler version 6.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONNECTFORM_H
#define UI_CONNECTFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_connectForm
{
public:
    QGridLayout *gridLayout;
    QPushButton *connectPbt;
    QSpacerItem *horizontalSpacer;
    QGroupBox *logBox;
    QGridLayout *gridLayout_2;
    QWidget *widget;
    QGroupBox *userBox;
    QFormLayout *formLayout;
    QLineEdit *portLine;
    QLineEdit *userLine;
    QLineEdit *passwLine;
    QLineEdit *urlLine;
    QLabel *urlLbl;
    QLabel *portLbl;
    QLabel *userLbl;
    QLabel *passwLbl;

    void setupUi(QWidget *connectForm)
    {
        if (connectForm->objectName().isEmpty())
            connectForm->setObjectName(QString::fromUtf8("connectForm"));
        connectForm->resize(330, 420);
        gridLayout = new QGridLayout(connectForm);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        connectPbt = new QPushButton(connectForm);
        connectPbt->setObjectName(QString::fromUtf8("connectPbt"));

        gridLayout->addWidget(connectPbt, 2, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 2, 1, 1, 1);

        logBox = new QGroupBox(connectForm);
        logBox->setObjectName(QString::fromUtf8("logBox"));
        gridLayout_2 = new QGridLayout(logBox);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        widget = new QWidget(logBox);
        widget->setObjectName(QString::fromUtf8("widget"));

        gridLayout_2->addWidget(widget, 0, 0, 1, 1);


        gridLayout->addWidget(logBox, 1, 0, 1, 2);

        userBox = new QGroupBox(connectForm);
        userBox->setObjectName(QString::fromUtf8("userBox"));
        formLayout = new QFormLayout(userBox);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        portLine = new QLineEdit(userBox);
        portLine->setObjectName(QString::fromUtf8("portLine"));

        formLayout->setWidget(1, QFormLayout::LabelRole, portLine);

        userLine = new QLineEdit(userBox);
        userLine->setObjectName(QString::fromUtf8("userLine"));

        formLayout->setWidget(2, QFormLayout::LabelRole, userLine);

        passwLine = new QLineEdit(userBox);
        passwLine->setObjectName(QString::fromUtf8("passwLine"));

        formLayout->setWidget(3, QFormLayout::LabelRole, passwLine);

        urlLine = new QLineEdit(userBox);
        urlLine->setObjectName(QString::fromUtf8("urlLine"));

        formLayout->setWidget(0, QFormLayout::LabelRole, urlLine);

        urlLbl = new QLabel(userBox);
        urlLbl->setObjectName(QString::fromUtf8("urlLbl"));

        formLayout->setWidget(0, QFormLayout::FieldRole, urlLbl);

        portLbl = new QLabel(userBox);
        portLbl->setObjectName(QString::fromUtf8("portLbl"));

        formLayout->setWidget(1, QFormLayout::FieldRole, portLbl);

        userLbl = new QLabel(userBox);
        userLbl->setObjectName(QString::fromUtf8("userLbl"));

        formLayout->setWidget(2, QFormLayout::FieldRole, userLbl);

        passwLbl = new QLabel(userBox);
        passwLbl->setObjectName(QString::fromUtf8("passwLbl"));

        formLayout->setWidget(3, QFormLayout::FieldRole, passwLbl);


        gridLayout->addWidget(userBox, 0, 0, 1, 2);


        retranslateUi(connectForm);

        QMetaObject::connectSlotsByName(connectForm);
    } // setupUi

    void retranslateUi(QWidget *connectForm)
    {
        connectForm->setWindowTitle(QCoreApplication::translate("connectForm", "Form", nullptr));
        connectPbt->setText(QCoreApplication::translate("connectForm", "Connect", nullptr));
        logBox->setTitle(QCoreApplication::translate("connectForm", "Log", nullptr));
        userBox->setTitle(QCoreApplication::translate("connectForm", "User and domain", nullptr));
        urlLbl->setText(QCoreApplication::translate("connectForm", "Url", nullptr));
        portLbl->setText(QCoreApplication::translate("connectForm", "Port", nullptr));
        userLbl->setText(QCoreApplication::translate("connectForm", "User", nullptr));
        passwLbl->setText(QCoreApplication::translate("connectForm", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class connectForm: public Ui_connectForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONNECTFORM_H
