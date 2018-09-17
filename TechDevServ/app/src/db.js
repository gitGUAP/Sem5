const mongoose = require("mongoose");
mongoose.connect("mongodb://localhost/test");

const Item = mongoose.model("Item", {
  name: String,
  count: Number,
  img: String,
  desc: String,
  price: Number
});

const User = mongoose.model("User", { username: String, password: String });

module.exports = {
  Item,
  User
};
