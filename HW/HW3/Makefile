all:
	gcc lex.c -o lex

clean:
	rm -rf lex lex.out example.ac random_code.ac a.out

test:
	gcc lex.c -o lex
	python3 code_generator.py > example.ac
	./lex example.ac
	tail lex.out

test-stress:
	gcc lex.c -o lex
	python3 code_generator.py --stress
	./lex random_code.ac
	tail lex.out