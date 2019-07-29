faro_shuffle : faro_shuffle.c shuffle_methods.c list_methods.c faro_shuffle.h
		clang -o faro_shuffle faro_shuffle.c shuffle_methods.c list_methods.c -lm
clean:
		rm faro_shuffle
