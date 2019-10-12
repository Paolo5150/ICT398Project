#pragma once
#include <string>
#include <functional>

/**
* @class Affordance
* @brief Generic class for an affordance
*
*
* @author Paolo Ferri
* @version 01
* @date 29/09/2019
*
*
* @bug No known bugs.
*/
class Affordance
{
public:
	friend class AffordanceObject;
	enum class AffordanceTypes
	{
		NONE,
		REST,
		COLLECTABLE
	};

	/**
	* @brief		Creates object and initialize parameters.
	*/
	Affordance() { maxUsers = 1; currentUsers = 0; affordanceType = AffordanceTypes::NONE; };

	/**
	* @brief		Destroys the object.
	*/
	virtual ~Affordance() {};

	/**
	* @brief		Points to the function which will be called once a GameObject engages the affordance
	*/
	std::function<void()> Callback;

	/**
	* @brief		Returns the affordance score
	*/
	int GetScore() { return score; }

	/**
	* @brief		Set the affprdance score
	* @param s		The new score
	*/
	void SetScore(int s) { score = s; }

	/**
	* @brief Return the maximum number of users for the affordance
	*/
	int GetMaxUsers() { return maxUsers; }


	/**
	* @brief Returns the current number of users for the affordance
	*/
	int GetCurrentUsers() { return currentUsers; };

	/**
	* @brief Sets the current number of users for the affordance
	*/
	void SetCurrentUsers(int c) { currentUsers = c; };

	/**
	* @brief The type the affordance belongs to
	*/
	AffordanceTypes affordanceType;


	std::string& GetName() { return affordanceName; }
protected:
	int score;
	/**
	* @brief The maximum number of users for the affordance
	*/
	int maxUsers;

	/**
	* @brief The current number of users for the affordance
	*/
	int currentUsers;

	std::string affordanceName;

};