#pragma once

#include <wx/wxprec.h>
#include <wx/dcbuffer.h>
#include <wx/colordlg.h>
#include <iostream>
#include <math.h>

// Funkcja która znajduje optymalny rozmiar obrazu w polu o wymiarach windowWidth i windowHeight
void fitInWindow(wxImage& img, unsigned int windowWidth, unsigned int windowHeight);
// Funkcja która aplikuje zmiany do wszystkich kana³ów (obiekt wxImage, w jakim przechowywany jest obraz przechowuje dane o pikselach w reprezentacji RGB,
// wiêc aby uzyskaæ odcienie szaroœci, ten sam kolor jest ustawiany w ka¿dym z kana³ów)
void applyToAllChannels(unsigned char* pixels, unsigned int width, unsigned int height);

// Operacja która zmienia obraz z kolorowego, na obraz o odcieniach szaroœci
void grayScale(unsigned char* pixels, unsigned int width, unsigned int height);
// Operacja zmieniaj¹ca jasnoœæ obrazu o wartoœæ _brightness
void setBrightness(unsigned char* pixels, unsigned int width, unsigned int height, int _brightness);
// Operacja zmieniaj¹ca kontrast obrazu o wartoœæ _contrast
void setContrast(unsigned char* pixels, unsigned int width, unsigned int height, double _contrast);
// Operacja zmieniaj¹ca korekcjê gamma obrazu o wartoœæ _gamma
void setGamma(unsigned char* pixels, unsigned int width, unsigned int height, double gamma);

// Operacja która rozci¹ga histogram
void normalizeHistogram(unsigned char* pixels, unsigned int width, unsigned int height);
// Operacja która wyrównuje histogram
void equalHistogram(unsigned char* pixels, unsigned int width, unsigned int height);

// Powy¿sze operacje (rozci¹ganie i wyrównywanie histogramu) odbywaj¹ sie z pomoc¹ tablicy LUT, która dla ka¿dej mo¿liwej wartoœci koloru przypisuje now¹, odpowiadaj¹c¹ mu wartoœæ.
// Obie operacje najpierw wyznaczaj¹ tak¹ tablicê, a potem modyfikuj¹ ka¿dy piksel obrazu zgodnie z tablic¹

// Operacja która przemna¿a 2 obrazy
void multiplicate(unsigned char* pixels, unsigned char* pixels2, unsigned int width, unsigned int height);
// Operacja która przeplata 2 obrazy, udzia³ drugiego okreœlony przez contribution
void interlace(unsigned char* pixels, unsigned char* pixels2, unsigned int width, unsigned int height, double contribution);