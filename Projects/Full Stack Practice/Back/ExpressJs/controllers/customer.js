const models = require("../models").sequelize.models;
const Customer = models.Customer;

async function get(req, res) {
    try {
        const customer = await Customer.findAll({
            attributes: [
                'id', 'customerName', 'contact',
                'country', 'city', 'postalCode', 'address'
            ]
        });
        res.json(customer);
    } catch (error) {
        res.status(500).json({ error: 'Internal Server Error' });
    }
}

async function getById(req, res) {
    const id = req.params.id;
    try {
        const customer = await Customer.findByPk(id, {
            attributes: [
                'id', 'customerName', 'contact',
                'country', 'city', 'postalCode', 'address'
            ]
        });
        if (customer) { res.json(customer); }
        else {
            res.status(404).json({ error: 'Customer not found' });
        }
    } catch (error) {
        res.status(500).json({ error: 'Internal Server Error' });
    }
}

async function post(req, res) {
    const { customerName, contact, country,
        city, postalCode, address } = req.body;

    try {
        const newCustomer = await Customer.create({
            customerName,
            contact,
            country,
            city,
            postalCode,
            address 
        });

        const customer = newCustomer.get({ plain: true });

        delete customer.updatedAt;
        delete customer.createdAt;

        res.status(201).json(customer);
    } catch (error) {
        res.status(500).json({ error: 'Internal Server Error' });
    }
}

async function put(req, res) {
    const id = req.params.id;
    const { customerName, contact, country,
        city, postalCode, address } = req.body;
    
    try {
        const customer = await Customer.findByPk(id);
        if (customer) {
            customer.customerName = customerName;
            customer.contact = contact;
            customer.country = country;
            customer.city = city;
            customer.postalCode = postalCode;
            customer.address = address;

            const c = customer.get({ plain: true });

            delete c.updatedAt;
            delete c.createdAt;

            await customer.save();
            res.json(c);
        } else {
            res.status(404).json({ error: 'Customer not found' });
        }
    } catch (error) {
        res.status(500).json({ error: 'Internal Server Error' });
    }
}

async function remove(req, res) {
    const id = req.params.id;
    try {
        const customer = await Customer.findByPk(id);
        if (customer) {
            const c = customer.get({ plain: true });

            delete c.updatedAt;
            delete c.createdAt;

            await customer.destroy();
            res.json(c);
        } else {
            res.status(404).json({ error: 'Customer not found' });
        }
    } catch (error) {
        res.status(500).json({ error: 'Internal Server Error' });
    }
}

const endpoint = '/Customer';
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