const express = require('express');
const router = express.Router();
const db = require('../src/db');

const en = require("../eng.json")
const ru = require("../ru.json")

router.get('/', function(req, res, next) {
    const login = req.cookies.token === 'secret' ? true : false;
    if (!login) {
        return res.redirect('/');
    }

    db.Item.find({}, (err, data) => {
        if (err) {
            return next(err);
        }

        const lang = req.cookies.lang === "en" ? en : ru;

        res.render('edit', { title: 'Edit', login, data, lang });
    });
});

router.delete('/delete/:id', function(req, res, next) {
    const login = req.cookies.token === 'secret' ? true : false;
    if (!login) {
        return res.redirect('/');
    }

    db.Item.deleteOne({ _id: req.params.id }, (err, data) => {
        if (err) {
            return next(err);
        }

        res.send(200)
    });
});

router.get('/item/:id', function(req, res, next) {
    const login = req.cookies.token === 'secret' ? true : false;
    if (!login) {
        return res.redirect('/');
    }

    db.Item.findOne({ _id: req.params.id }, (err, data) => {
        if (err) {
            return next(err);
        }
        const lang = req.cookies.lang === "en" ? en : ru;

        res.render('new', { title: 'New', login, ...data._doc, lang });
    });
});

module.exports = router;