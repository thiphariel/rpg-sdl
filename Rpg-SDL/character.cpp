/**
 * @author Thiphariel - 14/01/2016
 */

#include "character.h"

Character::Character(SDL_Texture *sprites) : m_sprites(sprites), m_frame(0), m_x(48), m_y(192)
{
}

SDL_Texture *Character::sprites() const { return m_sprites; }
int Character::frame() const { return m_frame; }
Animation Character::state() const { return m_state; }
int Character::x() const { return m_x; }
int Character::y() const { return m_y; }

void Character::move(Animation state)
{
    m_state = state;

    m_frame++;
    if (m_frame > 2) {
        m_frame = 0;
    }

    switch (state) {
    case UP:
        m_y -= 4;
        break;
    case DOWN:
        m_y += 4;
        break;
    case LEFT:
        m_x -= 4;
        break;
    case RIGHT:
        m_x += 4;
        break;
    }
}
