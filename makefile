OBJS	= obj/BK.o obj/Liste.o obj/Auxiliaire.o obj/Levenshtein.o obj/ATR.o 
CFLAGS = -Wall -ansi -pedantic
CC = gcc -c 
TARGET = correcteur_0 correcteur_1 correcteur_2


all : $(TARGET)

correcteur_2 : $(OBJS) obj/correcteur_2.o
	gcc -o $@ $^

correcteur_1 : $(OBJS) obj/correcteur_1.o
	gcc -o $@ $^

correcteur_0 : $(OBJS) obj/correcteur_0.o
	gcc -o $@ $^

obj/correcteur_0.o : src/correcteur_0.c src/Liste.h src/ATR.h src/Auxiliaire.h
	$(CC) -o $@ $< 

obj/correcteur_1.o : src/correcteur_1.c src/Liste.h src/ATR.h src/Auxiliaire.h src/Levenshtein.h
	$(CC) -o $@ $< $(CFLAGS)

obj/correcteur_2.o: src/correcteur_2.c src/Liste.h src/BK.h src/Auxiliaire.h src/Levenshtein.h
	$(CC) -o $@ $< $(CFLAGS)

obj/BK.o: src/BK.c src/BK.h src/Liste.h src/Levenshtein.h src/ATR.h
	$(CC) -o $@ $< $(CFLAGS)

obj/Liste.o: src/Liste.c src/Liste.h
	$(CC) -o $@ $< $(CFLAGS)

obj/Auxiliaire.o : src/Auxiliaire.c src/Auxiliaire.h
	$(CC) -o $@ $< $(CFLAGS)

obj/Levenshtein.o : src/Levenshtein.c src/Levenshtein.h src/ATR.h src/Liste.h
	$(CC) -o $@ $< $(CFLAGS)

obj/ATR.o : src/ATR.c src/ATR.h
	$(CC) -o $@ $< $(CFLAGS)

clean : 
	rm -f $(OBJS)

mrproper : clean
	rm -f obj/*.o
	rm -f obj/nouveau
	rm -f $(TARGET)
	rm -f texte_propre
	rm -f arbre.dot