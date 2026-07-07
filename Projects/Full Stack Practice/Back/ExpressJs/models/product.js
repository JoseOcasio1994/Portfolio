'use strict';

const { Model } = require('sequelize');

module.exports = (sequelize, DataTypes) => {
  class Product extends Model { 
    static associate(models) {
      Product.belongsTo(models.Category, {
        foreignKey: 'categoryId',
        as: 'category',
      });

      Product.hasMany(models.OrderDetail, {
        foreignKey: 'orderId',
        as: 'detail',
        onDelete: 'CASCADE'
      });
    }
  }

  Product.init({
    productName: DataTypes.STRING,
    categoryId: DataTypes.INTEGER,
    unit: DataTypes.STRING,
    price: DataTypes.FLOAT
  }, {
    sequelize,
    modelName: 'Product',
  });

  return Product;
};