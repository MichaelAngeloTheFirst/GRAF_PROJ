#include "Controler.h"



Controler::Controler(wxWindow* parent, View & view, Model & model) : wxPanel(parent), m_view(view), m_model(model)
{
	SetAutoLayout(true);
	
	//collapseButton = new wxButton(this, ID::BUTTON_COLLAPSE, ">", wxPoint(80, 0), wxSize(20, 20));

	//tworzenie sizera.
	m_bsizer = new wxBoxSizer(wxVERTICAL);
	
	//tworzenie przycisków
	m_loadButton = new wxButton(this, ID::BUTTON_LOAD, "Load image",wxDefaultPosition,wxSize(90,-1));
	m_saveButton = new wxButton(this, ID::BUTTON_SAVE, "Save image", wxDefaultPosition, wxSize(90, -1));
	m_saveButton->Disable();
	m_resetButton = new wxButton(this, ID::BUTTON_RESET, "Reset", wxDefaultPosition, wxSize(90, -1));
	m_resetButton->Disable();
	m_animateButton = new wxButton(this, ID::BUTTON_GIF, "Animate", wxDefaultPosition, wxSize(90, -1));
	m_animateButton->Disable();
	m_axisCheckbox = new wxCheckBox(this, ID::AXIS_CHECKBOX, "Show axis");
	m_axisText = new wxTextCtrl(this, ID::AXIS_TEXT, _("1"), wxDefaultPosition, wxSize(90, -1), 0);
	m_rotationText = new wxTextCtrl(this, ID::ROTATION_TEXT, _("0"), wxDefaultPosition, wxSize(90, -1), 0);
	m_kaleidoButton = new wxButton(this, ID::BUTTON_KALEIDO, "Go Kaleido",wxDefaultPosition, wxSize(90, -1));
	m_kaleidoButton->Disable();
	//m_frame_count_input = new wxTextCtrl(this, ID::FRAME_COUNT_TEXT, _("90"), wxDefaultPosition, wxSize(90, -1), 0);
	//m_gif_scale_image = new wxTextCtrl(this, ID::SCALE_TEXT, _("100"), wxDefaultPosition, wxSize(90, -1), 0);
	m_progress_bar = new wxGauge(this, ID::PROGRESS, 180);


	
	//sizery
	m_bsizer->AddSpacer(30);
	m_bsizer->Add(new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxSize(100, 2), wxLI_HORIZONTAL), 0, wxTOP | wxBOTTOM | wxALIGN_CENTER, 2);
	m_bsizer->AddSpacer(10);
	m_bsizer->Add(new wxStaticLine(this), 0, wxTOP | wxBOTTOM | wxALIGN_CENTER, 2);
	m_bsizer->Add(m_loadButton, 0, wxTOP | wxBOTTOM | wxALIGN_CENTER, 2);	
	m_bsizer->Add(m_saveButton, 0, wxTOP | wxBOTTOM | wxALIGN_CENTER, 2);
	m_bsizer->Add(m_resetButton, 0, wxTOP | wxBOTTOM | wxALIGN_CENTER, 2);
	m_bsizer->AddSpacer(10);

	m_bsizer->Add(new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxSize(100,2), wxLI_HORIZONTAL), 0, wxTOP | wxBOTTOM | wxALIGN_CENTER, 2);
	m_bsizer->AddSpacer(15);
	m_bsizer->Add(m_axisCheckbox, 0, wxTOP | wxBOTTOM | wxALIGN_CENTER, 2);	
	m_bsizer->Add(new wxStaticText(this, ID::AXIS_TEXT, "Axis Count"), 0, wxTOP | wxBOTTOM | wxALIGN_CENTER, 2);
	m_bsizer->Add(m_axisText, 0, wxTOP | wxBOTTOM | wxALIGN_CENTER, 2);
	m_bsizer->Add(new wxStaticText(this, wxID_ANY, "Rotation"), 0, wxTOP | wxBOTTOM | wxALIGN_CENTER, 2);
	m_bsizer->Add(m_rotationText, 0, wxTOP | wxBOTTOM | wxALIGN_CENTER, 2);
	m_bsizer->Add(m_kaleidoButton, 0, wxTOP | wxBOTTOM | wxALIGN_CENTER, 2);
	m_bsizer->AddSpacer(10);

	m_bsizer->Add(new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxSize(100, 2), wxLI_HORIZONTAL), 0, wxTOP | wxBOTTOM | wxALIGN_CENTER, 2);
	m_bsizer->AddSpacer(10);
	//m_bsizer->Add(new wxStaticText(this, ID::AXIS_TEXT, "Frame count"), 0, wxTOP | wxBOTTOM | wxALIGN_CENTER, 2);
	//m_bsizer->Add(m_frame_count_input, 0, wxTOP | wxBOTTOM | wxALIGN_CENTER, 2);
	//m_bsizer->Add(new wxStaticText(this, ID::AXIS_TEXT, "Downscale [%]"), 0, wxTOP | wxBOTTOM | wxALIGN_CENTER, 2);
	//m_bsizer->Add(m_gif_scale_image, 0, wxTOP | wxBOTTOM | wxALIGN_CENTER, 2);
	m_bsizer->Add(m_animateButton, 0, wxTOP | wxBOTTOM | wxALIGN_CENTER, 2);
	m_bsizer->Add(m_progress_bar, 0, wxTOP | wxBOTTOM | wxALIGN_CENTER, 2);

	
	//podpinanie funkcji do przycisków
	Bind(wxEVT_BUTTON, &Controler::onLoadClick, this, ID::BUTTON_LOAD);
	Bind(wxEVT_BUTTON, &Controler::onSaveClick, this, ID::BUTTON_SAVE);
	Bind(wxEVT_BUTTON, &Controler::onResetClick, this, ID::BUTTON_RESET);
	Bind(wxEVT_CHECKBOX, &Controler::onAxisCheck, this, ID::AXIS_CHECKBOX);
	Bind(wxEVT_TEXT, &Controler::onAxisWrite, this, ID::AXIS_TEXT);
	//Bind(wxEVT_TEXT, &Controler::onFramesWrite, this, ID::FRAME_COUNT_TEXT);
	//Bind(wxEVT_TEXT, &Controler::onScaleWrite, this, ID::SCALE_TEXT);
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
		m_kaleidoButton->Enable();
		m_animateButton->Enable();
		m_saveButton->Enable();
		m_resetButton->Enable();
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



