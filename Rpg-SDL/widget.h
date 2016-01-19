//
//  widget.h
//  Rpg-SDL
//
//  Created by Thomas on 18/01/2016.
//  Copyright © 2016 Thiphariel. All rights reserved.
//

#ifndef widget_h
#define widget_h

#define MAX(a, b) ((a)>(b)?(a):(b))

#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>

class Widget
{
public:
    Widget();
    Widget(SDL_Renderer *renderer, SDL_Texture *texture, TTF_Font *font, SDL_Rect *src, SDL_Rect *dst);
    
    bool onEvent(SDL_Event &event);
    virtual bool draw() const;
    
    bool destroyed() const;
    void destroyed(bool destroyed);
protected:
    SDL_Renderer *m_renderer;
    SDL_Texture *m_texture;
    TTF_Font *m_font;
    SDL_Rect *m_src;
    SDL_Rect *m_dst;
    SDL_Rect *m_offset;
    bool m_destroyed;
};

#endif /* widget_h */
