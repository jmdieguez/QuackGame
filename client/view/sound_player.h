#ifndef SOUND_PLAYER_H
#define SOUND_PLAYER_H

#include <QObject>
#include <QMediaPlayer>
#include <QUrl>
#include <QSound>
#include <QTimer>

class SoundPlayer : public QObject {
    Q_OBJECT

public:
    static SoundPlayer* instance() {
        static SoundPlayer* instance = nullptr;
        if (!instance) {
            instance = new SoundPlayer();
        }
        return instance;
    }

    // Reproducir música o sonido con opción de loop
    void playSound(const QString& filePath, bool loop = false) {
        stopMusic();  // Detener cualquier sonido previo si ya se está reproduciendo
        soundFilePath = filePath;

        if (loop) {
            playLoop();  // Reproducir en loop
        } else {
            playOnce();  // Reproducir una sola vez
        }
    }

private:
    SoundPlayer() {
        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &SoundPlayer::playLoop);
    }

    // Reproducir sonido en loop
    void playLoop() {
        QSound::play(soundFilePath);
        timer->start(500);  // Repetir cada medio segundo (ajustable según la duración del sonido)
    }

    // Reproducir solo una vez
    void playOnce() {
        QSound::play(soundFilePath);
    }

    // Detener la música o sonido
    void stopMusic() {
        if (timer->isActive()) {
            timer->stop();
        }
    }

    QString soundFilePath;
    QTimer* timer;
};

#endif // SOUND_PLAYER_H