#ifndef ARM9
#define ARM9
#endif
#include <nds.h>
#include "../lib/gl2d.h"

#include <cstdlib>
#include <ctime>

#include "consts.hpp"
#include "gameengine.hpp"
#include "state_game.hpp"

// GRIT auto-generated files
#include "tile_nums.h"

PrintConsole topScreen;
PrintConsole bottomScreen;
glImage tile_num_images[10];

void initVideo() {
    TIMER0_CR = TIMER_ENABLE|TIMER_DIV_1024;
	TIMER1_CR = TIMER_ENABLE|TIMER_CASCADE;  
	
	videoSetMode(MODE_5_3D | DISPLAY_BG2_ACTIVE | DISPLAY_BG3_ACTIVE);
	videoSetModeSub(MODE_0_2D | DISPLAY_BG3_ACTIVE);	
	vramSetBankI(VRAM_I_SUB_BG_0x06208000);	
	vramSetBankA(VRAM_A_TEXTURE);
	vramSetBankE(VRAM_E_TEX_PALETTE); 
			 
	consoleSelect(&bottomScreen);
	consoleInit(&bottomScreen, 0, BgType_Text4bpp, BgSize_T_256x256, 20, 0, false, false);	
    lcdMainOnBottom();

    setBackdropColorSub(COLOR_BG);
    glScreen2D();
}

int main(void) {
    powerOn(POWER_ALL_2D);
    srand(time(NULL));
    initVideo();

    GameEngine game = GameEngine();
    game.init();
    game.changeState(GameState::instance());

    while(1) {
        game.handleEvents();
        game.update();
        game.render();
    }

	return 0;
}
