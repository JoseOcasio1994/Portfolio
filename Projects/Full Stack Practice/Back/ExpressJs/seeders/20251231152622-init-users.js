'use strict';

const bcrypt = require('bcryptjs');

/** @type {import('sequelize-cli').Migration} */
module.exports = {
  async up(queryInterface, Sequelize) {
    const user1 = {
      userName: "lilwolf",
      email: "ocasio.jose132@gmail.com",
      password: await bcrypt.hash("Lilwolf100#", 10),
      role: "admin"
    };

    const user2 = {
      userName: "silentwolf",
      email: "example@gmail.com",
      password: await bcrypt.hash("mannie13", 10),
      role: "user"
    };

    user1['createdAt'] = user1['updatedAt'] = new Date();
    user2['createdAt'] = user2['updatedAt'] = new Date();

    return queryInterface.bulkInsert('Users', [user1, user2], {})
  },

  async down (queryInterface, Sequelize) {
    return queryInterface.bulkDelete('Users', null, {})
  }
};
