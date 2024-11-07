#include "lobby.h"
#include <QMessageBox>
#include <QLineEdit>

Lobby::Lobby(ClientProtocol protocol, QWidget *parent) : QWidget(parent), protocol(protocol) {
    setWindowTitle("Lobby");

    menuContainer = new QWidget(this);
    menuContainer->setStyleSheet("QWidget {"
                                 "background-color: #D2B48C; "
                                 "border: 2px solid #8B4513; "
                                 "border-radius: 15px; "
                                 "padding: 20px;"
                                 "}");
    menuContainer->setFixedSize(400, 300);

    QPushButton *createButton = createLobbyButton("Create new game");
    QPushButton *joinButton = createLobbyButton("Join");
    QPushButton *exitButton = createLobbyButton("Exit");

    connect(createButton, &QPushButton::clicked, this, &Lobby::showCreateGameUI);
    connect(joinButton, &QPushButton::clicked, this, &Lobby::onJoinGameClicked);

    initialLayout = new QVBoxLayout(menuContainer);
    initialLayout->addWidget(createButton);
    initialLayout->addWidget(joinButton);
    initialLayout->addWidget(exitButton);
    initialLayout->setAlignment(createButton, Qt::AlignCenter);
    initialLayout->setAlignment(joinButton, Qt::AlignCenter);
    initialLayout->setAlignment(exitButton, Qt::AlignCenter);
    menuContainer->setLayout(initialLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(menuContainer);
    setLayout(mainLayout);
}

void Lobby::showCreateGameUI() {
    clearLayout(initialLayout);

    nameEdit = new QLineEdit();
    nameEdit->setPlaceholderText("Enter game name...");
    nameEdit->setFixedSize(300, 40);
    nameEdit->setStyleSheet("font-size: 18px; padding: 5px;");

    QPushButton *createGameButton = createLobbyButton("Create");

    QPushButton *backButton = createLobbyButton("Back");

    connect(createGameButton, &QPushButton::clicked, this, &Lobby::onCreateGameClicked);
    connect(backButton, &QPushButton::clicked, this, &Lobby::showMainLobbyUI);

    // Añadir widgets al layout
    initialLayout->addWidget(nameEdit);
    initialLayout->addWidget(createGameButton);
    initialLayout->addWidget(backButton);
    initialLayout->setAlignment(nameEdit, Qt::AlignCenter);
    initialLayout->setAlignment(createGameButton, Qt::AlignCenter);
    initialLayout->setAlignment(backButton, Qt::AlignCenter);
}

void Lobby::showMainLobbyUI() {
    clearLayout(initialLayout);

    QPushButton *createButton = createLobbyButton("Create new game");
    QPushButton *joinButton = createLobbyButton("Join");
    QPushButton *exitButton = createLobbyButton("Exit");

    connect(createButton, &QPushButton::clicked, this, &Lobby::showCreateGameUI);
    connect(joinButton, &QPushButton::clicked, this, &Lobby::onJoinGameClicked);

    initialLayout->addWidget(createButton);
    initialLayout->addWidget(joinButton);
    initialLayout->addWidget(exitButton);
    initialLayout->setAlignment(createButton, Qt::AlignCenter);
    initialLayout->setAlignment(joinButton, Qt::AlignCenter);
    initialLayout->setAlignment(exitButton, Qt::AlignCenter);
}

void Lobby::onJoinGameClicked() {
    QMessageBox::information(this, "Unirse a partida", "Se ha unido a la partida con éxito.");
}

void Lobby::onCreateGameClicked() {
    QString gameName = nameEdit->text();
    QMessageBox::information(this, "Partida creada", "Se ha creado la partida con éxito.");
}

QPushButton* Lobby::createLobbyButton(const QString &text) {
    QPushButton *button = new QPushButton(text);
    button->setFixedSize(250, 50);
    applyButtonStyle(button);
    return button;
}

void Lobby::clearLayout(QLayout *layout) {
    QLayoutItem *child;
    while ((child = layout->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }
}

void Lobby::applyButtonStyle(QPushButton *button) {
    button->setStyleSheet("QPushButton {"
                          "background-color: #4C9F70; "
                          "color: white; "
                          "font-size: 20px; "
                          "border: 4px solid #2C6B43; "
                          "border-radius: 5px; "
                          "padding: 10px 20px;"
                          "text-align: center;"
                          "}"
                          "QPushButton:pressed {"
                          "background-color: #3E7F58;"
                          "}");
}
