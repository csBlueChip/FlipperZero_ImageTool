#!/bin/bash

[ -z $1 ] && {
	echo "specify file.h"
	exit 2
}

[ ! -f $1 ] && {
	echo "file missing $F"
	exit 1
}

# filename (sans extension)
F=${1%%.*}
echo "¦$F¦"

# compile name
C=${F}_

# clean up gimp output
sed -e "s/gimp_image/img/g" \
	-e 's/guint8/unsigned char/g' \
	-e 's/width/w/g' \
	-e 's/height/h/g' \
	-e 's/bytes_per_pixel/bpp/g' \
	-e 's/pixel_data/b/g' \
	-e 's/guint/unsigned int/g' \
	$1 \
	| grep -v ^/ \
	| grep -v ^$ \
	> ${C}.c

# append conversion code
cat _convert.c >> ${C}.c

# compile & run converter
rm -f ${C}
gcc ${C}.c -o ${C}
./${C} ${F} img_${F}.c
rm ${C} ${C}.c

# (create &) update header
[[ ! -f images.h ]] && cp _convert.h images.h
sed -i "/img_${F}/d" images.h
sed -i "s#//\[TAG\]#//\[TAG\]\nextern  const image_t  img_${F};#" images.h

# test
sed "s/zzz/${F}/" _convert_test.c > img_${F}_test.c
rm -f img_${F}
gcc img_${F}_test.c img_${F}.c -o img_${F}
./img_${F}
rm -f img_${F} img_${F}_test.c
