#pragma once
#include <string>
#include <functional>
class Affordance
{
public:
	Affordance(){ maxUsers = 1; currentUsers = 0; };
	virtual ~Affordance() {};

	std::function<void()> Callback;
	int GetScore() { return score; }
	void SetScore(int s) { score = s; }
	int maxUsers;
	int currentUsers;

protected:
	int score;

};