#ifndef UI_DEFS_H
#define UI_DEFS_H

#define DEFAULT_WINDOW_WIDTH 1024 // 16:9 ratio
#define DEFAULT_WINDOW_HEIGHT 576

struct SDL_Color;

#define BLUE SDL_Color{100, 100, 255, 255}
#define WHITE SDL_Color{255, 255, 255, 255}

#define FONT_PATH "/var/quackgame/04B_30.TTF"
#define ICON "/var/quackgame/logo.png"
#define ICON_SIZE 256
#define CLICK_SOUND "/var/quackgame/sound/click_sound.wav"
#define MUSIC_SOUND "/var/quackgame/sound/click_sound.wav"

#endif // UI_DEFS_H
