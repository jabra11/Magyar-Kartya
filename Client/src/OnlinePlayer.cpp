#include "headers/OnlinePlayer.h"

OnlinePlayer::OnlinePlayer(Logic* logic, Client& client, Host& host)
	:Player{ logic },
	m_client{client}, m_host{host}
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
		m_host.modify_buffer().is_valid = true;
		m_host.modify_buffer().header = OnlineUser::Header::DEFAULT_HEADER;
		m_host.modify_buffer().uses_card = true;
		m_host.modify_buffer().card_rank = m_playerHand.back().getRank();
		m_host.modify_buffer().card_typ = m_playerHand.back().getTyp();
		std::cout << "validated host packet.\n";
	}

	else
	{
		m_client.modify_buffer().is_valid = true;
		m_client.modify_buffer().header = OnlineUser::Header::DEFAULT_HEADER;
		m_client.modify_buffer().uses_card = true;
		m_client.modify_buffer().card_rank = m_playerHand.back().getRank();
		m_client.modify_buffer().card_typ = m_playerHand.back().getTyp();
		std::cout << "validated client packet\n";
	}

	m_playerHand.pop_back();
}


void OnlinePlayer::drawCard(const Card& card, const int how_many)
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

	if (m_is_hosting)
	{
		m_host.modify_buffer().is_valid = true;
		m_host.modify_buffer().header = OnlineUser::Header::DEFAULT_HEADER;
		m_host.modify_buffer().uses_card = false;
		m_host.modify_buffer().amount_of_cards_drawn = how_many;
		std::cout << "validated packet\n";
	}
	else
	{
		m_client.modify_buffer().is_valid = true;
		m_client.modify_buffer().header = OnlineUser::Header::DEFAULT_HEADER;
		m_client.modify_buffer().uses_card = false;
		m_client.modify_buffer().amount_of_cards_drawn = how_many;
		std::cout << "validated packet\n";
	}
}

void OnlinePlayer::set_host_status(bool is_hosting)
{
	m_is_hosting = is_hosting;
}
