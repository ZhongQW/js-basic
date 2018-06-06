

window.onload = function() {
    var selectD =  document.getElementById("selectD");
    var passD = document.getElementById("passwordD");
    var nameD = document.getElementById("nameD");
    var btnD = document.getElementById("buttonD");
    var passZ = document.getElementById("passwordZ");
    var nameZ = document.getElementById("nameZ");
    var btnZ = document.getElementById("buttonZ");
    var selectZ =  document.getElementById("selectZ");
    var fromD = document.getElementById("fromD");
    var fromZ = document.getElementById("fromZ");
   btnZ.onclick=function(){
        console.log("Select:"+selectZ.value+",Name:"+nameZ.value+",Password:"+passZ.value);
    };
    btnD.onclick=function(){
        console.log("Select:"+selectD.value+",Name:"+nameD.value+",Password:"+passD.value);
    }
    //注册
    btnZ.onclick = function(){
        var identity;
        if (selectZ.value === '售票员'){
            identity = 0;
        }
        else{
            identity = 1;
        }
        $.ajax({
             type: "post",
             // dataType: "json",
             url: "http://localhost:8080/users/reg",
             data: {
                'username':nameZ.value,
                'password':passZ.value,
                 'identity':identity
             },
             success: function (res) {
                // console.log(result);
                if (!res.error) {
                    alert("注册成功,请重新登录");
                }else{
                    alert(res.result);
                }
             },
             error: function (res) {
                // alert(JSON.stringify(res));
                alert("注册失败："+ JSON.stringify(res));
             }
        });
    };


    //登陆
    btnD.onclick = function() {
            //判断用户登录的是什么身份！
            var urlD;
            var identity;
            if(selectD.value === "售票员") {
                urlD = "../售票员/mian-售票员.html";
                identity = 0;
            }
            else {
                urlD = "../管理员/main-管理员.html";
                identity = 1;
            }
           $.ajax({
                type: "post",
                dataType: "json",
                url: "http://localhost:8080/users/log",
                data: {
                    'username':nameD.value,
                    'password':passD.value,
                    'identity':identity
                },
                success: function (res) {
                    // console.log(res);
                    if (!res.error) {
                        // alert('登录成功');
                        // window.location = urlD;
                        window.location = urlD;
                    }else {
                        alert(res.result);
                    }
                },
                error: function () {
                    alert("登陆失败！");
                }
            });
        };
};
