# $1 -> src directory
# $2 -> output file
# $3 -> flags

CC=gcc
FILES='main.c Image.c ini.c LinkedList.c load.c render.c Tileset.c'
FLAGS='-lSDL2 -lSDL2_image'
DIR=`pwd`

cd $1
$CC $FILES -w $FLAGS $3 -o $DIR/$2
cd $DIR
