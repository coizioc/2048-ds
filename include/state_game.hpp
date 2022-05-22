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
		return &s_state;
	}

protected:
	GameState() {}

private:
    int m_animation_offset;
    int m_buttons_pressed;
    int m_swipe_dir;
    Grid m_grid;
    Grid m_prev_grid;
    Vec2 m_tile_transitions[Grid::NUM_TILES];
	static GameState s_state;

    void addStartTiles();
    void addRandomTile();

    void resetMovesArray();
    bool move(Vec2 velocity);
    Vec2 doMove(bool* blocked, int x, int y, Vec2 velocity);

    void drawGrid(GameEngine* game, int dy);
};

#endif
