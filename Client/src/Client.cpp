#include "headers/Client.h"



Client::Client(int port)
	:OnlineUser{port}
{
	m_address_of_other_user = sf::IpAddress::None;
}

bool Client::connect_to_user()
{
	/*
	sf::Socket::Status status{ m_socket.connect(m_address_of_other_user, m_port) };
	while (status != sf::Socket::Done)
	{
		std::cerr << "not done!\n";
		status = m_socket.connect(m_address_of_other_user, m_port);
	}	

	std::cout << "Successfully connected to " << m_address_of_other_user << '\n';

	return true;
	*/
	
	// enable blocking to safely establish a connection
	m_socket.setBlocking(true);
	if (m_socket.connect(m_address_of_other_user, m_port, sf::Time(sf::seconds(3.0f))) == sf::Socket::Done)
	{
		std::cout << "Successfully connected to " << m_address_of_other_user << " on port " << m_socket.getRemotePort() << ".\n";
		return true;
	}

	else
		std::cerr << "Couldn't connect to " << m_address_of_other_user << ".\n";

	//disable blocking to allow smooth iterations
	m_socket.setBlocking(false);
	


	/*

	if (m_socket.connect(m_address_of_other_user, m_port) == sf::Socket::Done)
	{
		std::cout << "Successfully connected to " << m_address_of_other_user << '\n';
		return true;
	}

	else
	{
		std::cerr << "Couldn't connect to " << m_address_of_other_user << '\n';
		return false;
	}*/
}

void Client::receive_deck_information(Deck& deck_to_copy_in)
{
	int counter{ 0 };
	for (int i{ 0 }; true; ++i)
	{
		sf::Packet temp;
		//std::cout << "connected to " << m_socket.getRemoteAddress() << std::endl;
		m_socket.receive(temp);
		Default_packet card;
		temp >> card;

		(card.is_valid) ? std::cout << "is valid\n" : std::cout << "is not valid\n";
		
		if (card.is_valid)
		{
			std::cout << "received #" << i << std::endl;
			deck_to_copy_in[i].setRank(static_cast<Card::CardRank>(card.card_rank));
			deck_to_copy_in[i].setTyp(static_cast<Card::CardTyp>(card.card_typ));
			deck_to_copy_in[i].setTexture();
		}
		else if (!card.is_valid)
		{
			counter = i;
			break;
		}
	}

	std::cout << "Deck is syncronized. Received " << counter << " Cards\n";
}

void Client::set_IP_address(const std::string& address)
{
	sf::IpAddress temp { address };
	m_address_of_other_user = temp;
	std::cout << "IP-address of other user is now: " << address << '\n';
}
