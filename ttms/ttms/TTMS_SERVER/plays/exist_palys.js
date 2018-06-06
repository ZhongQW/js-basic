var existPlays = function(db, id, name, callback) {
	sql = 'SELECT `play_id` FROM paly WHERE `play_id` = ' + id  + 'or `play_name` = \'' + name +'\'';
	db.query(sql, function(err, data) {
		if(err) {
			callback({
				'error' :true,
				'result' : 'mysql error'
			})
		}else {
			if(0 === JSON.parse(JSON.stringify(data)).length) {
				callback({
					'error' : false,
					'result' : 'play not exist'
				})
			}else {
				callback({
					'error' : true,
					'result' : 'play has existed'
				})
			}
		}
	})
}

module.exports = existPlays;