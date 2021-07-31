define art                
(ɔ◔‿◔)ɔ ♥
endef
export art

CC := em++

all: clear init compwasm end

init:
	@echo "Compilando, meu consagrado"

end: 
	@echo "Terminei! Hacking is good $$art"

compwasm: nnrz.cpp
	@${CC} $^ -O3 -s WASM=1 -s EXPORTED_RUNTIME_METHODS='["cwrap", "ccall"]' -o tt.js

clear: 
	@echo "Removendo os arquivos..."
	@rm -rf tt.js tt.wasm