var Exist = function(db, studio_name, callback) {
	var sql = 'SELECT studio_id FROM studio WHERE studio_name = ?';
	db.query(sql, [studio_name], function(err, data) {
		if(err) {
			callback({
				'error' : true,
				'result' : 'mysql error'
			})
		}else {
			if(data) {
				callback({
					'error' : true,
					'result' : 'studio_name exist',
					'data' : JSON.parse(JSON.stringify(data))
				})
			}else {
				callback({
					'error' : false,
					'result' : 'studio_name not exist'
				})
			}
		}
	})
}

module.exports = Exist;