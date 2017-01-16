#include <cstdlib>
#include <iostream>
using namespace std;

/* Use glew.h instead of gl.h to getall the GL prototypes declared */
#include <GL/glew.h>
/* using SDL2 for the base window and OpenGL context init */
#include <SDL.h>

//TODO add global variables here later

GLUint program;
GLint attribute_coord2d;

bool init_resources(void)
{
	//for GLSL program
	GLint compile_ok = GL_FALSE, link_ok = GL_FALSE;

	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
		const char *vs_source = 
		//"#version 100\n" //OpenGL ES2.0
		"#version 120\n"	//OpenGL 2.1
		"attribute vec2 coord2d;"
	
		"void main(void)"
		"{"
		"	gl_Position = vec4(coord2d, 0.0, 1.0);"
		"};";

	glShaderSource(vs, 1, &vs_source, NULL);
	glCompileShader(vs);
	glGetShaderiv(vs, GL_COMPILE_STATUS, &compile_ok);
		if(!compile_ok)
		{
			cerr << "Error in vertex shader" << endl;

			return false;
		}

	program = glCreateProgram();
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &link_ok);
		if(!link_ok)
		{
			cerr << "Error in glLinkProgram" << endl;

			return false;
		}

	const char* attribute_name = "coord2d";
	attribute_coord2d = glGetAttribLocation(program, attribute_name);
		if(attribute_coord2d == -1)
		{
			err << "Could not bind attribute " << attribute_name << endl;
				return false;
		}

		return true;

}

void render(SDL_Window* window)
{
	//fill in later
	//draw triangle

	//clear background as white
	glClearColor(1.0,1.0,1.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glUserProgram(program);

	glEnableVertexAttribArray(attribute_coord2d);
		GLfloat triangle_vertices[] = 
		{
			0.0, 0.8,
			-0.8, -0.8,
			0.8, -0.8,
		};

	glVertexAttribPointer(attribute_coord2d, 2, GL_FLOAT, GL_FALSE, 0, triangle_vertices);
			
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glDisableVertexAttribArray(attribute_coord2d0);

	SDL_GL_SwapWindow(window);
}

void free_resources()
{
	//destroy GLSL program
	//fill in later

	glDeleteProgram(program);
}

void mainLoop(SDL_Window* window)
{
	while (true)
	{
		SDL_Event ev;
		while(SDL_PollEvent(&ev))
		{
			if (ev.type == SDL_QUIT)
				return;
		}
		render(window);
	}
}

int main(int argc, char* argv[])
{
	//SDL-related initialising functions
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* window = SDL_CreateWindow("Drawing a Triangle"),
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		640,480,
		SDL_WINDOW_RESIZABLE | 
	SDL_WINDOW_OPENGL()
;		SDL_GL_CreateContext(window);

		// extension wrangler initialising
		GLenum glew_status = glewInit();
		if(glew_status != GlEW_OK)
		{
			cerr << "Error: glewInit: " << glewGetErrorString(glew_status) << endl;
				return EXIT_FAILURE;
		}

		// when all init functions run without errors, program can initialise the resources
		if(!init_resources())
			return EXIT_FAILURE;

		//we can display something if everying goes OK

		mainLoop(window);

		//if program exit in the usual way, free resources and exit with success

		free_resources();
		return EXIT_SUCCESS;
}

