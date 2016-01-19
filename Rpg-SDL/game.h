/**
 * @author Thiphariel - 14/01/2016
 */

#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <SDL2_ttf/SDL_ttf.h>

#include "map.h"
#include "character.h"
#include "animation.h"
#include "widget.h"
#include "dialog.h"

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
    
    SDL_Renderer *renderer() const;
    
    // Widgets
    void add_widget(Widget *widget);
    void remove_widget(Widget *widget);

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

    // Resources
    Mix_Music *m_background;
    SDL_Texture *m_tileset;
    SDL_Texture *m_dialog;
    SDL_Texture *m_player_spritesheet;
    SDL_Texture *m_player_dialog;
    TTF_Font *m_font_pixel;

    // Map related
    Map *m_map;

    // Character
    Character *m_player;
    
    // Widget
    SDL_Rect src, dst;
    Widget *widget;

    // Widgets
    std::vector<Widget*> *m_widgets;
};

#endif // GAME_H
