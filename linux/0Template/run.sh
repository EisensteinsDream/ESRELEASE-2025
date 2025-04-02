export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:./lib/release

make release && ./bin/release/main
