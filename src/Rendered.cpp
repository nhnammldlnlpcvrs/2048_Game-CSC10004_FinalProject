#include "Renderer.h"
#include "Global.h"

void renderGame() {
    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
    SDL_RenderClear(gRenderer);
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            renderTile(board[i][j], i, j);
}