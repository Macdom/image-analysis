#include "histogram.h"

#define HIST_WIDTH 512
#define HIST_HEIGHT 300

HistFrame::HistFrame() : wxFrame(NULL, wxID_ANY, "Histogram", wxDefaultPosition, wxDefaultSize, wxCAPTION | wxCLOSE_BOX | wxMINIMIZE_BOX)
{
	SetSize(HIST_WIDTH, HIST_HEIGHT + 20);

	mainSizer = new wxBoxSizer(wxHORIZONTAL);
	mainSizer2 = new wxBoxSizer(wxVERTICAL);
	this->SetSizer(mainSizer);
	this->SetAutoLayout(true);
	mainPanel = new wxPanel(this, wxID_ANY, wxPoint(4, 4), wxSize(HIST_WIDTH, HIST_HEIGHT + 20));
	mainSizer->Add(mainPanel, 1, wxALIGN_LEFT | wxEXPAND | wxALL, 5);
	mainSizer->Add(mainSizer2, 0, wxALIGN_TOP | wxALL, 5);

	Layout();
	GetSizer()->SetSizeHints(this);
	Center();

	mainPanel->Bind(wxEVT_UPDATE_UI, &HistFrame::mainPanel_Update, this);
	Bind(wxEVT_CLOSE_WINDOW, &HistFrame::onClose, this);
}

void HistFrame::onClose(wxCloseEvent& e) { *isHist = false; Destroy(); }

void HistFrame::setPointer(bool* ptr) { isHist = ptr; }

void HistFrame::mainPanel_Update(wxUpdateUIEvent& e) {
	if (biggestCount == 0) return;
	wxClientDC myOtherDC(mainPanel);
	wxBufferedDC myDC(&myOtherDC);
	myDC.Clear();
	myDC.SetBrush(wxColor(150, 255, 255));
	for (unsigned int i = 0; i < 256; i++) {
		myDC.SetPen(wxPen(RGB(0, 0, i / 2)));
		myDC.DrawLine(2 * i, HIST_HEIGHT - 1, 2 * i, HIST_HEIGHT - 1 - 300 * colorCount[i] / biggestCount);
		myDC.DrawLine(2 * i + 1, HIST_HEIGHT - 1, 2 * i + 1, HIST_HEIGHT - 1 - 300 * colorCount[i] / biggestCount);
	}
	myDC.DrawRectangle(0, HIST_HEIGHT, HIST_WIDTH, 20);
	myDC.DrawText("0", 2, HIST_HEIGHT - 1);
	myDC.DrawText("0.5", HIST_WIDTH / 2 - 7, HIST_HEIGHT - 1);
	myDC.DrawText("1", HIST_WIDTH - 9, HIST_HEIGHT - 1);
	myDC.DrawText("<- ciemniej", HIST_WIDTH / 5, HIST_HEIGHT - 1);
	myDC.DrawText("jaœniej ->", 2 * HIST_WIDTH / 3, HIST_HEIGHT - 1);
}

void HistFrame::drawHistogram(unsigned char* pixels, unsigned int width, unsigned int height) {
	mainPanel->ClearBackground();
	biggestCount = 0;
	for (unsigned int i = 0; i < 256; i++) colorCount[i] = 0;
	for (unsigned int x = 0; x < width; x++) {
		for (unsigned int y = 0; y < height; y++) {
			colorCount[pixels[3 * width * y + 3 * x]]++;
			if (colorCount[pixels[3 * width * y + 3 * x]] > biggestCount)
				biggestCount = colorCount[pixels[3 * width * y + 3 * x]];
		}
	}
}