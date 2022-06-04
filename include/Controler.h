#pragma once
#include <wx/wx.h>
#include "id.h"
#include "View.h"
#include "Model.h"
#include <wx/statline.h>

class Controler : public wxPanel
{
public:
	Controler(wxWindow* parent, View& view, Model & model);
	~Controler() override;
	void onLoadClick(wxCommandEvent& event);
	void onSaveClick(wxCommandEvent& event);
	void onResetClick(wxCommandEvent& event);
	void onSliderAxisMove(wxCommandEvent& event);

private:
	bool isLoaded = false;
	std::string m_name;
	wxButton* collapseButton = nullptr;
	wxButton* m_loadButton = nullptr;
	wxButton* m_resetButton = nullptr;
	wxButton* m_saveButton = nullptr;
	wxCheckBox* m_axisCheckbox = nullptr;
	wxSlider* m_axisSlider = nullptr;
	wxSlider* m_rotationSlider = nullptr;
	wxBoxSizer* m_bsizer = nullptr;
	View& m_view;
	Model& m_model;


};
