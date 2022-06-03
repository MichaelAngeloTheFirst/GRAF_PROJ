#include "Controler.h"


Controler::Controler(wxWindow* parent, View & view, Model & model) : wxPanel(parent), m_view(view), m_model(model)
{
	SetAutoLayout(true);
	m_bsizer = new wxBoxSizer(wxVERTICAL);
	
	
	m_loadButton = new wxButton(this, ID::BUTTON_LOAD, "LOAD");
	m_saveButton = new wxButton(this, ID::BUTTON_SAVE, "SAVE");

	m_bsizer->Add(m_loadButton, 0, wxTOP | wxBOTTOM | wxALIGN_CENTER, 5);
	m_bsizer->Add(m_saveButton, 0, wxTOP | wxBOTTOM | wxALIGN_CENTER, 5);

	Bind(wxEVT_BUTTON, &Controler::onLoadClick, this, ID::BUTTON_LOAD);
	Bind(wxEVT_BUTTON, &Controler::onSaveClick, this, ID::BUTTON_SAVE);
	

	SetSizer(m_bsizer); // zawsze ma być ostatnie
} 

void Controler::onLoadClick(wxCommandEvent& event)
{
	auto handle = wxFileDialog(this, _("Choose a file"), _(""), _(""), _("JPEG files (*.jpg)|*.jpg"), wxFD_OPEN);
	if (handle.ShowModal() == wxID_OK)
	{
		m_model.model_load(handle.GetPath());
		m_view.MyPaint();
	}


	event.Skip(); //zawsze na koncu w handlerach
}

void Controler::onSaveClick(wxCommandEvent& event)
{
	m_model.model_save();
	event.Skip();
}


Controler::~Controler() = default;