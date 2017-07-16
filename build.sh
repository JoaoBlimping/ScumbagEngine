# $1 -> src directory
# $2 -> output file
# $3 -> flags

CC=gcc
FILES='main.c Image.c ini.c LinkedList.c load.c render.c Level.c tmx/tmx_err.c tmx/tmx_utils.c tmx/tmx_xml.c tmx/tmx.c'
FLAGS=`xml2-config --cflags`
LIBS='-lSDL2 -lSDL2_image -lm'
DIR=`pwd`

cd $1
$CC $FLAGS $FILES -w $LIBS `xml2-config --libs` $3 -o $DIR/$2
cd $DIR
