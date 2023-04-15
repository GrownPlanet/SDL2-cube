g++ -c *.cpp -std=c++14 -O3 -Wall -m64 -I C:/SDL2-w64/include && g++ *.o -o bin/release/main -s -L C:/SDL2-w64/lib -lmingw32 -lSDL2main -lSDL2 && start bin/release/main
