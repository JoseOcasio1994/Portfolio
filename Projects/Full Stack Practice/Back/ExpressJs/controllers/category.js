const models = require("../models").sequelize.models;
const Category = models.Category;

async function get(req, res) {
    try {
        const category = await Category.findAll({
            attributes: ['id', 'categoryName', 'description']
        });
        res.json(category);
    } catch (error) {
        res.status(500).json({ error: 'Internal Server Error' });
    }
}

async function getById(req, res) {
    const id = req.params.id;
    try {
        const category = await Category.findByPk(id, {
            attributes: ['id', 'categoryName', 'description']
        });
        if (category) { res.json(category); }
        else {
            res.status(404).json({ error: 'Category not found' });
        }
    } catch (error) {
        res.status(500).json({ error: 'Internal Server Error' });
    }
}

async function post(req, res) {
    const { categoryName, description } = req.body;

    try {
        const newCategory = await Category.create({
            categoryName,
            description,
        });

        const category = newCategory.get({ plain: true });

        delete category.updatedAt;
        delete category.createdAt;
        res.status(201).json(category);
    } catch (error) {
        res.status(500).json({ error: 'Internal Server Error' });
    }
}

async function put(req, res) {
    const id = req.params.id;
    const { categoryName, description } = req.body;
    try {
        const category = await Category.findByPk(id);
        if (category) {
            
            category.categoryName = categoryName;
            category.description = description;
            
            const cat = category.get({ plain: true });
            
            delete cat.updatedAt;
            delete cat.createdAt;
            
            await category.save();
            res.json(cat);
        } else {
            res.status(404).json({ error: 'Category not found' });
        }
    } catch (error) {
        res.status(500).json({ error: 'Internal Server Error' });
    }
}

async function remove(req, res) {
    const id = req.params.id;
    try {
        const category = await Category.findByPk(id);
        if (category) {

            const cat = category.get({ plain: true });

            delete cat.updatedAt;
            delete cat.createdAt;

            await category.destroy();
            res.json(cat);
        } else {
            res.status(404).json({ error: 'Category not found' });
        }
    } catch (error) {
        res.status(500).json({ error: 'Internal Server Error' });
    }
}

const endpoint = '/Category';
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