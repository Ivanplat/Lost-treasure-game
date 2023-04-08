export module GameTests;

import <cassert>;

import Game;
import Player;
import GameDefinitions;

using namespace GameAndPlayerDefinitions;


export void TestAddingPlayers()
{
	Game* game = new Game(0);
	assert(game->AddPlayer(0) == PLAYER_ADDED);
	assert(game->AddPlayer(PLAYER_ID_NONE) == FAILED_TO_ADD_A_PLAYER);
	assert(game->AddPlayer(0) == PLAYER_ALREADY_EXISTS);
	assert(game->AddPlayer(1) == PLAYER_ADDED);
	delete game;
}

export void TestKillPlayers()
{
	Game* game = new Game(0);
	game->AddPlayer(0);
	game->AddPlayer(1);
	game->AddPlayer(2);
	game->AddPlayer(3);
	assert(game->KillPlayer(0) == PLAYER_IS_KILLED);
	assert(game->KillPlayer(453) == PLAYER_IS_NOT_KILLED);
	assert(game->KillPlayer(PLAYER_ID_NONE) == PLAYER_ID_NONE);
	delete game;
}

export void TestGameStart()
{
	Game* game = new Game(0);
	game->AddPlayer(0);
	game->AddPlayer(1);
	game->AddPlayer(2);
	game->AddPlayer(3);
	assert(game->StartGame() == GAME_STARTED);
	delete game;

	Game* game2 = new Game(LEADER_ID_NONE);
	game2->AddPlayer(0);
	assert(game2->StartGame() == LEADER_ID_NONE);
	delete game2;

	Game* game3 = new Game(1);
	game3->AddPlayer(0);
	assert(game3->StartGame() == LEADER_IS_NOT_SET);
	delete game3;

	Game* game4 = new Game(0);
	assert(game4->StartGame() == NOT_ENOUGH_PLAYERS);
	delete game4;
}