/********************************************************************************
** Form generated from reading UI file 'find_dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FIND_DIALOG_H
#define UI_FIND_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_find_dialogClass
{
public:
    QWidget *centralWidget;
    QTextBrowser *textBrowser;
    QPushButton *closePushButton;
    QPushButton *findPushButton;
    QLineEdit *fileLineEdit;
    QLineEdit *keyLineEdit;
    QCheckBox *matchCheckBox;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *find_dialogClass)
    {
        if (find_dialogClass->objectName().isEmpty())
            find_dialogClass->setObjectName(QString::fromUtf8("find_dialogClass"));
        find_dialogClass->resize(525, 389);
        centralWidget = new QWidget(find_dialogClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        textBrowser = new QTextBrowser(centralWidget);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(60, 130, 401, 191));
        closePushButton = new QPushButton(centralWidget);
        closePushButton->setObjectName(QString::fromUtf8("closePushButton"));
        closePushButton->setGeometry(QRect(260, 60, 131, 21));
        findPushButton = new QPushButton(centralWidget);
        findPushButton->setObjectName(QString::fromUtf8("findPushButton"));
        findPushButton->setGeometry(QRect(260, 30, 131, 21));
        fileLineEdit = new QLineEdit(centralWidget);
        fileLineEdit->setObjectName(QString::fromUtf8("fileLineEdit"));
        fileLineEdit->setGeometry(QRect(100, 30, 157, 20));
        keyLineEdit = new QLineEdit(centralWidget);
        keyLineEdit->setObjectName(QString::fromUtf8("keyLineEdit"));
        keyLineEdit->setGeometry(QRect(100, 60, 157, 20));
        matchCheckBox = new QCheckBox(centralWidget);
        matchCheckBox->setObjectName(QString::fromUtf8("matchCheckBox"));
        matchCheckBox->setGeometry(QRect(100, 100, 101, 21));
        find_dialogClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(find_dialogClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 525, 25));
        find_dialogClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(find_dialogClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        find_dialogClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(find_dialogClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        find_dialogClass->setStatusBar(statusBar);

        retranslateUi(find_dialogClass);
        QObject::connect(closePushButton, SIGNAL(clicked()), find_dialogClass, SLOT(close()));

        QMetaObject::connectSlotsByName(find_dialogClass);
    } // setupUi

    void retranslateUi(QMainWindow *find_dialogClass)
    {
        find_dialogClass->setWindowTitle(QCoreApplication::translate("find_dialogClass", "find_dialog", nullptr));
        closePushButton->setText(QCoreApplication::translate("find_dialogClass", "Close", nullptr));
        findPushButton->setText(QCoreApplication::translate("find_dialogClass", "Find", nullptr));
        matchCheckBox->setText(QCoreApplication::translate("find_dialogClass", "Match Case", nullptr));
    } // retranslateUi

};

namespace Ui {
    class find_dialogClass: public Ui_find_dialogClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FIND_DIALOG_H
