// ImGui - standalone example application for GLFW + OpenGL 3, using programmable pipeline
// If you are new to ImGui, see examples/README.txt and documentation at the top of imgui.cpp.
// (GLFW is a cross-platform general purpose library for handling windows, inputs, OpenGL/Vulkan graphics context creation, etc.)
// (GL3W is a helper library to access OpenGL functions since there is no standard header to access modern OpenGL functions easily. Alternatives are GLEW, Glad, etc.)

#include <stdio.h>

static void glfw_error_callback(int error, const char* description)
{
	fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}
#include "GL/glew.h"
#include <iostream>
#include "display.h"
#include "inputManager.h"
#include <Windows.h>
#include "kdtree.h"
#include <string>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include <irrKlang/irrKlang.h>
#include <chrono>
#include <random>
#define OBJ_INDEX 5
#define SNAKE_HEAD 0
#define SNAKE_DEFAULT_SPEED 5
float far1 = 1000.0f;
float near1 = 1.0f;
bool restart = true;
static int diff = 0;
static float sound_ = 0.5;
static float sound2_ = 0.5;
static bool mutesound2_global = false;
static bool mutesound_global = false;
static int score = 0;
bool loading = true;
bool blood = true;
//Display display(DISPLAY_WIDTH, DISPLAY_HEIGHT, "OpenGL");
//Scene scn(glm::vec3(0.0f, 0.0f, -15.0f), CAM_ANGLE, relation, near1, far1);
glm::vec3 YAxis = glm::vec3(0, 1, 0);
glm::vec3 TranslatePos = glm::vec3(5, 0, 0);

std::queue<std::pair<Node*, Node*>> queue1;
	Vertex vertices[] =
	{
		Vertex(glm::vec3(-1, -1, -1), glm::vec2(1, 0), glm::vec3(0, 0, -1),glm::vec3(0, 0, 1)),
		Vertex(glm::vec3(-1, 1, -1), glm::vec2(0, 0), glm::vec3(0, 0, -1),glm::vec3(0, 0, 1)),
		Vertex(glm::vec3(1, 1, -1), glm::vec2(0, 1), glm::vec3(0, 0, -1),glm::vec3(0, 0, 1)),
		Vertex(glm::vec3(1, -1, -1), glm::vec2(1, 1), glm::vec3(0, 0, -1),glm::vec3(0, 0, 1)),

		Vertex(glm::vec3(-1, -1, 1), glm::vec2(1, 0), glm::vec3(0, 0, 1),glm::vec3(0, 1, 1)),
		Vertex(glm::vec3(-1, 1, 1), glm::vec2(0, 0), glm::vec3(0, 0, 1),glm::vec3(0, 1, 1)),
		Vertex(glm::vec3(1, 1, 1), glm::vec2(0, 1), glm::vec3(0, 0, 1),glm::vec3(0, 1, 1)),
		Vertex(glm::vec3(1, -1, 1), glm::vec2(1, 1), glm::vec3(0, 0, 1),glm::vec3(0, 1, 1)),

		Vertex(glm::vec3(-1, -1, -1), glm::vec2(0, 1), glm::vec3(0, -1, 0),glm::vec3(0, 1, 0)),
		Vertex(glm::vec3(-1, -1, 1), glm::vec2(1, 1), glm::vec3(0, -1, 0),glm::vec3(0, 1, 0)),
		Vertex(glm::vec3(1, -1, 1), glm::vec2(1, 0), glm::vec3(0, -1, 0),glm::vec3(0, 1, 0)),
		Vertex(glm::vec3(1, -1, -1), glm::vec2(0, 0), glm::vec3(0, -1, 0),glm::vec3(0, 1, 0)),

		Vertex(glm::vec3(-1, 1, -1), glm::vec2(0, 1), glm::vec3(0, 1, 0),glm::vec3(1, 1, 0)),
		Vertex(glm::vec3(-1, 1, 1), glm::vec2(1, 1), glm::vec3(0, 1, 0),glm::vec3(1, 1, 0)),
		Vertex(glm::vec3(1, 1, 1), glm::vec2(1, 0), glm::vec3(0, 1, 0),glm::vec3(1, 1, 0)),
		Vertex(glm::vec3(1, 1, -1), glm::vec2(0, 0), glm::vec3(0, 1, 0),glm::vec3(1, 1, 0)),

		Vertex(glm::vec3(-1, -1, -1), glm::vec2(1, 1), glm::vec3(-1, 0, 0),glm::vec3(1, 0, 0)),
		Vertex(glm::vec3(-1, -1, 1), glm::vec2(1, 0), glm::vec3(-1, 0, 0),glm::vec3(1, 0, 0)),
		Vertex(glm::vec3(-1, 1, 1), glm::vec2(0, 0), glm::vec3(-1, 0, 0),glm::vec3(1, 0, 0)),
		Vertex(glm::vec3(-1, 1, -1), glm::vec2(0, 1), glm::vec3(-1, 0, 0),glm::vec3(1, 0, 0)),

		Vertex(glm::vec3(1, -1, -1), glm::vec2(1, 1), glm::vec3(1, 0, 0),glm::vec3(1, 0, 1)),
		Vertex(glm::vec3(1, -1, 1), glm::vec2(1, 0), glm::vec3(1, 0, 0),glm::vec3(1, 0, 1)),
		Vertex(glm::vec3(1, 1, 1), glm::vec2(0, 0), glm::vec3(1, 0, 0),glm::vec3(1, 0, 1)),
		Vertex(glm::vec3(1, 1, -1), glm::vec2(0, 1), glm::vec3(1, 0, 0),glm::vec3(1, 0, 1))
	};


	unsigned int indices[] = { 0, 1, 2,
		0, 2, 3,

		6, 5, 4,
		7, 6, 4,

		10, 9, 8,
		11, 10, 8,

		12, 13, 14,
		12, 14, 15,

		16, 17, 18,
		16, 18, 19,

		22, 21, 20,
		23, 22, 20
	};

