#include "MainWindow.h"


void MainWindow::MW_resize(wxCommandEvent & event)
{
	m_model.model_resize();
	m_view->MyPaint();

	event.Skip();
}


MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, "Kaleidoscope")
{
	
	SetSize(wxSize(m_w_width, m_w_height));
	Center();
	SetAutoLayout(true);

	m_view = new View(this, m_model);
	m_control = new Controler(this, *m_view,m_model);


	
	m_view->SetMinSize(wxSize(400, 600));
	m_bsizer = new wxBoxSizer(wxHORIZONTAL);
	m_control->SetBackgroundColour(wxColor(127, 127, 127));

	m_control->SetMinSize(wxSize(200, 200));
	SetSizer(m_bsizer);

	m_bsizer->Add(m_view, 3, wxEXPAND | wxALL, 0);
	m_bsizer->Add(m_control,1, wxEXPAND | wxALL,5);

	//Bind(wxEVT_SIZE, &MainWindow::MW_resize, this, ID::MW_RESIZE);
	m_bsizer->SetSizeHints(this); // zawsze jako ostatnia metoda
}

MainWindow::~MainWindow() = default;