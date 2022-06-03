#pragma once

#include <wx/wx.h>
#include <wx/image.h>
#include "MainWindow.h"

class Application : public wxApp {
public:
    bool OnInit() override;

    int OnExit() override;

private:
    
    MainWindow * m_mainWindow = nullptr;

};

