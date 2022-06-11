#pragma once
#include <wx/wx.h>
#include <wx/statline.h>
#include <wx/wfstream.h>
#include <string>
#include "id.h"
#include "View.h"
#include "Model.h"
class Controler : public wxPanel
{
public:
	Controler(wxWindow* parent, View& view, Model & model);
	~Controler() override;
	void onLoadClick(wxCommandEvent& event);
	void onSaveClick(wxCommandEvent& event);
	void onResetClick(wxCommandEvent& event);
	void onAxisCheck(wxCommandEvent& event);
	void onAxisWrite(wxCommandEvent& event);
	void onFramesWrite(wxCommandEvent& event);
	void onScaleWrite(wxCommandEvent& event);
	void onRotationWrite(wxCommandEvent& event);
	void onGifClick(wxCommandEvent& event);
	void onKaleidoClick(wxCommandEvent& event);

private:
	bool isLoaded = false;
	std::string m_name;
	wxButton* collapseButton = nullptr;
	wxButton* m_loadButton = nullptr;
	wxButton* m_resetButton = nullptr;
	wxButton* m_saveButton = nullptr;
	wxCheckBox* m_axisCheckbox = nullptr;
	wxBoxSizer* m_bsizer = nullptr;
	wxTextCtrl* m_axisText = nullptr;
	wxTextCtrl* m_rotationText = nullptr;
	wxButton* m_animateButton = nullptr; // do generowania tego zakresu bitmap
	wxButton* m_kaleidoButton = nullptr;
	wxGauge* m_progress_bar = nullptr;
	wxTextCtrl* m_frame_count_input = nullptr;
	wxTextCtrl* m_gif_scale_image = nullptr;


	View& m_view;
	Model& m_model;


};
