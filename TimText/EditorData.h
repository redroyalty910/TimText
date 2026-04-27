// EditorData.h stores shared app data

#pragma once

#include <string>
#include <FL/Fl_Window.H>
#include <FL/Fl_Text_Editor.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_Box.H>

struct EditorData { // core callbacks grouped together
	Fl_Text_Buffer* textbuf; // because some callbacks need more than one object
	Fl_Text_Editor* editor;
	Fl_Window* window;
	Fl_Box* status_bar; // stores pointer to the status bar inside app state
};
