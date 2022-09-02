#ifndef  IMAGES_H_
#define  IMAGES_H_

#include <stdint.h>
#include <stdbool.h>

typedef
	struct image {
		uint8_t   w;       // width
		uint8_t   h;       // height
		bool      c;       // compressed?
		uint16_t  len;     // image data length
		uint8_t   tag;     // rle tag
		uint8_t   data[];  // image data
	} 
image_t;

//[TAG]
extern  const image_t  img_classic;
extern  const image_t  img_ZR3;
extern  const image_t  img_ZR2;
extern  const image_t  img_ZR1;
extern  const image_t  img_ZL3;
extern  const image_t  img_ZL2;
extern  const image_t  img_ZL1;
extern  const image_t  img_Y1;
extern  const image_t  img_X1;
extern  const image_t  img_UD1;
extern  const image_t  img_LR1;
extern  const image_t  img_B1;
extern  const image_t  img_A1;

#ifndef IMGTEST
#	include <gui/gui.h>
	void  show (Canvas* const canvas,  const uint8_t tlx,  const uint8_t tly,  const image_t* img) ;
#endif


#endif //IMAGES_H_
