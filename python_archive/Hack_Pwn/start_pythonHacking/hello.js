name = 'id';
value = 'HongGilDong';

var todayDate = new Date();

todayDate.setHours(todayDate.getDate() + 7);
document.cookie = name + "=" + escape( value ) + "; path=/; expires=" + todayDate.toGMTString() + "";
alert(document.cookie)
