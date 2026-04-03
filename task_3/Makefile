all: game

game: Knight.o Mage.o Archer.o Skeleton.o SkeletonKnight.o Necromancer.o main.o
	g++ -g Knight.o Mage.o Archer.o Skeleton.o SkeletonKnight.o Necromancer.o main.o -o game

Knight.o: Knight.cpp Knight.h Character.h
	g++ -std=c++23 -g -c Knight.cpp -o Knight.o

Mage.o: Mage.cpp Mage.h Character.h
	g++ -std=c++23 -g -c Mage.cpp -o Mage.o

Archer.o: Archer.cpp Archer.h Character.h
	g++ -std=c++23 -g -c Archer.cpp -o Archer.o

Skeleton.o: Skeleton.cpp Skeleton.h Character.h
	g++ -std=c++23 -g -c Skeleton.cpp -o Skeleton.o

SkeletonKnight.o: SkeletonKnight.cpp SkeletonKnight.h Skeleton.h Knight.h Character.h
	g++ -std=c++23 -g -c SkeletonKnight.cpp -o SkeletonKnight.o

Necromancer.o: Necromancer.cpp Necromancer.h Mage.h SkeletonKnight.h Character.h
	g++ -std=c++23 -g -c Necromancer.cpp -o Necromancer.o

main.o: main.cpp Character.h Knight.h Mage.h Archer.h SkeletonKnight.h Necromancer.h
	g++ -std=c++23 -g -c main.cpp -o main.o

clean:
	rm -f *.o game

run: game
	./game