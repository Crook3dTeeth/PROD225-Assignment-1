#pragma once
#include "MonsterWorld.h"
#include "TVector2D.h"
#include "Macros.h"


class TextRenderer
{
public:
	void RenderText(std::string Text, TVector2D<uint32_t> InScreenPosition, MonsterWorld* World, olc::Sprite* Tileset)
	{
		olc::vi2d CurrentTextPosition = { static_cast<int32_t>(InScreenPosition.X), static_cast<int32_t>(InScreenPosition.Y) };
		
		// Get the base of the sprite for the lower and upper case
		olc::vi2d SpriteLowerOffset = {79, 586};
		olc::vi2d SpriteUpperOffset = {1, 573};
		olc::vi2d TCurrentSprite;
		
		// Loop through all the characters 
		for (int CharIndex = 0; CharIndex < Text.size(); CharIndex++) {
			char CurrentChar = Text[CharIndex];

			// Check for space
			if (CurrentChar == ' ') {
				CurrentTextPosition.x += SPRITE_X_SIZE;
				continue;
			}
			// Capital letters
			else if (CurrentChar >= 65 && CurrentChar <= 90) {
				TCurrentSprite = SpriteUpperOffset;
				// Check if its on next row
				if (CurrentChar >= 85) {
					TCurrentSprite.y += (SPRITE_Y_SIZE + 1);
					TCurrentSprite.x += ((SPRITE_X_SIZE + 1) * (CurrentChar - 85));
				}
				else {
					TCurrentSprite.x += ((SPRITE_X_SIZE + 1) * (CurrentChar - 65));
				}
			}
			// Lowercase
			else if (CurrentChar >= 97 && CurrentChar <= 122) {
				TCurrentSprite = SpriteLowerOffset;
				// Check if its on next row
				if (CurrentChar <= 110) {
					TCurrentSprite.x += ((SPRITE_X_SIZE + 1) * (CurrentChar - 97));
				}
				else {
					TCurrentSprite.y += (SPRITE_Y_SIZE + 1);
					TCurrentSprite.x = (1 + ((SPRITE_X_SIZE +1) * (CurrentChar - 111)));
				}
			}
			else { // Error
				#ifdef DEBUG_OUTPUT
				std::cout << "ERROR PRINTING TEXT: " << CurrentChar << std::endl;
				#endif
				return;
			}

			// Render the text
			World->DrawPartialSprite(CurrentTextPosition, Tileset, TCurrentSprite, olc::vi2d{ SPRITE_X_SIZE, SPRITE_Y_SIZE });

			// Move the current char position
			CurrentTextPosition.x += SPRITE_X_SIZE;
		}
	}
};