void Controler::onFramesWrite(wxCommandEvent& event)
{
	
		int val = wxAtoi(m_frame_count_input->GetLineText(0));
		if (val <= 360 && val >= 10)
			m_model.set_frames(val);	//m_model.kaleidoscope(m_model.get_axis(), val);
		else
		{
			wxLogWarning("Proper value range: <10,360>");
			m_rotationText->SetValue("90");
		}

	event.Skip();
}



void Controler::onScaleWrite(wxCommandEvent& event)
{

	int val = wxAtoi(m_gif_scale_image->GetLineText(0));
	if (val <= 100 && val >= 10)
		m_model.set_scale(val);	//m_model.kaleidoscope(m_model.get_axis(), val);
	else
	{
		wxLogWarning("Proper value range: <10,100>");
		m_rotationText->SetValue("100");
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

/// <summary>
/// Metoda tworzy serię 60 bitmap, która następnie zostaje zamieniona na animacje w formacie ".gif".
/// 
/// Na początku tworzy plik "animation.gif", do którego zostanie zapisana animacja. Następnie zmieniany obrazek zostaje przeskalowany na rozmiar 500x500 pikseli
/// oraz utworzone zostają dwie tablice o rozmiarze 60. W kolejnym kroku generowane są kolejne klatki GIFa, które przed dodaniem do właściwej tablicy, dodatkowo zmniejsza się im rozamiar funkcją wxQuantize.
/// Na koniec liczony jest odstęp pomiędzy klatkami, aby było wyraźnie widać zmianę kąta i animacja zostaje zapisana do pliku "animation.gif". 
/// </summary>

void Controler::onGifClick(wxCommandEvent& event)
{
	if (isLoaded)
	{
		wxFileOutputStream* file = new wxFileOutputStream("animation.gif");
		wxImageArray frames;
		wxImage rescaled_frame = m_model.get_image();
		int frame_count = 60;



		rescaled_frame = rescaled_frame.Rescale(500,500);
		frames.Alloc(frame_count);
		m_model.get_gif_buffer().Alloc(frame_count);
		frames.Clear();

		if (!file->IsOk())
			wxLogWarning("Cannot write file.");
		
		for (int i = 0; i < frame_count; i++)
		{
			m_model.get_gif_buffer().Add(wxImage());
			frames.Add(m_model.kaleidoscope(rescaled_frame,m_model.get_axis(), i * 360. / static_cast<double>(frame_count)));
			wxQuantize::Quantize(frames[i], m_model.get_gif_buffer()[i]);
			m_progress_bar->SetValue(m_progress_bar->GetValue() + 4);
		}
		wxGIFHandler* tmp = new wxGIFHandler();
		
		int frame_delay = 1000 / frame_count;
		
		if (m_model.get_axis() >= 10)
		{
			frame_delay *= 5;
		}

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
		m_model.get_bitmap() = wxBitmap(m_model.kaleidoscope(m_model.get_image(), m_model.get_axis(), m_model.get_angle()));
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