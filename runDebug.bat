g++ -c *.cpp -c -std=c++14 -g -Wall -m64 -I myEngine/headerFiles -I C:/SDL2-w64/include && g++ *.o -o bin/debug/main -L C:/SDL2-w64/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image && start bin/debug/main