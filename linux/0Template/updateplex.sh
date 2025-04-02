cd ../Plexiglass_V_1
make "RECFOLDER=./resources/" "HEADERLESSDIRECTORY=./headerlesstex/" "ERRORDIRECTORY=./(DIRECTORYNAME)/error" all
cd  ../(DIRECTORYNAME)

rm -R ./include/plex
mkdir ./include/plex
cp -R ../Plexiglass_V_1/include/* ./include/plex

rm ./lib/release/libPLEX.so
rm ./lib/debug/libPLEX.so

cp ../Plexiglass_V_1/lib/release/libPLEX.so ./lib/release/
cp ../Plexiglass_V_1/lib/debug/libPLEX.so ./lib/debug/

rm -R ./resources/plex
mkdir ./resources/plex
cp -R ../Plexiglass_V_1/resources/plex/* ./resources/plex/
