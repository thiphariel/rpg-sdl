//
//  dialog.h
//  Rpg-SDL
//
//  Created by Thomas on 19/01/2016.
//  Copyright © 2016 Thiphariel. All rights reserved.
//

#ifndef dialog_h
#define dialog_h

#include "widget.h"

class Dialog : public Widget
{
public:
    Dialog(SDL_Renderer *renderer, SDL_Texture *texture, TTF_Font *font, SDL_Rect *src, SDL_Rect *dst, std::string text, SDL_Texture *speaker);
    
    void text(std::string text);
    void speaker(SDL_Texture *speaker);
    
    bool draw() const;
private:
    std::string m_text;
    SDL_Texture *m_speaker;
};

#endif /* dialog_h */
