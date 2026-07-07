const sequelize = require("../models").sequelize;
const models = sequelize.models;
const Order = models.Order;
const OrderDetail = models.OrderDetail;

async function get(req, res) {
    try {
        const order = await Order.findAll({
            attributes: ['id', 'customerId', 'orderDate'],
            include: [{
                model: OrderDetail,
                as: 'detail', 
                attributes: ['id', 'productId', 'quantity'] 
            }]
        });
        res.json(order);
    } catch (error) {
        console.log(error);
        res.status(500).json({ error: 'Internal Server Error' });
    }
}

async function getById(req, res) {
    const id = req.params.id;
    try {
        const order = await Order.findByPk(id, {
            attributes: ['id', 'customerId', 'orderDate'],
            include: [{
                model: OrderDetail,
                as: 'detail', 
                attributes: ['id', 'productId', 'quantity'] 
            }]
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
    const { customerId, orderDate, detail } = req.body;
    try {
        const newOrder = await Order.create({
            customerId,
            orderDate,
            detail
        }, {
            include: [{
                model: OrderDetail, as: 'detail',
                attributes: ['id', 'productId', 'quantity']
            }]
        });

        const o = newOrder.get({ plain: true });

        delete o.updatedAt;
        delete o.createdAt;

        for (const d of o.detail) {
            delete d.updatedAt;
            delete d.createdAt;
            delete d.orderId;
        }

        res.status(201).json(o);
    } catch (error) {
        console.log(error)
        res.status(500).json({ error: 'Internal Server Error' });
    }
}

async function put(req, res) {
    const id = req.params.id;
    const { customerId, orderDate, detail } = req.body;
    try {
        const order = await Order.findByPk(id,{
            include: [
                {
                    model: OrderDetail, as: 'detail',
                    attributes: ['id', 'productId', 'quantity']
                }  
            ]
        });

        if (!order) {
            return res.status(404).json({ error: 'Order not found' });
        }
        
        await sequelize.transaction(async (t) => {
            
            await order.update({ customerId, orderDate }, { transaction: t });

            if (order.detail && detail) {
                for (const d of detail) {
                    if (!d.id) {
                        await OrderDetail.create(
                            { 
                                orderId: id,
                                productId: d.productId,
                                quantity: d.quantity
                            },
                            { transaction: t });
                    }
                    else {
                        const originalDetail = order.detail.find(x => x.dataValues.id === d.id)
                        if (originalDetail) {
                            if (d.quantity == 0) {
                                await originalDetail.destroy();
                            }
                            else {
                                await originalDetail.update(
                                    { productId: d.productId, quantity: d.quantity },
                                    { transaction: t });
                            }
                        }
                    }
                }
            }
        });
        
        const updatedOrder = await Order.findByPk(id,{
            include: [
                {
                    model: OrderDetail, as: 'detail',
                    attributes: ['id', 'productId', 'quantity']
                }  
            ]
        });

        const o = updatedOrder.get({ plain: true });

        delete o.updatedAt;
        delete o.createdAt;

        res.json(o);

    } catch (error) {
        console.log(error);
        res.status(500).json({ error: 'Internal Server Error' });
    }
}

async function remove(req, res) {
    const id = req.params.id;
    try {
        const order = await Order.findByPk(id, {
            attributes: ['id', 'customerId', 'orderDate'],
            include: [{
                model: OrderDetail,
                as: 'detail', 
                attributes: ['id', 'productId', 'quantity'] 
            }]
        });
        if (order) {
            await order.destroy();
            res.json(order);
        } else {
            res.status(404).json({ error: 'Order not found' });
        }
    } catch (error) {
        console.log(error);
        res.status(500).json({ error: 'Internal Server Error' });
    }
}

const endpoint = '/Order';
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