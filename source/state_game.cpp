#ifndef ARM9
#define ARM9
#endif
#include <nds.h>
#include "../lib/gl2d.h"

#include "consts.hpp"
#include "animation.hpp"
#include "state_game.hpp"

GameState GameState::s_state;

void GameState::init(GameEngine* game) {
    addStartTiles();
    const int y_offset = 50;

    std::vector<int> ease_out_frame_values = Animations::ease_out(30, y_offset);
    for (std::vector<int>::iterator it = ease_out_frame_values.begin(); it != ease_out_frame_values.end(); it++) {
        int frame_value = *it;
        
        glBegin2D();

        drawGrid(game, y_offset - frame_value);

        glEnd2D();
        glFlush(0);

        swiWaitForVBlank();
    }
}

void GameState::dispose(GameEngine* game) {
    const int y_offset = 50;
    std::vector<int> ease_in_frame_values = Animations::ease_in(30, y_offset);
    for (std::vector<int>::iterator it = ease_in_frame_values.begin(); it != ease_in_frame_values.end(); it++) {
        int frame_value = *it;
        
        glBegin2D();

        drawGrid(game, y_offset - frame_value);

        glEnd2D();
        glFlush(0);

        swiWaitForVBlank();
    }
}

void GameState::pause(GameEngine* game) {

}

void GameState::resume(GameEngine* game) {

}

void GameState::handleEvents(GameEngine* game) {

}

void GameState::update(GameEngine* game) {
    int keys_pressed = keysDown();
    if (game->input_handler().isSwipe()) {
        m_swipe_dir = game->input_handler().getSwipe();
        keys_pressed |= m_swipe_dir;
    }
    if (keys_pressed & KEY_R) {
        for (size_t i = 0; i < Grid::GRID_SIZE; i++) {
            for (size_t j = 0; j < Grid::GRID_SIZE; j++) {
                m_grid.setTile(i, j, m_grid.getTile(i, j) * 2);
            }
        }
    }

    Vec2 velocity = getVelocity(keys_pressed);

    bool moved = move(velocity);
    if (moved) {
        addRandomTile();
        m_animation_offset = ANIMATION_FRAMES;
    }
}

void GameState::render(GameEngine* game) {
    glBegin2D();

    drawGrid(game, 0);

    glEnd2D();
    glFlush(0);

    swiWaitForVBlank();
}

void GameState::addStartTiles() {
    const int startTiles = 2;
    for (int i = 0; i < startTiles; i++) {
        addRandomTile();
    }
}

void GameState::addRandomTile() {
    if (m_grid.anyCellsAvailable()) {
        int value = rand() % 10 < 9 ? 2 : 4;

        int rand_idx = m_grid.randomAvailableCell();

        m_grid.setTile(rand_idx, value);
    }
}

bool canMerge(Grid& grid, bool* blocked, int x1, int y1, int x2, int y2) {
    return grid.cellOccupied(x2, y2)
        && grid.getTile(x1, y1) == grid.getTile(x2, y2)
        && !blocked[Grid::GRID_SIZE * y1 + x1]
        && !blocked[Grid::GRID_SIZE * y2 + x2];
}

bool canShift(Grid& grid, int x1, int y1, int x2, int y2) {
    return grid.cellEmpty(x2, y2) && grid.cellOccupied(x1, y1);
}

void GameState::resetMovesArray() {
    for (size_t i = 0; i < Grid::NUM_TILES; i++) {
        m_tile_transitions[i] = Vec2(0, 0);
    }
}