void init()
{
	glfwSetKeyCallback(display.m_window, key_callback);
	glfwSetWindowSizeCallback(display.m_window, window_size_callback);
}

void draw_loading()
{

	ImGuiWindowFlags window_flags = 0;
	window_flags |= ImGuiWindowFlags_NoTitleBar;
	window_flags |= ImGuiWindowFlags_NoMove;
	window_flags |= ImGuiWindowFlags_NoCollapse;
	window_flags |= ImGuiWindowFlags_NoResize;
	window_flags |= ImGuiWindowFlags_AlwaysAutoResize;


	int i = 0;
	while (loading==true&& !glfwWindowShouldClose(display.m_window))
	{
		glfwPollEvents();
		{		
			char arr[32] = { 0 };
			//sscanf_s(arr,"")
			sprintf_s(arr, "loading %7.2lf%%", 100*i/600.0f);
			// Start the Dear ImGui frame
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();
			ImGuiStyle& style = ImGui::GetStyle();
			style.Alpha = 0.65;

			ImVec4 colora = ImVec4(1, 0, 0, 1);
			ImVec4 colorb = ImVec4(0, 1,0, 1);
			ImVec4 colorc = ImVec4(0, 0, 1,1);
			ImVec4 colorx;
			// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
			//	if (show_demo_window)
			//			ImGui::ShowDemoWindow(&show_demo_window);
			static bool start = false;
			static float f = 0.0f;
			ImGui::SetNextWindowPos(ImVec2(300, 200));
			ImGui::SetNextWindowSize(ImVec2(300, 700), ImGuiCond_FirstUseEver);
			float p = i / 600.0f;
			if (p < 0.5)
			{
				float red = colorb.x*p*2.0f + colora.x*(0.5 - p)*2.0f;
				float green = colorb.y*p*2.0f + colora.y*(0.5 - p)*2.0f;
				float blue = colorb.z*p*2.0f + colora.z*(0.5 - p)*2.0f;
				float alpha = colorb.w*p*2.0f + colora.w*(0.5 - p)*2.0f;
				colorx = ImVec4(red, green, blue, alpha);
			}
			else
			{
				float red = colorc.x*(p-0.5)*2.0f + colorb.x*(1 - p)*2.0f;
				float green = colorc.y*(p - 0.5)*2.0f + colorb.y*(1 - p)*2.0f;
				float blue = colorc.z*(p - 0.5)*2.0f + colorb.z*(1 - p)*2.0f;
				float alpha = colorc.w*(p - 0.5)*2.0f + colorb.w*(1 - p)*2.0f;
				colorx = ImVec4(red, green, blue, alpha);
			}
			
			ImGui::Begin("main screen", NULL,window_flags);                         // Create a window called "Hello, world!" and append into it.
			ImGui::PushStyleColor(ImGuiCol_FrameBg, colorx);//empty
			ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(0, 0.6, 0.6, 1));//filled
			ImGui::ProgressBar(i/600.0f,ImVec2(0,0),arr);																										  //ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
			ImGui::PopStyleColor(2);
				ImGui::NewLine();
			ImGui::SameLine(0, 100);

			//ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::End();
		}
		{
				scn.setPicked(0);

		}
		display.Clear(0.40f, 0.05f, 1.0f, 1.0f);
		if (display.IsFullscreen())
		{
			GLint viewport[4];
			glfwGetFramebufferSize(display.m_window, &viewport[2], &viewport[3]);
			window_size_callback(display.m_window, viewport[2], viewport[3]);
		}

		scn.draw_loading();
		ImGui::Render();
		int display_w, display_h;
		glfwMakeContextCurrent(display.m_window);
		glfwGetFramebufferSize(display.m_window, &display_w, &display_h);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwMakeContextCurrent(display.m_window);
		display.SwapBuffers();
		if (i == 100)
		{
			scn.init(vertices, indices, sizeof(vertices) / sizeof(vertices[0]), sizeof(indices) / sizeof(indices[0]));
			i++;
			scn.loading_screen->myRotate(-90.0f, glm::vec3(0, 0, 1), -1);
			scn.loading_screen->myTranslate(glm::vec3(0,0,0.215), 0);
			scn.loading_screen->myTranslate(glm::vec3(0, 0.15, 0), 0);

			scn.loading_screen->myScale(glm::vec3(0.8,0.8,0.8));
		}
		else if (i == 200)
		{
			scn.medium();
			i++;
		}
		else if (i == 300)
		{
			scn.hard();
			i++;
		}
		else if(i==400)
		{
			scn.hide_medium();
			i++;
		}
		else if(i==500)
		{
			scn.hide_hard();
			i++;
		}
		else if(i==600) 
		{
			unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
			std::mt19937 generator(seed);  // mt19937 is a standard mersenne_twister_engine
			int id = generator() % 4 + 1;
			scn.menu(vertices, indices, sizeof(vertices) / sizeof(vertices[0]), sizeof(indices) / sizeof(indices[0]), id);
			i++;
			loading = false;
			i++;
		}
		else
		{
			i++;
		}
		
	}
}


