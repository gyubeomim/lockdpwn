$(function(){
  /*터치 슬라이드 비주얼 영역*/
   window.mySwipe =$('#mySwipe').Swipe({
     auto: 3000,  //배너가 3초 간격으로 이동합니다.
     continuous: true, // 반복해서 롤링됩니다.
     callback: function(index, element) { //이벤트가 완료되면 실행합니다.
    
        /*클래스 "active"를 포함하는 불릿 버튼을 비활성화 버튼으로 만들고, 
        "active" 클래스를 삭제합니다.*/
        $(".touch_bullet .active")
        .attr("src",$(".touch_bullet .active")
        .attr("src").replace("on.png","off.png"))
        .removeClass("active"); 
    
        /*인덱스(index)에 해당하는 불릿 버튼을 활성화된 버튼으로 만들고, 
        "active" 클래스를 생성합니다.*/
        $(".touch_bullet img").eq(index)
        .attr("src",$(".touch_bullet img").eq(index)
        .attr("src").replace("off.png","on.png"))
        .addClass("active");
     }
  }).data('Swipe');
    
    
  /*비주얼 이전, 다음 버튼*/
  $(".touch_left_btn a").on("click",function(){//이전 버튼을 누를 때마다...
     mySwipe.prev(); //이전 배너로 이동합니다.
     return false; //링크를 차단합니다.
  });
  $(".touch_right_btn a").on("click",function(){//다음 버튼을 누를 때마다...
     mySwipe.next(); //다음 배너로 이동합니다.
     return false; //링크를 차단합니다.
  });
    
    
  /*롤링 버튼 배너*/
  // 첫 번째 배너를 제외하고 숨깁니다.
  $("#roll_banner_wrap dd").not(":first").hide(); 

  // 첫 번째 버튼의 <a>를 저장합니다.
  var onBtn=$("#roll_banner_wrap dt a:first"); 
    
  $("#roll_banner_wrap dt a").on("click",function(){//1~4버튼을 클릭할 때...
      $("#roll_banner_wrap dd:visible").hide(); // 노출되어있는 배너를 숨깁니다.
    
      /*onBtn에 하위 요소 <img>에 "src"속성을 비활성화된
      이미지 경로로 바꿉니다.*/
      $("img",onBtn).attr("src",
      $("img",onBtn).attr("src").replace("over.gif","out.gif"));
    
      //1~4번 버튼 중 클릭한 버튼 <a>요소에 인덱스 값을 구해옵니다.
      var num=$("#roll_banner_wrap dt a").index(this);
      //클릭한 버튼에 인덱스 값과 일치하는 <dd>요소만 나타냅니다.
      $("#roll_banner_wrap dd").eq(num).show();
    
      /*클릭한 <a>에 하위 <img>에 "src"속성을 활성화된 
      버튼 이미지 경로로 바꿉니다.*/
      $("img",this).attr("src",
      $("img",this).attr("src").replace("out.gif","over.gif"));
    
      //클릭 이벤트가 발생한 버튼에 <a>요소가 변수 onBtn에 할당됩니다.
      onBtn=$(this);
    
      return false; //<a>에 링크를 차단합니다.
  });
    
  $(".playBtn").on("click",function(){//재생 버튼을  클릭했을 때...
     clearTimeout(auto1); //auto1에 할당된 seTimeout을 제거합니다.
     auto1=setTimeout(autoPlay,1000); //1초마다 autoPlay 함수를 실행합니다.
    
     //재생 버튼에 "src"속성을 활성화된 버튼 이미지로 바꿉니다.
     $("img",this).attr("src",
	 $("img",this).attr("src").replace("off.gif","on.gif"));
    
     //스톱 버튼에 "src"속성을 비활성화된 버튼이미지로 바꿉니다.
     $(".stopBtn img").attr("src",
     $(".stopBtn img").attr("src").replace("on.gif","off.gif"));
    
      return false; //<a> 링크를 차단합니다.
  });
   
  $(".stopBtn").on("click",function(){//스톱 버튼을  클릭했을 때...
      clearTimeout(auto1); //auto1에 할당된 seTimeout을 제거합니다.
    
      //스톱 버튼에 "src"속성을 활성화된 버튼이미지로 바꿉니다.
     $("img",this).attr("src",
     $("img",this).attr("src").replace("off.gif","on.gif"));
    
      //재생 버튼에 "src"속성을 비활성화된 버튼 이미지로 바꿉니다.
     $(".playBtn img").attr("src",
     $(".playBtn img").attr("src").replace("on.gif","off.gif"));
    
      return false; //<a>에 링크를 차단합니다.
  });
    
  var btnNum=0;
  function autoPlay(){//1~4버튼이 순서대로 강제 클릭 이벤트가 발생되는 함수
    btnNum++;
    if(btnNum>=4) btnNum=0;
    
    //1~4버튼이 btnNum 값에 따라 순서대로 선택되고 강제로 클릭됩니다.
    $("#roll_banner_wrap dt a").eq(btnNum).trigger("click");
    
    /*4초 간격으로 재귀함수 호출이 발생합니다. 그러므로 autoPlay()함수에
    일련의 실행문이 반복 실행됩니다.*/
    auto1=setTimeout(autoPlay,4000);
  }
    
  //최초 로딩시 3초 이후에 function autoPlay(){ ... }를 실행합니다.
  var auto1=setTimeout(autoPlay,3000);
    
  /*탭메뉴*/
  //초기에 활성화된 첫 번째 탭 버튼 <a>만 변수 onTab에 할당하엿습니다.
  var onTab=$("#tabmenu dt a:first");
    
  //탭 버튼에 마우스 오버, 포커스 이동, 클릭했을 때 이벤트 핸들러가 실행됩니다.
  $("#tabmenu dt a").on("mouseover focus click",function(){
      $("#tabmenu dd:visible").hide(); //현재 보이는 게시물 목록을 숨깁니다.
    
      /*onTab에 할당된 요소의 하위 <img>에 "src" 속성을 비활성화
      버튼이미지로 바꿉니다.*/
      $("img",onTab).attr("src",$("img",onTab).attr("src").replace("over.gif",
  "out.gif"));
    
      //클릭한 <a>에 부모 요소인 <dt>에 다음 요소만 노출시킵니다.
      $(this).parent().next().show(); 
    
      //클릭한 <a>에 하위 버튼 이미지를 활성화된 이미지로 바꿉니다.
      $("img",this).attr("src",$("img",this).attr("src").replace("out.gif","over.gif"));
      
      onTab=$(this); //클릭할 때 마다 클릭한 요소에 <a>가 onTab에 할당됩니다.
      return false; //링크를 차단하였스니다.
  });

  /* 베스트북 슬라이더 */
  var mySlider=$("#best_bg ul").bxSlider({
      mode:"horizontal",
        speed:500,
        pager:false,
        moveSlides:1,
        slideWidth:125,
        minSlides:5,
        maxSlides:5,
        slideMargin:30,
        auto:true,
        autoHover:true,
        controls:false
  });

  $(".prev_btn").on("click",function(){
  mySlider.goToPrevSlide();
  return false;
  });

  $(".next_btn").on("click",function(){
  mySlider.goToNextSlide();
  return false;
  });

   /*팝업 연동*/
  if($.cookie("pop") != "no") $("#pop_wrap").show();
   $("#pop_wrap").css("cursor","move").draggable();

   $("#pop_wrap area:eq(0)").on("click",function(){
      $("#pop_wrap").fadeOut("fast");
      return false;
  });

  $("#pop_wrap area:eq(1)").on("click",function(){
      $.cookie("pop","no",{expires:1});
      $("#pop_wrap").fadeOut("fast");
      return false;
  });
});