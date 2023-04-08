export module Game;

import <iostream>;
import <vector>;
import <algorithm>;
import <random>;

import Player;
import GameDefinitions;

using namespace GameAndPlayerDefinitions;

//Interface class for the game
export class IGame
{
public:
	IGame() noexcept = default;
	virtual ~IGame() noexcept;
public:
	//Virtual methode to add player to the game. SHOULD BE OVERRIDED!
	virtual int AddPlayer(int Id) = 0;
	//Virtual methode to kill player during the game. SHOULD BE OVERRIDED!
	virtual int KillPlayer(int Id) = 0;
	//Virtual methode to find the player by its id (returns pointer). SHOULD BE OVERRIDED!
	virtual Player* FindPlayerById(int Id) = 0;
	//Virtual methode to find the player by its id (returns iterator). SHOULD BE OVERRIDED!
	virtual std::vector<Player*>::iterator FindPlayerById_Iterator(int Id) = 0;
	//Virtual methode to get all players as an array (vector). SHOULD BE OVERRIDED!
	virtual std::vector<Player*>& GetPlayersArray() = 0;
	//Virtual methode to start the game. SHOULD BE OVERRIDED!
	virtual int StartGame() = 0;
protected:
	std::vector<Player*> Players_;
};


export class Game : public IGame
{
public:
	explicit Game(int LeaderId);
public:
	/// <summary>
	/// Adding a player to the game
	/// </summary>
	/// <param name="Id:">The id of the player</param>
	/// <returns>
	/// FAILED_TO_ADD_A_PLAYER in the case of the adding is failed.
	/// PLAYER_ALREADY_EXISTS in the case of the player is already exists / added.
	/// PLAYER_ADDED in the case of the player has been added to the game
	/// </returns>
	virtual int AddPlayer(int Id) override;
	/// <summary>
	/// Find the player by its id
	/// </summary>
	/// <param name="Id:">The id of the player</param>
	/// <returns>
	/// The pointer to the player if found and nullptr otherwise
	/// </returns>
	virtual Player* FindPlayerById(int Id) override;
	/// <summary>
	/// Killing the player
	/// </summary>
	/// <param name="Id:">The id of the player</param>
	/// <returns>
	/// PLAYER_ID_NONE in the case of Id == PLAYER_ID_NONE. PLAYER_IS_KILLED if the player has been killed and PLAYER_IS_NOT_KILLED otherwise
	/// </returns>
	virtual int KillPlayer(int Id) override;
	/// <summary>
	/// Find the player by its id
	/// </summary>
	/// <param name="Id:">The id of the player</param>
	/// <returns>
	/// The iterator to the player in the Players_ if found and Players_.end() otherwise
	/// </returns>
	virtual std::vector<Player*>::iterator FindPlayerById_Iterator(int Id) override;
	/// <summary>
	/// Get all players
	/// </summary>
	/// <returns>
	/// The players array (vector)
	/// </returns>
	virtual std::vector<Player*>& GetPlayersArray() override;
	/// <summary>
	/// Get the leader in the current game
	/// </summary>
	/// <returns>
	/// The pointer to the game leader if found and nullptr otherwise
	/// </returns>
	virtual Player* GetLeaderPlayer();
	/// <summary>
	/// Starting the game
	/// </summary>
	/// <returns>
	/// NOT_ENOUGH_PLAYERS if the count of the players is 0. LEADER_IS_NOT_SET if there are any players but no one of them is leader. LEADER_ID_NONE
	/// in the case of the LeaderId_ is LEADER_ID_NONE. GAME_STARTED if the case if the game has been successfuly started
	/// </returns>
	virtual int StartGame() override;
private:
	/// <summary>
	/// Check does this id is unique or not
	/// </summary>
	/// <param name="Id:">The player id</param>
	/// <returns>
	/// True if the id is not found: it hasn't found in the players array (vector) and it is not PLAYER_ID_NONE. False otherwise
	/// </returns>
	bool IsUniqueId(int Id) const;
protected:
	//The id of the leader of the game
	int LeaderId_;
};


IGame::~IGame() noexcept
{
	for (auto player : Players_)
	{
		if (player)
		{
			delete player;
		}
	}
}

