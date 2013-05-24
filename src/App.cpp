#include "../include/App.h"

App::App():
    GL(&toolsMenu),
    box(false, 3),
    toolsMenu(false, &bOpen, &bSave, &bNew)
{
    set_title("App");
    Gtk::Image *m_image=new Gtk::Image("icons/openFile.png");
    bOpen.set_image_position(Gtk::POS_LEFT);
    bOpen.set_image(*m_image);

    m_image=new Gtk::Image("icons/saveAs.png");
    bSave.set_image_position(Gtk::POS_LEFT);
    bSave.set_image(*m_image);

    m_image=new Gtk::Image("icons/new.png");
    bNew.set_image_position(Gtk::POS_LEFT);
    bNew.set_image(*m_image);

    // Get automatically redrawn if any of their children changed allocation.
    set_reallocate_redraws(true);
    add(box);
    GL.set_size_request(1000, 600);

    bOpen.signal_clicked().connect(sigc::mem_fun(*this, &App::onButtonOpen));
    bSave.signal_clicked().connect(sigc::mem_fun(*this, &App::onButtonSave));
    bNew.signal_clicked().connect(sigc::mem_fun(*this, &App::onButtonNew));

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

void App::onButtonNew (){
    GL.newImage();
}
