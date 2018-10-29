const imgs = [
    "p-b_l.png",
    "p-b_r.png",
    "p-horizontally.png",
    "p-l.png",
    "p-t-l.png",
    "p-t-r.png",
    "p-vertically.png",
]

function infoByImg(path) {
    return {
        
    }
}

window.onload  = function name(params) {
    const cells = document.querySelectorAll(".cell")

    for (const el of cells) {
        el.style.backgroundImage = `url('./img/${imgs[Math.floor(Math.random()*imgs.length)]}')`;
    }

    startWater(30);
}

function startWater(start) {
    console.log("Stat water");
    let t = setInterval(() => {
        document.querySelector(".timer").innerHTML = start + "s";
        start -= 1;

        if (start <= 0 ) {
            clearInterval(t);
            alert("WATER");
        }
    },1000)
}