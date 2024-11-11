#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include "lobby.h"
#include <QMainWindow>
#include "../../view/main_window_ui.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(Lobby* lobby, QWidget *parent = nullptr);
    ~MainWindow();

    private slots:
        // Slot para reaccionar al clic de un botón
        void on_createNewGameButton_clicked();  // Ejemplo de botón para crear nuevo juego
    void on_startGameButton_clicked();      // Ejemplo de botón para iniciar el juego

private:
    Ui::MainMenu *ui;
    Lobby *lobbyUI;  // Instancia del controlador Lobby si es necesario mostrarlo

    void showLobby();
};

#endif // MAIN_WINDOW_H