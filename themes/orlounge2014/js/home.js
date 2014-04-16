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

 jQuery('.add-comment-body').each(function(){
      jQuery(this).blur(function(){
      if(jQuery(this).val().length==0){
   	jQuery(this).val('Write a comment...');
       }
      
      });
       jQuery(this).focus(function(){
   
      if(jQuery(this).val()=="Write a comment..."){
   	jQuery(this).val('');
       }
      });
  
 }); 


});


function enterIn(evt,nid,uid){
  var evt=evt?evt:(window.event?window.event:null);

  if(evt.keyCode==13){
  comment = jQuery('.comment-node-'+nid).val();
         jQuery.post("/add_new_comment", {
      nid : nid,
      uid : uid,
      comment:comment	
    }, function(data){      
       jQuery('#node-'+nid+' .post-comment .form-textarea-wrapper').before(data);
      jQuery('.comment-node-'+nid).val('');
    }, "text");
  }

}

