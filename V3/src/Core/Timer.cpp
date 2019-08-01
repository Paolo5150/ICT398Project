#include "pch.h"

#include "Timer.h"
#include "..\Events\TimerEvents.h"
#include "Logger.h"
#include "..\Events\EventDispatcher.h"
#include "..\Core\Input.h"
#include  <sstream>

bool Timer::m_displayFPS;
double Timer::m_timerMultiplier;
double Timer::m_delta;
int Timer::m_FPSCounter;
double Timer::m_FPS;
double Timer::m_limitFPS;
double Timer::m_now;
double Timer::m_prev;
long long Timer::tickCount;
GUIText* Timer::FPSText;

void Timer::Initialize()
{
	m_delta = 0;
	
	m_FPSCounter = 0;
	m_FPS = 60;
	m_limitFPS = 1.0 / m_FPS;
	m_now = glfwGetTime();
	m_prev = glfwGetTime();
	m_timerMultiplier = 1.0;
	m_displayFPS = 0;
	tickCount = 0;

}

std::string Timer::GetFPSString()
{
	std::stringstream ss;
	ss << "FPS: ";
	ss << m_FPSCounter;
	return ss.str();
}


float Timer::GetDeltaS()
{
	return m_delta * m_timerMultiplier;
}

void Timer::SetDisplayFPS(bool dfps)
{
	m_displayFPS = dfps;
}

float Timer::GetTimeS()
{
	return glfwGetTime()* m_timerMultiplier;
}

long long& Timer::GetTickCount()
{
	return tickCount;
}


void Timer::Update()
{
	static float accumulator = 1000;

	m_now = glfwGetTime();
	m_delta = (m_now - m_prev);
	m_prev = m_now;

	accumulator += m_delta;
	

/*	if (accumulator >= 0.1)
	{
		Logger::LogInfo("Major hang");

	
	}*/




	if (accumulator >= m_limitFPS)
	{
		if (Input::GetKeyPressed(GLFW_KEY_Q))
		{
			m_displayFPS = !m_displayFPS;

		}
		static float fixedNow = glfwGetTime();
		static float fixedPrev = glfwGetTime();

		fixedNow = glfwGetTime();
		m_delta = (fixedNow - fixedPrev);
		fixedPrev = fixedNow;

		accumulator = 0;

		EventDispatcher::Instance().DispatchEvent(new EngineUpdateEvent());
		EventDispatcher::Instance().DispatchEvent(new LogicUpdateEvent());
		EventDispatcher::Instance().DispatchEvent(new RenderEvent());
		EventDispatcher::Instance().DispatchEvent(new LateUpdateEvent());
		tickCount++;	
	}

	m_FPSCounter++;



	if (m_displayFPS)
	{
		static double st = 0;
		st += m_delta;
		if (st >= 1)
		{
			st = 0;
			Logger::LogInfo("FPS", m_FPSCounter);
			m_FPSCounter = 0;
		}
	}
}