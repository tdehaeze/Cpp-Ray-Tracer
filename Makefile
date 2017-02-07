main: main.cpp
		g++ -Wall -o main.o *.cpp -O1 -O2 -Dcimg_display=0

clean:
		rm -f *~

mrproper:
		rm -f hello

watch:
		fswatch -r ./*.cpp | xargs -n1 make
