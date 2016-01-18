/**
 * @author Thiphariel - 14/01/2016
 */

#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <SDL2_ttf/SDL_ttf.h>

#include "map.h"
#include "character.h"
#include "ui.h"
#include "animation.h"

class Game
{
    public:
        Game();
        bool onInit();
        int onRun();
        bool onLoad();
        void onLoop();
        void onDraw();
        void onEvent();

        // Extern
        void clean();
        void delay(unsigned int frameLimit);
        SDL_Texture *load_image(SDL_Renderer *renderer, std::string name);
        Mix_Music *load_music(std::string name);
        TTF_Font *load_font(std::string name, int size);
        void draw(SDL_Texture *texture, int x, int y);
        void draw(SDL_Texture *texture, int sx, int sy, int dx, int dy);
        void draw_character(SDL_Texture *texture, int sx, int sy, int dx, int dy);

    private:
        SDL_Window *m_window;
        SDL_Renderer *m_renderer;
        SDL_Event m_event;
        bool m_running;

        Mix_Music *m_background;

        // Map related
        Map *m_map;

        // Character
        Character *m_player;

        // Ui
        Ui *m_ui;
};

#endif // GAME_H
