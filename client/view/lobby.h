
#ifndef LOBBY_H
#define LOBBY_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>
#include <iostream>
#include "../model/protocol.h"

class Lobby : public QWidget {
    Q_OBJECT

public:
    Lobby(ClientProtocol&);
    ~Lobby();
    private slots:
        void showCreateGameUI();
    void showMainLobbyUI();
    void onJoinGameClicked();
    void onCreateGameClicked();

private:
    QWidget *menuContainer;
    QVBoxLayout *initialLayout;
    QLineEdit *nameEdit;
    ClientProtocol& protocol;

    QPushButton *createLobbyButton(const QString &text);
    void clearLayout(QLayout *layout);
    void applyButtonStyle(QPushButton *button);
};

#endif // LOBBY_H