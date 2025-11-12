phonebook: mini5main.o mini5phone.o
	gcc -o phonebook mini5main.o mini5phone.o
mini5main.o: mini5main.c
	gcc -c mini5main.c
mini5phone.o: mini5phone.c
	gcc -c mini5phone.c
backup:
	cp *.c ../backup