bool GameState::move(Vec2 velocity) {
    if (velocity == Vec2(0, 0)) {
        return false;
    }

    bool moved = false;
    bool blocked[Grid::NUM_TILES] = { false };

    m_prev_grid = Grid(m_grid);
    resetMovesArray();

    // If vertical movement...
    if (velocity.x == 0) {
        for (size_t i = 0; i < Grid::GRID_SIZE; i++) {
            size_t j = (velocity.y == -1) ? 1 : 2;
            while (j >= 0 && j < Grid::GRID_SIZE) {
                if (m_grid.cellOccupied(i, j)) {
                    Vec2 movedBy = doMove(blocked, i, j, velocity);
                    m_tile_transitions[Grid::GRID_SIZE * j + i] = movedBy;
                    moved |= movedBy != Vec2(0, 0);
                }
                j -= velocity.y;
            }
        }
    // If horizontal movement...
    } else {
        for (size_t j = 0; j < Grid::GRID_SIZE; j++) {
            size_t i = (velocity.x == -1) ? 1 : 2;
            while (i >= 0 && i < Grid::GRID_SIZE) {
                if (m_grid.cellOccupied(i, j)) {
                    Vec2 movedBy = doMove(blocked, i, j, velocity);
                    m_tile_transitions[Grid::GRID_SIZE * j + i] = movedBy;
                    moved |= movedBy != Vec2(0, 0);
                }
                i -= velocity.x;
            }
        }
    }

    return moved;
}

Vec2 GameState::doMove(bool* blocked, int x, int y, Vec2 velocity) {
    Vec2 movedBy = Vec2(0, 0);
    bool moved = false;
    int dx = velocity.x;
    int dy = velocity.y;

    int new_x = x + dx;
    int new_y = y + dy;

    if (canMerge(m_grid, blocked, x, y, new_x, new_y)) {
        m_grid.removeTile(x, y);
        m_grid.setTile(new_x, new_y, m_grid.getTile(new_x, new_y) * 2);
        blocked[Grid::GRID_SIZE * new_y + new_x] = true;
        // score += grid.getTile(new_x, new_y);
        moved = true;
    } else if (canShift(m_grid, x, y, new_x, new_y)) {
        m_grid.setTile(new_x, new_y, m_grid.getTile(x, y));
        m_grid.removeTile(x, y);
        moved = true;
    }

    if (moved) {
        movedBy = velocity;
    }

    if ((dx > 0 && new_x < 3) || (dx < 0 && new_x > 0) || (dy > 0 && new_y < 3) || (dy < 0 && new_y > 0)) {
        Vec2 newMovedBy = doMove(blocked, new_x, new_y, velocity);
        movedBy = Vec2(newMovedBy.x + movedBy.x, newMovedBy.y + movedBy.y);
    }

    return movedBy;
}

void GameState::drawGrid(GameEngine* game, int dy) {
    glBoxFilled(0, 0, 255, 191, COLOR_BG);

    const int border = 6;
    const int box_length = 32;
    const int length = 5 * border + 4 * box_length;

    const int border_x = 256 / 2 - length / 2;
    const int border_y = 192 / 2 - length / 2 + dy;

    glBoxFilled(border_x, border_y, border_x + length, border_y + length, COLOR_GRID_BG);
    
    for (size_t i = 0; i < Grid::GRID_SIZE; i++) {
        for (size_t j = 0; j < Grid::GRID_SIZE; j++) {
            int x = border_x + border + (box_length + border) * i;
            int y = border_y + border + (box_length + border) * j;

            glBoxFilled(x, y, x + box_length - 1, y + box_length - 1, COLOR_GRID_EMPTY);
            
        }
    }

    Grid grid_to_use = (m_animation_offset > 0) ? m_prev_grid : m_grid;

    for (size_t i = 0; i < Grid::GRID_SIZE; i++) {
        for (size_t j = 0; j < Grid::GRID_SIZE; j++) {
            if (grid_to_use.cellOccupied(i, j)) {
                int x = border_x + border + (box_length + border) * i;
                int y = border_y + border + (box_length + border) * j;

                if (m_animation_offset > 0) {
                    Vec2 velocity = m_tile_transitions[Grid::GRID_SIZE * j + i];

                    float distance_x = velocity.x * (border + box_length);
                    float distance_y = velocity.y * (border + box_length);

                    int dx = (int)((float)(ANIMATION_FRAMES - m_animation_offset) / (float)ANIMATION_FRAMES * distance_x);
                    int dy = (int)((float)(ANIMATION_FRAMES - m_animation_offset) / (float)ANIMATION_FRAMES * distance_y);

                    x += dx;
                    y += dy;

                    m_animation_offset--;
                }

                int tile_idx = grid_to_use.getSpriteIndexOfTileValue(i, j);
                glSprite(x, y, GL_FLIP_NONE, game->m_tile_num_images + tile_idx);
            }
        }
    }
}
