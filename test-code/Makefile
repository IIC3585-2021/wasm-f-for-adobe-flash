
EMCC=emcc

all: main.c
	$(EMCC) -O3 -s WASM=1 -s EXPORT_ES6=1 -s EXPORTED_FUNCTIONS="['_findbest','_malloc']" -s EXPORTED_RUNTIME_METHODS=["intArrayFromString","ALLOC_NORMAL","allocate","UTF8ToString"] -s ASSERTIONS=1 -o findbestWASM.js main.c