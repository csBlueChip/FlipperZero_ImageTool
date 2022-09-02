// Sample code for displaying an image on a FZ

#include  <gui/gui.h>      // GUI (screen/keyboard) API

#include  "images.h"

//----------------------------------------------------------------------------- ----------------------------------------
// This will be the plot function out of your graphics library
//
#define  PLOT(x,y,c) do { \
	canvas_set_color(canvas, (c ? ColorBlack : ColorWhite));  \
	canvas_draw_dot(canvas, (tlx +x), (tly +y));              \
}while(0)

//============================================================================= ========================================
// The pain we endure to avoid code duplication cleanly
//
#define  PLOTBYTE(b)  do { \
	for (uint8_t m = 0x80;  m;  m>>=1) {                                    \
		PLOT(x,y, (b & m));                                                 \
		if ( ((++x) == img->w) && !(x = 0) && ((++y) == img->h) )  break ;  \
	}                                                                       \
}while(0)

//+============================================================================
void  show (Canvas* const canvas,  const uint8_t tlx,  const uint8_t tly,  const image_t* img)
{
	// Some variables
	const uint8_t*  bp = img->data;
	unsigned int    x  = 0;
	unsigned int    y  = 0;

	// Compressed
	if (img->c) {
		for (unsigned int i = 0;  i < img->len;  i++, bp++) {
			// Compressed data? {tag, length, value}
			if (*bp == img->tag) {
				for (uint16_t c = 0;  c < bp[1];  c++)  PLOTBYTE(bp[2]) ;
				bp += 3 -1;
				i  += 3 -1;

			// Uncompressed byte
			} else {
				PLOTBYTE(*bp);
			}
		}

	// Not compressed
	} else {
		for (unsigned int i = 0;  i < img->len;  i++, bp++)  PLOTBYTE(*bp) ;
	}
}

#undef  PLOTBYTE
