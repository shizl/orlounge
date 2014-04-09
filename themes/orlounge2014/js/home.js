jQuery(document).ready(function() {

 jQuery('#edit-firstname').focus(function(){
      if(jQuery(this).val()=="Your First Name (required)"){
   	jQuery(this).val('');
       }
  });
 jQuery('#edit-firstname').blur(function(){
      if(jQuery(this).val().length==0){
   	jQuery(this).val('Your First Name (required)');
       }
  });


 jQuery('#edit-lastname').focus(function(){
      if(jQuery(this).val()=="Your Last Name"){
   	jQuery(this).val('');
       }
  });
 jQuery('#edit-lastname').blur(function(){
      if(jQuery(this).val().length==0){
   	jQuery(this).val('Your Last Name');
       }
  });

 jQuery('#edit-email').focus(function(){
      if(jQuery(this).val()=="Your Email (required)"){
   	jQuery(this).val('');
       }
  });
 jQuery('#edit-email').blur(function(){
      if(jQuery(this).val().length==0){
   	jQuery(this).val('Your Email (required)');
       }
  });

 jQuery('#edit-password-confirm').blur(function(){
      if(jQuery(this).val()!=jQuery('#edit-password').val()){
   	 alert('Passwords do not match');
       }
  });

});
