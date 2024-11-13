
#include "game_list.h"
#include "ui_game_list.h"

GameList::GameList(Lobby* lobby, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameList),
    lobby(lobby)
{
    ui->setupUi(this);

    connect(ui->GameList, &QListWidget::itemClicked, this, &GameList::onGameClicked);
    // TODO: implementar este metodo y separar las cosas, manejarlo por señales
    loadGames(lobby->get_game_list());
}

GameList::~GameList()
{
    delete ui;
}

void GameList::loadGames(const QList<GameInfo> &games)
{
    ui->GameList->clear();

    for (const GameInfo &game : games) {
        QListWidgetItem *item = new QListWidgetItem(game.name);
        item->setData(Qt::UserRole, game.id);
        ui->GameList->addItem(item);
    }
}

void GameList::onGameClicked(QListWidgetItem *item)
{
    int gameId = item->data(Qt::UserRole).toInt();
    emit joinGameRequested(gameId);
}