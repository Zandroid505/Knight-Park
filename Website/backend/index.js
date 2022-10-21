const express = require("express");
const notes = require("./data/notes");
const dotenv = require("dotenv");

const app = express();
dotenv.config();

app.get("/", (req, res) => {
  res.send("API is running");
});

app.get("/api/notes", (req, res) => {
  res.json(notes);
});

app.get("/api/notes/:id", (req, res) => {
  const note = notes.find((n) => n._id === req.params.id);
  //console.log(req.params);
  /*
    req.params will return all parameters in app.get
        ie: {id: '1', id2: '3'}
    req.params.(id or id2) returns

    */
  res.send(note);
});

const PORT = process.env.PORT || 5000;

app.listen(PORT, console.log(`server is on ${PORT}`));
