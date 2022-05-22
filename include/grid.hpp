#ifndef GRID_HPP
#define GRID_HPP

#include <cstdlib>

class Grid {   
public:
    static const size_t GRID_SIZE = 4;
    static const size_t NUM_TILES = GRID_SIZE * GRID_SIZE;

    Grid() {
        for(size_t i = 0; i < NUM_TILES; i++) {
            this->m_cells[i] = 0;
        }
    }

    Grid(const Grid& grid) {
        for (size_t i = 0; i < NUM_TILES; i++) {
            this->m_cells[i] = grid.m_cells[i];
        }
    }

    size_t randomAvailableCell() {
        size_t rand_idx;
        do {
            rand_idx = rand() % NUM_TILES;
        } while(cellOccupied(rand_idx));

        return rand_idx;
    }

    bool anyCellsAvailable() {
        for (size_t i = 0; i < NUM_TILES; i++) {
            if (cellEmpty(i)) {
                return true;
            }
        }
        return false;
    }

    bool cellEmpty(size_t x, size_t y) {
        return cellEmpty(flatten2DCoords(x, y));
    }

    bool cellEmpty(size_t idx) {
        return this->m_cells[idx] == 0;
    }

    bool cellOccupied(size_t x, size_t y) {
        return cellOccupied(flatten2DCoords(x, y));
    }
    
    bool cellOccupied(size_t idx) {
        return !cellEmpty(idx);
    }

    int getTile(size_t x, size_t y) {
        return getTile(flatten2DCoords(x, y));
    }

    int getTile(size_t idx) {
        return this->m_cells[idx];
    }

    void setTile(size_t x, size_t y, size_t value) {
        setTile(flatten2DCoords(x, y), value);
    }

    void setTile(size_t idx, size_t value) {
        this->m_cells[idx] = value;
    }

    void removeTile(size_t x, size_t y) {
        removeTile(flatten2DCoords(x, y));
    }

    void removeTile(size_t idx) {
        this->m_cells[idx] = 0;
    }

    bool withinBounds(size_t x, size_t y) {
        return x >= 0 && x < GRID_SIZE && y >= 0 && y < GRID_SIZE;
    }

    int getSpriteIndexOfTileValue(size_t x, size_t y) {
        int value = getTile(x, y);

        if (value == 0) {
            return 1;
        }

        value >>= 1;

        int index = 0;
        while ((value & 1) == 0) {
            value >>= 1;
            index++;
        }
        return index;
    }

private:
    int m_cells[NUM_TILES];

    size_t flatten2DCoords(size_t x, size_t y) {
        return GRID_SIZE * y + x;
    }
};

#endif
