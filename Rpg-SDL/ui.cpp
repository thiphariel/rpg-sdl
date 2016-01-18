/**
 * @author Thiphariel - 14/01/2016
 */

#include "ui.h"

Ui::Ui(SDL_Texture *texture, TTF_Font *font) : m_texture(texture), m_font(font)
{
}

void Ui::dialog(SDL_Renderer *renderer, SDL_Rect *src, SDL_Rect *dst) const
{
    // Create a copy of the dst rect so we can modify it
    SDL_Rect frame = *dst;
    // Make sure that the dst isn't too small
    // Sort of like how CSS box-sizing: border-box; works
    // if we have a width of 50px, but the padding is set to 30px, then we will have a 60px wide box
    frame.w = MAX(frame.w, src->x+src->w);
    frame.h = MAX(frame.h, src->y+src->h);
    int w, h;
    SDL_QueryTexture(m_texture, NULL, NULL, &w, &h);

    SDL_Point srcPoints[] = {
        {0, 0},
        {src->x, src->y},
        {w - src->w, h - src->h},
        {w, h}
    };

    SDL_Point dstPoints[] = {
        {frame.x, frame.y},
        {frame.x + src->x, frame.y + src->y},
        {frame.x + frame.w - src->w, frame.y + frame.h - src->h},
        {frame.x + frame.w, frame.y + frame.h}
    };

    //Loop trough and draw each rect
    for (int y = 0; y < 3; y++ ) {
        for (int x = 0; x < 3; x++) {
            SDL_Rect src_ = {
                srcPoints[x].x,
                srcPoints[y].y,
                srcPoints[x+1].x,
                srcPoints[y+1].y
            };
            src_.w -= src_.x;
            src_.h -= src_.y;

            SDL_Rect dst_ = {
                dstPoints[x].x,
                dstPoints[y].y,
                dstPoints[x+1].x,
                dstPoints[y+1].y
            };
            dst_.w -= dst_.x;
            dst_.h -= dst_.y;

            SDL_RenderCopy(renderer, m_texture, &src_, &dst_);
        }
    }
}

void Ui::add_text(SDL_Renderer *renderer, std::string text, SDL_Color color, SDL_Rect *dst) const
{
    SDL_Surface *surfaceMessage = TTF_RenderText_Solid(m_font, text.c_str(), color);
    SDL_Texture *msg = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

    dst->w = surfaceMessage->w;
    dst->h = surfaceMessage->h;
    SDL_RenderCopy(renderer, msg, NULL, dst);
}
