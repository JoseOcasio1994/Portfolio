'use strict';

const { Model } = require('sequelize');

module.exports = (sequelize, DataTypes) => {
  class Order extends Model {
    static associate(models) {
      Order.belongsTo(models.Customer, {
        foreignKey: 'customerId',
        as: 'customer',
      });

      Order.hasMany(models.OrderDetail, {
        foreignKey: 'orderId',
        as: 'detail',
        onDelete: 'CASCADE'
      });
    }
  }

  Order.init({
    orderDate: DataTypes.DATEONLY
  }, {
    sequelize,
    modelName: 'Order',
  });

  return Order;
};