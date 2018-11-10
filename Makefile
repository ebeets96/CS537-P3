537make:      main.o     build_spec_graph.o    text_parsing.o build_spec_repr.o proc_creation_prog_exe.o
	gcc -g -o 537make main.o build_spec_graph.o text_parsing.o build_spec_repr.o proc_creation_prog_exe.o -lpthread

main.o:main.c build_spec_graph.h text_parsing.h build_spec_repr.h proc_creation_prog_exe.h
	gcc -g -Wall -Wextra -c main.c

build_spec_graph.o: build_spec_graph.c build_spec_graph.h
	gcc -g -Wall -Wextra -c build_spec_graph.c

text_parsing.o: text_parsing.c text_parsing.h
	gcc -g -Wall -Wextra -c text_parsing.c

build_spec_repr.o: build_spec_repr.c build_spec_repr.h
	gcc -g -Wall -Wextra -c build_spec_repr.c

proc_creation_prog_exe.o: proc_creation_prog_exe.c proc_creation_prog_exe.h
	gcc -g -Wall -Wextra -c proc_creation_prog_exe.c

clean: recompile
	rm -f 537make *.o

recompile: clean

testing: recompile
	cp 537make testing/

clang: clean
	scan-build -o scan-build-out make
