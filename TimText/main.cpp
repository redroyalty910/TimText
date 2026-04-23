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

struct EditorData { // core callbacks grouped together
	Fl_Text_Buffer* textbuf; // because some callbacks need more than one object
	Fl_Text_Editor* editor;
	Fl_Window* window;
};

std::string current_file = ""; // empty string = no file yet / non-empty = already saved a file
bool is_modified = false; // false? nothing changed. true? user edited text

void update_title(Fl_Window* window) {
	std::string title = "TimText --> "; // name of app "TimText"

	if (current_file.empty()) { // check if file has a name
		title += "Untitled"; // if not, labeled as "untitled"
	}
	else {
		title += current_file; // if not empty, labels based on current file name
	}
	if (is_modified) {  // if unsaved changes exist
		title += " *";
	}
	window->label(title.c_str()); // apply changes to the window
}

void modify_cb(int, int, int, int, const char*, void* data) { // when text buffer changes this runs and marks doc as modified
	is_modified = true; // modify changes is_modified
	Fl_Window* window = (Fl_Window*)data;
	update_title(window); // modify updates the title
}

void new_cb(Fl_Widget*, void* data) { // callback for file -> new
	EditorData* app = (EditorData*)data;
	app->textbuf->text("");
	current_file = ""; // forgets current file
	is_modified = false; // resets to false
	update_title(app->window); 
}

void open_cb(Fl_Widget*, void* data) { // callback for file -> open
	EditorData* app = (EditorData*)data;

	if (is_modified) {
		int choice = fl_choice(
			"You have some unsaved changes there skippy,\nare you SURE about this?",
			"Naw",
			"Yaw",
			nullptr
		);
		if (choice == 0) return; // cancel option
	}

	const char* filename = fl_file_chooser("Open File", "*txt", ""); // opens file picker

	if (!filename) { // if the user cancels
		return;
	}

	std::ifstream file(filename); // creates a stream for reading the file

	if (!file) { // error check
		fl_message("Dude I can't open that.");
		return;
	}
	std::stringstream buffer; // creates an empty stream called buffer
	buffer << file.rdbuf(); // give raw content of file stream

	app->textbuf->text(buffer.str().c_str());

	current_file = filename;
	is_modified = false;
	update_title(app->window);
	fl_message("Your file has been opened.");
}

void save_cb(Fl_Widget*, void* data) { // callback for file -> save
	EditorData* app = (EditorData*)data;
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
	file << app->textbuf->text(); // writes text from buffer to file
	file.close();
	is_modified = false;
	update_title(app->window);
	fl_message("Your file has been 100% saved successfully!");
}

void save_as_cb(Fl_Widget*, void* data) { // callback for file -> save as
	EditorData* app = (EditorData*)data;
		const char* filename = fl_file_chooser("Save File As", "*.txt", ""); // let's user pick a file name in a new window

		if (!filename) // string if file path, nullptr if cancelled
			return; // implies that the user cancelled
		current_file = filename;

	std::ofstream file(current_file); // creates file output stream to write file
	
	if (!file) {
		fl_message("Hey bud, it's tim... we couldn't save your file.");
		return;
	}
	file << app->textbuf->text(); // writes text from buffer to file
	file.close();
	is_modified = false; // reset modification to false
	fl_message("Your file has been 100% saved successfully!");

}

void copy_cb(Fl_Widget*, void* data) { // callback for edit -> copy
	EditorData* app = (EditorData*)data;
	Fl_Text_Editor::kf_copy(0, app->editor); // FLTK's built-in copy function
}

void paste_cb(Fl_Widget*, void* data) { // callback for edit -> paste
	EditorData* app = (EditorData*)data;
	Fl_Text_Editor::kf_paste(0, app->editor); // FLTK's built-in paste function
}

void cut_cb(Fl_Widget*, void* data) { // callback for edit -> cut
	EditorData* app = (EditorData*)data;
	Fl_Text_Editor::kf_paste(0, app->editor); // FLTK's built-in cut function
}

void delete_cb(Fl_Widget*, void* data) { // callback for edit -> delete
	EditorData* app = (EditorData*)data;
	Fl_Text_Editor::kf_delete(0, app->editor); // FLTK's built-in cut function
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
	window->show(); // tells FLTK to make the window visible

	return Fl::run(); // keeps the program alive
}