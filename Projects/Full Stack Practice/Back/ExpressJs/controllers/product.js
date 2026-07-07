const sequelize = require("../models").sequelize
const models = sequelize.models;
const Product = models.Product;

async function get(req, res) {
    try {
        const product = await Product.findAll({
            attributes: [
                'id', 'productName', 'categoryId',
                'unit', 'price'
            ]
        });
        res.json(product);
    } catch (error) {
        console.log(error)
        res.status(500).json({ error: 'Internal Server Error' });
    }
}

async function getById(req, res) {
    const id = req.params.id;
    try {
        const product = await Product.findByPk(id, {
            attributes: [
                'id', 'productName', 'categoryId',
                'unit', 'price'
            ]
        });
        if (product) { res.json(product); }
        else {
            res.status(404).json({ error: 'Product not found' });
        }
    } catch (error) {
        res.status(500).json({ error: 'Internal Server Error' });
    }
}

async function post(req, res) {
    const { productName, categoryId, unit, price } = req.body;

    try {
        const newProduct = await Product.create({
            productName,
            categoryId,
            unit,
            price
        });

        const p = newProduct.get({ plain: true });

        delete p.updatedAt;
        delete p.createdAt;

        res.status(201).json(p);
    } catch (error) {
        res.status(500).json({ error: 'Internal Server Error' });
    }
}

async function put(req, res) {
    const id = req.params.id;
    const { productName, categoryId, unit, price } = req.body;
    try {
        const product = await Product.findByPk(id);
        if (product) {
            product.productName = productName;
            product.categoryId = categoryId;
            product.unit = unit;
            product.price = price;

            const p = product.get({ plain: true });

            delete p.updatedAt;
            delete p.createdAt;

            await product.save();
            res.json(p);
        } else {
            res.status(404).json({ error: 'Product not found' });
        }
    } catch (error) {
        res.status(500).json({ error: 'Internal Server Error' });
    }
}

async function remove(req, res) {
    const id = req.params.id;
    try {
        const product = await Product.findByPk(id);
        if (product) {
            const p = product.get({ plain: true });

            delete p.updatedAt;
            delete p.createdAt;
            
            await product.destroy();
            res.json(product);
        } else {
            res.status(404).json({ error: 'Product not found' });
        }
    } catch (error) {
        res.status(500).json({ error: 'Internal Server Error' });
    }
}

const endpoint = '/Product';
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