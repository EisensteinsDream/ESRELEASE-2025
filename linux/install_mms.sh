cd ./Plexiglass_V_1
make RECFOLDER=../resources/ HEADERLESSDIRECTORY=../headerlesstex/ ERRORDIRECTORY=MM_SideTales/error/ rebuild

cd ../MM_Common
make clean
rm -R ./include/plex
mkdir ./include/plex
cp ../Plexiglass_V_1/lib/release/libPLEX.so ./lib/release
cp -R ../Plexiglass_V_1/include/* ./include/plex/
make all

cd ../MM_SideTales
make clean
rm -R ./include/plex
mkdir ./include/plex
cp ../Plexiglass_V_1/lib/release/libPLEX.so ./lib/release
cp -R ../Plexiglass_V_1/include/* ./include/plex/
rm -R ./include/mm_common
mkdir ./include/mm_common
cp ../MM_Common/lib/release/libMM_COMMON.so ./lib/release
cp -R ../MM_Common/include/* ./include/mm_common/
rm -R ./include/mm_common/plex
make all