Game::Game(int LeaderId)
{
	LeaderId_ = LeaderId;
}

int Game::AddPlayer(int Id)
{
	if (Id == PLAYER_ID_NONE)
	{
		std::cerr << "The id is not set properly or it's 'NONE'\n";
		return FAILED_TO_ADD_A_PLAYER;
	}
	if (!IsUniqueId(Id))
	{
		std::cerr << "The player is already exists!\n";
		return PLAYER_ALREADY_EXISTS;
	}
	if (auto player = new Player(Id, CreateRandomPlayerName()))
	{
		Players_.push_back(player);
		return PLAYER_ADDED;
	}
	return FAILED_TO_ADD_A_PLAYER;
}

Player* Game::FindPlayerById(int Id)
{
	for (const auto player : std::as_const(Players_))
	{
		if (player->GetPlayerId() == LeaderId_)
		{
			return player;
		}
	}
	std::cerr << "No leader!\n";
	return nullptr;
}

int Game::KillPlayer(int Id)
{
	if (Id == PLAYER_ID_NONE)
	{
		std::cerr << "Id is 'NONE'\n";
		return PLAYER_ID_NONE;
	}
	auto playerIterator = FindPlayerById_Iterator(Id);
	if (playerIterator != Players_.end())
	{
		auto player = *playerIterator;
		Players_.erase(playerIterator);
		delete player;
		player = nullptr;
		return PLAYER_IS_KILLED;
	}
	return PLAYER_IS_NOT_KILLED;
}

std::vector<Player*>::iterator Game::FindPlayerById_Iterator(int Id)
{
	for (std::vector<Player*>::iterator it = Players_.begin(); it != Players_.end(); it++)
	{
		if ((*it)->GetPlayerId() == LeaderId_)
		{
			return it;
		}
	}
	return Players_.end();
}

std::vector<Player*>& Game::GetPlayersArray()
{
	return Players_;
}

bool Game::IsUniqueId(int Id) const
{
	for (const auto player : std::as_const(Players_))
	{
		if (player->GetPlayerId() == Id)
		{
			return false;
		}
	}
	return true;
}

Player* Game::GetLeaderPlayer()
{
	if (LeaderId_ == LEADER_ID_NONE)
	{
		std::cerr << "Id is 'NONE'\n";
		return nullptr;
	}
	return FindPlayerById(LeaderId_);
}

int Game::StartGame()
{
	if (Players_.size() == 0)
	{
		std::cerr << "Not enough players to start the game! Aborting....\n";
		return NOT_ENOUGH_PLAYERS;
	}
	if (LeaderId_ == LEADER_ID_NONE)
	{
		std::cerr << "Leader id is not set! Aborting...\n";
		return LEADER_ID_NONE;
	}
	auto Leader = GetLeaderPlayer();
	if (Leader == nullptr)
	{
		std::cerr << "Leader is 'nullptr'! Aborting...\n";
		return LEADER_IS_NOT_SET;
	}
	auto make_rd = [](int min, int max)
	{
		std::random_device rd;
		std::uniform_int_distribution<> ui(min, max);
		return ui(rd);
	};
	auto playersKilled = make_rd(0, Players_.size() - 1);
	auto playersLeft = Players_.size() - playersKilled;
	auto goldFarmed = make_rd(100, 1000000);
	std::cout << "\nA brave group of " << Players_.size() << " set out on a quest" <<
		" -- in search of the lost treasure of the Ancient Dwarves.\n" <<
		"The group was lead by that legendary rogue, " << Leader->GetPlayerName() << ".\n" <<
		"Along the way, a band of marauding ogres ambushed the party. " <<
		"All fought bravely under the command of " << Leader->GetPlayerName() <<
		", and the orges were defeated, but at a cost. " <<
		"Of the adventures, " << playersKilled << " were vanquished, " <<
		"leaving just " << playersLeft << " in the group\n" <<
		"\nThe party was about to give up all hope. But while laying the deceased to rest, " <<
		"they stumbled upon the buried fortune. So the adventures split " << goldFarmed << " gold pieces.\n" <<
		Leader->GetPlayerName() << " held on to the extra " << (goldFarmed % playersLeft) << " pieces to keep things fair of course.\n";
	return GAME_STARTED;
}
