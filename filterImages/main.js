const getRBGFromImage = async function(src) {
 
    const blob = await fetch(src).then(r => r.blob());
    const img = await createImageBitmap(blob);

    const canvas = document.createElement("canvas");
    canvas.width = img.width;
    canvas.height = img.height;

    document.querySelector("#panel").appendChild(canvas);
    const ctx = canvas.getContext("2d");


    ctx.drawImage(img, 0, 0);
    const imageData =  ctx.getImageData(0, 0, img.width, img.height);
    
    rgbArray = []
    for (var i = 0; i < imageData.data.length; i+=4) {
        rgbArray.push([imageData.data[i], imageData.data[i+1], imageData.data[i+2]]);
    }
    
    return {
        rgbArray,
        w: img.width,
        h: img.height
    };
}


const api = {
    createBuffer: Module.cwrap("createBuffer", "number", ["number", "number"]),
    clearBuffer: Module.cwrap("clearBuffer", "", ["number"]),

    sepia: Module.cwrap("sepia", "", ["number", "number", "number", "number", "number"]),
    freeResult: Module.cwrap("free_result", "", ["number"]),
    getResultPointer: Module.cwrap("get_result_pointer", "number", []),
    getResultSize: Module.cwrap("get_result_size", "number", []),
}



async function init() {
    const img = await getRBGFromImage("./img.jpeg");
    const  p = api.createBuffer(img.w, img.h);
    Module.HEAP8.set(img.rgbArray, p);

    api.sepia(p, img.width, img.height, 100);
    const rp = api.getResultPointer();
    const rs = api.getResultSize();

    const rvw = new Uint8Array(Module.HEAP8.buffer, rp, rs);
    const r = new Uint8Array(rvw);

    const bl = new Blob([r], {type: "image/webp"});
    const url = URL.createObjectURL(bl);
    const im = document.createElement("img");
    im.src = url;
    document.querySelector("#result").appendChild(im);


    api.freeResult();

    api.clearBuffer(p);

}
