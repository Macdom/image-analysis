#pragma once

#include <iostream>
#include <sstream>

// Klasa programu
class AOProject : public wxApp
{
public:
	virtual bool OnInit();
};

// Klasa g��wnego okna
class AOFrame : public wxFrame
{
public:
	AOFrame();
private:
	// Sizery - poziomy i pionowy
	wxBoxSizer* mainSizer;
	wxBoxSizer* mainSizer2;
	// Panel na kt�rym wy�wietlany jest obraz
	wxPanel* mainPanel;
	// Wska�nik do okienka z histogramem
	HistFrame* histFrame;
	// Wska�nik do okienka w kt�rym si� przemna�a/przeplata obrazy
	MultFrame* multFrame;
	// Czy okno z histogramem jest wy�wietlone?
	bool* isHist;
	// Czy okno do przemna�ania/przeplatania jest wy�wietlone?
	short* isMult;

	// Przycisk "Wczytaj JPG"
	wxButton* btLoad;
	// Przycisk "Zapisz do JPG"
	wxButton* btSave;
	// Przycisk "Zastosuj"
	wxButton* btApply;
	// Przycisk "Wy�wietl histogram"
	wxButton* btHistogram;
	// Przycisk "Zresetuj obraz"
	wxButton* btRestore;
	// Przycisk "Rozci�gnij histogram"
	wxButton* btNormHist;
	// Przycisk "Wyr�wnaj histogram"
	wxButton* btEqualHist;
	// Przycisk "Przemn� obrazy"
	wxButton* btMultImage;
	// Przycisk "Przeple� obrazy"
	wxButton* btInterImage;
	// Suwak do jasno�ci
	wxScrollBar* sbBrightness;
	// Suwak do kontrastu
	wxScrollBar* sbContrast;
	// Suwak do korekcji gamma
	wxScrollBar* sbGamma;

	// Static Texty do wy�wietlania instrukcji na ekranie
	wxStaticText* stInfo;
	wxStaticText* stInfo2;
	wxStaticText* stInfo3;

	// Do wy�wietlania poziomu jasno�ci
	wxStaticText* stBrightness;
	// Do wy�wietlania poziomu kontrastu
	wxStaticText* stContrast;
	// Do wy�wietlania poziomu korekcji gamma
	wxStaticText* stGamma;

	// Bitmapa do przechowywania obrazu
	wxBitmap mainBMP;
	// Orygina� obrazu, nigdy nie jest modyfikowana
	wxImage mainImg;
	// Kopia obrazu, do modyfikacji
	wxImage copyImg;

	// Okna dialogowe do wczytywania i zapisywania obraz�w
	wxFileDialog* dialLoad;
	wxFileDialog* dialSave;

	// Kolor wype�nienia t�a
	wxColour fillColor;
	// �cie�ka wczytanego obrazu
	wxString filename;
	// �cie�ka zapisanego obrazu
	wxString outFilename;
	// Czy jest obraz wczytany?
	short isLoad;
	// Czy wydano rozkaz zapisu obrazu?
	bool isSave;

	// Wymiary obrazu
	double imgWidth, imgHeight;

	// Jasno��
	int brightness = 0;
	// Kontrast
	double contrast = 1;
	// Korekcja gamma
	double gamma = 1;

	// Handlery do zdarze�
	void btLoad_Click(wxCommandEvent& e);
	void btSave_Click(wxCommandEvent& e);
	void sbBrightness_Scroll(wxScrollEvent& e);
	void sbContrast_Scroll(wxScrollEvent& e);
	void sbGamma_Scroll(wxScrollEvent& e);
	void btApply_Click(wxCommandEvent& e);
	void btHistogram_Click(wxCommandEvent& e);
	void btRestore_Click(wxCommandEvent& e);
	void btNormHist_Click(wxCommandEvent& e);
	void btEqualHist_Click(wxCommandEvent& e);
	void btMultImage_Click(wxCommandEvent& e);
	void btInterImage_Click(wxCommandEvent& e);
	void mainPaint_Paint(wxPaintEvent& e);
	void mainPanel_Update(wxUpdateUIEvent& e);
	void onClose(wxCloseEvent& e);

	void onExit(wxCommandEvent& e);

};