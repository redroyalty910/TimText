// EditorData.h stores shared app data

#pragma once

#include <string>
#include <FL/Fl_Window.H>
#include <FL/Fl_Text_Editor.H>
#include <FL/Fl_Text_Buffer.H>

struct EditorData { // core callbacks grouped together
	Fl_Text_Buffer* textbuf; // because some callbacks need more than one object
	Fl_Text_Editor* editor;
	Fl_Window* window;
};

extern std::string current_file = ""; // empty string = no file yet / non-empty = already saved a file
extern bool is_modified = false; // false? nothing changed. true? user edited text