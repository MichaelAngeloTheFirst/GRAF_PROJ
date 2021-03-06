#pragma once
#include <wx/wx.h>
#include <wx/statline.h>
#include <wx/wfstream.h>
#include <string>
#include "id.h"
#include "View.h"
#include "Model.h"


/// <summary>
/// Klasa odpowiadająca za implementacje przycisków.
/// </summary>
class Controler : public wxPanel
{
public:
	Controler(wxWindow* parent, View& view, Model & model);
	~Controler() override;

	void onLoadClick(wxCommandEvent& event);///<Metoda do wczytania obrazka.
	void onSaveClick(wxCommandEvent& event);///<Metoda do zapisania utworzonego kalejdoskopem obrazka.
	void onResetClick(wxCommandEvent& event);///<Metoda do zresetowania obrazka do oryginalnego stanu.
	void onAxisCheck(wxCommandEvent& event);///<Metoda do wyświetlania osi na obrazku.
	void onAxisWrite(wxCommandEvent& event);///<Metoda do ustawienia ilości osi kalejdoskopu.
	void onFramesWrite(wxCommandEvent& event);///<Nieużywane. Metoda ustalająca ilość klatek do GIFa.
	void onScaleWrite(wxCommandEvent& event);///<Nieużywane. Metoda ustalająca rozmiar GIFa.
	void onRotationWrite(wxCommandEvent& event);///<Metoda do ustawienia obrotu o dodatkowy kąt obrazka w kalejdoskopie.
	void onGifClick(wxCommandEvent& event);///<Metoda do wygenerowania GIFa.
	void onKaleidoClick(wxCommandEvent& event);///<Metoda do wygenerowania obrazka kalejdoskopu.

private:

	bool isLoaded = false;///<Zmienna do sprawdzenia czy obrazek się wczytał.
	std::string m_name;///<Zmienna do przechowania nazwy zapisywanego obrazka.


	wxButton* collapseButton = nullptr;///<Nieużywane. Przycisk chowający UI.
	wxButton* m_loadButton = nullptr;///<Przycisk do wczytania obrazka do programu.
	wxButton* m_resetButton = nullptr;///<Przycisk do zresetowania wyświetlanego obrazka.
	wxButton* m_saveButton = nullptr;///<Przycisk do zapisania obrazka do pliku .jpg.
	wxCheckBox* m_axisCheckbox = nullptr;///<Checkbox do włączenia widoku osi kalejdoskopu.
	wxBoxSizer* m_bsizer = nullptr;///<Sizer okna.
	wxTextCtrl* m_axisText = nullptr;///<Pole tekstowe do ustawiania ilości osi kalejdoskopu.
	wxTextCtrl* m_rotationText = nullptr;///<Pole tekstowe do ustawienia kątu obrotu obrazka w kalejdoskopie.
	wxButton* m_animateButton = nullptr;///<Przycisk do generacji GIFa.
	wxButton* m_kaleidoButton = nullptr;///<Przycisk do wygenerowania obrazka z kalejdoskopu o określnej ilości osi oraz kątu obrotu obrazka.
	wxGauge* m_progress_bar = nullptr;///<Pasek ładowania podczas tworzenia GIFa.
	wxTextCtrl* m_frame_count_input = nullptr;///<Nieużywane. Pole tekstowe do wpisywania ilości klatek GIFa.
	wxTextCtrl* m_gif_scale_image = nullptr;///<Nieużywane. Pole tekstowe do ustalenia rozmiarów GIFa.


	View& m_view;///<Referencja do View.
	Model& m_model;///<Referencja do Modelu.


};
