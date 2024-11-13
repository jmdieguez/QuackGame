#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H


#include <QMainWindow>
#include "create_room.h"
#include "../model/lobby/lobby.h"


QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(Lobby *lobby, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onCreateButtonClicked();
    void onExitButtonClicked();
    void onJoinButtonClicked();
    void onBackToMainWindow();

private:
    Ui::MainWindow *ui;
    Lobby* lobby;
    CreateRoom* create_room;
};

#endif // MAIN_WINDOW_H
