
#include "game_list.h"
#include "ui_game_list.h"
#include <iostream>
#include <QStringList>
#include <QDebug>
#include <QCloseEvent>

GameList::GameList(Lobby* lobby, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameList),
    lobby(lobby)
{
    ui->setupUi(this);
    connect(ui->listWidget, &QListWidget::itemClicked, this, &GameList::onItemClicked);

}

GameList::~GameList()
{
    delete ui;
}

void GameList::setGameList(const std::map<uint16_t, std::string>& games)
{
    QStringList gameNames;

    ui->listWidget->clear();
    nameToIdMap.clear();

    for (const auto& game : games) {
        QString qName = QString::fromStdString(game.second);
        gameNames.append(qName);

        ui->listWidget->addItem(qName);

        nameToIdMap[qName] = game.first;
    }
}

void GameList::onItemClicked(QListWidgetItem* item)
{
    QString gameName = item->text();
    if (nameToIdMap.count(gameName) > 0) {
        uint16_t gameId = nameToIdMap[gameName];


        lobby->join_room(gameId);
        QApplication::closeAllWindows();
    }
}



void GameList::closeEvent(QCloseEvent* event)
{
    emit closed();
    event->accept();
    delete ui;
}