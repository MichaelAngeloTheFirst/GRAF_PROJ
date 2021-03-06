#pragma once

#include <wx/wx.h>
#include <wx/image.h>
#include <wx/xrc/xmlres.h>
#include "MainWindow.h"
#include <wx/statline.h>

class Application : public wxApp {
public:
    bool OnInit() override;

    int OnExit() override;

private:
    
    MainWindow * m_mainWindow = nullptr;

};

