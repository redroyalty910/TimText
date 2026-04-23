#include <FL/Fl.H> // core FLTK header (basic tools and declerations)
#include <FL/Fl_Window.H> // the FLTK window class
#include <FL/Fl_Menu_Bar.H> // header for the menu bar
#include <FL/Fl_Text_editor.H> // for visible text editing widget
#include <FL/Fl_Text_Buffer.H> // class for text buffer
#include <FL/fl_ask.H> // a simple popup message box
#include <Fl/fl_File_Chooser.H> // opens a file picker window in explorer
#include <fstream> // file stream, lets C++ write to files

std::string current_file = ""; // empty string = no file yet / non-empty = already saved a file

void new_cb(Fl_Widget*, void* data) { // callback for file -> new
	Fl_Text_Buffer* textbuf = (Fl_Text_Buffer*)data;
	textbuf->text("");
}

void save_cb(Fl_Widget*, void* data) { // callback for file -> save
	Fl_Text_Buffer* textbuf = (Fl_Text_Buffer*)data;
	if(current_file.empty()) { // if there is no file, ask for one
		const char* filename = fl_file_chooser("Save File", "*.txt", ""); // let's user pick a file name in a new window

		if (filename == nullptr) // string if file path, nullptr if cancelled
		return; // implies that the user cancelled
		current_file = filename;
	}
	std::ofstream file(current_file); // creates file output stream to write file
	if (!file) {
		fl_message("Hey bud, it's tim... we couldn't save your file.");
		return;
	}
	file << textbuf->text(); // writes text from buffer to file
	file.close();
	fl_message("Your file has been 100% saved successfully!");
}

void save_as_cb(Fl_Widget*, void* data) { // callback for file -> save as
	Fl_Text_Buffer* textbuf = (Fl_Text_Buffer*)data;
		const char* filename = fl_file_chooser("Save File As", "*.txt", ""); // let's user pick a file name in a new window

		if (filename == nullptr) // string if file path, nullptr if cancelled
			return; // implies that the user cancelled
		current_file = filename;

	std::ofstream file(current_file); // creates file output stream to write file
	
	if (!file) {
		fl_message("Hey bud, it's tim... we couldn't save your file.");
		return;
	}
	file << textbuf->text(); // writes text from buffer to file
	file.close();
	fl_message("Your file has been 100% saved successfully!");
}
void copy_cb(Fl_Widget*, void* data) { // callback for edit -> copy
	Fl_Text_Editor* editor = (Fl_Text_Editor*)data;
	Fl_Text_Editor::kf_copy(0, editor); // FLTK's built-in copy function
}

void paste_cb(Fl_Widget*, void* data) { // callback for edit -> paste
	Fl_Text_Editor* editor = (Fl_Text_Editor*)data;
	Fl_Text_Editor::kf_paste(0, editor); // FLTK's built-in paste function
}

void cut_cb(Fl_Widget*, void* data) { // callback for edit -> cut
	Fl_Text_Editor* editor = (Fl_Text_Editor*)data;
	Fl_Text_Editor::kf_paste(0, editor); // FLTK's built-in cut function
}

void delete_cb(Fl_Widget*, void* data) { // callback for edit -> delete
	Fl_Text_Editor* editor = (Fl_Text_Editor*)data;
	Fl_Text_Editor::kf_delete(0, editor); // FLTK's built-in cut function
}

void about_cb(Fl_Widget*, void*) { // does exactly what you think
	fl_message("TimText!\nBUILT WITH C++ AND FLTK!");
}

void hello_cb(Fl_Widget*, void*) { // callback for testing purposes
	fl_message("Daniel Mode");
}

int main() {
	Fl_Window* window = new Fl_Window(800, 600, "TimText"); // main app window
	Fl_Menu_Bar* menu = new Fl_Menu_Bar(0, 0, 800, 25); // bar at top of GUI
	Fl_Text_Buffer* textbuf = new Fl_Text_Buffer(); // where text lives; the document in memory	
	Fl_Text_Editor* editor = new Fl_Text_Editor(0, 25, 800, 575); // typing area, displays/edits the buffer
	editor->buffer(textbuf); // connects editor widet to text buffer
		menu->add("&File/&New", FL_CTRL + 'n', new_cb, textbuf); // parent menu / child item format, 0 = keyboard sc, whenclikced = runs callback above
		menu->add("&File/&Open", 0, hello_cb);
		menu->add("&File/&Save", FL_CTRL + 's', save_cb, textbuf);
		menu->add("&File/Save &As", FL_CTRL + 'a', save_as_cb, textbuf);

		menu->add("&Edit/&Cut", FL_CTRL + 'x', cut_cb, editor);
		menu->add("&Edit/&Copy", 0, copy_cb, editor);
		menu->add("&Edit/&Paste", 0, paste_cb, editor);
		menu->add("&Edit/&Delete", 0, delete_cb, editor);

		menu->add("&Help/&About", 0, about_cb);
		menu->add("&Tim/&Tim", 0, hello_cb);
		menu->add("&Tim/&Tim", 0, hello_cb);

	window->end(); // nothing else to add to the window
	window->show(); // tells FLTK to make the window visible

	return Fl::run(); // keeps the program alive
}