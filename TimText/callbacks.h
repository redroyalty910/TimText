// callbacks.h only decalres the callback functions

#pragma once

#include <FL/Fl_Widget.H>
#include <FL/Fl_Window.H>

void update_title(Fl_Window* window);

void modify_cb(int, int, int, int, const char*, void*);

void new_cb(Fl_Widget*, void*);
void open_cb(Fl_Widget*, void*);
void save_cb(Fl_Widget*, void*);
void save_as_cb(Fl_Widget*, void*);

void cut_cb(Fl_Widget*, void*);
void copy_cb(Fl_Widget*, void*);
void paste_cb(Fl_Widget*, void*);
void delete_cb(Fl_Widget*, void*);

void about_cb(Fl_Widget*, void*);