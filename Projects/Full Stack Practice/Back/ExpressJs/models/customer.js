'use strict';
const { Model } = require('sequelize');
module.exports = (sequelize, DataTypes) => {
  class Customer extends Model {
    static associate(models) {
      Customer.hasMany(models.Order, {
        foreignKey: 'customerId',
        as: 'customer',
        onDelete: 'CASCADE'
      });
    }
  }

  Customer.init({
    customerName: DataTypes.STRING,
    contact: DataTypes.STRING,
    country: DataTypes.STRING,
    city: DataTypes.STRING,
    postalCode: DataTypes.STRING,
    address: DataTypes.STRING
  }, {
    sequelize,
    modelName: 'Customer',
  });
  
  return Customer;
};