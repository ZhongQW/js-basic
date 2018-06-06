var exist = function (db,username, callback) {
	var sql = 'SELECT `userID` FROM users WHERE username = \'' + username +'\'';
	db.query(sql, function(err, data) {
		console.log('exist',err,data);
		if(err) {
			callback({
				'error' : true,
				'result' : 'mysql error'
			})
		}else {
			var myData = JSON.parse(JSON.stringify(data));
			if(myData.length === 0){
				callback({
					'error' : false,
					'result' : 'not exist'
				})
			}else {
				callback({
					'error' : true,
					'result' : 'user has existed'
				})
			}
		}
	})
}

module.exports = exist;