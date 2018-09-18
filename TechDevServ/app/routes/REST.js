const express = require("express");
const router = express.Router();
const db = require("../src/db");

router.get("/records", function(req, res, next) {
  db.Item.find({}, (err, data) => {
    if (err) {
      return next(err);
      throw err;
    }

    res.send(data);
  });
});

router.post("/login", function(req, res, next) {
  const userData = { ...req.body };

  db.User.findOne(userData, (err, data) => {
    if (err) {
      return next(err);
    }
    if (data === null) {
      return res.redirect("/");
    }

    res.cookie("token", "secret", { maxAge: 900000 });
    return res.redirect("/");
  });
});

router.post("/logout", function(req, res, next) {
  res.clearCookie("token");
  return res.redirect("/");
});

module.exports = router;
