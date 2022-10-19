#pragma once
#pragma once
#include"imgui.h"
#include"imgui_impl_glfw.h"
#include"imgui_impl_opengl3.h"

#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <vector>

#ifndef IMGUI_DEFINE_MATH_OPERATORS
#define IMGUI_DEFINE_MATH_OPERATORS
#endif
#include "imgui_internal.h"
#include <functional>
#include <climits>
#include <string>
#include <sstream>
#include <cwchar>
#include <cctype>
#include <algorithm>
#include <cmath>
#include <regex>
#include <map>
#include <algorithm>
#include <chrono>

#include <sys/stat.h>
#if defined (WIN32) || defined (_WIN32) || defined (__WIN32)
#define OSWIN
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#else
#include <dirent.h>
#endif // defined (WIN32) || defined (_WIN32)

class Component;
class TextInfo;
class TextDisplay;
class Window;
class Application;

class SmartObject;


class Component {

public:
	ImVec2 pos;

	Component(ImVec2 pos);

	virtual void added_update();

	virtual int render();

};


class TextInfo {
public:
	ImFont* font;
	ImColor* color;

	TextInfo(ImFont* font, ImColor* color);
};


class ColorData {
public:

	ImColor default_color;

	ImColor number_color;

	ImColor string_color;

	ImColor keyword_color;

	ImColor identifier_color;

	std::map<std::string, ImColor> lists;

	void addColor(std::string, ImColor);

};


class Object;
class SybolTable;



class SymbolTable {

public:

	std::vector<Object*>* objects;

	SymbolTable();


};

class Object {

public:
	std::string name;

	int type;

	SymbolTable* table;

	Object(std::string name, int type, SymbolTable* table = NULL);

};


class Lexer {

public:

	ColorData* data;

	SymbolTable* table;

	char currentChar;

	std::vector< std::pair<std::string, ImColor>> tokens;

	std::string last_thing;

	bool in_class = false;

	std::string str;

	int index = 0;

	void increment();

	Lexer(std::string str, ColorData* data);

	std::pair<std::string, ImColor> lexToken();

	void reset(std::string);

	//standard

	//positional

};




class TextDisplay : public Component {
public:
	std::string text = "";

	TextInfo* info;

	Window* parent;

	std::vector<int>* indexes;

	Lexer* lexer;

	int lines = 0;

	int cursor = 0;

	TextDisplay(std::string text, ImVec2 pos, TextInfo* info, Window* parent);

	void added_update();

	void calculateIndexes();

	std::string getLine(int line);

	std::string getText();

	int currentMouseLine();

	int currentLine();

	void drawCursor();

	int currentMouseCharacter();

	int render();

	void handleKeys();

	void drawText();


};

class SmartObject {

public:
	Component* parent;

	ImVec2 pos;

	bool focus;

	bool isMouseOver();

	bool isClicked();

};

class SmartText : public SmartObject {

public:
	std::string str;
};

class Window {
public:

	std::string title;

	ImVec2 pos;

	ImVec2 size;

	bool focused;

	ColorData* colorData;

	std::vector<Component*> components;

	Application* parent;

	ImDrawList* drawList;

	Window(std::string title, ImVec2 pos, ImVec2 size);

	int addComponent(Component* component);

	void render();

};


class Application {

public:

	GLFWwindow* window;

	std::vector<Window*> windowList;

	ColorData* colorData;

	std::string fileReader(std::string fileName);

	Application(std::string label, ImVec2 size, ColorData* colorData);

	int addWindow(Window* window);

	int render();
};


