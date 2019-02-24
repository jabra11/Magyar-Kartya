#include "OnlinePlayer.h"



OnlinePlayer::OnlinePlayer(Logic *logic, Client *client, Host *host)
	:Player{logic}, m_client{client}, m_host{host}
{
}

