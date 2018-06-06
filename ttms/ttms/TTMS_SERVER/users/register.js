var register = function (db,username, password, callback) {
	//db ： 不变 数据库
	//username ,password ...为传进来的参数 会变
	//callback 回调函数 不用管 固定
	//sql 为sql语句 ，根据功能不同自己拼接出语句用于db.query()
    var sql = 'INSERT INTO users (`userID`,`username`,`password`) VALUES( ' +'null,\'' + username +'\',\'' + password +'\')';	//db.query(sql,function(err, data) {...})
	//err: 报错   data :没错的时候 sql 返回的数据
	db.query(sql, function (err, data) {
		console.log('register',err,data);
		if(err) {
			callback({
				'error' : true,
				'result' : 'mysql error'
			})
		}else {
			callback({
				'error' : false,
				'result' : 'register success'
			})
		}
	})
}
//把写的函数exports出去
module.exports = register;