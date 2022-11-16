const express = require("express");
const notes = require("./data/notes");
const dotenv = require("dotenv");
const {spawn} = require('node:child_process');

const app = express();
dotenv.config();

app.get("/", (req, res) => {
  res.send("api is running");
});

app.get("/here", (req, res) => {
  var dataToSend;

  python = spawn("python3", ["parkSpotFetch.py"]);

  // collect data from script
  python.stdout.on("data", (data) => {
    console.log("Pipe data from python script ...");
    dataToSend = data.toString();
  });

  python.stderr.on('data', (data) => {
    console.log('stderr: ', + data);
  });

  // in close event we are sure that stream from child process is closed
  python.on("close", (code) => {
    console.log(`child process close all stdio with code ${code}`);
    // send data to browser
    res.send(dataToSend);
  });

  // res.send("API is running");
});

 

// app.get("/api/notes", (req, res) => {
//   res.json(notes);
// });

// app.get("/api/notes/:id", (req, res) => {
//   const note = notes.find((n) => n._id === req.params.id);
//   //console.log(req.params);
//   /*
//     req.params will return all parameters in app.get
//         ie: {id: '1', id2: '3'}
//     req.params.(id or id2) returns

//     */
//   res.send(note);
// });

const PORT = process.env.PORT || 5000;

app.listen(PORT, console.log(`server is on ${PORT}`));
