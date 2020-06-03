#include "SpriteList.h"
#include <stdlib.h>

/*
* Fills list with SpriteData structs representing the sprites to be displayed on the line, ordered in increases priority
*/
void AddSprites(SpriteList *list,  int8_t *memory) {
	int8_t lcdcY = memory[0xFF44];

	// Initialise list
	list->first = (SpriteData *) malloc(sizeof(SpriteData));

	// Loop through each entry in the OAM
	for (int i = 0xFE00; i < 0xFE9F; i += 4) {
		int8_t spriteX = memory[i + 1];
		// If the sprite is not on the line, continue
		if (spriteX > lcdcY || spriteX + 8 < lcdcY) {
			continue;
		}

		// If the list is empty, insert at start
		if (list->spriteCount == 0) {
			list->first->next = (SpriteData *) malloc(sizeof(SpriteData));
			list->first->next->attributeLocation = i;
			list->first->next->next = NULL;
			list->first->next->xPos = spriteX;

			list->spriteCount++;
		} else  {
			int inserted = 0;
			// Iterate through the list and find where
			// the sprite should be
			SpriteData *tmp = list->first;

			do {
				// If the priority is lower, insert
				if ((spriteX > tmp->next->xPos) || ((spriteX == tmp->next->xPos) && (i > tmp->next->attributeLocation))) { // X
					SpriteData *tmp2 = tmp->next;

					tmp->next = (SpriteData *) malloc(sizeof(SpriteData));
					tmp->next->xPos = spriteX;
					tmp->next->attributeLocation = i;
					tmp->next->next = tmp2;
					list->spriteCount++;
					inserted = 1;
					break;
				}

				tmp = tmp->next;
			} while (tmp->next != NULL);

			if (inserted) continue;

			// If we reach the end, place the sprite there
			tmp->next = (SpriteData *) malloc(sizeof(SpriteData));
			tmp->next = NULL;
			tmp->next->xPos = spriteX;
			tmp->next->attributeLocation = i;
			list->spriteCount++;
		}
	}
}