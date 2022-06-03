#include "Application.h"


bool Application::OnInit()
{
	wxImage::AddHandler(new wxJPEGHandler);
	wxImage::AddHandler(new wxPNGHandler);
	m_mainWindow = new MainWindow();
	m_mainWindow->Show();
	return true;
}



int Application::OnExit()
{
	return 0;
}



IMPLEMENT_APP(Application)

