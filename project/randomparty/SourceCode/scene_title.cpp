#include "all.h"

#define SELECT_COUNT 2              //‘I‘ğˆ‚Ì”

int title_state;
int title_timer;

int select_c;

Sprite* backspr;

//--------------------------------------
//  ‰Šúİ’è
//--------------------------------------
void title_init()
{
    title_state = 0;
    title_timer = 0;
    select_c = 0;
}

//--------------------------------------
//  I—¹ˆ—
//--------------------------------------
void title_deinit()
{
    music::stop(3);

    safe_delete(backspr);
}

void title_update()
{
}
void title_render()
{
    // ‰æ–Ê‚ğÂ‚Å“h‚è‚Â‚Ô‚·
    GameLib::clear(0.3f, 0.5f, 1.0f);
}