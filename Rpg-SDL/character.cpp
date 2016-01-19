/**
 * @author Thiphariel - 14/01/2016
 */

#include "character.h"

Character::Character(SDL_Texture *sprites) : m_moving(false), m_sprites(sprites), m_frame(0), m_x(48), m_y(192)
{
    m_state = DOWN;
}

SDL_Texture *Character::sprites() const { return m_sprites; }
int Character::frame() const { return m_frame / 9; }
Animation Character::state() const { return m_state; }
int Character::x() const { return m_x; }
int Character::y() const { return m_y; }
bool Character::moving() const { return m_moving; }

void Character::add_frame() {
    m_frame++;
    
    // Update the frame if we are out of bounds
    if (m_frame / 9 >= 3) {
        m_frame = 0;
    }
}
void Character::state(Animation state) {
    m_moving = true;
    m_state = state;
}

void Character::move()
{
    if (!m_moving) {
        return;
    }

    switch (m_state) {
    case UP:
        m_y -= Character::character_speed;
        break;
    case DOWN:
        m_y += Character::character_speed;
        break;
    case LEFT:
        m_x -= Character::character_speed;
        break;
    case RIGHT:
        m_x += Character::character_speed;
        break;
    }
}

void Character::stop()
{
    m_moving = false;
    m_frame = 1;
}
