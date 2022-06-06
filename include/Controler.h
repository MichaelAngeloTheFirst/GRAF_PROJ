#pragma once
#include <wx/wx.h>
#include <wx/statline.h>
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
	void onAxisWrite(wxCommandEvent& event);
	void onRotationWrite(wxCommandEvent& event);
	void onRangeClick(wxCommandEvent& event);

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
	wxButton* m_rangeButton = nullptr; // do generowania tego zakresu bitmap

	View& m_view;
	Model& m_model;


};
