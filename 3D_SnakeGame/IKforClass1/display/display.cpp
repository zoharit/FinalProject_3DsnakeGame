#define GLEW_STATIC
#include <GL/glew.h>
#include <iostream>
#include "display.h"

Display::Display(int width, int height, const std::string& title)
{
	/* Initialize the library */
    if (!glfwInit())
        error =  -1;

	m_window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	if(!m_window)
	{
		glfwTerminate();
		error = -1;
	}
	glfwMakeContextCurrent(m_window);
	//m_glContext = SDL_GL_CreateContext(m_window);
	glfwSwapInterval(1); // Enable vsync

	GLenum res = glewInit();

	 if(res != GLEW_OK)
   {
		std::cerr << "Glew failed to initialize!" << std::endl;
    }
	 std::cout << "init\n";
	isFullScreen = false;
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_SMOOTH);
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_FRONT_AND_BACK);
}

Display::~Display()
{
	//SDL_GL_DeleteContext(m_glContext);
	glfwDestroyWindow(m_window);
	glfwTerminate();
	//SDL_Quit();
}

void Display::Clear(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

bool Display::IsFullscreen( void )
{
	if((glfwGetWindowMonitor( m_window ) == nullptr) != isFullScreen)
	{
		isFullScreen = (glfwGetWindowMonitor( m_window ) == nullptr);
		return true;
	}
	else 
		return false;
} 

void Display::SwapBuffers()
{
	glfwSwapBuffers(m_window);
}