make:
	g++ -o main -g -Wall *.cpp 
clean:
	rm main
val:
	valgrind -v --tool=memcheck --leak-check=full --track-origins=yes ./main
