const express = require(express); 
const request = require(request); 

const app = express(); 
const port = 3000;


app.listen(port, () => {
    console.log("Listening on port 3000"); 
}); 

app.use(express.static("PWA")); 

app.get("/", (req, resp) => {
    resp.send("Here's some data "); 
    console.log(req);
});

app.post("/", (req, resp) => {
    resp.send("Code 200: POST Request Successful"); 
    console.log(req); 
});