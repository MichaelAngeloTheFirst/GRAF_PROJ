#include "Controler.h"


Controler::Controler(wxWindow* parent, View & view, Model & model) : wxPanel(parent), m_view(view), m_model(model)
{
	SetAutoLayout(true);
	
	//collapseButton = new wxButton(this, ID::BUTTON_COLLAPSE, ">", wxPoint(80, 0), wxSize(20, 20));

	m_bsizer = new wxBoxSizer(wxVERTICAL);
	
	m_loadButton = new wxButton(this, ID::BUTTON_LOAD, "Load image");
	m_saveButton = new wxButton(this, ID::BUTTON_SAVE, "Save image");
	m_resetButton = new wxButton(this, ID::BUTTON_RESET, "Reset");
	wxCheckBox* m_axisCheckbox = new wxCheckBox(this, ID::AXIS_CHECKBOX, "Show axis");
	wxSlider* m_axisSlider = new wxSlider(this,ID::AXIS_SLIDER, 5, 3, 15);
	wxSlider* m_rotationSlider = new wxSlider(this, ID::ROTATION_SLIDER, 5, 3, 15);


	m_bsizer->Add(new wxStaticLine(this), 0, wxTOP | wxBOTTOM | wxALIGN_CENTER, 2);
	m_bsizer->Add(m_loadButton, 0, wxTOP | wxBOTTOM | wxALIGN_CENTER, 2);
	m_bsizer->Add(m_saveButton, 0, wxTOP | wxBOTTOM | wxALIGN_CENTER, 2);
	m_bsizer->Add(m_resetButton, 0, wxTOP | wxBOTTOM | wxALIGN_CENTER, 2);
	m_bsizer->Add(new wxStaticLine(this) , 0, wxTOP | wxBOTTOM | wxALIGN_CENTER, 2);
	m_bsizer->Add(m_axisCheckbox, 0, wxTOP | wxBOTTOM | wxALIGN_CENTER, 2);
	m_bsizer->Add(new wxStaticLine(this), 0, wxTOP | wxBOTTOM | wxALIGN_CENTER, 2);

	m_bsizer->Add(new wxStaticText(this, ID::AXIS_SLIDER, "Axis count"), 0, wxTOP | wxBOTTOM | wxALIGN_CENTER, 2);
	m_bsizer->Add(m_axisSlider, 0, wxTOP | wxBOTTOM | wxALIGN_CENTER, 2);
	m_bsizer->Add(new wxStaticLine(this), 0, wxTOP | wxBOTTOM | wxALIGN_CENTER, 2);
	m_bsizer->Add(new wxStaticText(this, wxID_ANY, "Rotation"), 0, wxTOP | wxBOTTOM | wxALIGN_CENTER, 2);
	m_bsizer->Add(m_rotationSlider, 0, wxTOP | wxBOTTOM | wxALIGN_CENTER, 2);
	m_bsizer->Add(new wxStaticLine(this) , 0, wxTOP | wxBOTTOM | wxALIGN_CENTER, 2);

	Bind(wxEVT_BUTTON, &Controler::onLoadClick, this, ID::BUTTON_LOAD);
	Bind(wxEVT_BUTTON, &Controler::onSaveClick, this, ID::BUTTON_SAVE);
	Bind(wxEVT_BUTTON, &Controler::onResetClick, this, ID::BUTTON_RESET);
	Bind(wxEVT_SLIDER, &Controler::onSliderAxisMove, this, ID::AXIS_SLIDER);


	//additional operations
	m_axisSlider->SetRange(1,20);

	SetSizer(m_bsizer); // zawsze ma być ostatnie
} 

void Controler::onLoadClick(wxCommandEvent& event)
{
	auto handle = wxFileDialog(this, _("Choose a file"), _(""), _(""), _("JPEG files (*.jpg)|*.jpg"), wxFD_OPEN);
	if (handle.ShowModal() == wxID_OK)
	{	
		isLoaded = true;
		m_name = handle.GetPath();
		m_model.model_load(handle.GetPath());
		m_view.MyPaint();
	}


	event.Skip(); //zawsze na koncu w handlerach
}

void Controler::onSaveClick(wxCommandEvent& event)
{	
	if (isLoaded)
		m_model.model_save();
	else
		wxLogWarning("No image is loaded, please load image first");
	event.Skip();
}

void Controler::onResetClick(wxCommandEvent& event)
{
	if (isLoaded)
	{
		m_model.model_load(m_name);
		m_view.MyPaint();
	}
	else
		wxLogWarning("No image is loaded, please load image first");
	event.Skip();
}

void Controler::onSliderAxisMove(wxCommandEvent& event)
{
	/*if (!m_axisSlider->GetLineSize())//== nullptr)
		wxLogError("axis jest rowne 0");
	else
	{
		int val = m_axisSlider->GetLineSize();
		if (val == 5)
			wxLogWarning("axis Val:: " + val);
	}*/
	
}



Controler::~Controler() = default;