#ifndef  IMAGES_H_
#define  IMAGES_H_

#include <stdint.h>
#include <stdbool.h>

#ifndef IMGTEST
void  show (Canvas* const canvas,  const uint8_t tlx,  const uint8_t tly,  const image_t* img) ;
#endif

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

#endif //IMAGES_H_
