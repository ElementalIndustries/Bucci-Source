/********************************************************************************
** Form generated from reading UI file 'buccimain.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BUCCIMAIN_H
#define UI_BUCCIMAIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BucciMain
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *BucciMain)
    {
        if (BucciMain->objectName().isEmpty())
            BucciMain->setObjectName(QStringLiteral("BucciMain"));
        BucciMain->resize(400, 300);
        centralWidget = new QWidget(BucciMain);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(150, 20, 93, 28));
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(150, 70, 93, 28));
        pushButton_3 = new QPushButton(centralWidget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(150, 120, 93, 28));
        pushButton_4 = new QPushButton(centralWidget);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setGeometry(QRect(150, 170, 93, 28));
        BucciMain->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(BucciMain);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 26));
        BucciMain->setMenuBar(menuBar);
        mainToolBar = new QToolBar(BucciMain);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        BucciMain->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(BucciMain);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        BucciMain->setStatusBar(statusBar);

        retranslateUi(BucciMain);

        QMetaObject::connectSlotsByName(BucciMain);
    } // setupUi

    void retranslateUi(QMainWindow *BucciMain)
    {
        BucciMain->setWindowTitle(QApplication::translate("BucciMain", "BucciMain", 0));
        pushButton->setText(QApplication::translate("BucciMain", "New Game", 0));
        pushButton_2->setText(QApplication::translate("BucciMain", "Stats", 0));
        pushButton_3->setText(QApplication::translate("BucciMain", "Settings", 0));
        pushButton_4->setText(QApplication::translate("BucciMain", "Exit", 0));
    } // retranslateUi

};

namespace Ui {
    class BucciMain: public Ui_BucciMain {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BUCCIMAIN_H
