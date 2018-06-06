var addPlays = function(db, playinfo, callback) {
	var sql = 'INSERT INTO `play` (`play_type_id`,`play_lang_id`, `play_name`,`play_introduction`,`play_image`,`play_length`,`play_ticket_price`,	`play_status`) VALUES (?,?,?,?,?,?,?,?)';
	db.query(sql, [playinfo.type,playinfo.lang,playinfo.name,playinfo.introduction, playinfo.image,playinfo.time,playinfo.price,0], function (err, data) {
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

module.exports = addPlays;