#pragma once
#include <string>
#include <functional>
class Affordance
{
public:


	Affordance(){ maxUsers = 1; currentUsers = 0; };
	virtual ~Affordance() {};

	std::function<void()> Callback;
	int maxUsers;
	int currentUsers;

protected:

	int score;

};