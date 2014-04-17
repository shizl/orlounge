<?php

function get_hospital_by_state($state="AK"){
  
   $hospitals = array();
  switch($state){
   case 'AK':
    $hospitals  = array(
		'ALASKA NATIVE MEDICAL CENTER'=>'ALASKA NATIVE MEDICAL CENTER',
		'ALASKA REGIONAL HOSPITAL'=>'ALASKA REGIONAL HOSPITAL',
		'BARTLETT REGIONAL HOSPITAL'=>'BARTLETT REGIONAL HOSPITAL',
		'CENTRAL PENINSULA GENERAL HOSPITAL'=>'CENTRAL PENINSULA GENERAL HOSPITAL',
		'FAIRBANKS MEMORIAL HOSPITAL'=>'FAIRBANKS MEMORIAL HOSPITAL',
		'KETCHIKAN GENERAL HOSPITAL'=>'KETCHIKAN GENERAL HOSPITAL',
		'MAT-SU REGIONAL MEDICAL CENTER'=>'MAT-SU REGIONAL MEDICAL CENTER',
		'MT EDGECUMBE HOSPITAL'=>'MT EDGECUMBE HOSPITAL',
		'PROVIDENCE ALASKA MEDICAL CENTER'=>'PROVIDENCE ALASKA MEDICAL CENTER',
		'SITKA COMMUNITY HOSPITAL'=>'SITKA COMMUNITY HOSPITAL',
		'SOUTH PENINSULA HOSPITAL'=>'SOUTH PENINSULA HOSPITAL',
		'WRANGELL MEDICAL CENTER'=>'WRANGELL MEDICAL CENTER',
		'YUKON KUSKOKWIM DELTA REG HOSPITAL'=>'YUKON KUSKOKWIM DELTA REG HOSPITAL',
		);
   break;
   case 'AL':
    $hospitals  = array(
		'ANDALUSIA REGIONAL HOSPITAL'=>'ANDALUSIA REGIONAL HOSPITAL',
		'ATHENS-LIMESTONE HOSPITAL'=>'ATHENS-LIMESTONE HOSPITAL',
		'ATMORE COMMUNITY HOSPITAL'=>'ATMORE COMMUNITY HOSPITAL',
		'BAPTIST MEDICAL CENTER EAST'=>'BAPTIST MEDICAL CENTER EAST',
		'BAPTIST MEDICAL CENTER SOUTH'=>'BAPTIST MEDICAL CENTER SOUTH',
		'BIBB MEDICAL CENTER'=>'BIBB MEDICAL CENTER',
		'BROOKWOOD MEDICAL CENTER'=>'BROOKWOOD MEDICAL CENTER',
		'BRYAN W WHITFIELD MEM HOSP INC'=>'BRYAN W WHITFIELD MEM HOSP INC',
		'BULLOCK COUNTY HOSPITAL'=>'BULLOCK COUNTY HOSPITAL',
		'CALLAHAN EYE FOUNDATION HOSPITAL'=>'CALLAHAN EYE FOUNDATION HOSPITAL',
		'CHEROKEE MEDICAL CENTER'=>'CHEROKEE MEDICAL CENTER',
		'CHILTON MEDICAL CENTER'=>'CHILTON MEDICAL CENTER',
		'CITIZENS BAPTIST MEDICAL CENTER'=>'CITIZENS BAPTIST MEDICAL CENTER',
		'CLAY COUNTY HOSPITAL'=>'CLAY COUNTY HOSPITAL',
		'COMMUNITY HOSPITAL INC'=>'COMMUNITY HOSPITAL INC',
		'COOPER GREEN HOSPITAL'=>'COOPER GREEN HOSPITAL',
		'COOSA VALLEY MEDICAL CENTER'=>'COOSA VALLEY MEDICAL CENTER',
		'CRENSHAW COMMUNITY HOSPITAL'=>'CRENSHAW COMMUNITY HOSPITAL',
		'CRESTWOOD MEDICAL CENTER'=>'CRESTWOOD MEDICAL CENTER',
		'CULLMAN REGIONAL MEDICAL CENTER'=>'CULLMAN REGIONAL MEDICAL CENTER',
		'D C H REGIONAL MEDICAL CENTER'=>'D C H REGIONAL MEDICAL CENTER',
		'D W MCMILLAN MEMORIAL HOSPITAL'=>'D W MCMILLAN MEMORIAL HOSPITAL',
		'DALE MEDICAL CENTER'=>'DALE MEDICAL CENTER',
		'DECATUR GENERAL HOSPITAL'=>'DECATUR GENERAL HOSPITAL',
		'EAST ALABAMA MEDICAL CENTER AND SNF'=>'EAST ALABAMA MEDICAL CENTER AND SNF',
		'ELBA GENERAL HOSPITAL'=>'ELBA GENERAL HOSPITAL',
		'ELIZA COFFEE MEMORIAL HOSPITAL'=>'ELIZA COFFEE MEMORIAL HOSPITAL',
		);
   break;
   } 

 return $hospitals;
}

