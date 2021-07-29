
async function init(img) {


    var len = img.data.length;
    var bytes_per_element = img.data.BYTES_PER_ELEMENT;


    const p = Module._malloc(len * bytes_per_element);
    Module.HEAP8.set(img.data, p);

    const t1 = performance.now();
    const response = Module.resizeNearestNeighboor(p, len, img.width, img.height, 28, 28);
    const t2 = performance.now();

    console.log(t2 - t1);

    var output_array = new Uint8ClampedArray(response);
    const smallData = smallCtx.getImageData(0, 0, smallcv.width, smallcv.height);


    for (let i = 0; i < smallData.data.length; i++) {
        smallData.data[i] = output_array[i];
    }

    smallCtx.putImageData(smallData, 0, 0);

    Module._free(p);

}


const largecv = document.querySelector("#largecv");
const smallcv = document.querySelector("#smallcv");
const processBtn = document.querySelector("#process");



/** @type {CanvasRenderingContext2D} */
const smallCtx = smallcv.getContext("2d");

smallCtx.fillStyle = "black";
smallCtx.fillRect(0, 0, 28, 28);


const newSize = 28;



function processing() {

    const largecv = document.querySelector("#largecv");
    const largeCtx = largecv.getContext("2d");
    const largeData = largeCtx.getImageData(0, 0, largecv.width, largecv.height);

    init(largeData, newSize, newSize);


}




function nearestNeighborResize(srcImageData, width, height) {
    const srcPixels = srcImageData.data;
    const srcWidth = srcImageData.width;

    const srcHeight = srcImageData.height;
    const dstImageData = smallCtx.createImageData(width, height);
    const dstPixels = dstImageData.data;


    const xFactor = srcWidth / width;

    const yFactor = srcHeight / height;
    let dstIndex = 0;
    let srcIndex, x, y, offset;

    for (y = 0; y < height; y += 1) {
        offset = ((y * yFactor) | 0) * srcWidth;

        for (x = 0; x < width; x += 1) {
            srcIndex = (offset + x * xFactor) << 2;

            dstPixels[dstIndex] = srcPixels[srcIndex];
            dstPixels[dstIndex + 1] = srcPixels[srcIndex + 1];
            dstPixels[dstIndex + 2] = srcPixels[srcIndex + 2];
            dstPixels[dstIndex + 3] = srcPixels[srcIndex + 3];
            dstIndex += 4;
        }
    }

    return dstImageData;
}



// MIT http://rem.mit-license.org
function trimCanvas(c) {

    var ctx = c.getContext('2d'),
        copy = document.createElement('canvas').getContext('2d'),
        pixels = ctx.getImageData(0, 0, c.width, c.height),
        l = pixels.data.length,
        i,
        bound = {
            top: null,
            left: null,
            right: null,
            bottom: null
        },
        x, y;

    // Iterate over every pixel to find the highest
    // and where it ends on every axis ()
    for (i = 0; i < l; i += 4) {
        if (pixels.data[i + 3] !== 0) {
            x = (i / 4) % c.width;
            y = ~~((i / 4) / c.width);

            if (bound.top === null) {
                bound.top = y;
            }

            if (bound.left === null) {
                bound.left = x;
            } else if (x < bound.left) {
                bound.left = x;
            }

            if (bound.right === null) {
                bound.right = x;
            } else if (bound.right < x) {
                bound.right = x;
            }

            if (bound.bottom === null) {
                bound.bottom = y;
            } else if (bound.bottom < y) {
                bound.bottom = y;
            }
        }
    }

    // Calculate the height and width of the content
    var trimHeight = bound.bottom - bound.top,
        trimWidth = bound.right - bound.left,
        trimmed = ctx.getImageData(bound.left, bound.top, trimWidth, trimHeight);

    copy.canvas.width = trimWidth;
    copy.canvas.height = trimHeight;
    copy.canvas.classList.add("trimmedCv");
    copy.putImageData(trimmed, 0, 0);

    // Return trimmed canvas
    return copy.canvas;
}




window.addEventListener('load', () => {

    resize(); // Resizes the canvas once the window loads
    document.getElementById('clearBtn').addEventListener('click', clearCanvas);
    document.getElementById('process').addEventListener('click', processing);
    document.addEventListener('mousedown', startPainting);
    document.addEventListener('mouseup', stopPainting);
    document.addEventListener('mousemove', sketch);
    window.addEventListener('resize', resize);
});

const canvas = document.querySelector('#largecv');

// Context for the canvas for 2 dimensional operations
const ctx = canvas.getContext('2d');

// Resizes the canvas to the available size of the window.
function resize() {
    ctx.canvas.width = 280;
    ctx.canvas.height = 280;
}

// Stores the initial position of the cursor
let coord = { x: 0, y: 0 };

// This is the flag that we are going to use to
// trigger drawing
let paint = false;

// Updates the coordianates of the cursor when
// an event e is triggered to the coordinates where
// the said event is triggered.
function getPosition(event) {
    coord.x = event.clientX - canvas.offsetLeft;
    coord.y = event.clientY - canvas.offsetTop;
}

// The following functions toggle the flag to start
// and stop drawing
function startPainting(event) {
    paint = true;
    getPosition(event);
}
function stopPainting() {
    paint = false;
}

function sketch(event) {
    if (!paint) return;
    ctx.beginPath();

    ctx.lineWidth = 10;

    // Sets the end of the lines drawn
    // to a round shape.
    ctx.lineCap = 'round';

    ctx.strokeStyle = 'black';

    // The cursor to start drawing
    // moves to this coordinate
    ctx.moveTo(coord.x, coord.y);

    // The position of the cursor
    // gets updated as we move the
    // mouse around.
    getPosition(event);

    // A line is traced from start
    // coordinate to this coordinate
    ctx.lineTo(coord.x, coord.y);

    // Draws the line.
    ctx.stroke();
}


function clearCanvas() {
    ctx.clearRect(0, 0, 280, 280);
}