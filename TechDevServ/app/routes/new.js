const express = require("express");
const router = express.Router();
const uuidv1 = require("uuid/v1");
const path = require("path");
const db = require("../src/db");

router.post("/update/:id", function(req, res, next) {
  const login = req.cookies.token === "secret" ? true : false;
  if (!login) {
    return res.redirect("/");
  }

  db.Item.updateOne({ _id: req.params.id }, { $set: req.body }, (err, data) => {
    if (err) {
      return next(err);
    }

    return res.redirect("/edit");
  });

  try {
    const img = req.files.img;
    const imgExt = path.extname(img.name);
    const name = uuidv1() + imgExt;
    const pathToImg = `/data/${name}`;

    img.mv(`./public${pathToImg}`, function(err) {
      if (err) return res.status(500).send(err);

      db.Item.updateOne(
        { _id: req.params.id },
        { $set: { img: pathToImg } },
        (err, data) => {}
      );
    });
  } catch (error) {}
});

router.get("/", function(req, res, next) {
  const login = req.cookies.token === "secret" ? true : false;
  if (!login) {
    return res.redirect("/");
  }

  res.render("new", { title: "New", login });
});

router.post("/", function(req, res, next) {
  const login = req.cookies.token === "secret" ? true : false;
  if (!login) {
    return res.redirect("/");
  }

  const img = req.files.img;
  const imgExt = path.extname(img.name);
  const name = uuidv1() + imgExt;
  const pathToImg = `/data/${name}`;

  img.mv(`./public${pathToImg}`, function(err) {
    if (err) return res.status(500).send(err);

    const item = new db.Item({ ...req.body, img: pathToImg });
    item.save().then(() => res.redirect("/"));
  });
});

module.exports = router;
