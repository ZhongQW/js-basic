const express = require('express');
var router = express.Router();

var db = require('../libs/db.js');

var exist = require('../studio/exist.js');
var add = require('../studio/add.js');
var getAll = require('../studio/getall.js');
var getDetails = require('../studio/getdetails.js');

router.get('/add', function(res) {
	var name = req.query.name;
	var row = req.query.row;
	var col = req.query.col;
	var intro = req.query.intro;

	exist(db, studio_name,function(data) {
		if(data.error) {
			res.send(data);
		}else {
			add(db, name, row, col, intro, function(data){
				res.send(data);
			})
		}
	})
})

router.get('/all', function(res) {
	getAll(db,function(data) {
		res.send(data);
	})
})

router.get('/details', function(res) {
	getDetails(db, res.query.sid, function(data) {
		res.send(data);
	})
})

module.exports = router;