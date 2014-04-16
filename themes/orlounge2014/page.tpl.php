
<div id="page"><div id="page_wrapper"><!-- start page_wrapper -->
    <div id="header">
      <div class="header_main">    
     <div class="logo">
      <?php if ($logo): ?>
            <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home" id="logo">
            <img src="<?php print $logo; ?>" alt="<?php print t('logo'); ?>" />
            </a>
         <?php endif; ?>
      </div>
      <?php  global $user ;  ?>
      <?php if($user->uid !=0): ?>
	<div class="user_block">
	 <?php 
		$picture = db_query('SELECT filename FROM {file_managed} where fid='.$user->picture)->fetchfield();
		echo '<img src="/sites/default/files/pictures/'.$picture.'" />';
 		echo '<div>'.$user->name.'</div>'; 
 		echo '<a href="/user/'.$user->uid.'/edit">Edit profile</a>'; 
	?> 
	</div>
      <?php  endif; ?>
      <?php  if($page['header']): ?>
        <?php  print render($page['header']) ; ?>
      <?php endif; ?>
      </div>
    </div> <!-- header end -->
<!--
    <div id="menu">
      <?php if ($main_menu): ?>
      <div id="main-menu" class="navigation">
        <?php print theme('links__system_main_menu', array(
          'links' => $main_menu,
          'attributes' => array(
            'id' => 'main-menu-links',
            'class' => array('links', 'clearfix'),
          ),
          'heading' => array(
            'text' => t('Main menu'),
            'level' => 'h2',
            'class' => array('element-invisible'),
          ),
        )); ?> 
    </div>
      <?php endif; ?>
    </div> ---><!--main menu end -->
    <div id="center">     
     <div id="middle"> 
	<?php if ($messages): ?>
		<div id="messages"><div class="section clearfix">
			<?php print $messages; ?>
		</div></div> <!-- /.section, /#messages -->
	<?php endif; ?>

      <div class="center_main">
        <?php  print render($page['content']);?>
      </div>    
     </div>
    </div> <!-- center --->

    <div id="footer">
     <div class="footer_main"> <?php print render($page['footer']); ?> </div>
    </div> <!-- footer end -->

</div></div><!-- end page_wrapper-->



