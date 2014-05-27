<?php

function get_hospital_by_state($state="AL",$vid=6){
  
   $hospitals = array();
   $state_id = db_query('select tid from {taxonomy_term_data} where name =:name and vid =:vid',array(':name'=>$state,':vid'=>$vid))->fetchfield();  
   $hot_name_array = db_query('select tid, name from {taxonomy_term_data} where tid in (select tid from {taxonomy_term_hierarchy} where parent =:parent)',array(':parent'=>$state_id));      

    foreach($hot_name_array as $hot){
       $hospitals[$hot->tid] = $hot->name;
    }

  $exist_hot_arr = db_query("select title from {node} where type='group'");
  
   foreach($exist_hot_arr as $exist_hot){
       $hot_id = db_query('select tid from {taxonomy_term_data} where name =:name',array(':name'=>$exist_hot->title))->fetchfield();  
      unset($hospitals[$hot_id]);
   }
 return $hospitals;
}

function get_join_group($state="AL",$vid=6){
 
  $hospitals = array();
      $hospitals_arr = db_query('select nid , type from {hospital} where state = :state',array(':state'=>$state));
        
      foreach($hospitals_arr as $value){
        $hot_name = db_query(' select name from {taxonomy_term_data} where tid=:tid and vid=:vid',array(':tid'=>$value->type,':vid'=>$vid))->fetchfield();
        $hospitals[$value->nid] = $hot_name;
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
  $form['hospital_location']['type'] = array(
    '#title'=>t('Type'),
    '#type'=>'select',
    '#options'=>array('6'=>'Hospital','7'=>'Ambulatory Surgery Center'),
  );
  $default_hot = get_hospital_by_state();
  $form['hospital_location']['hospital'] = array(
    '#title'=>t('Hospital'),
    '#type'=>'select',
    '#options' =>empty($form_state['values']['state'])?$default_hot:get_hospital_by_state($form_state['values']['state'],$form_state['values']['type']),
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
   $hot_name = db_query(' select name from {taxonomy_term_data} where tid=:tid',array(':tid'=>$form_state['values']['hospital']))->fetchfield();
   $newNode = (object) NULL; 
   $newNode->type = 'group'; 
   $newNode->uid = $user->uid; 
   $newNode->title = $hot_name;
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
   $newNode->field_og_subscribe_settings[$newNode->language][0]['value']='approval';
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

   drupal_goto('create/access');
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
  $form['Join_Form']['type'] = array(
    '#title'=>t('Type'),
    '#type'=>'select',
    '#options'=>array('6'=>'Hospital','7'=>'Ambulatory Surgery Center'),
  );
  $default_hot = get_join_group();
  $form['Join_Form']['hospital'] = array(
    '#title'=>t('Hospital'),
    '#type'=>'select',
    '#options' => empty($form_state['values']['state'])?$default_hot:get_join_group($form_state['values']['state'],$form_state['values']['type']),
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
  
  $status = db_query("select status from {node} where type='group' and nid =".$form_state['values']['hospital'])->fetchfield();
  if($status){
  drupal_set_message('Thank you!');
  $form_state['redirect'] = 'node/'.$form_state['values']['hospital'];
  }else{
     drupal_set_message('This Group is not published.','warning');
  } 
}


