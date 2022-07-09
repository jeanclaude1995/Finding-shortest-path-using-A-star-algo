OBJ = status.o List.o aStar.o City.o main.o
aStar: $(OBJ)
	gcc -o aStar $(OBJ)

status.o: status.c status.h
	gcc -c status.c

List.o: List.c List.h status.h
	gcc -c List.c


City.o: City.c City.h status.h

	gcc -c City.c


aStar.o: aStar.c aStar.h List.h City.h status.h

	gcc -c aStar.c


main.o: main.c aStar.h City.h List.h status.h

	gcc -c main.c