#pragma once

#define WINDOW_TITLE "LD40"

#define SCALE_FACTOR 2

#define SCREEN_WIDTH 10 * 32 * SCALE_FACTOR
#define SCREEN_HEIGHT 8 * 32 * SCALE_FACTOR

#define MAP_WIDTH 10 * 32 * SCALE_FACTOR
#define MAP_HEIGHT 5 * 32 * SCALE_FACTOR

#define NUM_TILES_X MAP_WIDTH / (32 * SCALE_FACTOR)
#define NUM_TILES_Y MAP_HEIGHT / (32 * SCALE_FACTOR)


#define SPLASH_STATE_SHOW_TIME 3.0f
#define LOGO_FILEPATH "Resources/res/newlogo.png"
#define SHADE_PIXELATE_FILEPATH "Resources/shaders/pixelate.shader"

#define MAIN_MENU_FILEPATH "Resources/res/main_menu.png"

#define TILE_FILEPATH "Resources/res/road.png"
#define BUCKET_EMPTY_FILEPATH "Resources/res/bucket_empty.png"
#define BUCKET_SLIGHTLY_FULL_FILEPATH "Resources/res/bucket_sightly_full.png"
#define BUCKET_HALF_FULL_FILEPATH "Resources/res/bucket_half_full.png"
#define BUCKET_FULL_FILEPATH "Resources/res/bucket_full.png"


#define PLAYER_STATIC_FILEPATH "Resources/res/player_static_0.png"
#define PLAYER_STATIC_EMPTY_FILEPATH "Resources/res/player_static_1.png"
#define PLAYER_STATIC_SLIGHTLY_FULL_FILEPATH "Resources/res/player_static_2.png"
#define PLAYER_STATIC_HALF_FULL_FILEPATH "Resources/res/player_static_3.png"

#define PAUSE_MENUE_FILEPATH "Resources/res/pause_menu.png"

#define FLACKE_FILEPATH "Resources/res/flake_3.png"
#define SHADOW_FILEPATH "Resources/res/shadow.png"

#define HAUSES_FILEPATH "Resources/res/bg.png"

#define GAME_OVER_BACK_GROUND_FILEPATH "Resources/res/gameover.png"
#define GAME_OVER_BACK_SHOW_TIME 1.0f

#define BACK_GROUND_MUSIC_FILEPATH "Resources/audio/christmas.wav"
#define FONT_FILEPATH "Resources/fonts/ka1.ttf"
#define TUTORIAL_FONT_FILEPATH "Resources/fonts/tutorialFont.ttf"


