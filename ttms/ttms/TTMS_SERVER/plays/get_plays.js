var getPlays = function(db, status, callback) {
	var sql = 'SELECT * FROM `play` WHERE `play_status` = ?';
	db.query(sql, [status], function(err, data) {
		if(err) {
			callback({
				'error' : true,
				'result' : 'mysql error'
			})
		}else {
			callback({
				'error' : false,
				'result' : 'add play success'
			})
		}
	})
}

module.exports = getPlays;