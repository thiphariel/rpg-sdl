/**
 * @author Thiphariel - 14/01/2016
 */

#include "map.h"

Map::Map()
{
}

Map::Map(SDL_Texture *background, SDL_Texture *tileset, int layers, int width, int height, int size)
: m_background(background), m_tileset(tileset), m_layers(layers), m_width(width), m_height(height), m_size(size)
{
}

/**
 * Getters
 */
SDL_Texture *Map::background() const { return m_background; }
SDL_Texture *Map::tileset() const { return m_tileset; }
// Retrieve the number of tile for a row in the tileset
int Map::tiles_for_row() const {
    int w, h;
    SDL_QueryTexture(m_tileset, NULL, NULL, &w, &h);

    return w / m_size;
}
int Map::width() const { return m_width; }
int Map::height() const { return m_height; }
int Map::size() const { return m_size; }
int Map::layers() const { return m_layers; }
int ***Map::tiles() const { return m_tiles; }

/**
 * Handle tiles initialization
 */
void Map::init()
{
    m_tiles = new int**[m_layers];
    for (int layer = 0; layer < m_layers; layer++) {
        m_tiles[layer] = new int*[m_width];

        for (int i = 0; i < m_width; i++) {
            m_tiles[layer][i] = new int[m_height];
            for (int j = 0; j < m_height; j++) {
                m_tiles[layer][i][j] = 0;
            }
        }
    }
}

/**
 * Load all data tiles from the binary file
 */
void Map::load(std::string name)
{
    std::string path = SDL_GetBasePath() + name;
    std::fstream stream(path.c_str(), std::ios::in | std::ios::binary);
    if (!stream.is_open()) {
        std::cerr << "Error while loading map data !\n";
        exit(1);
    }

    for (int layer = 0; layer < m_layers; layer++) {
        for (int i = 0; i < m_width; i++) {
            for (int j = 0; j < m_height; j++) {
                binary_read(stream, m_tiles[layer][i][j]);
            }
        }
    }

    stream.close();

    /*std::vector<std::vector<int> > tiles;
    std::vector<int> data;
    std::string buffer, tmp;
    std::stringstream iostr;

    // Loop throup map data
    while (!stream.eof()) {
        getline(stream, buffer);

        // Do not loop through this iteration if the line is empty
        if (!buffer.size())  {
            continue;
        }

        iostr.clear();
        iostr.str(buffer);

        data.clear();

        while (true) {
            getline(iostr, tmp, ' ');

            // Just push tile number data
            data.push_back(atoi(tmp.c_str()));

            // Have we finished ? :)
            if (!iostr.good()) {
                break;
            }
        }

        // If this line is not empty, push it
        if (data.size()) {
            tiles.push_back(data);
        }
    }*/

    // Assign data to the map tiles
    /*for (int i = 0; i < m_width; i++) {
        for (int j = 0; j < m_height; j++) {
            m_tiles[i][j] = tiles[i][j];
        }
    }*/

    output();
}

// Just output Map tiles content
void Map::output() const
{
    for (int layer = 0; layer < m_layers; layer++) {
        for (int i = 0; i < m_width; i++) {
            for (int j = 0; j < m_height; j++) {
                std::cout << m_tiles[layer][i][j] << " ";
            }

            std::cout << std::endl;
        }

        std::cout << "Fin de la couche n" << layer << "\n" << std::endl;
    }
}
