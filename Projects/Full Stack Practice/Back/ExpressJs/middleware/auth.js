const process = require('process');
const jwt = require('jsonwebtoken');

const authMiddleware = (req, res, next) => {
    const auth = req.header('Authorization');

    if (!auth) {
        return res.status(401).json({ message: 'Access denied. No token provided.' });
    }

    try {
        const token = auth.slice(7); // remove 'Bearer '
        const decoded = jwt.verify(token, process.env.JWT_SECRET);
        req.user = decoded;
        next();
    } catch (err) {
        res.status(400).json({ message: 'Invalid token' });
    }
};

module.exports = authMiddleware;