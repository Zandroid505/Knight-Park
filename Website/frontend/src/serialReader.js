// Possible replacement for the python Script

const { SerialPort } = new require("serialport");
const Readline = new require("@serialport/parser-readline");

const port = new SerialPort( {
    path: 'COM4',
    baudRate: 115200,
    parser: Readline
});

port.on('data', (data) => {
    console.log('Data:', data)
})

// Serial Port parser
// const parser = Readline();
// port.pipe(parser);

// Read the data
// port.parser.on("data", (line => console.log(line)));