var mysql = require('mysql');

var db = mysql.createConnection({
	host : 'localhost',
	user : 'Zhongqw',
	password : '881127',
	database : 'ttms',
	multipleStatements : true  //设置属性为true 允许执行多条sql
});

module.exports = db;