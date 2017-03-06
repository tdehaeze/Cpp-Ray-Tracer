main: main.cpp
		clang-omp++ -Wall -g -std=c++11 -fopenmp -o main.o *.cpp -Dcimg_display=0
		# clang-omp++ -Wall -g -std=c++11 -fopenmp -o main.o *.cpp -O1 -O2 -Dcimg_display=0

clean:
		rm -f *~

mrproper:
		rm -f hello

watch:
		fswatch -r ./*.cpp | xargs -n1 make

tags:
		ctags -R .
