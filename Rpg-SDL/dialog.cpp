//
//  dialog.cpp
//  Rpg-SDL
//
//  Created by Thomas on 19/01/2016.
//  Copyright © 2016 Thiphariel. All rights reserved.
//

#include "dialog.h"

Dialog::Dialog(SDL_Renderer *renderer, SDL_Texture *texture, TTF_Font *font, SDL_Rect *src, SDL_Rect *dst, std::string text, SDL_Texture *speaker)
: Widget(renderer, texture, font, src, dst), m_text(text), m_speaker(speaker)
{
}

bool Dialog::draw() const
{
    if (m_speaker == NULL) {
        std::cout << "A speaker must be set before drawing !\n";
        return false;
    }
    
    // Draw the based widget
    Widget::draw();
    
    // Draw the speaker
    // Retrieve the tile size
    // TODO : speaker animation
    SDL_Rect src;
    src.x = 0;
    src.y = 0;
    src.w = 96;
    src.h = 96;
        
    SDL_Rect dest;
    dest.x = m_dst->x + 15;
    dest.y = m_dst->y + 10;
    dest.w = 96;
    dest.h = 96;
        
    SDL_RenderCopy(m_renderer, m_speaker, &src, &dest);
    
    // Draw now all the text of the dialog
    int width = 0, height = 0;
    TTF_SizeText(m_font, m_text.c_str(), &width, &height);
    
    // Destination of the text
    SDL_Rect dst = *m_dst;
    
    SDL_Surface *surfaceMessage = TTF_RenderText_Blended_Wrapped(m_font, m_text.c_str(), {255, 255, 255}, m_dst->w - 140);
    SDL_Texture *msg = SDL_CreateTextureFromSurface(m_renderer, surfaceMessage);
    
    dst.x += 125;
    dst.y += 10;
    dst.w = surfaceMessage->w;
    dst.h = surfaceMessage->h;
    SDL_RenderCopy(m_renderer, msg, NULL, &dst);
    
    return true;
}