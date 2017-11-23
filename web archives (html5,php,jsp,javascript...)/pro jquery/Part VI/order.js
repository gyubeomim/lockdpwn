$(document).ready(function() {

    //extract the data from the table    
    var data = new Object();
    $('tr').each(function(index, elem) {
        var sel = $(this).children();
        data[sel.eq(0).text()] = sel.eq(1).text();
    })
    // remove the table
    $('#data').remove();

    // 

});