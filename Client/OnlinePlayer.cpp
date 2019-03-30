#include "OnlinePlayer.h"

OnlinePlayer::OnlinePlayer(Logic* logic, int port)
	:m_logic{ logic }, m_client{port}, m_host{port}
{
}

