cd ./Plexiglass_V_1
make clean

cd ../MM_Common
make clean
rm -R ./include/plex

cd ../MM_SideTales
make clean
rm -R ./include/plex
rm -R ./include/mm_common
rm -R ./include/mm_common/plex
