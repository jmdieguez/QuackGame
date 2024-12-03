#ifndef GAME_RESULT_WINDOW_H
#define GAME_RESULT_WINDOW_H
#include <QWidget>
#include "ui_game_result_window.h"
#include <QDialog>
#include <string>

namespace Ui {
    class GameResultWindow;
}

class GameResultWindow : public QDialog {
    Q_OBJECT

public:
    explicit GameResultWindow(const std::string& playerColor, QWidget *parent = nullptr);
    ~GameResultWindow();

private:
    Ui::GameResultWindow *ui;
    void displayResult(const QString &playerColor);

    private slots:
        void onExitButtonClicked();
};


#endif // GAME_RESULT_WINDOW_H