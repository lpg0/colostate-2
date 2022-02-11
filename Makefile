all: generator lucas hexagonal harmonic

generator: Generator.c
	gcc -o generator Generator.c

lucas: Lucas.c
	gcc -o lucas Lucas.c

hexagonal: HexagonalSeries.c
	gcc -o hexagonal HexagonalSeries.c

harmonic: HarmonicSeries.c
	gcc -o harmonic HarmonicSeries.c

clean:
	rm -f generator.o lucas.o hexagonal.o harmonic.o
