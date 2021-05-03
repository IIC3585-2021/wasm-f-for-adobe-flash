
EMCC=emcc

all: main.c
	$(EMCC) -O3 -s WASM=1 -s TOTAL_MEMORY=512mb -s EXPORT_ES6=1 -s EXPORTED_FUNCTIONS="['_fib','_malloc']" -s EXTRA_EXPORTED_RUNTIME_METHODS=["intArrayFromString","ALLOC_NORMAL","allocate","UTF8ToString"] -s ASSERTIONS=1 -o fibWASM.js main.c