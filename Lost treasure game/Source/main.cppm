import Game;

#ifdef TESTS_ON
import GameTests;
import PlayerTests;
#endif

int main()
{
#ifdef TESTS_ON
	TestPlayerId();
	TestAddingPlayers();
	TestKillPlayers();
	TestGameStart();
#endif
#ifndef TESTS_ON
	Game g(0);
	g.AddPlayer(0);
	g.AddPlayer(1);
	g.AddPlayer(2);
	g.AddPlayer(3);
	g.AddPlayer(4);
	g.StartGame();
#endif
	return 0;
}