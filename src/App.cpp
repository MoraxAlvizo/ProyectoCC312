#include "../include/App.h"

App::App(): box(false, 3), buttonQuit("Quit")
{

    set_title("App");

    // Get automatically redrawn if any of their children changed allocation.
    set_reallocate_redraws(true);
    add(box);
    GL.set_size_request(800, 600);
    box.pack_start(GL);

    // App quit button.
    buttonQuit.signal_clicked().connect(sigc::mem_fun(*this, &App::on_button_quit_clicked));
    box.pack_start(buttonQuit, Gtk::PACK_SHRINK, 0);
    // Show window.
    show_all();
}

App::~App()
{}

void App::on_button_quit_clicked()
{
  Gtk::Main::quit();
}
