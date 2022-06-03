#include "Controler.h"


Controler::Controler(wxWindow* parent, View & view, Model & model) : wxPanel(parent), m_view(view), m_model(model)
{
	SetAutoLayout(true);
	
	//collapseButton = new wxButton(this, ID::BUTTON_COLLAPSE, ">", wxPoint(80, 0), wxSize(20, 20));

	m_bsizer = new wxBoxSizer(wxVERTICAL);
	
	m_loadButton = new wxButton(this, ID::BUTTON_LOAD, "Load image");
	m_saveButton = new wxButton(this, ID::BUTTON_SAVE, "Save image");
	wxCheckBox* m_axisCheckbox = new wxCheckBox(this, ID::AXIS_CHECKBOX, "Show axis");
	wxSlider* m_axisSlider = new wxSlider(this,ID::AXIS_CHECKBOX, 5, 3, 15);
	wxSlider* m_rotationSlider = new wxSlider(this, ID::ROTATION_SLIDER, 5, 3, 15);


	m_bsizer->Add(new wxStaticLine(this), 0, wxTOP | wxBOTTOM | wxALIGN_CENTER, 2);
	m_bsizer->Add(m_loadButton, 0, wxTOP | wxBOTTOM | wxALIGN_CENTER, 2);
	m_bsizer->Add(m_saveButton, 0, wxTOP | wxBOTTOM | wxALIGN_CENTER, 2);
	m_bsizer->Add(new wxStaticLine(this) , 0, wxTOP | wxBOTTOM | wxALIGN_CENTER, 2);
	m_bsizer->Add(m_axisCheckbox, 0, wxTOP | wxBOTTOM | wxALIGN_CENTER, 2);
	m_bsizer->Add(new wxStaticLine(this), 0, wxTOP | wxBOTTOM | wxALIGN_CENTER, 2);
	m_bsizer->Add(new wxStaticText(this, wxID_ANY, "Axis count"), 0, wxTOP | wxBOTTOM | wxALIGN_CENTER, 2);
	m_bsizer->Add(m_axisSlider, 0, wxTOP | wxBOTTOM | wxALIGN_CENTER, 2);
	m_bsizer->Add(new wxStaticLine(this), 0, wxTOP | wxBOTTOM | wxALIGN_CENTER, 2);
	m_bsizer->Add(new wxStaticText(this, wxID_ANY, "Rotation"), 0, wxTOP | wxBOTTOM | wxALIGN_CENTER, 2);
	m_bsizer->Add(m_rotationSlider, 0, wxTOP | wxBOTTOM | wxALIGN_CENTER, 2);
	m_bsizer->Add(new wxStaticLine(this) , 0, wxTOP | wxBOTTOM | wxALIGN_CENTER, 2);

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