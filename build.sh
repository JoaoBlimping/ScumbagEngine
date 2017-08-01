# $1 -> src directory
# $2 -> output file
# $3 -> flags

CC=gcc
FILES='Image.c ini.c LinkedList.c load.c render.c Level.c Bullet.c HashMap.c BulletGroup.c main.c gui.c font.c scenes/Scene.c scenes/Gameplay.c tmx/tmx_err.c tmx/tmx_utils.c tmx/tmx_xml.c tmx/tmx.c'
FLAGS=`xml2-config --cflags`
LIBS='-lSDL2 -lSDL2_image -lSDL2_ttf -lm'
DIR=`pwd`

cd $1
$CC $FLAGS $FILES $LIBS `xml2-config --libs` $3 -o $DIR/$2
cd $DIR
