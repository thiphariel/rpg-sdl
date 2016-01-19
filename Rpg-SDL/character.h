/**
 * @author Thiphariel - 14/01/2016
 */

#ifndef CHARACTER_H
#define CHARACTER_H

#include <SDL2/SDL.h>
#include "animation.h"

class Character
{
public:
    Character(SDL_Texture *sprites);

    void move();
    void stop();

    SDL_Texture *sprites() const;
    int frame() const;
    Animation state() const;
    int x() const;
    int y() const;
    bool moving() const;
    
    void add_frame();
    void state(Animation state);
    
    // Static confs
    static int const character_speed = 2;
protected:
private:
    SDL_Texture *m_sprites;
    bool m_moving;
    int m_frame;
    Animation m_state;
    int m_x;
    int m_y;
};

#endif // CHARACTER_H
