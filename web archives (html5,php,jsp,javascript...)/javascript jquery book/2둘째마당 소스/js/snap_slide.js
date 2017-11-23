var myScroll;
function i_scroll(m){
    var imgWidth=m.width;
    $("#sc_wrap").css("max-width",imgWidth+"px");
    $("#scroller").width($("#scroller>li").size()*100+"%");
    $("#scroller>li").width(100/$("#scroller li").size()+"%");
    $("#indicator").css("margin-left",-($("#indicator").width()/2)+"px");
    myScroll = new IScroll('#sc_wrap', {
      vScrollbar:true,
      scrollX: true,
      scrollY: true,
      momentum: false,
      snap: true,
      snapSpeed: 400,
      keyBindings: false
    });
    myScroll.on("scrollEnd", function() {
      var bulletNum=Math.floor(Math.abs(myScroll.x/$("#sc_wrap").width()));
      $("#indicator .active").removeClass("active");
      $("#indicator li").eq(bulletNum).addClass("active");
	  return bulletNum;
    });
}
document.addEventListener('touchmove', function (e) { e.preventDefault(); }, false);