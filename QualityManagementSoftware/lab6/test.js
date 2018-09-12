const {Builder, By, Key} = require('selenium-webdriver');

(async function example() {
  let driver = await new Builder().forBrowser('chrome').build();
  try {
    await driver.get('http://localhost:8080/');
    await driver.findElement(By.name('str')).sendKeys('webdriver');
    await driver.findElement(By.name('substr'))
        .sendKeys('web,dr,ver,test', Key.RETURN);

    const res = await driver.findElement(By.id('table')).getText();
    const exp = `dr true
test false
ver true
web true`;

    if (res == exp) {
      console.log('Done');
    } else {
      console.log('Fail');
    }
  } finally {
    await driver.quit();
  }
})();
