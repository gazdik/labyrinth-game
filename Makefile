#Authors: Peter Gazdik, Klara Mihalikova

QMAKE = qmake

bin:
	cd src/; $(QMAKE) project.pro; $(MAKE); mv labyrinth2015 ../

.PHONY: clean doxygen pack run
clean:
	rm -f xgazdi03-xmihal05.tar.gz labyrinth2015
	rm -rf doc/
	cd src/; $(MAKE) clean; rm -f Makefile

doxygen:
	doxygen Doxyfile

pack:
	tar -cvzf xgazdi03-xmihal05.tar.gz src/ examples/ Makefile README.txt Doxyfile

run: bin
	./labyrinth2015
