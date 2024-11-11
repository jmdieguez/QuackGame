/********************************************************************************
** Form generated from reading UI file 'main_window.ui'
**
** Created by: Qt User Interface Compiler version 5.15.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef MAIN_WINDOW_UI_H
#define MAIN_WINDOW_UI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_main_menu
{
public:
    QWidget *widget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *CreateNewGame;
    QPushButton *JoinGame;
    QPushButton *Exit;

    void setupUi(QDialog *main_menu)
    {
        if (main_menu->objectName().isEmpty())
            main_menu->setObjectName(QString::fromUtf8("main_menu"));
        main_menu->resize(1060, 641);
        widget = new QWidget(main_menu);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(-10, 0, 1071, 641));
        widget->setStyleSheet(QString::fromUtf8(""));
        verticalLayoutWidget = new QWidget(widget);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(410, 110, 221, 251));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        CreateNewGame = new QPushButton(verticalLayoutWidget);
        CreateNewGame->setObjectName(QString::fromUtf8("CreateNewGame"));
        CreateNewGame->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"                          background-color: #4C9F70; \n"
"                          color: white; \n"
"                          font-size: 18px; \n"
"                          border: 4px solid #2C6B43; \n"
"                          border-radius: 5px; \n"
"                          padding: 10px 20px;\n"
"                          text-align: center;\n"
"                          }\n"
"QPushButton:pressed {\n"
"                          background-color: #3E7F58;\n"
"}\n"
"QPushButton:hover {\n"
"                          background-color: #3E7F58;\n"
"}"));

        verticalLayout->addWidget(CreateNewGame);

        JoinGame = new QPushButton(verticalLayoutWidget);
        JoinGame->setObjectName(QString::fromUtf8("JoinGame"));
        JoinGame->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"                          background-color: #4C9F70; \n"
"                          color: white; \n"
"                          font-size: 18px; \n"
"                          border: 4px solid #2C6B43; \n"
"                          border-radius: 5px; \n"
"                          padding: 10px 10px;\n"
"                          text-align: center;\n"
"                          }\n"
"QPushButton:pressed {\n"
"                          background-color: #3E7F58;\n"
"}\n"
"QPushButton:hover {\n"
"                          background-color: #3E7F58;\n"
"}"));

        verticalLayout->addWidget(JoinGame);

        Exit = new QPushButton(verticalLayoutWidget);
        Exit->setObjectName(QString::fromUtf8("Exit"));
        Exit->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"                          background-color: #4C9F70; \n"
"                          color: white; \n"
"                          font-size: 18px; \n"
"                          border: 4px solid #2C6B43; \n"
"                          border-radius: 5px; \n"
"                          padding: 10px 20px;\n"
"                          text-align: center;\n"
"                          }\n"
"QPushButton:pressed {\n"
"                          background-color: #3E7F58;\n"
"}\n"
"QPushButton:hover {\n"
"                          background-color: #3E7F58;\n"
"}"));

        verticalLayout->addWidget(Exit);


        retranslateUi(main_menu);

        QMetaObject::connectSlotsByName(main_menu);
    } // setupUi

    void retranslateUi(QDialog *main_menu)
    {
        main_menu->setWindowTitle(QCoreApplication::translate("main_menu", "main_menu", nullptr));
        CreateNewGame->setText(QCoreApplication::translate("main_menu", "Create new game", nullptr));
        JoinGame->setText(QCoreApplication::translate("main_menu", "Join", nullptr));
        Exit->setText(QCoreApplication::translate("main_menu", "Exit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainMenu: public Ui_main_menu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // MAIN_WINDOW_UI_H
