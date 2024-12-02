#ifndef UI_DEFS_H
#define UI_DEFS_H

#define DEFAULT_WINDOW_WIDTH 1024 // 16:9 ratio
#define DEFAULT_WINDOW_HEIGHT 576

struct SDL_Color;

#define BLUE SDL_Color{100, 100, 255, 255}
#define WHITE SDL_Color{255, 255, 255, 255}

#define ICON_SIZE 256

#ifdef GLOBAL_INSTALL
    #define FONT_PATH "/var/quackgame/04B_30.TTF"
    #define ICON "/var/quackgame/logo.png"
    #define CLICK_SOUND "/var/quackgame/sound/click_sound.wav"
    #define MUSIC_SOUND "/var/quackgame/sound/click_sound.wav"
    #define BACKGROUND "/var/quackgame/background_menu.jpg"
    #define VICTORY_BACKGROUND "/var/quackgame/victory.jpg"
    #define DEFEAT_BACKGROUND "/var/quackgame/game_over.jpg"
    #define VICTORY_SOUND "/var/quackgame/sound/victory_sound.wav"
    #define DEFEAT_SOUND "/var/quackgame/sound/game_over_sound.wav"
#else // LOCAL_INSTALL
    #define FONT_PATH "assets/04B_30.TTF"
    #define ICON "assets/logo.png"
    #define CLICK_SOUND "assets/sound/click_sound.wav"
    #define MUSIC_SOUND "assets/sound/click_sound.wav"
    #define BACKGROUND "assets/background_menu.jpg"
    #define VICTORY_BACKGROUND "assets/victory.jpg"
    #define DEFEAT_BACKGROUND "assets/game_over.jpg"
    #define VICTORY_SOUND "assets/sound/victory_sound.wav"
    #define DEFEAT_SOUND "assets/sound/game_over_sound.wav"
#endif

#endif // UI_DEFS_H
