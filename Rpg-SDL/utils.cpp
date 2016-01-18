/**
 * @author Thiphariel - 14/01/2016
 */

#include "game.h"

void Game::clean()
{
    delete m_map;
    m_map = NULL;
    delete m_ui;
    m_ui = NULL;

    // Destroy textures here if needed !

    TTF_Quit();
    Mix_Quit();
    IMG_Quit();
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

void Game::delay(unsigned int frameLimit)
{
    // Block at 60 fps
    unsigned int ticks = SDL_GetTicks();

    if (frameLimit < ticks) {
        return;
    }

    if (frameLimit > ticks + 16) {
        SDL_Delay(16);
    } else {
        SDL_Delay(frameLimit - ticks);
    }
}

/**
 * Load an image as texture
 */
SDL_Texture *Game::load_image(SDL_Renderer *renderer, std::string name)
{
    SDL_Surface *image = NULL;
    SDL_Texture *texture = NULL;

    std::string path = SDL_GetBasePath() + name;
    image = IMG_Load(path.c_str());

    if (image != NULL) {
        texture = SDL_CreateTextureFromSurface(renderer, image);

        SDL_FreeSurface(image);
        image = NULL;
    } else {
        std::cout << "L'image n'a pas pu tre chargŽe! SDL_Error : " << SDL_GetError();
    }

    return texture;
}

Mix_Music *Game::load_music(std::string name)
{
    Mix_Music *music = NULL;

    std::string path = SDL_GetBasePath() + name;
    music = Mix_LoadMUS(path.c_str());
    if (music == NULL) {
        std::cerr << "An error occured while loading background music";
    }

    return music;
}

/**
 * Load font
 */
TTF_Font *Game::load_font(std::string name, int size)
{
    TTF_Font *font = NULL;

    std::string path = SDL_GetBasePath() + name;
    font = TTF_OpenFont(path.c_str(), size);
    if (font == NULL) {
        std::cerr << "An error occured while loading font";
    }

    return font;
}

void Game::draw(SDL_Texture *texture, int x, int y)
{
    // Retrieve the tile size
    int size = m_map->size();

    SDL_Rect dest;
    dest.x = x * size;
    dest.y = y * size;

    SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
    SDL_RenderCopy(m_renderer, texture, NULL, &dest);
}

void Game::draw(SDL_Texture *texture, int sx, int sy, int dx, int dy)
{
    // Retrieve the tile size
    int size = m_map->size();

    SDL_Rect src;
    src.x = sx * size;
    src.y = sy * size;
    src.w = size;
    src.h = size;

    SDL_Rect dest;
    dest.x = dx * size;
    dest.y = dy * size;
    dest.w = size;
    dest.h = size;

    SDL_RenderCopy(m_renderer, texture, &src, &dest);
}

void Game::draw_character(SDL_Texture *texture, int sx, int sy, int dx, int dy)
{
    // Retrieve the tile size
    int size = m_map->size();

    SDL_Rect src;
    src.x = sx * size;
    src.y = sy * size;
    src.w = size;
    src.h = size;

    SDL_Rect dest;
    dest.x = dx;
    dest.y = dy;
    dest.w = size;
    dest.h = size;

    SDL_RenderCopy(m_renderer, texture, &src, &dest);
}
