// callbacks.cpp is where the functions are defined

#include "callbacks.h"
#include "EditorData.h"

#include <FL/fl_ask.H>
#include <FL/Fl_File_Chooser.H>

#include <fstream>
#include <sstream>
#include <string>

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
	if (current_file.empty()) { // if there is no file, ask for one
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
