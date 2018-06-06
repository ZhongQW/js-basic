const express = require('express');
var router = express.Router();

var db = require('../libs/db.js');

var Existplays = require('../plays/exist_palys.js');
var Addplays = require('../plays/add_plays.js');
var Delplays = require('../plays/del_plays.js');
var Checkplays = require('../plays/check_plays.js');
var Getplays = require('../plays/get_plays.js');

//添加剧目
router.use('/add', function(req, res) {
	console.log(req.body);
	var playinfo = req.body;
	Addplays(db,playinfo,function(data){
		res.send(data);
	})
})

//删除剧目
router.use('/del', function(req, res) {
	var id = req.query.id;
	Delplays(db,id,function (data) {
		res.send(data);
	})
})

//按名称或者id查询剧目
router.use('/check', function(req, res) {
	var name = req.query.name;
	var id = req.query.id;
	Checkplays(db, id, name, function (data) {
		res.send(data);
	})
})

//更改剧目信息
router.use('/upd', function(req, res) {
})

//获取上线的剧目 
router.use('/get', function(req, res) {
	var status = req.query.status;
	Getplays(db, status, function(data) {
		res.send(data);
	})
})

module.exports = router;