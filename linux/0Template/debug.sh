export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:./lib/debug

make debug && kdbg ./bin/debug/main
