ttfpatch: build/ttfpatch.o build/woktools.o
	g++ -o $@ $^
	

build/%.o: src/%.cpp
	g++ -Isrc -o $@ -c $<
