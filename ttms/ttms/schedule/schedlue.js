window.onload = function(){
    //动态加载
    var table = document.getElementById("customers");
    $.ajax({
        type:"post",
        url:"http://localhost:8080/",
        success:function(res){
            if(!res.error) {
                for (var i = 0; i < res.result.length; i++) {
                    var div = document.createElement("div");
                    var p_img = document.createElement("img");
                    var p_name = document.createElement("name");
                    var p_time = document.createElement("time");
                    div.className = 'schedule';
                    p_img.src = res.result[i].play_image;
                    p_name.innerHTML = res.result[i].play_name;
                    p_time.innerHTML = res.result[i].sched_time;
                    div.appendChild(p_img);
                    div.appendChild(p_name);
                    div.appendChild(p_time);
                }
            }else{
                alert(res.result);
            }
        },
        error:function(res){
            alert("加载失败！"+JSON.stringify(res));
        }
    })

    //未安排的剧目
    $('#btnP').onclick = function(){
        $.ajax({
            type:"post",
            url:"http://localhost:8080/",
            data:{

            },
            success:function(res){
                if(!res.error) {
                }
            }
   })
}
    //安排剧目
    $('#btnAdd').onclick = function(){

    }
    //选择剧目
    function select(e){
        var logo = 1;
        e.target.setAttribute("play_select")
    };
}