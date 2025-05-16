#include "store.h"
#include <assert.h>
#include "ui_style.h"
#define TILE_SIZE  65



void Add_Slot(GameData* g, Vector2* Cursor){
    DrawRectangle(Cursor->x , Cursor->y, TILE_SIZE, TILE_SIZE, GREEN);

Cursor->x += TILE_SIZE + PADDING;
if(Cursor->x += TILE_SIZE - PADDING){
Cursor->x += 10; 
    
}

}
void ui_store(GameData* g){
    assert(0 && "@TODO: Implemente me");
    Vector2 Cursor = {10,10};
    int tileSize = 15;
    int tilesPerRow = g->img->width / tileSize;
    int tilesPerCol = g->img->height / tileSize;
    int startRow = 0;
    int startCol = tilesPerRow / 9;
    int startIndex = startRow * tilesPerRow + startCol;
    for(int i = 0; i<60 && (startIndex+1)< (tilesPerRow * tilesPerCol); i++){
        int tileIndex = startIndex + i;
        Rectangle sourceRect = {
            (tileIndex % tilesPerRow) * tileSize,
            (tileIndex / tilesPerRow) * tileSize,
            tileSize,
            tileSize,
        };
        Add_Slot(g, &Cursor, sourceRect);
    }
}