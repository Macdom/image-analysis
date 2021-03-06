#pragma once

#include <wx/wxprec.h>
#include <wx/dcbuffer.h>
#include <wx/colordlg.h>

// Klasa okna wyświetlającego histogram
class HistFrame : public wxFrame
{
public:
	HistFrame();
	// Uzyskuje wskaźnik do informacji o tym, czy okno jest wyświetlone
	void setPointer(bool* ptr);
	// Oblicza histogram do wyświetlenia go
	void drawHistogram(unsigned char* pixels, unsigned int width, unsigned int height);
private:
	// Sizery - poziomy i pionowy
	wxBoxSizer* mainSizer;
	wxBoxSizer* mainSizer2;
	// Panel na którym wyświetlany jest histogram
	wxPanel* mainPanel;
	// Czy okno histogramu jest wyświetlone?
	bool* isHist;

	// Histogram w postaci tablicy
	unsigned int colorCount[256];
	// Kolor o największej częstotliwości. Liczony by móc znormalizować wielkość wykresu histogramu
	unsigned int biggestCount;

	// Handlery do zdarzeń
	void mainPanel_Update(wxUpdateUIEvent& e);
	void onClose(wxCloseEvent& e);
};