#include <FL/Fl.H> // core FLTK header (basic tools and declerations)
#include <FL/Fl_Window.H> // the FLTK window class
#include <FL/Fl_Menu_Bar.H> // header for the menu bar
#include <FL/Fl_Text_editor.H> // for visible text editing widget
#include <FL/Fl_Text_Buffer.H> // class for text buffer
#include <FL/fl_ask.H> // a simple popup message box

void hello_cb(Fl_Widget*, void*) { // callback function for testing purposes
	fl_message("Daniel Mode");
}

int main() {
	Fl_Window* window = new Fl_Window(800, 600, "TimText"); // main app window
	Fl_Menu_Bar* menu = new Fl_Menu_Bar(0, 0, 800, 25); // bar at top of GUI
		menu->add("&File/&New", 0, hello_cb); // parent menu / child item format, 0 = keyboard sc, whenclikced = runs callback above
		menu->add("&File/&Open", 0, hello_cb);
		menu->add("&File/&Save", 0, hello_cb);
		menu->add("&Edit/&Copy", 0, hello_cb);
		menu->add("&Edit/&Paste", 0, hello_cb);
		menu->add("&Help/&About", 0, hello_cb);
		menu->add("&Tim/&Tim", 0, hello_cb);
	Fl_Text_Buffer* textbuf = new Fl_Text_Buffer(); // where text lives; the document in memory
	Fl_Text_Editor* editor = new Fl_Text_Editor(0, 25, 800, 575); // typing area, displays/edits the buffer
	editor->buffer(textbuf); // connects editor widet to text buffer

	window->end(); // nothing else to add to the window
	window->show(); // tells FLTK to make the window visible

	return Fl::run(); // keeps the program alive
}