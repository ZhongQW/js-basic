window.onload = function() {
    // $.ajax({
    //     type: "post",
    //     dataType: "json",
    //     url: "http://localhost:8080/seat",
    //     data: {
    //         'id':ww
    //     },
    //     success: function (res) {
    //         // console.log(result);
    //         if (!res.error) {
    var price = 80; //票价
    $(document).ready(function () {
        var $cart = $('#selected-seats'), //座位区
            $counter = $('#counter'), //票数
            $total = $('#total'); //总计金额

        var sc = $('#seat-map').seatCharts({
            map: [  //座位图
                'aaaaaaaaaaaaaaaaaa',
                'aaaaaaaaaaaaaaaaaa',
                '__________________',
                'aaaaaaaaaaaaaaa___',
                'aaaaaaaaaaaaaaaaaa',
                'aaaaaaaaaaaaaaaaaa',
                'aaaaaaaaaaaaaaaaaa',
                'aaaaaaaaaaaaaaaaaa',
                'aaaaaaaaaaaaaaaaaa',
                'aa__aa__aa__aa__aa'
            ],
            naming: {
                top: false,
                getLabel: function (character, row, column) {
                    return column;
                }
            },
            legend: { //定义图例
                node: $('#legend'),
                items: [
                    ['a', 'available', '可选座'],
                    ['a', 'unavailable', '已售出']
                ]
            },
            click: function () { //点击事件
                if (this.status() == 'available') { //可选座
                    $('<li>' + (this.settings.row + 1) + '排' + this.settings.label + '座</li>')
                        .attr('id', 'cart-item-' + this.settings.id)
                        .data('seatId', this.settings.id)
                        .appendTo($cart);

                    $counter.text(sc.find('selected').length + 1);
                    $total.text(recalculateTotal(sc) + price);

                    return 'selected';
                } else if (this.status() == 'selected') { //已选中
                    //更新数量
                    $counter.text(sc.find('selected').length - 1);
                    //更新总计
                    $total.text(recalculateTotal(sc) - price);

                    //删除已预订座位
                    $('#cart-item-' + this.settings.id).remove();
                    //可选座
                    return 'available';
                } else if (this.status() == 'unavailable') { //已售出
                    return 'unavailable';
                } else {
                    return this.style();
                }
            }
        });

    });
//计算总金额
    function recalculateTotal(sc) {
        var total = 0;
        sc.find('selected').each(function () {
            total += price;
        });

        return total;
    }
}