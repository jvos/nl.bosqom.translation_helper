/* 
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
jQuery( document ).ready(function() {   
    jQuery.ajax({
        url: base_url + '/admin/config/regional/translate/translation_helper/translation_text/process'
    });
    
    var intervalId = setInterval(function() {
                
        jQuery.ajax({
            url: base_url + '/admin/config/regional/translate/translation_helper/translation_text/status',
            success: function(data){
       
                data = unserialize(data);

                jQuery( '.translation_helper #progress .bar .filled' ).css('width', data.percent + '%');
                jQuery( '.translation_helper #progress .percentage' ).html(data.percent + '%');

                jQuery( '.translation_helper #progress .message' ).html(data.count + ' ' + data.message);

                if('status' == data.status || 'error' == data.status){
                    clearInterval(intervalId);
                    translation_helper_goto(base_url, '/admin/config/regional/translate/translation_helper/translation_text');
                }
            }
        });
    }, 1000); // updates every second
});