
#ifndef GAME_LIST_H
#define GAME_LIST_H

#include <QWidget>
#include <QListWidget>
#include <map>
#include <string>
#include "../model/lobby/lobby.h"

QT_BEGIN_NAMESPACE
namespace Ui {
    class GameList;
}
QT_END_NAMESPACE

class GameList : public QWidget
{
    Q_OBJECT

public:
    explicit GameList(Lobby* lobby, QWidget *parent = nullptr);
    ~GameList();

    void setGameList(const std::map<uint16_t, std::string>&);

    signals:
        void closed();
        void goBack();

protected:
    void closeEvent(QCloseEvent* event) override;

private slots:
    void onItemClicked(QListWidgetItem *item);
    void onBackButtonClicked();
    void onJoinSinglePlayerClicked();
    void onJoinMultiplayerClicked();
private:
    Ui::GameList *ui;
    Lobby* lobby;
    std::map<QString, uint16_t> nameToIdMap;
    QString selectedGame;
};

#endif //GAME_LIST_H
