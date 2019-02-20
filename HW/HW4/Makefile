all:
	flex compiler.l
	gcc lex.yy.c -o compiler -lfl

clean:
	rm -rf *.c
	rm -rf compiler
	rm -rf *.ac
	rm -rf *.out

test:
	flex compiler.l
	gcc lex.yy.c -o compiler -lfl
	python3 code_generator.py > example.ac

	./compiler example.ac > lex.out
	tail lex.out

test-stress:
	flex compiler.l
	gcc lex.yy.c -o compiler -lfl
	python3 code_generator.py --stress

	./compiler random_code.ac > lex.out
	tail lex.out