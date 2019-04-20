#pragma once
#include "Client.h"
#include "Host.h"
#include "Logic.h"
#include "Player.h"

class OnlinePlayer : public Player
{

public: // functions

	OnlinePlayer(Logic *logic, int port);

	void dealCard(int card_to_deal, std::vector<Card>& card_stack) override;
	void drawCard(const Card& card, const int how_many = 1);

	// set whether the object should be the host or not
	void set_host_status(bool is_hosting);

	Card& operator[](int index);

	Client m_client;
	Host m_host;

private:
	bool m_is_hosting;
};