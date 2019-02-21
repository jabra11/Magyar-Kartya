#pragma once
#pragma once

#include "SFML/Network.hpp"
#include "User.h"

class Client : public User
{
private:

public:
	Client(const sf::IpAddress &addressOfHost);

};