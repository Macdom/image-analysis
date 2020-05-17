#include "operations.h"

void fitInWindow(wxImage& img, unsigned int windowWidth, unsigned int windowHeight) {
	unsigned int width = img.GetWidth();
	unsigned int height = img.GetHeight();
	if ((double)width / (double)height > (double)windowWidth / (double)windowHeight) img.Rescale(windowWidth, (double)windowWidth * (double)height / (double)width);
	else img.Rescale((double)windowHeight * (double)width / (double)height, windowHeight);
}

void applyToAllChannels(unsigned char* pixels, unsigned int width, unsigned int height) {
	for (unsigned int x = 0; x < width; x++) {
		for (unsigned int y = 0; y < height; y++) {
			pixels[3 * width * y + 3 * x + 1] = pixels[3 * width * y + 3 * x];
			pixels[3 * width * y + 3 * x + 2] = pixels[3 * width * y + 3 * x];
		}
	}
}

void grayScale(unsigned char* pixels, unsigned int width, unsigned int height) {
	for (unsigned int x = 0; x < width; x++) {
		for (unsigned int y = 0; y < height; y++) {
			short gray = pixels[3 * width * y + 3 * x + 0] * 0.299 + pixels[3 * width * y + 3 * x + 1] * 0.587 + pixels[3 * width * y + 3 * x + 2] * 0.114;
			pixels[3 * width * y + 3 * x] = gray;
		}
	}
	applyToAllChannels(pixels, width, height);
}

void setBrightness(unsigned char* pixels, unsigned int width, unsigned int height, int _brightness) {
	for (unsigned int x = 0; x < width; x++) {
		for (unsigned int y = 0; y < height; y++) {
			short value = pixels[3 * width * y + 3 * x] + _brightness;
			if (value < 0) value = 0;
			if (value > 255) value = 255;
			pixels[3 * width * y + 3 * x] = (char)value;
		}
	}
	applyToAllChannels(pixels, width, height);
}

void setContrast(unsigned char* pixels, unsigned int width, unsigned int height, double _contrast) {
	for (unsigned int x = 0; x < width; x++) {
		for (unsigned int y = 0; y < height; y++) {
			double value = (double)pixels[3 * width * y + 3 * x] * (double)_contrast;
			if (value < 0) value = 0;
			if (value > 255) value = 255;
			pixels[3 * width * y + 3 * x] = (char)value;
		}
	}
	applyToAllChannels(pixels, width, height);
}

void setGamma(unsigned char* pixels, unsigned int width, unsigned int height, double gamma) {
	for (unsigned int x = 0; x < width; x++) {
		for (unsigned int y = 0; y < height; y++) {
			double value = pow(pixels[3 * width * y + 3 * x], gamma);
			if (value < 0) value = 0;
			if (value > 255) value = 255;
			pixels[3 * width * y + 3 * x] = (char)value;
		}
	}
	applyToAllChannels(pixels, width, height);
}

void normalizeHistogram(unsigned char* pixels, unsigned int width, unsigned int height) {
	int lut[256];
	unsigned char minVal = 255;
	unsigned char maxVal = 0;
	for (unsigned int x = 0; x < width; x++) {
		for (unsigned int y = 0; y < height; y++) {
			if (pixels[3 * width * y + 3 * x] < minVal)
				minVal = pixels[3 * width * y + 3 * x];
			if (pixels[3 * width * y + 3 * x] > maxVal)
				maxVal = pixels[3 * width * y + 3 * x];
		}
	}
	for (unsigned int i = 0; i < 256; i++) {
		lut[i] = 255.0 / (maxVal - minVal) * (i - minVal);
		if (lut[i] < 0) lut[i] = 0;
		if (lut[i] > 255) lut[i] = 255;
	}
	for (unsigned int x = 0; x < width; x++) {
		for (unsigned int y = 0; y < height; y++) {
			pixels[3 * width * y + 3 * x] = lut[pixels[3 * width * y + 3 * x]];
		}
	}
	applyToAllChannels(pixels, width, height);
}

void equalHistogram(unsigned char* pixels, unsigned int width, unsigned int height) {
	unsigned int h[256];
	for (unsigned int i = 0; i < 256; i++) h[i] = 0;
	for (unsigned int x = 0; x < width; x++) {
		for (unsigned int y = 0; y < height; y++) {
			h[pixels[3 * width * y + 3 * x]]++;
		}
	}
	unsigned int s = width * height;
	double dystr[256];
	for (unsigned int i = 0; i < 256; i++) {
		dystr[i] = 0.0;
		for (unsigned int j = 0; j < i+1; j++) dystr[i] += h[j];
		dystr[i] /= (double)s;
	}
	unsigned int i0 = 0;
	while (dystr[i0] == 0.0) i0++;
	double d0 = dystr[i0];
	unsigned int lut[256];
	for (unsigned int i = 0; i < 256; i++) {
		lut[i] = int(255.0 * (dystr[i] - d0) / (1 - d0));
	}
	for (unsigned int x = 0; x < width; x++) {
		for (unsigned int y = 0; y < height; y++) {
			pixels[3 * width * y + 3 * x] = lut[pixels[3 * width * y + 3 * x]];
		}
	}
	applyToAllChannels(pixels, width, height);
}

void multiplicate(unsigned char* pixels, unsigned char* pixels2, unsigned int width, unsigned int height) {
	for (unsigned int x = 0; x < width; x++) {
		for (unsigned int y = 0; y < height; y++) {
			pixels[3 * width * y + 3 * x] = (pixels[3 * width * y + 3 * x] * pixels2[3 * width * y + 3 * x] / 255);
		}
	}
	applyToAllChannels(pixels, width, height);
}

void interlace(unsigned char* pixels, unsigned char* pixels2, unsigned int width, unsigned int height, double contribution) {
	for (unsigned int x = 0; x < width; x++) {
		for (unsigned int y = 0; y < height; y++) {
			pixels[3 * width * y + 3 * x] = pixels2[3 * width * y + 3 * x] * contribution + pixels[3 * width * y + 3 * x] * (1 - contribution);
		}
	}
	applyToAllChannels(pixels, width, height);
}