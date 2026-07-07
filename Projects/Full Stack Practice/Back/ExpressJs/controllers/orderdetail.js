const models = require("../models").sequelize.models;
const Order = models.Order;

async function get(req, res) {
    try {
        const order = await Order.findAll({
            attributes: [ 'id', 'orderId', 'productId', 'quantity' ]
        });
        res.json(order);
    } catch (error) {
        res.status(500).json({ error: 'Internal Server Error' });
    }
}

async function getById(req, res) {
    const id = req.params.id;
    try {
        const order = await Order.findByPk(id, {
            attributes: ['id', 'orderId', 'productId', 'quantity'  ]
        });
        if (order) { res.json(order); }
        else {
            res.status(404).json({ error: 'Order not found' });
        }
    } catch (error) {
        res.status(500).json({ error: 'Internal Server Error' });
    }
}

async function post(req, res) {
    const { orderId, productId, quantity } = req.body;

    try {
        const newOrder = await Order.create({
            orderId,
            productId,
            quantity
        });
        res.status(201).json(newOrder);
    } catch (error) {
        res.status(500).json({ error: 'Internal Server Error' });
    }
}

async function put(req, res) {
    const id = req.params.id;
    const { orderId, productId, quantity } = req.body;
    try {
        const order = await Order.findByPk(id);
        if (order) {
            order.orderId = orderId;
            order.productId = productId;
            order.quantity = quantity;
            await order.save();
            res.json(order);
        } else {
            res.status(404).json({ error: 'Order not found' });
        }
    } catch (error) {
        res.status(500).json({ error: 'Internal Server Error' });
    }
}

async function remove(req, res) {
    const id = req.params.id;
    try {
        const order = await Order.findByPk(id);
        if (order) {
            await order.destroy();
            res.json(order);
        } else {
            res.status(404).json({ error: 'Order not found' });
        }
    } catch (error) {
        res.status(500).json({ error: 'Internal Server Error' });
    }
}

const endpoint = '/OrderDetail';
const id = '/:id';

const actions = [
    {
        type: "get",
        route: endpoint,
        callback: get,
        validation: undefined
    },
    {
        type: "get",
        route: endpoint + id,
        callback: getById,
        validation: undefined
    },
    {
        type: "post",
        route: endpoint,
        callback: post,
        validation: undefined
    },
    {
        type: "put",
        route: endpoint + id,
        callback: put,
        validation: undefined
    },
    {
        type: "delete",
        route: endpoint + id,
        callback: remove,
        validation: undefined
    }
]


module.exports = actions;