#include "sprite_utils.hpp"

void SpriteUtils::drawTwoByTwoTileSprite(glImage* top_left, int x, int y, int tile_size) {
    glSprite(x, y, GL_FLIP_NONE, top_left);
    glSprite(x + tile_size, y, GL_FLIP_NONE, top_left + 1);
    glSprite(x, y + tile_size, GL_FLIP_NONE, top_left + 8);
    glSprite(x + tile_size, y + tile_size, GL_FLIP_NONE, top_left + 9);
}
