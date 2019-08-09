#pragma once
#include "Client.hpp"
#include "Host.hpp"
#include "Logic.hpp"
#include "Player.hpp"

class OnlinePlayer : public Player
{

public: // functions

	OnlinePlayer(Logic *logic, Client& client, Host& host);

	void dealCard(int card_to_deal, std::vector<Card>& card_stack) override;
	void drawCard(const Card& card, const int how_many = 1);

	// set whether the object should be the host or not
	void set_host_status(bool is_hosting);

	Card& operator[](int index);

	Client& m_client;
	Host& m_host;

private:
	bool m_is_hosting;
};