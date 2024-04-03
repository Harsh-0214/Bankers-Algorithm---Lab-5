banker: main.c Banker.c
	gcc -o banker main.c Banker.c
	./banker 10 5 7
clean:
	rm -f banker
