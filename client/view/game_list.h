
#ifndef GAME_LIST_H
#define GAME_LIST_H



#include <QWidget>
#include "../model/lobby/lobby.h"

namespace Ui {
    class GameList;
}

class GameList : public QWidget
{
    Q_OBJECT

public:
    explicit GameList(Lobby* lobby, QWidget *parent = nullptr);
    ~GameList();

private:
    Ui::GameList *ui;
    Lobby* lobby;
};


#endif //GAME_LIST_H
