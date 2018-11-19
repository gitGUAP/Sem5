const imgs = [
    "p-0_0_1_1.png",
    "p-0_1_0_1.png",
    "p-0_1_1_0.png",
    "p-1_0_0_1.png",
    "p-1_0_1_0.png",
    "p-1_1_0_0.png",
]
let click = 0;
const maxHUE = 100;

function infoByImg(path) {
    return path.split("/").pop().split(".")[0].split("-")[1].split("_");
}

Object.defineProperty(Array.prototype, 'chunk_inefficient', {
    value: function (chunkSize) {
        var array = this;
        return [].concat.apply([],
            array.map(function (elem, i) {
                return i % chunkSize ? [] : [array.slice(i, i + chunkSize)];
            })
        );
    }
});

function getMap() {
    const cells = document.querySelectorAll(".cell")
    const st = document.querySelector(".cell_start")
    const ed = document.querySelector(".cell_end")

    all = [st, ...cells, ed]
    return all.chunk_inefficient(7)
}

function select(event) {
    const next = document.querySelector(".next-cell");
    const next_img = next.src.split("/").pop();
    next.src = `./img/${imgs[Math.floor(Math.random() * imgs.length)]}`
    click++;

    event.toElement.style.backgroundImage = `url('./img/${next_img}')`;
}

window.onload = function name(params) {
    getMap()
    const cells = document.querySelectorAll(".cell")

    for (const el of cells) {
        el.addEventListener("click", select);
    }
    startTimer(5);
}

function startTimer(start) {
    let t = setInterval(() => {
        document.querySelector(".timer").innerHTML = start + "s";

        if (start <= 0) {
            clearInterval(t);
            startWater()
        }

        start -= 1;
    }, 1000)
}


function startWater() {
    let t = setInterval(() => {
        addWater(0, 0)
    }, 200)
}

function addWater(x, y) {
    const el = getMap()[x][y]
    console.log(el.style.backgroundImage);

    if (addHUE(el, 5) >= maxHUE) {
        console.log(infoByImg(el.style.backgroundImage));
    }

    return false;
}

function addHUE(el, inc) {
    const cur = el.style.filter.match(/\d+/g) | ["0"];
    const next = cur + inc;

    el.style.filter = `grayscale(${next}%)`;
    return next;
}