int main(int argc, char** argv)
{

	float speed_snake=0.055;
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937 generator(seed);  // mt19937 is a standard mersenne_twister_engine

	

	scn.addShader("./res/shaders/basicShader");
	scn.addShader("./res/shaders/pickingShader");



	// Setup window
	glfwSetErrorCallback(glfw_error_callback);
	if (!glfwInit())
		return 1;

	// Decide GL+GLSL versions
#if __APPLE__
	// GL 3.2 + GLSL 150
	const char* glsl_version = "#version 150";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
	// GL 3.0 + GLSL 130
	const char* glsl_version = "#version 130";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif
	glfwMakeContextCurrent(display.m_window);
	glfwSwapInterval(1); // Enable vsync
	glewInit();

	// Setup Dear ImGui binding
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   // Enable Gamepad Controls

	ImGui_ImplGlfw_InitForOpenGL(display.m_window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);

	// Setup style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

	// Load Fonts
	// - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them. 
	// - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple. 
	// - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
	// - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
	// - Read 'misc/fonts/README.txt' for more instructions and details.
	// - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
	//io.Fonts->AddFontDefault();
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
	io.Fonts->AddFontFromFileTTF("res/fonts/Cousine-Regular.ttf", 30.0f);
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/ProggyTiny.ttf", 10.0f);
	//ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
	//IM_ASSERT(font != NULL);

	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	scn.set_shape(vertices, indices, sizeof(vertices) / sizeof(vertices[0]), sizeof(indices) / sizeof(indices[0]));
	draw_loading();


	bool menu = true;
	bool flag = true;
	ImGuiWindowFlags window_flags = 0;
	window_flags |= ImGuiWindowFlags_NoTitleBar;
	window_flags |= ImGuiWindowFlags_NoMove;
	window_flags |= ImGuiWindowFlags_NoCollapse;
	window_flags |= ImGuiWindowFlags_NoResize;
	window_flags |= ImGuiWindowFlags_AlwaysAutoResize;


	irrklang::ISoundEngine* engine = irrklang::createIrrKlangDevice();
	irrklang::ISoundEngine* engine2 = irrklang::createIrrKlangDevice();

	if (!engine)
	{
		printf("Could not startup engine\n");
		return 0; // error starting up the engine
	}

	if (!engine2)
	{
		printf("Could not startup engine\n");
		return 0; // error starting up the engine
	}
	engine->play2D("./res/sounds/breakout.mp3", true);



	while (menu&& !glfwWindowShouldClose(display.m_window))
	{

		glfwPollEvents();
		{

			// Start the Dear ImGui frame
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();
			ImGuiStyle& style = ImGui::GetStyle();
			style.Alpha = 0.85;
static bool start = false;
			static float f = 0.0f;
			ImGui::SetNextWindowPos(ImVec2(300, 200));
			ImGui::SetNextWindowSize(ImVec2(300, 700), ImGuiCond_FirstUseEver);

			ImGui::Begin("main screen", &flag, window_flags| ImGuiWindowFlags_MenuBar);                          // Create a window called "Hello, world!" and append into it.
																						  //ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
																			  //	ImGui::SameLine(0,320);
			if(ImGui::BeginMenuBar())
			{ 
				if (ImGui::BeginMenu("menu"))
				{
					float sz = ImGui::GetTextLineHeight();
					{
						const char* name = "exit";
						ImVec2 p = ImGui::GetCursorScreenPos();
						ImGui::GetWindowDrawList()->AddRectFilled(p, ImVec2(p.x + sz, p.y + sz), ImGui::ColorConvertFloat4ToU32(ImVec4(0.9, 0.2, 0, 1)));
						ImGui::Dummy(ImVec2(sz, sz));
						ImGui::SameLine();
						if (ImGui::MenuItem(name))
						{
							exit(1);
						}
					}
					ImGui::EndMenu();
				}
				ImGui::EndMenuBar();
			}
			
			const char* items[] = { "Easy", "Medium", "Hard"};
			static const char* current_item = "Easy";
			static ImGuiTextBuffer log;
			static int lines = 0;
			ImGui::Text("difficulty:");
			ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 1);
			if (ImGui::BeginCombo("##combo", current_item)) // The second parameter is the label previewed before opening the combo.
			{
				ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
				for (int n = 0; n < IM_ARRAYSIZE(items); n++)
				{
					bool is_selected = (current_item == items[n]); // You can store your selection however you want, outside or inside your objects
					if (ImGui::Selectable(items[n], is_selected))
					{
						current_item = items[n];
						diff = n;
					}
				}
				ImGui::EndCombo();
			}
			
			ImGui::PopStyleVar();
			ImGui::Text("Background Volume:");
			if (ImGui::Checkbox("mute## background_sound", &mutesound_global))
			{
				engine->setAllSoundsPaused(mutesound_global);
			}
			
			ImGui::SliderFloat("##background sound", &sound_, 0.0f, 1.0f);
			ImGui::Text("Game Volume:");
			if (ImGui::Checkbox("mute## game sounds", &mutesound2_global))
			{
				engine2->stopAllSounds();
			}
			
			ImGui::SliderFloat("##Game sound", &sound2_, 0.0f, 1.0f);
			ImGui::NewLine();
			ImGui::SameLine(0, 100);
			if (ImGui::Button("start", ImVec2(300, 145)))
				menu = false;
			ImGui::End();
		}
		engine->setSoundVolume(sound_);
		engine2->setSoundVolume(sound2_);
			{
				scn.setPicked(0);

					}
			display.Clear(1.0f, 1.0f, 1.0f, 1.0f);
			if (display.IsFullscreen())
			{
				GLint viewport[4];
				glfwGetFramebufferSize(display.m_window, &viewport[2], &viewport[3]);
				window_size_callback(display.m_window, viewport[2], viewport[3]);
			}

			scn.draw_menu(0);
			ImGui::Render();
			int display_w, display_h;
			glfwMakeContextCurrent(display.m_window);
			glfwGetFramebufferSize(display.m_window, &display_w, &display_h);
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
			glfwMakeContextCurrent(display.m_window);
			display.SwapBuffers();
		}

	init();

	if (diff >= 1)
	{
		scn.show_medium(true);
	}

	if (diff >= 2)
	{
		scn.show_hard(true);
	}

