const express = require(express); 
const request = require(request); 

const app = express(); 
const port = 3000;


app.listen(port, () => {
    console.log("Listening on port 3000"); 
}); 

app.use(express.static("PWA")); 

app.get

app.post("/", (req, res) => {
    res.send("Code 200: POST Request Successful"); 
    console.log(req); 
});