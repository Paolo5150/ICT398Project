#include "pch.h"
#include "Window.h"
#include "Logger.h"
#include "..\Events\EventDispatcher.h"
#include "..\Events\WindowEvents.h"


Window Window::instance;

Window& Window::Instance()
{

	return instance;
}

void Window::Initialize()
{

	//Set up environment
	//Glew init MUST be called after creating the context (the window)
	if (!glfwInit())
	{
		Logger::LogError("GLFW failed to initialize");
	}


	glfwWindowHint(GLFW_DOUBLEBUFFER, true);

	instance.window = std::unique_ptr<GLFWwindow, DestroyglfwWin>(glfwCreateWindow(800, 600, "", NULL, NULL));
	glfwMakeContextCurrent(instance.window.get());
	glfwSetWindowPos(instance.window.get(), 200, 20);
	
	glfwSetWindowCloseCallback(instance.window.get(), OnClose);
	glfwSetWindowSizeCallback(instance.window.get(), OnResize);
	glfwSwapInterval(0);

}

Window::Window()
{
}

Window::~Window()
{
	Logger::LogError("Window destroyed");

}



void Window::UpdateEvents()
{
	glfwPollEvents();
}

float Window::GetAspectRatio()
{
	int w, h;
	GetWindowSize(w, h);
	return (float)w / h;
}

void Window::SetWindowSize(int w, int h)
{
	glfwSetWindowSize(this->window.get(),w, h);

}
void Window::GetWindowSize(int& w, int& h)
{
	glfwGetWindowSize(this->window.get(), &w, &h);
}

void Window::SetWindowTitle(std::string title)
{
	glfwSetWindowTitle(this->window.get(), title.c_str());
}

void Window::Refresh()
{
	//Logger::LogInfo("Refresh");

	glfwSwapBuffers(window.get());

}

void Window::Destroy()
{
	glfwSetWindowShouldClose(window.get(), true);
	glfwDestroyWindow(window.get());
	window = NULL;
}

void Window::OnClose(GLFWwindow* win)
{
	glfwSetWindowShouldClose(win, false); //Prevent window from closing	
	EventDispatcher::Instance().DispatchEvent(new WindowCloseEvent());
}



void Window::OnResize(GLFWwindow* win, int w, int h)
{
	EventDispatcher::Instance().DispatchEvent(new WindowResizeEvent(w,h));
}