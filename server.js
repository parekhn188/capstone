//Required modules for setting up the server and handling requests
const express = require("express"); 

//Initialize
const app = express(); 
const port = 5000;

app.listen(port, () => {
    console.log("Listening on port 5000"); 
}); 

app.use(express.static("PWA")); 

//Get routing
app.get("/get", (req, resp) => {
    resp.send("Here's some data "); 
    console.log(req);
});

//Post routing 
app.post("/sendData", (req, resp) => {
    console.log(req.body); 
    resp.send("Code 200: POST Request Successful");  
});

/*
(async () => {
    try {
        const {body} = await got.post('http://localhost:3000/sendData', {
            json: {
                hello : 'world'
            },
            responseType: 'json'
        }); 
        console.log(body.data); 
    } catch (error) {
        console.log(error.response.body); 
    } 
})();
*/
