#include "Controler.h"



Controler::Controler(wxWindow* parent, View & view, Model & model) : wxPanel(parent), m_view(view), m_model(model)
{
	SetAutoLayout(true);
	
	//collapseButton = new wxButton(this, ID::BUTTON_COLLAPSE, ">", wxPoint(80, 0), wxSize(20, 20));

	m_bsizer = new wxBoxSizer(wxVERTICAL);
	
	m_loadButton = new wxButton(this, ID::BUTTON_LOAD, "Load image");
	m_saveButton = new wxButton(this, ID::BUTTON_SAVE, "Save image");
	m_resetButton = new wxButton(this, ID::BUTTON_RESET, "Reset");
	m_rangeButton = new wxButton(this, ID::BUTTON_GIF, "Animate");
	m_axisCheckbox = new wxCheckBox(this, ID::AXIS_CHECKBOX, "Show axis");
	m_axisText = new wxTextCtrl(this, ID::AXIS_TEXT, _("1"), wxDefaultPosition, wxSize(50, -1), 0);
	m_rotationText = new wxTextCtrl(this, ID::ROTATION_TEXT, _("0"), wxDefaultPosition, wxSize(50, -1), 0);
	m_kaleidoButton = new wxButton(this, ID::BUTTON_KALEIDO, "Go Kaleido");
	m_progress_bar = new wxGauge(this, ID::PROGRESS, 180);
	m_bsizer->Add(new wxStaticLine(this), 0, wxTOP | wxBOTTOM | wxALIGN_CENTER, 2);
	m_bsizer->Add(m_loadButton, 0, wxTOP | wxBOTTOM | wxALIGN_CENTER, 2);	
	m_bsizer->Add(m_saveButton, 0, wxTOP | wxBOTTOM | wxALIGN_CENTER, 2);
	m_bsizer->Add(m_resetButton, 0, wxTOP | wxBOTTOM | wxALIGN_CENTER, 2);
	m_bsizer->Add(new wxStaticLine(this) , 0, wxTOP | wxBOTTOM | wxALIGN_CENTER, 2);
	m_bsizer->Add(m_axisCheckbox, 0, wxTOP | wxBOTTOM | wxALIGN_CENTER, 2);
	m_bsizer->Add(new wxStaticLine(this), 0, wxTOP | wxBOTTOM | wxALIGN_CENTER, 2);
	
	m_bsizer->Add(new wxStaticText(this, ID::AXIS_TEXT, "Axis Count"), 0, wxTOP | wxBOTTOM | wxALIGN_CENTER, 2);
	m_bsizer->Add(m_axisText, 0, wxTOP | wxBOTTOM | wxALIGN_CENTER, 2);
	m_bsizer->Add(new wxStaticLine(this), 0, wxTOP | wxBOTTOM | wxALIGN_CENTER, 2);

	m_bsizer->Add(new wxStaticText(this, wxID_ANY, "Rotation"), 0, wxTOP | wxBOTTOM | wxALIGN_CENTER, 2);
	m_bsizer->Add(m_rotationText, 0, wxTOP | wxBOTTOM | wxALIGN_CENTER, 2);
	m_bsizer->Add(new wxStaticLine(this) , 0, wxTOP | wxBOTTOM | wxALIGN_CENTER, 2);
	m_bsizer->Add(m_kaleidoButton, 0, wxTOP | wxBOTTOM | wxALIGN_CENTER, 2);
	m_bsizer->Add(m_rangeButton, 0, wxTOP | wxBOTTOM | wxALIGN_CENTER, 2);
	m_bsizer->Add(m_progress_bar, 0, wxTOP | wxBOTTOM | wxALIGN_CENTER, 2);

	Bind(wxEVT_BUTTON, &Controler::onLoadClick, this, ID::BUTTON_LOAD);
	Bind(wxEVT_BUTTON, &Controler::onSaveClick, this, ID::BUTTON_SAVE);
	Bind(wxEVT_BUTTON, &Controler::onResetClick, this, ID::BUTTON_RESET);
	Bind(wxEVT_CHECKBOX, &Controler::onAxisCheck, this, ID::AXIS_CHECKBOX);
	Bind(wxEVT_TEXT, &Controler::onAxisWrite, this, ID::AXIS_TEXT);
	Bind(wxEVT_TEXT, &Controler::onRotationWrite, this, ID::ROTATION_TEXT);
	Bind(wxEVT_BUTTON, &Controler::onGifClick, this, ID::BUTTON_GIF);
	Bind(wxEVT_BUTTON, &Controler::onKaleidoClick, this, ID::BUTTON_KALEIDO);




	SetSizer(m_bsizer); // zawsze ma być ostatnie
} 

