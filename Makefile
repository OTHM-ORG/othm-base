all: libothm_base.so

libothm_base.so: othm_base.o
	gcc -shared -o libothm_base.so othm_base.o
othm_base.o: othm_base.c othm_base.h
	gcc -c -Wall -Werror -fPIC othm_base.c -o othm_base.o

.PHONY : clean install uninstall test
clean :
	-rm  othm_base.o libothm_base.so test
install :
	cp othm_base.h /usr/include/
	cp othm_cpp.h /usr/include/
	cp libothm_base.so /usr/lib/
	ldconfig
uninstall :
	-rm  /usr/include/othm_base.h
	-rm  /usr/include/othm_cpp.h
	-rm  /usr/lib/libothm_base.so
	ldconfig
test :
	gcc -o test test.c -lothm_base
	./test
