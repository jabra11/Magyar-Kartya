#pragma once
#include "Player.h"

class OnlinePlayer : public Player
{
	Client *m_client;
	Host *m_host;

public:
	OnlinePlayer(Logic *logic, Client *client = nullptr, Host *host = nullptr);
};

