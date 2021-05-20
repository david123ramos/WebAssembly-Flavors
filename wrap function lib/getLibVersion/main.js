
Module.onRuntimeInitialized = async _ => {
    const api = {
        version: Module.cwrap("version", "number", []),
    }

    console.log(api.version());
}

// emcc -O3 -s WASM=1 -s EXTRA_EXPORTED_RUNTIME_METHODS='["cwrap"]' -I libwebp webp.c libwebp/src/{dec,dsp,demux,enc,mux,utils}/*.c