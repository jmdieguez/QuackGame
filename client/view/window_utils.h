
#ifndef WINDOW_UTILS_H
#define WINDOW_UTILS_H

#include <QGuiApplication>
#include <QScreen>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QPixmap>
#include <QStyle>
#include <QIcon>
#include "../ui/defs.h"

class WindowUtils {
public:
    static void centerWindow(QWidget* window, const QString& backgroundPath) {
        QList<QScreen *> screens = QGuiApplication::screens();
        QScreen *screen = screens.isEmpty() ? nullptr : screens[0];

        if (screen) {
            QRect screenRect = screen->availableGeometry();
            int x = (screenRect.width() - window->width()) / 2;
            int y = (screenRect.height() - window->height()) / 2;
            window->move(x, y);
        }
        QLabel* backgroundLabel = new QLabel(window);
        QPixmap backgroundPixmap(backgroundPath);
        backgroundLabel->setPixmap(backgroundPixmap);
        backgroundLabel->setScaledContents(true);
        backgroundLabel->setGeometry(0, 0, window->width(), window->height());

        backgroundLabel->lower();
        QIcon icon(ICON);
        window->setWindowIcon(icon);
    }

    static void setFixedSize(QWidget* window, int width, int height) {
        window->resize(width, height);
    }
};
#endif //WINDOW_UTILS_H
