.PHONY: build
build:
	mkdir -p build
	cd build; \
		cmake ..; \
		make

.PHONY: doc
doc:
	doxygen doxygen_format.txt

open-doc:
	xdg-open ./doc/html/index.html

clean: 
	rm -rf build
	rm -rf doc
