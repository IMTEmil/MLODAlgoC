FLAGS= -std=c11 -Wall -Wextra

test: Spitofy
	./Spitofy "music.csv" > sortie.txt
	diff sortie.txt music.csv
	./Spitofy "music.csv" -sort > sorted_list.txt
	
Spitofy: linkedList.c linkedListOfMusic.c Spitofy.c
	gcc $(FLAGS) -o Spitofy linkedList.c linkedListOfMusic.c Spitofy.c 

clean:
	rm -rf Spitofy
	rm -rf sortie.txt
	rm -rf sorted_list.txt
