//Required modules for setting up the server and handling requests
const express = require("express"); 
const bodyParser = require("body-parser"); 


//Initialize
const app = express(); 
const port = 3000;
var strumStatus;  
var chordSwitch; 

app.use(bodyParser.json()); 
app.set("view engine", "ejs"); 
app.set("views", __dirname + "/views");

app.listen(port, () => {
    console.log("Listening on port 3000"); 
}); 

app.use(express.static(__dirname + '/public')); 

//Routes
app.get("/", (req, resp) => {
    resp.render("index"); 
});

// app.get("/chords", (req, resp) => {
//     resp.render("chords"); 
// });

app.get("/song", (req, resp) => {
    resp.render("song"); 
});

// app.get("/stringUI", (req, resp) => {
//     resp.render("stringUI"); 
// });

app.get("/about", (req, resp) => {
    resp.render("about"); 
});

//Get routing
app.get("/get", (req, resp) => {
    resp.send("Here's some data "); 
    console.log(req);
});

//Post routing 
app.post("/sendData", (req, resp) => {
    console.log(req.body);  
    strumStatus = req.body["Strum Status"]; 
    chordSwitch = req.body["Switch Chord"]; 
    //resp.render("chords", {status: strumStatus});
    app.get("/Chords", (req, resp) => {
        resp.render("chords", {status: strumStatus, chordSwitch:chordSwitch}); 
    });
    resp.send("Code 200: POST Request Successful");  
});

console.log(strumStatus); 

//Parse and return variables back 
var sendStatus = function() {
    var stat = {
        status:strumStatus
    }; 
    return stat; 
}

