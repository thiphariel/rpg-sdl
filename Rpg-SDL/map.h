/**
 * @author Thiphariel - 14/01/2016
 */

#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <SDL2/SDL.h>
#include "binary.h"

class Map
{
    public:
        Map();
        Map(SDL_Texture *background, SDL_Texture *tileset, int layers, int width, int height, int size);
        void init();
        void load(std::string name);
        void output() const;

        SDL_Texture *background() const;
        SDL_Texture *tileset() const;
        int tiles_for_row() const;
        int width() const;
        int height() const;
        int size() const;
        int layers() const;
        int ***tiles() const;
    private:
        SDL_Texture *m_background;
        SDL_Texture *m_tileset;
        int m_layers;
        int m_width;
        int m_height;
        int m_size;
        int ***m_tiles;
};

#endif // MAP_H
