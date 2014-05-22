<div class="post-content" id="node-<?php print $node->nid ;?>">
  <div class="content">
    <div class="user-picture"><?php print $user_picture?></div>
    <div class="user-name"><?php $account = user_load($node->uid);  print $account->name; ?></div>
    <div class="post-body"><?php print $node->body['und'][0]['value']; ?></div>
    <div class="post-created"><?php print format_interval((time() - $node->created) , 2) . t(' ago') ?><span class="count_comment"> 
    <?php $num = db_query('select count (distinct nid) from {comment} where nid =:nid',array(':nid'=>$node->nid))->fetchfield(); echo $num; ?>
  people comment on this post </span></div>
  </div>
  <div class="post-comment">
     <?php  
$comment_body = db_query('select comment_body_value,entity_id from {field_data_comment_body} where entity_id in (select cid from {comment} where nid = :nid)',array(':nid'=>$node->nid));

    foreach($comment_body as $value){

    $arr = db_query('select uid,created from {comment} where cid = :cid ', array(':cid'=>$value->entity_id))->fetchAssoc();

      $user = user_load($arr['uid']);
 
      if($user->picture==null){
        $path = '/sites/default/files/styles/50x50/public/pictures/picture-default.jpg';
      }else{
        $picture =  $user->picture->filename;
        $path = '/sites/default/files/pictures/'.$picture; 
      }
      print '<div class="comment-row">';
      print '<img src="'.$path.'" />';
      print '<div class="comment-body"><span class="user-name">'.$user->name.'</span>'.$value->comment_body_value.'<div class="comment-date">'.format_interval((time() - $arr['created']) , 2) . t(' ago') .'</div></div>';
      print '</div>';
    } 
     ?>
         <?php  global $user; ?> 
         <?php if ($user->uid !=0): ?>
   <div class="form-textarea-wrapper">
	 <?php $picture = db_query('SELECT filename FROM {file_managed} where fid='.$user->picture)->fetchfield();
	 	print '<img src="/sites/default/files/pictures/'.$picture.'" />'; ?>
   <input type="textarea" row="3" cols="60" class="add-comment-body comment-node-<?php print $node->nid ?>" value="Write a comment..." onkeydown="enterIn(event,<?php print $node->nid ?>,<?php  print $user->uid ?>);" />
   </div>
     <?php endif; ?>
  </div>

</div>
