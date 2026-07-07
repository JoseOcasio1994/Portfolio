const fs = require('fs');
const path = require('path');
const controllers = {};

fs.readdirSync(__dirname)
  .forEach((file) => {
    if (file === 'index.js') return;

    const name = path.parse(file).name;
    
    const actions = require(path.join(__dirname, file));

    controllers[name] = actions;
  }
);

module.exports = controllers;