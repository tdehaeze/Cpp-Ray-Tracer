main: main.cpp
		g++ -Wall -o main main.cpp Vector.cpp Ray.cpp Sphere.cpp Light.cpp Scene.cpp Material.cpp -Dcimg_display=0

clean:
		rm -f *~

mrproper:
		rm -f hello

watch:
		fswatch -r ./*.cpp | xargs -n1 make
