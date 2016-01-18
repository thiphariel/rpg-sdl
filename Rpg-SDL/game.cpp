/**
 * @author Thiphariel - 14/01/2016
 */

#include "game.h"

// Constructor
Game::Game() : m_window(0), m_renderer(0), m_running(true), m_background(0)
{
}

/**
 * Init all the game content, such as SDL window,
 * renderer and more if needed.
 */
bool Game::onInit()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        return false;
    }

    // Init the window
    m_window = SDL_CreateWindow("SDL 2.0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
    if (!m_window) {
        std::cerr << "An error occured while trying to create window : " << SDL_GetError() << std::endl;
        return false;
    }

    // Init the renderer
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!m_renderer) {
        std::cerr << "An error occured while trying to create renderer : " << SDL_GetError() << std::endl;
        return true;
    }

    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
        std::cerr << "An error occured while trying to initiate audio : " << SDL_GetError() << std::endl;
        return false;
    }

    if (TTF_Init() == -1) {
        std::cerr << "An error occured while trying to initiate TTF : " << SDL_GetError();
        return false;
    }

    return true;
}

/**
 * Main game loop, which handle the drawing
 * events, the FPS limitation (if any), and
 * also all the cleaning process
 */
int Game::onRun()
{
    // Init window and renderer
    if (onInit() == false) {
        std::cerr << "An error occured while init";
        return -1;
    }

    // Load resources - textures etc
    if (onLoad() == false) {
        std::cerr << "An error occured while loading resources";
        return -1;
    }

    Mix_PlayMusic(m_background, -1);

    // Main game loop
    unsigned int fps = SDL_GetTicks() + 16;
    while(m_running) {
        // Event loop
        while(SDL_PollEvent(&m_event)) {
            onEvent();
        }

        onLoop();
        onDraw();

        delay(fps);
        fps = SDL_GetTicks() + 16;
    }

    // Clean memory before exit
    clean();

    return 0;
}

/**
 * Load all game resources here
 * such as : tilesets, spritesheets, characters, sounds
 * and all that stuff :)
 */
bool Game::onLoad()
{
    m_background = load_music("music/background.mp3");

    //SDL_Texture *background = loadImage(m_renderer, "graphics/background.png");
    SDL_Texture *tileset = load_image(m_renderer, "graphics/map.png");
    SDL_Texture *ui = load_image(m_renderer, "graphics/ui/alpha.png");
    SDL_Texture *player = load_image(m_renderer, "graphics/character/witch.png");

    // Create a new Map
    m_map = new Map(0, tileset, 3, 50, 50, 32);

    m_map->init();
    m_map->load("map/map.dat");

    // Player
    m_player = new Character(player);

    // Load font
    TTF_Font *font = load_font("fonts/kenpixel_mini.ttf", 18);
    // Ui dialog
    m_ui = new Ui(ui, font);

    return true;
}

/**
 * ? oO
 */
void Game::onLoop()
{
}

/**
 * Handle all the drawing, such as display
 * textures on screen.
 */
void Game::onDraw()
{
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_renderer);

    // Draw map background
    //drawImage(m_map->getBackground(), 0, 0);

    // Display map tiles
    for (int layer = 0; layer < m_map->layers(); layer++) {
        for (int i = 0; i < m_map->height(); i++) {
            for (int j = 0; j < m_map->width(); j++) {
                int tile = m_map->tiles()[layer][j][i] - 1;

                int sx = tile % m_map->tiles_for_row();
                int sy = tile / m_map->tiles_for_row();

                draw(m_map->tileset(), sx, sy, i, j);

                // TODO Character drawing on the right layer
                if (layer == 1) {
                    draw_character(m_player->sprites(), m_player->frame(), m_player->state(), m_player->x(), m_player->y());
                }
            }
        }
    }

    // Border on each 4 sides offset
    SDL_Rect border_offset = {10, 10, 10, 10};
    SDL_Rect frame = (SDL_Rect){0, 300, 640, 180};
    m_ui->dialog(m_renderer, &border_offset, &frame);

    // Write text
    SDL_Color color = {255, 255, 255};
    frame = (SDL_Rect){15, 310, 0, 0};
    m_ui->add_text(m_renderer, "Coucou", color, &frame);

    SDL_RenderPresent(m_renderer);
}

/**
 * Handle all inputs (mouse & keyboard)
 */
void Game::onEvent()
{
    // Quit the game
    if (m_event.type == SDL_QUIT) {
        m_running = false;
    }

    switch (m_event.type) {
        case SDL_KEYDOWN:
            switch(m_event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    m_running = false;
                    break;

                // Character move
                case SDLK_z:
                    m_player->move(UP);
                    break;
                case SDLK_s:
                    m_player->move(DOWN);
                    break;
                case SDLK_q:
                    m_player->move(LEFT);
                    break;
                case SDLK_d:
                    m_player->move(RIGHT);
                    break;
            }
            break;
    }
}
