var updPlays = function (db,playinfo,callback) {
	var sql = 'UPDATE `play` SET `play_type_id` = ' + playinfo.type + ', `play_lang_id` = ' + playinfo.lang + 
	'`,play_name` = \'' + playinfo.name +'\' ,' +'`play_introduction` = \''+',`play_image`' + playinfo.image +
	',`play_length` = '+ playinfo.time +',`play_ticket_price` = ' + playinfo.price +'WHERE play_id = ' + playinfo.id;

	db.query(sql, function(ere, data) {
		if(err) {
			callback({
				'error' : true,
				'result' : 'mysql error'
			})
		}else {
			callback({
				'error' : false,
				'result' : 'update play success'
			})
		}
	})
}

module.exports = updPlays;