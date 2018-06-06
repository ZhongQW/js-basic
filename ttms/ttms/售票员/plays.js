window.onload = function(){

    //正在热映
    var aCover = document.getElementsByClassName('cover');
    var aList = document.getElementsByClassName('l-list');
    var aLi = document.getElementsByClassName('l-li');
    var oLi = aLi[0];
    var alBtn = document.getElementsByClassName('l-left');
    var arBtn = document.getElementsByClassName('l-right');
    var alen = aList.length;
    var ilen = aLi.length;

    for(var i = 0; i < alen; i ++) {
        aCover[i].style.width = oLi.clientWidth*5 + 2 + 'px';
        aList[i].style.width = oLi.clientWidth*ilen + 2 +'px';
        aCover[i].style.height = aList[i].style.height = oLi.clientHeight + 1 + 'px';
        aList[i].index = i;
        alBtn[i].index = i;
        arBtn[i].index = i;
    }

    var len = alBtn.length;
    for(i = 0; i < len; i ++) {
        arBtn[i].addEventListener('click',function(e) {
            var index = e.target.index;
            var distance ;
            var dislen = ilen*oLi.clientWidth;
            if(aList[index].offsetLeft + dislen > 1000) {
                distance = -5 * oLi.clientWidth;
                move(aList[index], aList[index].offsetLeft + distance);
            }else {
                var num = ilen%5 * oLi.clientWidth;
                if(num == 0) {
                    move(aList[index],0);
                }else{
                    move(aList[index],aList[index].offsetLeft + (-1)*num * oLi.clientWidth);
                }
            }
        },false);
        alBtn[i].addEventListener('click',function(e){
            var index = e.target.index;
            var distance ;
            var dislen = ilen*oLi.clientWidth;
            if(aList[index].offsetLeft < 0) {
                move(aList[index], aList[0].offsetLeft +5*oLi.clientWidth);
            }else {
                move(aList[index], -(dislen - 5*(oLi.clientWidth)));
            }
        },false);
    }
    var timer = null;
    function move(aLi, distance) {
        clearTimeout(timer);
        var speed = (distance - aLi.offsetLeft)/3;
        speed = speed > 0 ? Math.ceil(speed) : Math.floor(speed);
        timer = setTimeout(function(){
            aLi.style.left = aLi.offsetLeft + speed + 'px';
            move(aLi,distance);
            if(aLi.offsetLeft == distance){
                clearTimeout(timer);
            }
        },50);
    }

    //即将上映
}