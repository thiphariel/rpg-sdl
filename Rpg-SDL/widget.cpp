//
//  widget.cpp
//  Rpg-SDL
//
//  Created by Thomas on 18/01/2016.
//  Copyright © 2016 Thiphariel. All rights reserved.
//

#include "widget.h"

Widget::Widget()
{
}

Widget::Widget(SDL_Renderer *renderer, SDL_Texture *texture, TTF_Font *font, SDL_Rect *src, SDL_Rect *dst)
: m_renderer(renderer), m_texture(texture), m_font(font), m_src(src), m_dst(dst)
{
    m_destroyed = false;
}

bool Widget::destroyed() const
{
    return m_destroyed;
}

bool Widget::onEvent(SDL_Event &event)
{
    switch (event.type) {
        case SDL_KEYDOWN:
            switch(event.key.keysym.sym) {
                case SDLK_a:
                    std::cout << "A pressed on UI widget :)\n";
                    return true;
                    break;
            }
            break;
        case SDL_KEYUP:
            switch(event.key.keysym.sym) {
                    // Character move
                case SDLK_e:
                    std::cout << "E released on UI widget :)\n";
                    return true;
                    break;
            }
            break;
        case SDL_MOUSEBUTTONUP:
            if (event.motion.x > m_dst->x && event.motion.y > m_dst->y) {
                std::cout << "Mouse click up\n";
                std::cout << "A widget has been set to be destroyed\n";
                m_destroyed = true;
                return true;
            }
            
            break;
    }
    
    return false;
}

void Widget::draw() const
{
    // Create a copy of the dst rect so we can modify it
    SDL_Rect frame = *m_dst;
    // Make sure that the dst isn't too small
    // Sort of like how CSS box-sizing: border-box; works
    // if we have a width of 50px, but the padding is set to 30px, then we will have a 60px wide box
    frame.w = MAX(frame.w, m_src->x + m_src->w);
    frame.h = MAX(frame.h, m_src->y + m_src->h);
    
    int w, h;
    SDL_QueryTexture(m_texture, NULL, NULL, &w, &h);
    
    SDL_Point srcPoints[] = {
        {0, 0},
        {m_src->x, m_src->y},
        {w - m_src->w, h - m_src->h},
        {w, h}
    };
    
    SDL_Point dstPoints[] = {
        {frame.x, frame.y},
        {frame.x + m_src->x, frame.y + m_src->y},
        {frame.x + frame.w - m_src->w, frame.y + frame.h - m_src->h},
        {frame.x + frame.w, frame.y + frame.h}
    };
    
    //Loop trough and draw each rect
    for (int y = 0; y < 3; y++ ) {
        for (int x = 0; x < 3; x++) {
            SDL_Rect src = {
                srcPoints[x].x,
                srcPoints[y].y,
                srcPoints[x+1].x,
                srcPoints[y+1].y
            };
            src.w -= src.x;
            src.h -= src.y;
            
            SDL_Rect dst = {
                dstPoints[x].x,
                dstPoints[y].y,
                dstPoints[x+1].x,
                dstPoints[y+1].y
            };
            dst.w -= dst.x;
            dst.h -= dst.y;
            
            SDL_RenderCopy(m_renderer, m_texture, &src, &dst);
        }
    }
}