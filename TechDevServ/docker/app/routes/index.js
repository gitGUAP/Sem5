const express = require("express");
const router = express.Router();
const en = require("../eng.json")
const ru = require("../ru.json")


/* GET home page. */
router.get("/", function(req, res, next) {
    const login = req.cookies.token === "secret" ? true : false;
    const lang = req.cookies.lang === "en" ? en : ru;


    res.render("index", { title: "Main", login, lang });
});

router.get("/login", function(req, res, next) {
    const lang = req.cookies.lang === "en" ? en : ru;
    res.render("login", { title: "Login", lang });
});

router.get("/logout", function(req, res, next) {
    res.clearCookie("token");
    return res.redirect("/");
});

module.exports = router;