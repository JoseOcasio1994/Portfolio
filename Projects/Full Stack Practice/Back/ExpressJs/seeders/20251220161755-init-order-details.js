'use strict';

const fs = require('fs');
const { parse } = require('csv-parse');

/** @type {import('sequelize-cli').Migration} */
module.exports = {
  async up (queryInterface, Sequelize) {
      const results = [];
          
      await new Promise((resolve, reject) => {
        fs.createReadStream('./data/OrderDetails.csv')
          .pipe(parse({
            columns: true,
            skip_empty_lines: true,
            bom: true,
            trim: true
          }))
          .on('data', (data) => {
            data['orderId'] -= 10248
            data['createdAt'] = data['updatedAt'] = new Date()
            results.push(data)
          })
          .on('end', () => resolve())
          .on('error', (error) => reject(error));
      });
  
      return queryInterface.bulkInsert('OrderDetails', results, {})
  },

  async down (queryInterface, Sequelize) {
    return queryInterface.bulkDelete('OrderDetails', null, {})
  }
};
