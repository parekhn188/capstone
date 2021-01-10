//Required modules for setting up the server and handling requests
const express = require("express"); 
const request = require("request"); 

//Initialize
const app = express(); 
const port = 3000;


app.listen(port, () => {
    console.log("Listening on port 3000"); 
}); 

app.use(express.static("PWA")); 

//Get routing
app.get("/get", (req, resp) => {
    resp.send("Here's some data "); 
    console.log(req);
});

//Post routing 
app.post("/", (req, resp) => {
    resp.send("Code 200: POST Request Successful"); 
    console.log(req); 
});

//Testing post request
request.post({headers: {'content-type' : 'application/x-www-form-urlencoded'}, url:"http://localhost:3000", body:"testing"}, (err, resp, body) => {    
    console.log(body); 
    console.log(resp); 
});