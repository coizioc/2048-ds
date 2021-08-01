#ifndef GRID_HPP
#define GRID_HPP

#include <cstdlib>

class Grid {   
public:
    static const size_t grid_size = 4;
    static const size_t num_tiles = grid_size * grid_size;

    Grid() {
        for(size_t i = 0; i < num_tiles; i++) {
            this->cells[i] = 0;
        }
    }

    Grid(const Grid& grid) {
        for (size_t i = 0; i < num_tiles; i++) {
            this->cells[i] = grid.cells[i];
        }
    }

    size_t randomAvailableCell() {
        size_t rand_idx;
        do {
            rand_idx = rand() % num_tiles;
        } while(cellOccupied(rand_idx));

        return rand_idx;
    }

    bool anyCellsAvailable() {
        for (size_t i = 0; i < num_tiles; i++) {
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
        return this->cells[idx] == 0;
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
        return this->cells[idx];
    }

    void setTile(size_t x, size_t y, size_t value) {
        setTile(flatten2DCoords(x, y), value);
    }

    void setTile(size_t idx, size_t value) {
        this->cells[idx] = value;
    }

    void removeTile(size_t x, size_t y) {
        removeTile(flatten2DCoords(x, y));
    }

    void removeTile(size_t idx) {
        this->cells[idx] = 0;
    }

    bool withinBounds(size_t x, size_t y) {
        return x >= 0 && x < grid_size && y >= 0 && y < grid_size;
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
    int cells[num_tiles];

    size_t flatten2DCoords(size_t x, size_t y) {
        return grid_size * y + x;
    }
};

#endif
