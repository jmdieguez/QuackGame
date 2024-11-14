
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

    // Método para agregar una lista de juegos al QListWidget
    void setGameList(const std::map<uint16_t, std::string>&);

    signals:
        void closed();

protected:
    void closeEvent(QCloseEvent* event) override;

private slots:
        void onItemClicked(QListWidgetItem* item);
private:
    Ui::GameList *ui;
    Lobby* lobby;
    std::map<QString, uint16_t> nameToIdMap;

};

#endif //GAME_LIST_H
