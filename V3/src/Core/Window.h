#pragma once
#include <GLFW\glfw3.h>
#include <string>


struct DestroyglfwWin {

	void operator()(GLFWwindow* ptr) {
			}

};

/**
* @class Window
* @brief Manages the main window of the application
*
*
* @author Paolo Ferri
* @version 01
* @date 18/03/2019
*
*
* @bug No known bugs.
*/
class Window
{
public:
	friend class Core; //Core will initialize the window
	friend class Input;
	friend class GUIManager;

	/**
	* @brief		Return the window singleton instance
	*
	* @pre			The window instance is created
	* @post			The window instance is returned
	*/
	static Window& Instance();

	/**
	* @brief		Refresh the window content
	*
	* @pre			The window instance exists
	* @post			The window content is updated
	*/
	void Refresh();

	/**
	* @brief		Close and destroy
	*
	* @pre			The window instance exists
	* @post			The window is destroyed and no longer visible
	*/
	void Destroy();

	/**
	* @brief		Return the window aspect ratio
	*
	* @pre			The window instance exists
	* @post			The window aspect ratio is returned and left unchanged
	*/
	float GetAspectRatio();

	/**
	* @brief		Update input events
	*
	* @pre			The window instance exists
	* @post			The input events are updated
	*/
	void UpdateEvents();

	/**
	* @brief		Set the window size
	*
	* @pre			The window instance exists
	* @post			The window is resized
	*/
	void SetWindowSize(int w, int h);

	/**
	* @brief		Get the window size
	*
	* @pre			The window instance exists
	* @post			The window width and height are returned
	*
	*@param w		The window width
	*@param h		The window height
	*/
	void GetWindowSize(int& w, int& h);

	/**
	* @brief		Set the window title
	*
	* @pre			The window instance exists
	* @post			The window title is updated
	*
	*@param title		The window title

	*/
	void SetWindowTitle(std::string title);

	/**
	* @brief		The GLFW window object
	*/
	std::unique_ptr<GLFWwindow, DestroyglfwWin> window;

private:
	/**
	* @brief		Callback invoked when the user tried to close the window
	*/
	static void OnClose(GLFWwindow* win);

	/**
	* @brief		Callback invoked when the user tried to resize the window
	*/
	static void OnResize(GLFWwindow* win, int w, int h);

	/**
	* @brief		Initialize the window object
	* @pre			The window instance exists
	* @post			The window title is initialized
	*/
	static void Initialize();


	/**
	* @brief		The window instance
	*/
	static Window instance;


	/**
	* @brief		Create the window instance
	* @pre The window instance does not exists
	* @post The window instance is created
	*/
	Window();

	/**
	* @brief		Destroy the window instance
	* @pre The window instance exists
	* @post The window instance is destroyed
	*/
	~Window();
};
