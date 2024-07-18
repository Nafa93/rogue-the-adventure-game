#include "GameManager.h"

using namespace std;

//void render_hud(Player player)
//{
//    printf("Level: %d Hits:%d(%d) Str:%d(%d) Gold:%d Armor:%d Exp:%d/%d", player.level, player.currentHitPoints, player.hitPoints, player.currentStrength, player.strength, player.gold, player.armor, player.currentExperience, player.experience);
//}
//
//void render_canvas()
//{
//}

int main()
{
	GameManager* gameManager = new GameManager();

	gameManager->StartGame();
}