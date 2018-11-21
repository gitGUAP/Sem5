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

function infoByImg(x, y, path) {
    if (!path || path.length == 0) {
        return []
    }
    const direct = path.split("/").pop().split(".")[0].split("-")[1].split("_")

    const where = direct.map((val, inx) => {
        if (inx == 0 && val != 0) {
            return { x: x - 1, y: y }
        }
        if (inx == 1 && val != 0) {
            return { x: x, y: y + 1 }
        }
        if (inx == 2 && val != 0) {
            return { x: x + 1, y: y }
        }
        if (inx == 3 && val != 0) {
            return { x: x, y: y - 1 }
        }
        return false;
    })


    return where.filter(el => el)
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

    event.toElement.src = `./img/${next_img}`;
}

window.onload = function name(params) {
    getMap()
    const cells = document.querySelectorAll(".cell")

    for (const el of cells) {
        el.addEventListener("click", select);
    }
    startTimer(25);
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
    setInterval(() => {
        addWater(0, 0)
    }, 200)

    setTimeout(function () {
        const end = getMap()[5][6]
        if (addHUE(end, 0) > 0) {
            alert(`Вы выиграли! Счет: ${1000 - click * 10}`)
        } else {
            alert(`ПРОИГРАЛИ! Счет: ${1000 - click * 10}`)
        }
    }, 500)
}

function addWater(x, y) {
    const el = getMap()[x][y]

    if (addHUE(el, 10) >= maxHUE) {
        return;
    }

    let next = infoByImg(x, y, el.src).filter(el => {
        const nextEl = getMap()[el.x][el.y]
        const isConnect = infoByImg(el.x, el.y, nextEl.src).some(i => i.x == x && i.y == y)
        return isConnect
    })

    for (const iter of next) {
        addWater(iter.x, iter.y)
    }
}

function addHUE(el, inc) {
    const cur = el.style.filter.match(/\d+/g) | ["0"];
    const next = cur + inc;

    el.style.filter = `grayscale(${next}%)`;
    return next;
}