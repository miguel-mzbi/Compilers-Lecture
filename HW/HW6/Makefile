all:
	

clean:
	rm -rf *.ac
	rm -rf *.out

tokens:
	flex compiler.l
	gcc lex.yy.c -o lexical_analyzer.out -lfl
	python3 code_generator.py > random_code.ac

	./lexical_analyzer.out random_code.ac > tokens.out

tokens-stress:
	flex compiler.l
	gcc lex.yy.c -o lexical_analyzer.out -lfl
	python3 code_generator.py --stress

	./lexical_analyzer.out random_code.ac > tokens.out

grammar-analyzer:
	python grammar_analyzer.py cfg.txt
	python CFGtoBNF.py cleanCFG.out

parse:
	gcc syntax_calc.c -o syntax-calc.out
	./syntax-calc.out tokens.out