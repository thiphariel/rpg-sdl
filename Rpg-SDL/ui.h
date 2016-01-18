/**
 * @author Thiphariel - 14/01/2016
 */

#ifndef UI_H
#define UI_H

#include "widget.h"

#define MAX(a, b) ((a)>(b)?(a):(b))

class Ui : Widget
{
public:
    Ui(SDL_Renderer *renderer, SDL_Texture *texture, TTF_Font *font);
    void dialog(SDL_Rect *src, SDL_Rect *dst);
    void add_text(std::string text, SDL_Color color, SDL_Rect *dst) const;
    void destroy();
    bool onEvent(SDL_Event &event);
    
    void active(bool active);
    bool active() const;
protected:
private:
    SDL_Renderer *m_renderer;
    SDL_Texture *m_texture;
    TTF_Font *m_font;
    SDL_Rect m_position;
    SDL_Rect m_border;
    bool m_active;
};

#endif // UI_H