start:
	while (restart&&!glfwWindowShouldClose(display.m_window))
	{

		glfwPollEvents();
		if (scn.gameover == false)
		{
		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

			{
			static float f = 0.0f;
			static int counter = 0;
				ImGui::Begin("Game Gui",NULL, window_flags&(!ImGuiWindowFlags_NoCollapse));                          // Create a window called "Hello, world!" and append into it.
	ImGui::Text("Background Volume:");
			ImGui::SliderFloat("##background_vol", &sound_, 0.0f, 1.0f);
			ImGui::Text("Game Volume:");

			ImGui::SliderFloat("##game_vol", &sound2_, 0.0f, 1.0f);
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1, 0, 1, 1));
			ImGui::Text("Score = %d", score);
			ImGui::PopStyleColor();
			ImGui::Text("game average %.3f ms/frame\n (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::End();
		}

		engine->setSoundVolume(sound_);
		engine2->setSoundVolume(sound2_);


		scn.collidesnake = false;
		for (int i = 0; i < 5; i++)
		{
			for (int j = 12; j <= 26; j += 2)
			{
				if (scn.find_collision(i, j)) {	//monkey
					if (mutesound2_global == false)
					{
						speed_snake += 0.0009;
						engine2->play2D("./res/sounds/coin.wav");
					}
					scn.shapes[j]->collide = false;
					scn.shapes[j - 1]->toDraw = false;
					score++;
				}
			}
		}

		for (int i = 0; i < 5; i++)
		{
			if (scn.find_collision(i, 10)) {
				printf("gameover\n");
				if (blood)
				{
					scn.bonus = 1;
				}
				scn.gameover = true;
				if (mutesound2_global == false)
				{
					engine2->play2D("./res/sounds/smash.mp3");
				}
			}

		}
		if (scn.collidesnake == false) {

			for (int i = 0; i < 5; i++)
			{
				if (diff >= 1) {
					
					if (scn.find_collision(i, 28) || scn.find_collision(i, 30) || scn.find_collision(i, 32) || scn.find_collision(i, 34))
					{
						if (blood)
						{
							scn.bonus = 1;
						}
						scn.gameover = true;
						if (mutesound2_global == false)
						{
							engine2->play2D("./res/sounds/smash.mp3");
						}
						printf("game over!!!!!!\n");
					}
				}
			}
		}
		if (diff >= 2) {
			if (scn.collidesnake == false)
			{
				for (int i = 0; i < 5; i++)
				{
						if (scn.find_collision(i, 36) || scn.find_collision(i, 38) || scn.find_collision(i, 40) )
						{
								if (blood)
				{
					scn.bonus = 1;
				}
							scn.gameover = true;
							int id=(generator() % 4) + 1;
							if (mutesound2_global == false)
							{
								std::string s;
								s.append("./res/sounds/cat");
								s.append(std::to_string(id));
								s.append(".mp3");
								engine2->play2D(s.c_str());
							}
							printf("game over!!!!!!\n");
					}
				}
			}
		}
		for (int i = 0; i < 5; i++) {
			if (scn.find_collision(i, 42))
			{
				printf("WINNER!\n");
				if (mutesound2_global == false)
				{
					engine2->play2D("./res/sounds/yay.mp3");
				}
				scn.gameover = true;
			}
		}
		{
			scn.setPicked(0);

			scn.makeChange();
		}
		display.Clear(1.0f, 1.0f, 1.0f, 1.0f);
		if (display.IsFullscreen())
		{
			GLint viewport[4];
			glfwGetFramebufferSize(display.m_window, &viewport[2], &viewport[3]);
			window_size_callback(display.m_window, viewport[2], viewport[3]);
		}


			scn.shapes[0]->myTranslate(glm::vec3(0, 0, speed_snake), 1);
			scn.shapes[5]->translateInSystem(*scn.shapes[5], glm::vec3(0, 0, speed_snake + 0.005), 0, 0);
			scn.shapes[6]->translateInSystem(*scn.shapes[6], glm::vec3(0, 0, speed_snake + 0.005), 1, 0);
			scn.shapes[7]->myTranslate(glm::vec3(0, 0, speed_snake + 0.005), 1);
			scn.shapes[8]->translateInSystem(*scn.shapes[8], glm::vec3(0, 0, speed_snake + 0.005), 1, 0);
			scn.shapes[9]->translateInSystem(*scn.shapes[9], glm::vec3(0, 0, speed_snake + 0.005), 1, 0);
				scn.cameras[0]->MoveUp(0.055);
			scn.cameras[1]->Pitch(50);
			scn.cameras[1]->MoveUp(speed_snake);
			glm::vec3 tmp1 = scn.shapes[3]->getPointInSystem(glm::mat4(), scn.getTipPosition(3));
			glm::vec3 tmp2 = scn.shapes[4]->getPointInSystem(glm::mat4(), scn.getTipPosition(4));
			glm::vec3 tmp3 = scn.shapes[5]->getPointInSystem(glm::mat4(), scn.getTipPosition(5));
			float angle = glm::dot(glm::normalize(tmp2 - tmp1), glm::normalize(tmp3 - tmp2));
			angle = glm::acos(glm::clamp(angle, 1.0f, -1.0f));
			scn.shapes[11]->myRotate(4, glm::vec3(0, 0, 1), 1);
			scn.shapes[12]->myRotate(4, glm::vec3(0, 0, 1), 1);
			scn.shapes[13]->myRotate(4, glm::vec3(0, 0, 1), 1);
			scn.shapes[14]->myRotate(4, glm::vec3(0, 0, 1), 1);
			scn.shapes[15]->myRotate(4, glm::vec3(0, 0, 1), 1);
			scn.shapes[16]->myRotate(4, glm::vec3(0, 0, 1), 1);
			scn.shapes[17]->myRotate(4, glm::vec3(0, 0, 1), 1);
			scn.shapes[18]->myRotate(4, glm::vec3(0, 0, 1), 1);
			scn.shapes[19]->myRotate(4, glm::vec3(0, 0, 1), 1);


			if (diff >= 2)
			{
				for (int i = 35; i < 41; i++)
				{
					if (scn.shapes[i]->lock)
					{
						scn.shapes[i]->myRotate(180, glm::vec3(0, 0, 1), 1);
						
					}

					else
					{				
							glm::vec4 trans;
						scn.shapes.at(i)->getTraslate(trans);
						if (trans.x > scn.shapes[i]->maxx)
						{
							scn.shapes[i]->speed.x *= -1;
	

						}
						if (trans.x < scn.shapes[i]->minx)
						{
							scn.shapes[i]->speed.x *= -1;
						}
						scn.shapes[i]->translateInSystem(*scn.shapes[i], scn.shapes[i]->speed, 1, true);
					}
				}
			}
		
			scn.cameras[1]->Pitch(-50);
		
		
		scn.draw(0, scn.camera_index, true);
		ImGui::Render();
		int display_w, display_h;
		glfwMakeContextCurrent(display.m_window);
		glfwGetFramebufferSize(display.m_window, &display_w, &display_h);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwMakeContextCurrent(display.m_window);
		display.SwapBuffers();
	}
	else
	{ 

		display.Clear(1.0f, 1.0f, 1.0f, 1.0f);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGuiStyle& style = ImGui::GetStyle();
		style.Alpha = 0.95;
//		ImGui::PushStyleColor();
		ImGui::Begin("Game over");                          // Create a window called "Hello, world!" and append into it.

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 1, 0, 1));
		//ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0, 0.2, 1, 1));
		//ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1, 0, 0, 1));

		if (ImGui::Button("Restart"))
		{
			scn.show_easy(true);
			scn.show_medium(true);
			scn.show_hard(true);
			scn.showcave(true);
			score = 0;
			speed_snake = 0.055;
			if ((diff < 1))
			{
				scn.hide_medium();
			}
			if(diff<2)
			{
				scn.hide_hard();
			}
			scn.restcamera();
			restart = false;
			scn.bonus = 0;
		}
		ImGui::PopStyleColor();
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();


		scn.draw(0, scn.camera_index, true);
		ImGui::Render();
		int display_w, display_h;
		glfwMakeContextCurrent(display.m_window);
		glfwGetFramebufferSize(display.m_window, &display_w, &display_h);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwMakeContextCurrent(display.m_window);

		display.SwapBuffers();
	
	}

//		glfwSwapBuffers(display.m_window);

}

	if (restart == false)
	{
		engine2->stopAllSounds();
		restart = true;
		scn.gameover = false;
		goto start;
	}
ImGui_ImplOpenGL3_Shutdown();
ImGui_ImplGlfw_Shutdown();
ImGui::DestroyContext();

glfwDestroyWindow(display.m_window);
glfwTerminate();

engine->drop();
engine2->drop();
	return 0;
}





