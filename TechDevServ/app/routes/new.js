const express = require("express");
const router = express.Router();
const uuidv1 = require("uuid/v1");
const path = require("path");
const db = require("../src/db");
const kafka = require("kafka-node");


const en = require("../eng.json")
const ru = require("../ru.json")


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

            db.Item.updateOne({ _id: req.params.id }, { $set: { img: pathToImg } },
                (err, data) => {}
            );
        });
    } catch (error) {}
});

router.get("/", function(req, res, next) {
    const login = req.cookies.token === "secret" ? true : false;
    const lang = req.cookies.lang === "en" ? en : ru;

    if (!login) {
        return res.redirect("/");
    }

    res.render("new", { title: "New", login, lang });
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

        console.log({...req.body, img: pathToImg });


        const client = new kafka.Client("localhost:2181", "my-client-id", {
            sessionTimeout: 300,
            spinDelay: 100,
            retries: 2
        });

        const producer = new kafka.HighLevelProducer(client);
        producer.on("ready", function() {
            KafkaService.sendRecord()
        });

        // For this demo we just log producer errors to the console.
        producer.on("error", function(error) {
            console.error(error);
        });

        const KafkaService = {
            sendRecord: (callback = () => {}) => {

                const buffer = new Buffer.from(JSON.stringify({...req.body, img: pathToImg }));

                // Create a new payload
                const record = [{
                    topic: "webevents.dev",
                    messages: buffer,
                    attributes: 1 /* Use GZip compression for the payload */
                }];

                //Send record to Kafka and log result/error
                producer.send(record, callback);
            }
        };






        const item = new db.Item({...req.body, img: pathToImg });
        item.save().then(() => res.redirect("/"));
    });
});

module.exports = router;