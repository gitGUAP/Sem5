window.onload  = function name(params) {
    const cells = document.querySelectorAll(".cell")
    const imgs = [
        "p-d.png",
        "p-l.png",
        "p-r.png",
    ]

    for (const el of cells) {
        el.style.backgroundImage = `url('./img/${imgs[Math.floor(Math.random()*imgs.length)]}')`;
    }

    startWater(30);
}

function startWater(start) {
    console.log("Stat water");
    
    let t = setInterval(() => {
        start -= 1;

        document.querySelector(".timer").innerHTML = start + "s";

        if (start < 0 ) {
            clearInterval(t);
            console.log("WATER");
        }
    },1000)
}