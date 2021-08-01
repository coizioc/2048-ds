#ifndef STATE_GAME_HPP
#define STATE_GAME_HPP

#include "grid.hpp"
#include "state.hpp"
#include "vec2.hpp"

class GameState : public State {
public:
    static const int ANIMATION_FRAMES = 12;

    void init(GameEngine* game);
	void dispose(GameEngine* game);

	void pause(GameEngine* game);
	void resume(GameEngine* game);

	void handleEvents(GameEngine* game);
	void update(GameEngine* game);
	void render(GameEngine* game);
	
	static GameState* instance() {
		return &_state;
	}

protected:
	GameState() {}

private:
    int animation_offset;
    int buttonsPressed;
    int swipe_dir;
    Grid grid;
    Grid prev_grid;
    Vec2 tile_transitions[Grid::num_tiles];
	static GameState _state;

    void addStartTiles();
    void addRandomTile();

    void resetMovesArray();
    bool move(Vec2 velocity);
    Vec2 doMove(bool* blocked, int x, int y, Vec2 velocity);

    void drawGrid(GameEngine* game, int dy);
};

#endif
