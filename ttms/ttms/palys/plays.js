window.onload = function() {
    var btnAdd = document.getElementById("btnAdd");
    //动态加载剧目信息
    //0 :动作片, 1 : 喜剧片 , 2 : 恐怖片, 3 : 家庭片
    //0 : 国语 , 1 : 粤语, 2 : 英语, 3 : 韩语, 4 : 日语}
    //0：待安排演出 , 1：已安排演出, -1：下线
    var table = document.getElementById("table");
    $.ajax({
        type: "get",
        url: "http://localhost:8080/",
        success: function (res) {
            if (!res.error) {
                for (var i = 0; i < res.result.length; i++) {
                    var tr = document.createElement("tr");
                    var tdname = document.createElement("td");
                    var tdtype = document.createElement("td");
                    var tdlang = document.createElement("td");
                    var tdtime = document.createElement("td");
                    var tdtickt = document.createElement("td");
                    var tdstatus = document.createElement("td");
                    tr.index = res.result[i].play_id;
                    var tdCao = document.createElement("td");
                    var tda2 = document.createElement("a");
                    tda2.innerHTML = "上线  ";
                    tda2.addEventListener("click", onlineP, false);
                    var tda3 = document.createElement("a");
                    tda3.innerHTML = "下线  ";
                    tda3.addEventListener("click", outlinP, false);
                    var tda4 = document.createElement("a");
                    tda4.innerHTML = "删除";
                    tda4.addEventListener("click", deleteP, false);
                    tdCao.appendChild(tda2);
                    tdCao.appendChild(tda3);
                    tdCao.appendChild(tda4);

                    var lang;
                    switch (res.result[i].play_lang_id) {
                        case 0:
                            lang = '国语';
                            break;
                        case 1:
                            lang = '粤语';
                            break;
                        case 2:
                            lang = '英语';
                            break;
                        case 3:
                            lang = '韩语';
                            break;
                        case 4:
                            lang = '日语';
                            break;
                        default:
                            lang = '国语';
                    }

                    var status;
                    switch (res.result[i].play_status) {
                        case 0:
                            status = '待安排演出';
                            break;
                        case 1:
                            status = '已安排演出';
                            break;
                        case -1:
                            status = '下线';
                            break;
                        default:
                            status = '待安排演出';
                    }

                    var type;
                    switch (res.result[i].play_type_id) {
                        case 0:
                            status = '动作片';
                            break;
                        case 1:
                            status = '喜剧片';
                            break;
                        case 2:
                            status = '恐怖片';
                            break;
                        case 3:
                            status = '家庭片';
                            break;
                        default:
                            status = "动作片";
                    }

                    tdname.innerHTML = res.result[i].play_name;
                    tdtype.innerHTML = type;
                    tdlang.innerHTML = lang;
                    tdtime.innerHTML = res.result[i].play_length;
                    tdtickt.innerHTML = res.result[i].play_ticket_price;
                    tdstatus.innerHTML = status;

                    tr.appendChild(tdname);
                    tr.appendChild(tdtype);
                    tr.appendChild(tdlang);
                    tr.appendChild(tdtime);
                    tr.appendChild(tdtickt);
                    tr.appendChild(tdstatus);
                    tr.appendChild(tdCao);
                    table.appendChild(tr);
                }
                hover();
            }else{
                    alert(res.result);
                }
            },
            error: function (res) {
                alert("加载失败！" + JSON.stringify(res));
            }
    })
    var  getFile=()=>{
        var fileUrl = $('#xdaTanFileImg').value;
    }
    //添加剧目
    btnAdd.onclick = function () {

        $.ajax({
            type: "post",
            dataType: "json",
            url: "http://localhost:3000/plays/add",
            data: {
                'type': $('#select').value,             //剧目类型
                'lang': $('#lang').value,             //语言
                'name': $('#name').value,          //剧目名称
                'introduction': $('#introduction').value,   //介绍
                'image': fileUrl,          //图片
                'time': $('#length').value,             //时间
                'price': $('#price').value,        //价钱
            },
            success: function (res) {
                if (!res.error) {
                    var tr = document.createElement("tr");
                    var tdname = document.createElement("td");
                    var tdtype = document.createElement("td");
                    var tdlang = document.createElement("td");
                    var tdtime = document.createElement("td");
                    var tdtickt = document.createElement("td");
                    var tdstatus = document.createElement("td");
                    tr.index = res.id.play_id;
                    tdname.innerHTML = $('#name').value;
                    tdtype.innerHTML = $('#select').value;
                    tdlang.innerHTML = $('#lang').value;
                    tdtime.innerHTML = $('#length').value;
                    tdtickt.innerHTML = $('#price').value;
                    tdstatus.innerHTML = '待安排演出';

                    var tdCao = document.createElement("td");
                    var tda2 = document.createElement("a");
                    tda2.innerHTML = "上线  ";
                    tda2.addEventListener("click", onlineP, false);
                    var tda3 = document.createElement("a");
                    tda3.innerHTML = "下线  ";
                    tda3.addEventListener("click", outlinP, false);
                    var tda4 = document.createElement("a");
                    tda4.innerHTML = "删除";
                    tda4.addEventListener("click", deleteP, false);
                    tdCao.appendChild(tda2);
                    tdCao.appendChild(tda3);
                    tdCao.appendChild(tda4);

                    tr.appendChild(tdname);
                    tr.appendChild(tdtype);
                    tr.appendChild(tdlang);
                    tr.appendChild(tdtime);
                    tr.appendChild(tdtickt);
                    tr.appendChild(tdstatus);
                    tr.appendChild(tdCao);
                    table.appendChild(tr);
                } else {
                    alert(res.result);
                }
            },
            error: function () {
                alert("添加失败！");
            }
        });
    }


    //修改剧目状态

    //上线
    function onlineP(t) {
        var result = confirm("确认上线吗？");
        if(result){
            $.ajax({
                type: "get",
                url: "http://localhost:8080/play/online",
                data: {
                    "play_id": t.target.parentNode.index
                },
                success: function(res){//res里面包含了修改后的结果
                    if(!res.error){

                        var index = t.target.parentNode.rowIndex;
                        table.rows[index].cells[5].innerHTML = "res.result";
                    }else{
                        alert(res.result);
                    }
                },
                error: function(res){
                    alert("修改失败"+JSON.stringify(res));
                }
            })
        }
    }

    //下线
    function outlineP(t) {
        var result = confirm("确认下线吗？");
        if(result){
            $.ajax({
                type: "get",
                url: "http://localhost:8080/play/outline",
                data: {
                    "play_id": t.target.parentNode.index
                },
                success: function(res){//res里面包含了修改后的结果
                    if(!res.error){
                        var index = t.target.parentNode.rowIndex;
                        table.rows[index].cells[5].innerHTML = "res.result";
                    }else{
                        alert(res.result);
                    }
                },
                error: function(res){
                    alert("修改失败"+JSON.stringify(res));
                }
            })
        }
    }

    //删除
    function deleteP(t) {
        var result = confirm("确认删除？");
        if (result) {
            $.ajax({
                type: "get",
                url: "http://localhost:8080/play/del",
                data: {
                    "play_id": t.target.parentNode.index
                },
                ssuccess: function (res) {
                    if (!res.error) {
                        var index = t.target.parentNode.rowIndex;
                        table.deleteRow(index);
                    } else {
                        alert(res.result);
                    }
                },
                error: function (res) {
                    alert("删除失败！" + JSON.stringify(res));
                }
            });
        }
    }


function hover(){
    //滑动变色
    var rows = document.getElementsByTagName("tr");
    for(var i=0 ;i<rows.length; i++)
    {
        rows[i].onmouseover = function(){//鼠标移上去,添加一个类'hou'
            this.className += 'hou';
        }
        rows[i].onmouseout = function(){//鼠标移开,改变该类的名称
            this.className = this.className.replace('hou','');
        }
    }
}
}