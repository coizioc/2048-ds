#ifndef ARM9
#define ARM9
#endif
#include <nds.h>
#include "../lib/gl2d.h"

#include <cstdlib>
#include <ctime>

#include "consts.hpp"
#include "gameengine.hpp"
#include "state_menu.hpp"
// #include "state_game.hpp"

// GRIT auto-generated files
#include "tile_nums.h"

PrintConsole topScreen;
PrintConsole bottomScreen;
glImage tile_num_images[10];

void initVideo() {
    TIMER0_CR = TIMER_ENABLE|TIMER_DIV_1024;
	TIMER1_CR = TIMER_ENABLE|TIMER_CASCADE;  
	
	videoSetMode(MODE_5_3D | DISPLAY_BG2_ACTIVE | DISPLAY_BG3_ACTIVE);
	videoSetModeSub(MODE_5_2D);
    vramSetBankA(VRAM_A_TEXTURE);
    vramSetBankC(VRAM_C_SUB_BG_0x06200000);
    vramSetBankD(VRAM_D_SUB_SPRITE);
	vramSetBankE(VRAM_E_TEX_PALETTE);
	vramSetBankI(VRAM_I_SUB_SPRITE);

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
    game.changeState(MenuState::instance());

    while(1) {
        game.handleEvents();
        game.update();
        game.render();
    }

	return 0;
}
