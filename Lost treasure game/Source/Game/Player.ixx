export module Player;

import <iostream>;
import <string>;
import <vector>;
import <random>;

import GameDefinitions;

using namespace GameAndPlayerDefinitions;

//Function to create random name from the vector of pre-invented names
export std::string CreateRandomPlayerName()
{
	const std::vector<std::string> names =
	{
		"Adam",
		"Urih",
		"Oleg",
		"Alex",
		"Mari",
		"Ann",
		"George"
	};
	std::random_device rd;
	std::uniform_int_distribution<> ui(0, names.size() - 1);
	return names[ui(rd)];
}

//Interface class of a player
export class IPlayer
{
public:
	IPlayer() noexcept : m_Id(PLAYER_ID_NONE) {}
	virtual ~IPlayer() noexcept = default;
public:
	//Virtual methode to get id. SHOULD BE OVERRIDED!
	virtual int GetPlayerId() const = 0;
	//Virtual methode to get player name. SHOULD BE OVERRIDED!
	virtual std::string GetPlayerName() const = 0;
public:
	const bool operator==(const IPlayer& other) const;
protected:
	int m_Id;
	std::string PlayerName_;
};

export class Player : public IPlayer
{
public:
	explicit Player(int Id, std::string PlayerName) { m_Id = Id; PlayerName_ = PlayerName; }
public:
	//Returns m_Id of this player
	virtual int GetPlayerId() const override;
	//Returns PlayerName_ of this player
	virtual std::string GetPlayerName() const override;
};

int Player::GetPlayerId() const
{
	return m_Id;
}

std::string Player::GetPlayerName() const
{
	return PlayerName_;
}

const bool IPlayer::operator==(const IPlayer& other) const
{
	return m_Id == other.m_Id;
}
