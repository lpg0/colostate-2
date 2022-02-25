all: starter reader lucas hexagonal harmonic

starter: Starter.c
	gcc -lrt -o starter Starter.c

reader: Reader.c
	gcc -o reader Reader.c

lucas: Lucas.c
	gcc -lrt -o lucas Lucas.c

hexagonal: HexagonalSeries.c
	gcc -lrt -o hexagonal HexagonalSeries.c

harmonic: HarmonicSeries.c
	gcc -lrt -o harmonic HarmonicSeries.c

clean:
	rm -f starter.o reader.o lucas.o hexagonal.o harmonic.o
