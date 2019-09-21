#pragma once
#include <string>
#include <functional>
class Affordance
{
public:

	enum AffordanceTypes
	{
		REST = 1 << 0
	};

	Affordance(std::string name) : name(name) { affordanceType = 0; };
	virtual ~Affordance() {};

	std::function<void()> Callback;

	int GetScore() { return score; }
	void SetScore(int s) { score = s; }
	std::string GetName() { return name; }
	int GetType() { return affordanceType; }
	void AddAffordanceType(int type) { affordanceType |= type; };

protected:
	std::string name;
	int score;
	int affordanceType;

};