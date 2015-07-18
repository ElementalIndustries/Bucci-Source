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
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BucciMain
{
public:
    QWidget *centralWidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *vLayout;
    QPushButton *resumeGame;
    QPushButton *newGame;
    QPushButton *stats;
    QPushButton *settings;
    QPushButton *exit;
    QPushButton *howToPlay;
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
        verticalLayoutWidget = new QWidget(centralWidget);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(160, 30, 77, 170));
        vLayout = new QVBoxLayout(verticalLayoutWidget);
        vLayout->setSpacing(6);
        vLayout->setContentsMargins(11, 11, 11, 11);
        vLayout->setObjectName(QStringLiteral("vLayout"));
        vLayout->setContentsMargins(0, 0, 0, 0);
        resumeGame = new QPushButton(verticalLayoutWidget);
        resumeGame->setObjectName(QStringLiteral("resumeGame"));

        vLayout->addWidget(resumeGame);

        newGame = new QPushButton(verticalLayoutWidget);
        newGame->setObjectName(QStringLiteral("newGame"));

        vLayout->addWidget(newGame);

        stats = new QPushButton(verticalLayoutWidget);
        stats->setObjectName(QStringLiteral("stats"));

        vLayout->addWidget(stats);

        settings = new QPushButton(verticalLayoutWidget);
        settings->setObjectName(QStringLiteral("settings"));

        vLayout->addWidget(settings);

        exit = new QPushButton(verticalLayoutWidget);
        exit->setObjectName(QStringLiteral("exit"));

        vLayout->addWidget(exit);

        howToPlay = new QPushButton(verticalLayoutWidget);
        howToPlay->setObjectName(QStringLiteral("howToPlay"));

        vLayout->addWidget(howToPlay);

        BucciMain->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(BucciMain);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 21));
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
        resumeGame->setText(QApplication::translate("BucciMain", "Continue", 0));
        newGame->setText(QApplication::translate("BucciMain", "New Game", 0));
        stats->setText(QApplication::translate("BucciMain", "Stats", 0));
        settings->setText(QApplication::translate("BucciMain", "Settings", 0));
        exit->setText(QApplication::translate("BucciMain", "Exit", 0));
        howToPlay->setText(QApplication::translate("BucciMain", "How To Play", 0));
    } // retranslateUi

};

namespace Ui {
    class BucciMain: public Ui_BucciMain {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BUCCIMAIN_H
