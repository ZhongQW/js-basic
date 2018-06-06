var delPlays = function (db, id, callback) {
	var sql = 'DELETE FROM `play` WHERE `play_id` = ' + id;
	db.query(sql, function(err, data) {
		if(err) {
			callback({
				'error' : true,
				'result' : 'mysql error'
			})
		}else {
			callback({
				'error' : false,
				'result' : 'delete play success'
			})
		}
	})
}

module.exports = delPlays;