function create_group_form($form,&$form_state){

  // location_get_provinces($country = 'us');
 
  $form['page_title'] = array(
    '#markup'=>'<h2>'.t('Create a new ORLounge').'</h2>
    <h4>'.t('Read carefully before you Continue').'</h4>
    <p>'.t('www.ORLOUNGE.com is a site for people who work in a hospital-based or
           ASE operating room environment. You are registering to be a member of 
          a private password-protected Operating Room Lounge Site that is administered
         by the operating room that you wish to join. All potenial members must work in 
         an operating room and must be verified by the operating room. All requests for
        membership will send to the local site administrator for verification, Who will
        that approve or disapprove your membership. Once approved for membership, you
        will be notified and you can enjoy all the privileges of membership.').'</p>',
  );

  $form['hospital_location'] = array(
    '#type'=>'fieldset',
    '#title'=>t('Hospital Location'),
    '#collapsible' => FALSE, 
    '#collapsed' => FALSE,
  );

  $form['hospital_location']['country'] = array(
    '#title'=>t('Country'),
    '#type'=>'select',
    '#options'=> array('US'=>'United States'),
  );
  $form['hospital_location']['state'] = array(
    '#title'=>t('State'),
    '#type'=>'select',
    '#options'=>location_get_provinces(),
    '#ajax' => array(
      'callback' => 'state_choice',
      'wrapper' => 'hospital_wrapper',
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );
  $default_hot = get_hospital_by_state();
  $form['hospital_location']['hospital'] = array(
    '#title'=>t('Hospital'),
    '#type'=>'select',
    '#options' =>empty($form_state['values']['state'])?$default_hot:get_hospital_by_state($form_state['values']['state']),
    '#prefix' => '<div id="hospital_wrapper">',
    '#suffix' => '</div>', 

  );
  $form['hospital_location']['logo'] = array(
    '#title' => t('Logo'),
    '#type' => 'managed_file',
    '#description' => t('The uploaded image will be displayed on this page using the image style choosen below.'),
    '#upload_location' => 'public://',
  );
  $form['hospital_location']['message'] = array(
    '#title'=>'Message from OR Manager',
    '#type'=>'textarea',
  );
  $form['hospital_location']['submit'] = array(
    '#type'=>'submit',
    '#value'=>t('Submit Application'),
  );
  return $form;
}


function state_choice($form ,&$form_state){
 
   return $form['hospital_location']['hospital'];
}

function create_group_form_submit($form,&$form_state){

  global $user;  
  // Create a node object, and add node properties. 

   $files = db_query('select * from {file_managed} where fid = '.$form_state['values']['logo']);
   $image = (object) NULL; 
    foreach($files as $file){
    $image = $file;
    }  

  if($form_state['values']['hospital']!=null){
   $newNode = (object) NULL; 
   $newNode->type = 'group'; 
   $newNode->uid = $user->uid; 
   $newNode->title = $form_state['values']['hospital'];
   $newNode->created = strtotime("now");
   $newNode->changed = strtotime("now");
   $newNode->status = 0; 
   $newNode->comment = 0; 
   $newNode->promote = 0; 
   $newNode->sticky = 0; 
   $newNode->tnid = 0; 
   $newNode->language = 'und';
    $newNode->field_group_logo['und'][0] = (array)$image;
   if($form_state['values']['message']!=null){
      $newNode->body[$newNode->language][0]['value'] = $form_state['values']['message'];
   }else{
   $newNode->body[$newNode->language][0]['value'] ='';
   }
   $newNode->body[$newNode->language][0]['summary'] = '';
   $newNode->body[$newNode->language][0]['format'] = 'filtered_html'; 

  node_object_prepare($newNode);
  // Save the node.  // The node will also get published, if $newNode->status was set to 1. 
   $node = node_submit($newNode);
   node_save($node);
    $nid = db_query("select nid from {node} where type = 'group' order by nid desc LIMIT 0 , 1")->fetchfield();
     db_insert('hospital') 
	->fields(array(
  	'nid' => $nid,
  	'country' => $form_state['values']['country'],
  	'state' => $form_state['values']['state'],
	'type'=>$form_state['values']['hospital'],
	))->execute(); 

   drupal_set_message('Thank you! Please wait Management Audit.');
  }
}

function join_group_form($form,&$form_state){
    
   $form['page_title'] = array(
    '#markup'=>'<h2>'.t('Join an existing ORLounge').'</h2>
    <h4>'.t('Read carefully before you Continue').'</h4>
    <p>'.t('www.ORLOUNGE.com is a site for people who work in a hospital-based or
           ASE operating room environment. You are registering to be a member of 
          a private password-protected Operating Room Lounge Site that is administered
         by the operating room that you wish to join. All potenial members must work in 
         an operating room and must be verified by the operating room. All requests for
        membership will send to the local site administrator for verification, Who will
        that approve or disapprove your membership. Once approved for membership, you
        will be notified and you can enjoy all the privileges of membership.').'</p>',
  );

  $form['Join_Form'] = array(
    '#type'=>'fieldset',
    '#title'=>t('Join Form'),
    '#collapsible' => FALSE, 
    '#collapsed' => FALSE,
  );
   $form['Join_Form']['country'] = array(
    '#title'=>t('Country'),
    '#type'=>'select',
    '#options'=> array('US'=>'United States'),
  );
  $form['Join_Form']['state'] = array(
    '#title'=>t('State'),
    '#type'=>'select',
    '#options'=>location_get_provinces(),
    '#ajax' => array(
      'callback' => 'join_form_state_choice',
      'wrapper' => 'join_form_hospital_wrapper',
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );
  $default_hot = get_hospital_by_state();
  $form['Join_Form']['hospital'] = array(
    '#title'=>t('Hospital'),
    '#type'=>'select',
    '#options' =>empty($form_state['values']['state'])?$default_hot:get_hospital_by_state($form_state['values']['state']),
    '#prefix' => '<div id="join_form_hospital_wrapper">',
    '#suffix' => '</div>', 

  );
  $form['Join_Form']['message'] = array(
    '#title'=>'Message from OR Manager',
    '#type'=>'textarea',
  );
  $form['Join_Form']['submit'] = array(
    '#type'=>'submit',
    '#value'=>t('Submit Application'),
  );
  return $form;
}
function join_form_state_choice($form,&$form_state){
 return $form['Join_Form']['hospital'];
}


function join_group_form_submit($form,&$form_state){
 
}


