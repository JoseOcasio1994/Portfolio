'use strict';

const { Model } = require('sequelize');
const Product = require('./product');

module.exports = (sequelize, DataTypes) => {
  class Category extends Model { 
    static associate(models) {
      Category.hasMany(models.Product);
    }
  }

  Category.init({
    categoryName: DataTypes.STRING,
    description: DataTypes.STRING
  }, {
    sequelize,
    modelName: 'Category',
    tableName: 'Categories'
  });

  return Category;
};