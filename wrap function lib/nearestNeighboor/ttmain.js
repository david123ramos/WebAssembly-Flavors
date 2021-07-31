
const api = {
    createBuffer: Module.cwrap("createBuffer", "number", ["number", "number"]),
    clearBuffer: Module.cwrap("clearBuffer", "", ["number"]),

    encode: Module.cwrap("encode", "", ["number", "number","number" , "number", "number", "number"]),
    getResultPointer: Module.cwrap("get_result_pointer", "number", []),
    getResultSize: Module.cwrap("get_result_size", "number", []),
}


var  p  =  api.createBuffer(largecv.width, largecv.height);

var img = largecv.getContext("2d").getImageData(0,0, largecv.width, largecv.height);
Module.HEAP8.set(img.data,p);


var c  = api.createBuffer(28, 28);
Module.HEAP8.set(new Array(28 * 28 * 4), c);

api.encode(p, c, largecv.width, largecv.height, 28, 28)

var rvw = new Uint8Array(Module.HEAP8.buffer, c, 28*28*4);

var smalldata = smallCtx.getImageData(0,0,smallcv.width, smallcv.height);

for(let i =0; i< smalldata.data.length; i+=4 ) {
    smalldata.data[i]   = rvw[i];
    smalldata.data[i+1] = rvw[i+1];
    smalldata.data[i+2] = rvw[i+2];
    smalldata.data[i+3] = rvw[i+3];
}