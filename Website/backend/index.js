const express = require("express");
const {spawn} = require('node:child_process');
const app = express();
const notes = require("./data/notes");
const dotenv = require("dotenv");

dotenv.config();

app.get("/", (req, res) => {
  // res.send("API is running");
  // spawn new child process to call the python script
  const python = spawn('python', ['/home/montwes/cDrive/Documents/Coding/Projects/Knight-Park/Website/backend/parkSpotFetch.py']);
  
  // // collect data from script
  // python.stdout.on('data', function (data) {
  //   console.log('Pipe data from python script ...');
  //   dataToSend = data.toString();
  //  });

  //  // in close event we are sure that stream from child process is closed
  // python.on('close', (code) => {
  // console.log(`child process close all stdio with code ${code}`);
  
  // send data to browser
  res.send("Hi there")
  // });
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
