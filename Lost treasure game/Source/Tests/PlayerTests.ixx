export module PlayerTests;

import <cassert>;

import Player;
import GameDefinitions;

using namespace GameAndPlayerDefinitions;

export void TestPlayerId()
{
	Player p(0, CreateRandomPlayerName());
	Player p2(PLAYER_ID_NONE, CreateRandomPlayerName());
	assert(p.GetPlayerId() == 0);
	assert(p2.GetPlayerId() == PLAYER_ID_NONE);
}