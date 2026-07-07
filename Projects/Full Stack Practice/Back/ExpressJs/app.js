require('dotenv').config();

const express = require('express');
const router = require('./routes')
const { pool } = require('./database');
const app = express();
const PORT = process.env.PORT || 3000;

app.use(express.json())
app.use(express.urlencoded({ extended: false }));

app.get("/", (request, response) => {
    response.json({
        info: 'Hello world!'
    });
})

app.use("/api", router);

function printEndpoints() {
  var endPoints = [];

  router.stack.forEach(function(r) {
    if (r.route) {
      const path = '/api' + r.route.path;
      const method = r.route.stack[0].method;

      endPoints.push({
        "path": path,
        "action": method
      });
    }
  })

  console.table(endPoints);
}

printEndpoints();

pool.connect(err => {
  if (err) {
    console.error('Connection error', err.stack);
  } else {
    console.log('Connected to the PostgreSQL database');
  }
})

const server = app.listen(PORT, function () {
    let host = server.address().address;
    let port = server.address().port;
    console.log("Connected To localhost:" + port);
})