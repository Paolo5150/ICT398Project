#pragma once
#include <string>
#include <functional>
class Affordance
{
public:
	enum class AffordanceTypes
	{
		NONE,
		REST
	};
	Affordance() { maxUsers = 1; currentUsers = 0; affordanceType = AffordanceTypes::NONE; };
	virtual ~Affordance() {};

	std::function<void()> Callback;
	int GetScore() { return score; }
	void SetScore(int s) { score = s; }
	int maxUsers;
	int currentUsers;
	AffordanceTypes affordanceType;
protected:
	int score;

};