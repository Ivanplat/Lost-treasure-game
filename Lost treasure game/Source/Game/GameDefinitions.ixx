export module GameDefinitions;

//Global defintions of the game and the players
export namespace GameAndPlayerDefinitions
{
	//Predefined value for the case of a player has no id or player is invalid
	export constexpr int PLAYER_ID_NONE = -4;
	//Predefined value for the case of a leader has no id or player is invalid
	export constexpr int LEADER_ID_NONE = -3;
	//Predefined value for the case of failed to add a player into the game
	export constexpr int FAILED_TO_ADD_A_PLAYER = -2;
	//Predefined value for the case of failed to kill a player during the game
	export constexpr int PLAYER_IS_NOT_KILLED = -1;
	//Predefined value for the case of player has been successfuly added
	export constexpr int PLAYER_ADDED = 0;
	//Predefined value for the case of player has been successfuly killed
	export constexpr int PLAYER_IS_KILLED = 1;
	//Predefined value for the case of the player is already exist
	export constexpr int PLAYER_ALREADY_EXISTS = 2;
	//Predefined value for the case of there are not enough players to start the game
	export constexpr int NOT_ENOUGH_PLAYERS = 3;
	//Predefined value for the case of game has been successfuly started
	export constexpr int GAME_STARTED = 4;
	//Predefined value for the case of the leader is not set
	export constexpr int LEADER_IS_NOT_SET = 5;
}