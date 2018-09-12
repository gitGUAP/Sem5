const { Builder, By, Key } = require("selenium-webdriver");

// function getResult() {
//   return [...document.querySelector('#table').rows]
//       .map(el => {
//         const cell = [...el.cells].map(t => t.innerHTML);
//         return {[cell[0]]: cell[1] == 'true' ? true : false};
//       })
//       .reduce((acc, cur) => {
//         return {...acc, ...cur};
//       });
//   ;
// }

(async function example() {
  let driver = await new Builder().forBrowser("chrome").build();
  try {
    await driver.get("http://localhost:8080/");
    await driver.findElement(By.name("str")).sendKeys("webdriver");
    await driver
      .findElement(By.name("substr"))
      .sendKeys("web,dr,ver,test", Key.RETURN);

    const res = await driver.findElement(By.id("table")).getText();
    const exp = `dr true
test false
ver true
web true`;

    if (res == exp) {
      console.log("Done");
    } else {
      console.log("Fail");
    }
  } finally {
    await driver.quit();
  }
})();

(async function example() {
  let driver = await new Builder().forBrowser("chrome").build();
  try {
    await driver.get("http://localhost:8080/");
    await driver.findElement(By.name("str")).sendKeys("101");
    await driver.findElement(By.name("substr")).sendKeys("1,0", Key.RETURN);

    const res = await driver.findElement(By.id("table")).getText();
    const exp = `0 true
1 true`;

    if (res == exp) {
      console.log("Done");
    } else {
      console.log("Fail");
    }
  } finally {
    await driver.quit();
  }
})();
