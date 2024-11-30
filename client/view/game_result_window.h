#ifndef GAME_RESULT_WINDOW_H
#define GAME_RESULT_WINDOW_H
#include <QDialog>
#include <QWidget>


#include "ui_game_result_window.h"


class GameResultWindow : public QDialog {
    Q_OBJECT
public:
    explicit GameResultWindow(bool victory, QWidget *parent = nullptr);
    ~GameResultWindow();

    private slots:
        void onExitButtonClicked();

private:
    Ui::GameResultWindow *ui;
    void displayResult(bool victory);
};
#endif // GAME_RESULT_WINDOW_H