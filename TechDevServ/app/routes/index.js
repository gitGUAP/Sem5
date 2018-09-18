const express = require("express");
const router = express.Router();

/* GET home page. */
router.get("/", function(req, res, next) {
  const login = req.cookies.token === "secret" ? true : false;

  res.render("index", { title: "Main", login });
});

router.get("/login", function(req, res, next) {
  res.render("login", { title: "Login" });
});

router.get("/logout", function(req, res, next) {
  res.clearCookie("token");
  return res.redirect("/");
});

module.exports = router;
