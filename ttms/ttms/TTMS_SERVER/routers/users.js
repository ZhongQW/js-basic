const express = require('express');
var router = express.Router();

var db = require('../libs/db.js');

var Exist = require('../users/exist.js');
var Register = require('../users/register.js');
var Login = require('../users/login.js');
var Changepass = require('../users/change_pass.js');

//用户注册
router.use('/reg', function(req, res) {
	console.log(req.body);
	var username = req.body.username;
	var password = req.body.password;
	Exist(db, username, function (data) {
		console.log(data);
		if(data.error) {
			res.send(data);
		}else {
			Register(db, username, password, function (data) {
				res.send(data);
			})
		}
	})
})

//用户登录
router.use('/log', function(req, res) {
	console.log('login:',req.body);
	var username = req.body.username;
	var password = req.body.password;
	Login(db, username, password, function (data) {
		res.send(data);
	})
})

//更改密码
router.use('/chpass', function(req, res) {
	var id = req.body.id;
	var oldVal = req.body.oldVal;
	var newVal = req.body.newVal;
	Changepass(db, id, oldVal, newVal, function(data) {
		res.send(data);
	}) 
})

module.exports = router;