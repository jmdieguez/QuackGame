/********************************************************************************
** Form generated from reading UI file 'create_room.ui'
**
** Created by: Qt User Interface Compiler version 5.15.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef CREATE_ROOM_H
#define CREATE_ROOM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_create_room
{
public:
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QWidget *create_room)
    {
        if (create_room->objectName().isEmpty())
            create_room->setObjectName(QString::fromUtf8("create_room"));
        create_room->resize(677, 501);
        QFont font;
        font.setPointSize(10);
        create_room->setFont(font);
        lineEdit = new QLineEdit(create_room);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(230, 80, 221, 41));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lineEdit->sizePolicy().hasHeightForWidth());
        lineEdit->setSizePolicy(sizePolicy);
        QFont font1;
        font1.setPointSize(12);
        lineEdit->setFont(font1);
        lineEdit->setStyleSheet(QString::fromUtf8(""));
        pushButton = new QPushButton(create_room);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(250, 190, 181, 41));
        pushButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"                          background-color: #4C9F70; \n"
"                          color: white; \n"
"                          font-size: 16px; \n"
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
        pushButton_2 = new QPushButton(create_room);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(250, 250, 181, 41));
        pushButton_2->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"                          background-color: #4C9F70; \n"
"                          color: white; \n"
"                          font-size: 16px; \n"
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

        retranslateUi(create_room);

        QMetaObject::connectSlotsByName(create_room);
    } // setupUi

    void retranslateUi(QWidget *create_room)
    {
        create_room->setWindowTitle(QCoreApplication::translate("create_room", "Form", nullptr));
        lineEdit->setText(QString());
        lineEdit->setPlaceholderText(QCoreApplication::translate("create_room", "Enter a name", nullptr));
        pushButton->setText(QCoreApplication::translate("create_room", "Create", nullptr));
        pushButton_2->setText(QCoreApplication::translate("create_room", "Back", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CreateRoom: public Ui_create_room {};
} // namespace Ui

QT_END_NAMESPACE

#endif // CREATE_ROOM_H
