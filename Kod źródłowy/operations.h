#pragma once

#include <wx/wxprec.h>
#include <wx/dcbuffer.h>
#include <wx/colordlg.h>
#include <iostream>
#include <math.h>

// Funkcja kt�ra znajduje optymalny rozmiar obrazu w polu o wymiarach windowWidth i windowHeight
void fitInWindow(wxImage& img, unsigned int windowWidth, unsigned int windowHeight);
// Funkcja kt�ra aplikuje zmiany do wszystkich kana��w (obiekt wxImage, w jakim przechowywany jest obraz przechowuje dane o pikselach w reprezentacji RGB,
// wi�c aby uzyska� odcienie szaro�ci, ten sam kolor jest ustawiany w ka�dym z kana��w)
void applyToAllChannels(unsigned char* pixels, unsigned int width, unsigned int height);

// Operacja kt�ra zmienia obraz z kolorowego, na obraz o odcieniach szaro�ci
void grayScale(unsigned char* pixels, unsigned int width, unsigned int height);
// Operacja zmieniaj�ca jasno�� obrazu o warto�� _brightness
void setBrightness(unsigned char* pixels, unsigned int width, unsigned int height, int _brightness);
// Operacja zmieniaj�ca kontrast obrazu o warto�� _contrast
void setContrast(unsigned char* pixels, unsigned int width, unsigned int height, double _contrast);
// Operacja zmieniaj�ca korekcj� gamma obrazu o warto�� _gamma
void setGamma(unsigned char* pixels, unsigned int width, unsigned int height, double gamma);

// Operacja kt�ra rozci�ga histogram
void normalizeHistogram(unsigned char* pixels, unsigned int width, unsigned int height);
// Operacja kt�ra wyr�wnuje histogram
void equalHistogram(unsigned char* pixels, unsigned int width, unsigned int height);

// Powy�sze operacje (rozci�ganie i wyr�wnywanie histogramu) odbywaj� sie z pomoc� tablicy LUT, kt�ra dla ka�dej mo�liwej warto�ci koloru przypisuje now�, odpowiadaj�c� mu warto��.
// Obie operacje najpierw wyznaczaj� tak� tablic�, a potem modyfikuj� ka�dy piksel obrazu zgodnie z tablic�

// Operacja kt�ra przemna�a 2 obrazy
void multiplicate(unsigned char* pixels, unsigned char* pixels2, unsigned int width, unsigned int height);
// Operacja kt�ra przeplata 2 obrazy, udzia� drugiego okre�lony przez contribution
void interlace(unsigned char* pixels, unsigned char* pixels2, unsigned int width, unsigned int height, double contribution);