all:	cipher

cipher:	cipher.o Playfair.o RowTransposition.o RailFence.o Vigenere.o Ceasar.o Hill.o
	g++ cipher.o RowTransposition.o Playfair.o RailFence.o Vigenere.o Ceasar.o Hill.o -o cipher

cipher.o:	cipher.cpp
	g++ -g -c cipher.cpp 

Playfair.o:	Playfair.cpp Playfair.h CipherInterface.h
	g++ -g -c Playfair.cpp

RowTransposition.o:	RowTransposition.cpp RowTransposition.h CipherInterface.h
	g++ -g -c RowTransposition.cpp

RailFence.o: 	RailFence.cpp RailFence.h CipherInterface.h
	g++ -g -c RailFence.cpp

Vigenere.o: 	Vigenere.cpp Vigenere.h CipherInterface.h
	g++ -g -c Vigenere.cpp 

Ceasar.o: 	Ceasar.cpp Ceasar.h CipherInterface.h
	g++ -g -c Ceasar.cpp

Hill.o: 	Hill.cpp Hill.h CipherInterface.h
	g++ -g -c Hill.cpp

clean:
	rm -rf *.o cipher
