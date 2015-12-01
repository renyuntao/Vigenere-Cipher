CC = g++
OBJ = vigenere_cipher.o
CFLAG = -std=gnu++11

vigenere_cipher: $(OBJ)
	$(CC) -o $@ $^

%.o: %.cxx
	$(CC) $(CFLAG) -c -o $@ $^

clean:
	rm *.o vigenere_cipher
