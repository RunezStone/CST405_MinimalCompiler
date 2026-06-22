CC      = gcc
LEX     = flex
YACC    = bison
CFLAGS  = -g -Wall

TARGET  = oomini
OBJS    = lex.yy.o parser.tab.o main.o ast.o symtab.o semantic.o tac.o codegen.o flawcheck.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

lex.yy.c: scanner.l parser.tab.h
	$(LEX) scanner.l

parser.tab.c parser.tab.h: parser.y
	$(YACC) -d parser.y

lex.yy.o: lex.yy.c
	$(CC) $(CFLAGS) -c lex.yy.c

parser.tab.o: parser.tab.c
	$(CC) $(CFLAGS) -c parser.tab.c

main.o: main.c ast.h semantic.h tac.h codegen.h symtab.h
	$(CC) $(CFLAGS) -c main.c

ast.o: ast.c ast.h
	$(CC) $(CFLAGS) -c ast.c

symtab.o: symtab.c symtab.h
	$(CC) $(CFLAGS) -c symtab.c

semantic.o: semantic.c semantic.h ast.h symtab.h
	$(CC) $(CFLAGS) -c semantic.c

tac.o: tac.c tac.h ast.h symtab.h semantic.h
	$(CC) $(CFLAGS) -c tac.c

codegen.o: codegen.c codegen.h ast.h symtab.h semantic.h
	$(CC) $(CFLAGS) -c codegen.c

flawcheck.o: flawcheck.c flawcheck.h ast.h
	$(CC) $(CFLAGS) -c flawcheck.c

clean:
	rm -f $(TARGET) $(OBJS) lex.yy.c parser.tab.c parser.tab.h *.s *.tac

.PHONY: all clean
