#ifndef STATE_MENU_HPP
#define STATE_MENU_HPP

#include "state.hpp"
#include "vec2.hpp"

class MenuState : public State {
public:
    static const int ANIMATION_FRAMES = 12;

    void init(GameEngine* game);
	void dispose(GameEngine* game);

	void pause(GameEngine* game);
	void resume(GameEngine* game);

	void handleEvents(GameEngine* game);
	void update(GameEngine* game);
	void render(GameEngine* game);
	
	static MenuState* instance() {
		return &_state;
	}

protected:
	MenuState() {}

private:
	static MenuState _state;
};

#endif
