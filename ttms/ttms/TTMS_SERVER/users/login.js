var login = function (db, username, password, callback) {
	var sql = 'SELECT `password` FROM users WHERE `username` = \'' + username +'\'';
	db.query(sql, function(err, data) {
		if(err) {
			callback({
				'error' : true,
				'result' : 'mysql error'
			})
		}else {
			var pass = JSON.parse(JSON.stringify(data))[0].password;
			if(pass !== password) {
				callback({
					'error' : true,
					'result' : 'password error'
				});
			}else {
				callback({
					'error' : false,
					'result' : 'login success'
				})
			}
		}
	})
}

module.exports = login;