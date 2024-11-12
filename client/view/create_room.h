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
    QLineEdit *textBoxName;
    QPushButton *createButton;
    QPushButton *backButton;

    void setupUi(QWidget *create_room)
    {
        if (create_room->objectName().isEmpty())
            create_room->setObjectName(QString::fromUtf8("create_room"));
        create_room->resize(677, 501);
        QFont font;
        font.setPointSize(10);
        create_room->setFont(font);
        textBoxName = new QLineEdit(create_room);
        textBoxName->setObjectName(QString::fromUtf8("textBoxName"));
        textBoxName->setGeometry(QRect(230, 80, 221, 41));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(textBoxName->sizePolicy().hasHeightForWidth());
        textBoxName->setSizePolicy(sizePolicy);
        QFont font1;
        font1.setPointSize(12);
        textBoxName->setFont(font1);
        textBoxName->setStyleSheet(QString::fromUtf8(""));
        createButton = new QPushButton(create_room);
        createButton->setObjectName(QString::fromUtf8("createButton"));
        createButton->setGeometry(QRect(250, 160, 181, 41));
        createButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
        backButton = new QPushButton(create_room);
        backButton->setObjectName(QString::fromUtf8("backButton"));
        backButton->setGeometry(QRect(250, 210, 181, 41));
        backButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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
        textBoxName->setText(QString());
        textBoxName->setPlaceholderText(QCoreApplication::translate("create_room", "Enter a name", nullptr));
        createButton->setText(QCoreApplication::translate("create_room", "Create", nullptr));
        backButton->setText(QCoreApplication::translate("create_room", "Back", nullptr));
    } // retranslateUi

};

namespace Ui {
    class create_room: public Ui_create_room {};
} // namespace Ui

QT_END_NAMESPACE

#endif // CREATE_ROOM_H
