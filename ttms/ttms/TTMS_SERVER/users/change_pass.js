var changePass = function(db, id, oldVal, newVal, callback){
	var sql = 'SELECT password FROM users WHERE userID = ?';
	db.query(sql, [id], function(err, data) {
		if(err) {
			callback({
				'error' : true,
				'result' : 'mysql error'
			})
		}else {
			var val = JSON.parse(JSON.stringify(data))[0].password;
			if(val === oldVal) {
				var nsql = 'UPDATE users SET password = ? WHERE userID = ?';
				db.query(nsql, [newVal, id], function(err,data) {
					if(err) {
						callback({
							'error' : true,
							'result' : 'mysql error'
						})
					}else {
						callback({
							'error' : false,
							'result' : 'change success'
						})
					}
				})
			}else {
				callback({
					'error' : true,
					'result' : 'change fail'
				})
			}
		}
	})
}

module.exports = changePass;