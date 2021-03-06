//Required modules for setting up the server and handling requests
const express = require("express"); 
const bodyParser = require("body-parser"); 

//Initialize
const app = express(); 
const port = 3000;
var strumStatus; 

app.use(bodyParser.json()); 

app.listen(port, () => {
    console.log("Listening on port 3000"); 
}); 

app.use(express.static(__dirname + '/PWA')); 

//Get routing
app.get("/get", (req, resp) => {
    resp.send("Here's some data "); 
    console.log(req);
});

//Post routing 
app.post("/sendData", (req, resp) => {
    console.log(req.body); 
    strumStatus = req.body.strumStatus; 
    console.log(strumStatus); 
    resp.send("Code 200: POST Request Successful");  
});

