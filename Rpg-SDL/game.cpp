/**
 * @author Thiphariel - 14/01/2016
 */

#include "game.h"

// Constructor
Game::Game() : m_window(0), m_renderer(0), m_running(true), m_background(0)
{
    m_widgets = new std::vector<Widget*>();
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
        return false;
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
        onEvent();
    
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
    // Loading resources
    m_background = load_music("music/background.mp3");
    
    m_tileset = load_image(m_renderer, "graphics/map.png");
    m_dialog = load_image(m_renderer, "graphics/ui/alpha.png");
    m_player_spritesheet = load_image(m_renderer, "graphics/character/witch.png");
    m_player_dialog = load_image(m_renderer, "graphics/character/dialog/witch.png");
    
    m_font_pixel = load_font("fonts/kenpixel_mini.ttf", 18);

    // Create a new Map
    m_map = new Map(m_tileset, 3, 50, 50, 32);

    m_map->init();
    m_map->load("map/map.dat");

    // Player
    m_player = new Character(m_player_spritesheet);

    return true;
}

/**
 * Handle all looping actions that not concerne drawing or event,
 * such as Widgets
 */
void Game::onLoop()
{
    // For each widgets, if any, check if they need to be removed
    std::vector<Widget*>::iterator it = m_widgets->begin();
    while (it != m_widgets->end()) {
        if ((*it)->destroyed()) {
            std::cout << "A widget is going to be destroyed !\n";
            remove_widget(*it);
            return;
        }
        it++;
    }
    
    // Update player position
    if (m_player->moving()) {
        m_player->add_frame();
        m_player->move();
    }
}

/**
 * Handle all the drawing, such as display
 * textures on screen.
 */
void Game::onDraw()
{
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_renderer);

    // Display map tiles
    for (int layer = 0; layer < m_map->layers(); layer++) {
        for (int i = 0; i < m_map->height(); i++) {
            for (int j = 0; j < m_map->width(); j++) {
                int tile = m_map->tiles()[layer][j][i] - 1;

                int sx = tile % m_map->tiles_for_row();
                int sy = tile / m_map->tiles_for_row();

                // Draw the current tile
                draw(m_map->tileset(), sx, sy, i, j);

                // TODO Character drawing on the right layer
                if (layer == Layers::MID) {
                    draw_character(m_player->sprites(), m_player->frame(), m_player->state(), m_player->x(), m_player->y());
                }
            }
        }
    }
    
    // For each widgets, if any, draw them on screen
    std::vector<Widget*>::iterator it = m_widgets->begin();
    while (it != m_widgets->end() && !(*it)->destroyed()) {
        if (!(*it)->draw()) {
            remove_widget((*it));
            return;
        }
        it++;
    }

    SDL_RenderPresent(m_renderer);
}

/**
 * Handle all inputs (mouse & keyboard)
 */
void Game::onEvent()
{
    while (SDL_PollEvent(&m_event)) {
        // Quit the game
        if (m_event.type == SDL_QUIT) {
            m_running = false;
        }
        
        // Loop on each widget (reverse loop, to catch the last widget added first)
        // and call onEvent, if an event occured, then break this loop
        std::vector<Widget*>::iterator it = m_widgets->begin();
        // On parcour la liste des widget pour leur signaler l'evenement
        while (it != m_widgets->end()) {
            // Si la widget intercepte l'event, on arrete de boucler
            if ((*it)->onEvent(m_event)) {
                std::cout << "An event has been itercepted !\n";
                return;
            }
            it++;
        }
        
        // Main game event loop
        switch (m_event.type) {
            case SDL_MOUSEBUTTONUP:
                std::cout << "Click up on the main !\n";
                break;
            case SDL_KEYDOWN:
                switch(m_event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        m_running = false;
                        break;
                        
                    case SDLK_c:
                        src = {10, 10, 10, 10};
                        dst = (SDL_Rect){0, 360, 640, 120};
                        widget = new Dialog(m_renderer, m_dialog, m_font_pixel, &src, &dst, "This text could be intersting, but I decide to create a master piece of boring shit, instead of something you could enjoy reading. Are you ok with that ? Anyway, I don't mind. :)", m_player_dialog);
                        add_widget(widget);
                        break;
                        
                        // Character move
                    case SDLK_z:
                        m_player->state(UP);
                        break;
                    case SDLK_s:
                        m_player->state(DOWN);
                        break;
                    case SDLK_q:
                        m_player->state(LEFT);
                        break;
                    case SDLK_d:
                        m_player->state(RIGHT);
                        break;
                }
                break;
            case SDL_KEYUP:
                m_player->stop();
                break;
        }
    }
}
