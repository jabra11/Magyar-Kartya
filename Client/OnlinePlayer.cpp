#include "OnlinePlayer.h"

OnlinePlayer::OnlinePlayer(Logic* logic, int port)
	:Player{ logic },
	m_client{ port }, m_host{ port }
{
	m_is_hosting = true;
}

Card& OnlinePlayer::operator[](int index)
{
	return m_playerHand[index];
}

void OnlinePlayer::dealCard(int card_to_deal, std::vector<Card>& card_stack)
{
	std::cout << "Du " << m_playerHand[card_to_deal] << " -> " << card_stack.back() << '\n';
	std::swap(m_playerHand[card_to_deal], m_playerHand.back());

	// Insert card_to_deal into the card_stack
	card_stack.push_back(m_playerHand.back());

	// Modify buffer variable

	if (m_is_hosting)
	{
		m_host.modify_buffer().uses_card = true;
		m_host.modify_buffer().card_rank = m_playerHand.back().getRank();
		m_host.modify_buffer().card_typ = m_playerHand.back().getTyp();
	}

	else
	{
		m_client.modify_buffer().uses_card = true;
		m_client.modify_buffer().card_rank = m_playerHand.back().getRank();
		m_client.modify_buffer().card_typ = m_playerHand.back().getTyp();
	}

	m_playerHand.pop_back();
}


void OnlinePlayer::drawCard(const Card& card)
{
	m_playerHand.push_back(card);
	std::cout << "Du ziehst " << card << "\n";

	std::array<std::string, 6> temp;

	for (unsigned int i{ 0 }; i < m_logic->m_myFeed.size(); ++i)
	{
		temp[i] = m_logic->m_myFeed[i];
	}

	m_logic->m_myFeed[0] = "Du: Karte gezogen";

	for (unsigned int i{ 0 }; i < m_logic->m_myFeed.size() - 1; ++i)
	{
		m_logic->m_myFeed[i + 1] = temp[i];
	}

	m_host.modify_buffer().uses_card = false;
}

void OnlinePlayer::set_host_status(bool is_hosting)
{
	m_is_hosting = is_hosting;
}
