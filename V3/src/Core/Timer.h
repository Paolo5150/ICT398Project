#pragma once
#include "..\Events\EventDispatcher.h"

class GUIText;

/**
* @class Timer
* @brief Times the engine loops by sending events
*
*
* @author Paolo Ferri
* @version 01
* @date 12/03/2019
*
*
* @bug No known bugs.
*/
class Timer
{
public:
	/**
	* @brief Initialize the timer variables
	*
	*/
	static void Initialize();

	/**
	* @brief Advances the timer and send events
	*
	* @pre The EventDispatcher is created
	* @post The events are sent by the timer
	*/
	static void Update();

	/**
	* @brief Get the delta time between frames in seconds
	*
	* @pre The Timer has been initialized
	* @post The delta time is return and left unchanged
	*/
	static float GetDeltaS();

	/**
	* @brief Get the total time since the engine started in seconds
	*
	* @pre The Timer has been initialized
	* @post The time is return and left unchanged
	*/
	static float GetTimeS();

	/**
	* @brief Print FPS to the console and on screen
	*
	* @pre The Timer has been initialized
	* @post The FPS are displayed on the console and on the screen
	*/
	static void SetDisplayFPS(bool dfps);

	/**
	* @brief Returned the total number of ticks since the engine started
	*
	* @pre The Timer has been initialized
	* @post The  total number of ticks are returned and left unchanged
	*/
	static long long& GetTickCount();

	static void ResetTickCount(){ tickCount = 0; }
	/**
	* @brief Helper method the builds a string with FPS information to be displayed
	*/
	static std::string GetFPSString();


private:
	/**
	* @brief Whether the FPS should be displayed
	*/
	static bool m_displayFPS;

	/**
	* @brief The timer multiplier
	*/
	static double m_timerMultiplier;

	/**
	* @brief The time between frames
	*/
	static double m_delta;

	/**
	* @brief The frame per seconds counter
	*/
	static int m_FPSCounter;

	/**
	* @brief The frame per seconds target
	*/
	static double m_FPS;

	/**
	* @brief The inverse FPS
	*/
	static double m_limitFPS;

	/**
	* @brief The current time
	*/
	static double m_now;

	/**
	* @brief The time of the previous frame
	*/
	static double m_prev;

	/**
	* @brief The tick counter
	*/
	static long long tickCount;

	/**
	* @brief The text to be displayed on the screen
	*/
	static GUIText* FPSText;





};