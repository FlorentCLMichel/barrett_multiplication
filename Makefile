.PHONY: build_static
build_static:
	mkdir -p build
	cd build; \
		cmake ..; \
		make

.PHONY: build_dynamic
build_dynamic:
	mkdir -p build
	cd build; \
		cmake .. -DBUILD_DYNAMIC=ON; \
		make

.PHONY: examples
examples: 
	mkdir -p build
	cd build; \
		cmake .. -DBUILD_EXAMPLES=ON; \
		make

.PHONY: doc
doc:
	doxygen doxygen_format.txt

open-doc:
	xdg-open ./doc/html/index.html

clean: 
	rm -rf build
	rm -rf doc
