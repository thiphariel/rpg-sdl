/**
 * @author Thiphariel - 14/01/2016
 */

#ifndef UI_H
#define UI_H

#include <string>
#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>

#define MAX(a, b) ((a)>(b)?(a):(b))

class Ui
{
    public:
        Ui(SDL_Texture *texture, TTF_Font *font);
        void dialog(SDL_Renderer *renderer, SDL_Rect *src, SDL_Rect *dst) const;
        void add_text(SDL_Renderer *renderer, std::string text, SDL_Color color, SDL_Rect *dst) const;
    protected:
    private:
        SDL_Texture *m_texture;
        SDL_Rect m_border;
        TTF_Font *m_font;
};

#endif // UI_H
