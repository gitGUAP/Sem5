const express = require('express');
const router = express.Router();
const db = require('../src/db');

router.get('/', function(req, res, next) {
  const login = req.cookies.token === 'secret' ? true : false;
  if (!login) {
    return res.redirect('/');
  }

  db.Item.find({}, (err, data) => {
    if (err) {
      return next(err);
    }

    res.render('edit', {title: 'Edit', login, data});
  });
});

router.get('/delete/:id', function(req, res, next) {
  const login = req.cookies.token === 'secret' ? true : false;
  if (!login) {
    return res.redirect('/');
  }

  db.Item.deleteOne({_id: req.params.id}, (err, data) => {
    if (err) {
      return next(err);
    }

    return res.redirect('/edit');
  });
});

router.get('/item/:id', function(req, res, next) {
  const login = req.cookies.token === 'secret' ? true : false;
  if (!login) {
    return res.redirect('/');
  }

  db.Item.findOne({_id: req.params.id}, (err, data) => {
    if (err) {
      return next(err);
    }

    res.render('new', {title: 'New', login, ...data._doc});
  });
});

module.exports = router;
