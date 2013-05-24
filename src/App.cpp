#include "../include/App.h"

App::App():
    GL(&toolsMenu),
    box(false, 3),
    bOpen("Open"),
    bSave("Save"),
    toolsMenu(false, &bOpen, &bSave)
{
    set_title("App");

    // Get automatically redrawn if any of their children changed allocation.
    set_reallocate_redraws(true);
    add(box);
    GL.set_size_request(1000, 600);

    bOpen.signal_clicked().connect(sigc::mem_fun(*this, &App::onButtonOpen));
    bSave.signal_clicked().connect(sigc::mem_fun(*this, &App::onButtonSave));

    box.pack_start(toolsMenu);
    box.pack_start(GL);

    // Show window.
    show_all();
}

App::~App()
{

}

void App::onButtonOpen (){
    GL.openImage();
}

void App::onButtonSave (){
    GL.saveImage();

}
