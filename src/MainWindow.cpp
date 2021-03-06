#include "MainWindow.h"


void MainWindow::MW_resize(wxEvent & event)
{
	m_model.model_resize();
	m_view->MyPaint();
	//m_collapseButton->SetSize(m_view->GetSize().GetWidth() - 20, 0, 20, 20);
	event.Skip();
}

void MainWindow::MW_hideControl(wxCommandEvent& event) {
	hideControl = !hideControl; // toggle bool
	if (hideControl) {
		m_control->Hide();
		m_collapseButton->SetLabel("<");
	} else {
		m_control->Show();
		m_collapseButton->SetLabel(">");
	}
		
	this->Layout();
	event.Skip();
}

MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, "Kaleidoscope - GFK Project 2022")
{
	
	SetSize(wxSize(m_w_width, m_w_height));
	Center();
	SetAutoLayout(true);

	m_view = new View(this, m_model);
	m_control = new Controler(this, *m_view,m_model);
	//m_collapseButton = new wxButton(m_view, ID::BUTTON_COLLAPSE, ">", wxPoint(m_view->GetSize().x - 20,0), wxSize(20, 20));

	m_view->SetMinSize(wxSize(600, 600));
	m_view->SetSize(wxSize(600, 600));
	m_control->SetMinSize(wxSize(100, 100));


	m_bsizer = new wxBoxSizer(wxHORIZONTAL);
	

	m_control->SetBackgroundColour(wxColor(180, 180, 180));
	m_bsizer->Add(m_view, 5, wxSHAPED, 0);
	m_bsizer->Add(m_control, wxSizerFlags(0).Expand().Left());

	//Bind(wxEVT_SIZE, &MainWindow::MW_resize, this); //Dynamic and laggy

	Bind(wxEVT_IDLE, &MainWindow::MW_resize, this); //!<Calls resize event after all user input is done. Is also called on window maximizing.
	//Bind(wxEVT_BUTTON, &MainWindow::MW_hideControl, this, ID::BUTTON_COLLAPSE); //Hide controls event
	SetSizer(m_bsizer);
	m_bsizer->SetSizeHints(this); // zawsze jako ostatnia metoda
}

MainWindow::~MainWindow() = default;