// main.cpp only builds the GUI and starts the app

#include <FL/Fl.H> // core FLTK header (basic tools and declerations)
#include <FL/Fl_Window.H> // the FLTK window class
#include <FL/Fl_Menu_Bar.H> // header for the menu bar
#include <FL/Fl_Text_editor.H> // for visible text editing widget
#include <FL/Fl_Text_Buffer.H> // class for text buffer
#include <FL/fl_ask.H> // a simple popup message box
#include <Fl/fl_File_Chooser.H> // opens a file picker window in explorer
#include <fstream> // file stream, lets C++ write to files
#include <string> // for the use of strings
#include <sstream> // library for string streams

#include "EditorData.h"
#include "callbacks.h"

int main() {
	Fl_Window* window = new Fl_Window(800, 600, "TimText"); // main app window
	Fl_Menu_Bar* menu = new Fl_Menu_Bar(0, 0, 800, 25); // bar at top of GUI
	Fl_Text_Buffer* textbuf = new Fl_Text_Buffer(); // where text lives; the document in memory	
	textbuf->add_modify_callback(modify_cb, window);
	Fl_Text_Editor* editor = new Fl_Text_Editor(0, 25, 800, 575); // typing area, displays/edits the buffer
	editor->buffer(textbuf); // connects editor widet to text buffer
	EditorData* app = new EditorData{ textbuf, editor, window };
		menu->add("&File/&New", FL_CTRL + 'n', new_cb, app); // parent menu / child item format, 0 = keyboard sc, whenclikced = runs callback above
		menu->add("&File/&Open", FL_CTRL + 'o', open_cb, app);
		menu->add("&File/&Save", FL_CTRL + 's', save_cb, app);
		menu->add("&File/Save &As", FL_CTRL + 'a', save_as_cb, app);

		menu->add("&Edit/&Cut", FL_CTRL + 'x', cut_cb, app);
		menu->add("&Edit/&Copy", 0, copy_cb, app);
		menu->add("&Edit/&Paste", 0, paste_cb, app);
		menu->add("&Edit/&Delete", 0, delete_cb, app);

		menu->add("&Help/&About", 0, about_cb);
		menu->add("&Tim/&Tim", 0, hello_cb);
		menu->add("&Tim/&Tim", 0, hello_cb);

	window->end(); // nothing else to add to the window
	update_title(window); // when file state changes, update title
	window->callback([](Fl_Widget* w, void* data) {
		EditorData* app = (EditorData*)data;
		if (!confirm_save(app)) {
			return; // cancel close
		}
		w->hide(); // actually close
		}, app);
	window->show(); // tells FLTK to make the window visible

	return Fl::run(); // keeps the program alive
}