const express = require("express");
const router = express.Router();

/* GET home page. */
router.get("/", function(req, res, next) {
  const login = req.cookies.token === "secret" ? true : false;
  if (!login) {
    return res.redirect("/");
  }

  res.render("edit", { title: "Edit", login });
});

module.exports = router;
