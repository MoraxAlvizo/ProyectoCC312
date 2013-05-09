#include "../include/App.h"

App::App():
    GL(&toolsMenu),
    box(false, 3),
    toolsMenu(false)
{
    set_title("App");

    // Get automatically redrawn if any of their children changed allocation.
    set_reallocate_redraws(true);
    add(box);
    GL.set_size_request(1000, 600);
    box.pack_start(toolsMenu);
    box.pack_start(GL);

    // Show window.
    show_all();
}

App::~App()
{}
