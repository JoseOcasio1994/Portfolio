'use strict';

const { Model } = require('sequelize');

module.exports = (sequelize, DataTypes) => {
  class OrderDetail extends Model { 
    static associate(models) {
      OrderDetail.belongsTo(models.Order, {
        foreignKey: 'orderId',
        as: 'order',
      });
      
      OrderDetail.belongsTo(models.Product, {
        foreignKey: 'productId', 
        as: 'product',
      });
    }
  }

  OrderDetail.init({
    quantity: DataTypes.INTEGER
  }, {
    sequelize,
    modelName: 'OrderDetail',
  });

  return OrderDetail;
};