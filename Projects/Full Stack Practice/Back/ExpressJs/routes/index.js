const express = require('express');
const router = express.Router();
const authMiddleware = require('../middleware/auth');
const roleMiddleware = require('../middleware/role');
const controllers = require('../controllers');

for (const c of Object.keys(controllers)) {

    console.log('----------' + c + '----------');
    controllers[c].forEach(con => {
        const type = con.type;
        const route = con.route;
        const callback = con.callback;
        const validation = con.validation;

        if (type === 'get') {
            if (!validation) {
                router.get( route, callback);
            }
            else {
                router.get( route, validation, callback);
            }
        }

        else if (type === 'post') {
            if (!validation) {
                router.post( route, callback);
            }
            else {
                router.post( route, validation, callback);
            }
        }

        else if (type === 'put') {
            if (!validation) {
                router.put( route, callback);
            }
            else {
                router.put( route, validation, callback);
            }
        }

        else if (type === 'delete') {
            if (!validation) {
                router.delete( route, callback);
            }
            else {
                router.delete( route, validation, callback);
            }
        }
        
        else {
            console.log("Unknown HTTP Action: " + type);
        }
    });
    
}

router.get('/User', authMiddleware, (req, res) => {
  res.status(200).json({ message: 'Welcome to the user dashboard', user: req.user });
});

router.get('/Admin', [authMiddleware, roleMiddleware('admin')], (req, res) => {
  res.status(200).json({ message: 'Welcome to the admin dashboard', user: req.user });
});

module.exports = router;