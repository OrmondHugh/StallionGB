#include <stdint.h>

/*
* Unit of the list, containing information about the sprite
*/
typedef struct SpriteData {
	int8_t xPos;
	int8_t attributeLocation;
	struct SpriteData *next;
} SpriteData;

/*
* List of the <= 10 sprites to be displayed on the screen, 
* ordered based on their priority 
*/
typedef struct SpriteList {
	SpriteData *first;

	int spriteCount;
} SpriteList;

void AddSprites(SpriteList *list, int8_t *memory);