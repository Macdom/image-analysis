#pragma once

#include <iostream>
#include <sstream>

// Klasa programu
class AOProject : public wxApp
{
public:
	virtual bool OnInit();
};

// Klasa g³ównego okna
class AOFrame : public wxFrame
{
public:
	AOFrame();
private:
	// Sizery - poziomy i pionowy
	wxBoxSizer* mainSizer;
	wxBoxSizer* mainSizer2;
	// Panel na którym wyœwietlany jest obraz
	wxPanel* mainPanel;
	// WskaŸnik do okienka z histogramem
	HistFrame* histFrame;
	// WskaŸnik do okienka w którym siê przemna¿a/przeplata obrazy
	MultFrame* multFrame;
	// Czy okno z histogramem jest wyœwietlone?
	bool* isHist;
	// Czy okno do przemna¿ania/przeplatania jest wyœwietlone?
	short* isMult;

	// Przycisk "Wczytaj JPG"
	wxButton* btLoad;
	// Przycisk "Zapisz do JPG"
	wxButton* btSave;
	// Przycisk "Zastosuj"
	wxButton* btApply;
	// Przycisk "Wyœwietl histogram"
	wxButton* btHistogram;
	// Przycisk "Zresetuj obraz"
	wxButton* btRestore;
	// Przycisk "Rozci¹gnij histogram"
	wxButton* btNormHist;
	// Przycisk "Wyrównaj histogram"
	wxButton* btEqualHist;
	// Przycisk "Przemnó¿ obrazy"
	wxButton* btMultImage;
	// Przycisk "Przepleæ obrazy"
	wxButton* btInterImage;
	// Suwak do jasnoœci
	wxScrollBar* sbBrightness;
	// Suwak do kontrastu
	wxScrollBar* sbContrast;
	// Suwak do korekcji gamma
	wxScrollBar* sbGamma;

	// Static Texty do wyœwietlania instrukcji na ekranie
	wxStaticText* stInfo;
	wxStaticText* stInfo2;
	wxStaticText* stInfo3;

	// Do wyœwietlania poziomu jasnoœci
	wxStaticText* stBrightness;
	// Do wyœwietlania poziomu kontrastu
	wxStaticText* stContrast;
	// Do wyœwietlania poziomu korekcji gamma
	wxStaticText* stGamma;

	// Bitmapa do przechowywania obrazu
	wxBitmap mainBMP;
	// Orygina³ obrazu, nigdy nie jest modyfikowana
	wxImage mainImg;
	// Kopia obrazu, do modyfikacji
	wxImage copyImg;

	// Okna dialogowe do wczytywania i zapisywania obrazów
	wxFileDialog* dialLoad;
	wxFileDialog* dialSave;

	// Kolor wype³nienia t³a
	wxColour fillColor;
	// Œcie¿ka wczytanego obrazu
	wxString filename;
	// Œcie¿ka zapisanego obrazu
	wxString outFilename;
	// Czy jest obraz wczytany?
	short isLoad;
	// Czy wydano rozkaz zapisu obrazu?
	bool isSave;

	// Wymiary obrazu
	double imgWidth, imgHeight;

	// Jasnoœæ
	int brightness = 0;
	// Kontrast
	double contrast = 1;
	// Korekcja gamma
	double gamma = 1;

	// Handlery do zdarzeñ
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