void Controler::onLoadClick(wxCommandEvent& event)
{
	auto handle = wxFileDialog(this, _("Choose a file"), _(""), _(""), _("JPEG files (*.jpg)|*.jpg|PNG files (*.png) | *.png"), wxFD_OPEN);
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
		m_model.model_save("wynik.jpg");
	else
		wxLogWarning("No image is loaded, please load image first");
	event.Skip();
}

void Controler::onResetClick(wxCommandEvent& event)
{
	if (isLoaded)
	{
		m_model.reset_copy();
		m_view.MyPaint();
	}
	else
		wxLogWarning("No image is loaded, please load image first");
	event.Skip();
}



void Controler::onRotationWrite(wxCommandEvent& event)
{
	if (!m_rotationText)
		wxLogError("axis jest rowne 0");
	else
	{
		
		int val = wxAtoi(m_rotationText->GetLineText(0));
		if (val <= 360 && val >= 0)
			m_model.set_angle(val);	//m_model.kaleidoscope(m_model.get_axis(), val);
		else
		{
			wxLogWarning("Proper angle range: <0,360>");
			m_rotationText->SetValue("0");
		}
			
	}
	event.Skip();
}


void Controler::onAxisWrite(wxCommandEvent& event)
{
	if (!m_axisText)
		wxLogError("axis jest rowne 0");
	else
	{
		
		int val = wxAtoi(m_axisText->GetLineText(0));
		if (val >= 0 && val <= 20)
		{
			/*if (val == 0) val = 1;
			m_model.kaleidoscope(val, m_model.get_angle());*/
			m_model.set_axis(val);
		}
		else
		{
			wxLogWarning("proper axis amount range: <1,20>");
			m_axisText->SetValue("1");
		}
			
	}
	event.Skip();
}

void Controler::onGifClick(wxCommandEvent& event)
{
	if (isLoaded)
	{
		wxFileOutputStream* file = new wxFileOutputStream("animation.gif");
		wxImageArray frames;
		frames.Clear();
		if (!file->IsOk())
			wxLogWarning("Cannot write file.");
		int frame_count = 55 - 2 * m_model.get_axis();
		for (int i = 0; i < frame_count; i++)
		{
			m_model.get_gif_buffer().Add(wxImage());
			frames.Add(m_model.kaleidoscope(m_model.get_axis(), i * 360. / static_cast<double>(frame_count)));
			wxQuantize::Quantize(frames[i], m_model.get_gif_buffer()[i]);
			m_progress_bar->SetValue(m_progress_bar->GetValue() + 1);
			//m_model.kaleidoscope(m_model.get_axis(), i);
			//m_model.model_save(name);
		}
		wxGIFHandler* tmp = new wxGIFHandler();
		int frame_delay = 1000 / frame_count;
		tmp->SaveAnimation(m_model.get_gif_buffer(), file, true, frame_delay);
		m_model.get_gif_buffer().Empty();
		m_progress_bar->SetValue(0);
	}
	else
		wxLogWarning("No image is loaded, please load image first");


	event.Skip();
}

void Controler::onKaleidoClick(wxCommandEvent& event)
{
	if (isLoaded)
		m_model.get_bitmap() = wxBitmap(m_model.kaleidoscope(m_model.get_axis(), m_model.get_angle()));
	else
		wxLogWarning("No image is loaded, please load image first");

	event.Skip();
}

void Controler::onAxisCheck(wxCommandEvent & event)
{
	if (isLoaded)
	{
		bool val = m_axisCheckbox->GetValue();

		m_model.axis_show(val);
	}
	else
		wxLogWarning("No image is loaded, please load image first");
}


Controler::~Controler() = default;