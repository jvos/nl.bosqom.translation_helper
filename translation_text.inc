<?php
function translation_helper_translation_text($form, &$form_state)
{
  $translation_text = array
  (
    'path' => rawurlencode('sites/all/modules/custom/translation_helper'),
    'extensions' => 'php,phps,inc,module',
    'platform' => serialize(array('drupal' => t('drupal'), 'civicrm' => t('civicrm'))) 
  );
  
  $translation_text = unserialize(variable_get('translation_helper_translation_text', serialize($translation_text)));
  
  $form['#attributes']['class'][] = 'translation_helper';

  $form['#validate'][] = 'translation_helper_translation_text_validate';
  $form['#submit'][] = 'translation_helper_translation_text_submit';

  $form['path'] = array(
    '#type' => 'textfield', 
    '#title' => t('Path'), 
    '#description' => t('Path to module / extension'),
    '#size' => 155, 
    '#maxlength' => 255, 
    '#required' => TRUE,
    '#default_value' => rawurldecode($translation_text['path']), 
  );

  $form['extensions'] = array(
    '#type' => 'textfield', 
    '#title' => t('Allowed extensions'), 
    '#description' => t('Exentensions separated by comma. Don not use point before extension !'),
    '#size' => 100, 
    '#maxlength' => 255, 
    '#required' => TRUE,
    '#default_value' => $translation_text['extensions'], 
  );  
  
  $options = array('drupal' => t('Drupal'), 'civicrm' => t('Civicrm'));

  $form['platform'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Platform'),
    '#default_value' => 'drupal',
    '#options' => $options,
    '#required' => TRUE,
    '#default_value' => unserialize($translation_text['platform'])
  );
  
  $form['submit'] = array
  (
    '#type' => 'submit',
    '#value' => t('Save')
  );
  
  $form['translation_text'] = array
  (
    '#type' => 'submit',
    '#value' => t('Save & Get translation text')
  );
  
  if(file_exists(file_directory_temp() . '/translation_helper/translation_text.po')){
    $form['translation_text_po'] = array
    (
      '#type' => 'submit',
      '#value' => t('Save & Open translation_text_po file'),
    );
  }
    
  return $form;
}

function translation_helper_translation_text_validate($form, &$form_state)
{
  global $base_path;

  $form_state['values']['path'] = trim($form_state['values']['path']);
    
  // check if path to module exists
  if(!is_dir($_SERVER['DOCUMENT_ROOT'] . $base_path . $form_state['values']['path'])){
    form_set_error('path', t('Path is not a directory !'));
  }
}

function translation_helper_translation_text_submit($form, &$form_state)
{  
  $translation_text = array
  (
    'path' => rawurlencode($form_state['values']['path']),
    'extensions' => str_replace(' ', '', $form_state['values']['extensions']),
    'platform' => serialize($form_state['values']['platform']) 
  );
  
  variable_set('translation_helper_translation_text', serialize($translation_text));
  
  if(t('Save & Get translation text') == $form_state['values']['op']){
    $form_state['redirect'] = array
    (
      'admin/config/regional/translate/translation_helper/translation_text/progress', 
    );
  }
  
  if(t('Save & Open translation_text_po file') == $form_state['values']['op']){
    $form_state['redirect'] = array
    (
      'admin/config/regional/translate/translation_helper/translation_text/open', 
    );
  }
}

function translation_helper_translation_text_actions($form, &$form_state, $action = 'progress')
{
  global $base_url;
  global $base_path;
  
  switch($action)
  {
    case 'progress': 
      $queue = array
      (
        'status' => 'warning',
        'total' => 100,
        'message' => ' file(s) processed.',
        'percent' => 0,
        'count' => 0,
      );

      variable_set('translation_helper_translation_text_file_queue', serialize($queue)); // reset queu
      
      $form['#attributes']['class'][] = 'translation_helper';

      $variables =  array
      (
        'percent' => 0,
        'message' => '0 file(s) processed.',
      );

      $form['progress_bar'] = array();
      $form['progress_bar']['#markup'] = theme_progress_bar($variables);

      $form['script'] = array();
      $form['script']['#markup'] = '<script type="text/javascript">';
      $form['script']['#markup'] .= 'var base_url = "' . $base_url . '";';
      $form['script']['#markup'] .= 'var base_path = "' . $base_path . '";';
      $form['script']['#markup'] .= '</script>';


      $form['#attached']['js'] = array
      (
        array
        (
          'data' => drupal_get_path('module', 'translation_helper') . '/js/serialize.js',
          'options' => array
          (
            'group' => JS_LIBRARY,
            'preprocess' => TRUE,
            'every_page' => TRUE, 
          ),
        ),
        array
        (
          'data' => drupal_get_path('module', 'translation_helper') . '/js/unserialize.js',
          'options' => array
          (
            'group' => JS_LIBRARY,
            'preprocess' => TRUE,
            'every_page' => TRUE, 
          ),
        ),
        array
        (
          'data' => drupal_get_path('module', 'translation_helper') . '/js/rawurldecode.js',
          'options' => array
          (
            'group' => JS_LIBRARY,
            'preprocess' => TRUE,
            'every_page' => TRUE, 
          ),
        ),
        array
        (
          'data' => drupal_get_path('module', 'translation_helper') . '/js/rawurlencode.js',
          'options' => array
          (
            'group' => JS_LIBRARY,
            'preprocess' => TRUE,
            'every_page' => TRUE, 
          ),
        ),
        array
        (
          'data' => drupal_get_path('module', 'translation_helper') . '/js/api.js',
          'options' => array
          (
            'group' => JS_LIBRARY,
            'preprocess' => TRUE,
            'every_page' => TRUE, 
          ),
        ),
        array
        (
          'data' => drupal_get_path('module', 'translation_helper') . '/js/translation_text.js',
          'options' => array
          (
            'group' => JS_LIBRARY,
            'preprocess' => TRUE,
            'every_page' => TRUE, 
          ),
        ),
      );
      
      return $form;
      
      break;
    
    case 'process':
      set_time_limit(0);
      
      $translation_text = unserialize(variable_get('translation_helper_translation_text'));
      
      // get files
      $files = translation_helper_get_files($_SERVER['DOCUMENT_ROOT'] . $base_path . rawurldecode($translation_text['path']), explode(',', $translation_text['extensions']));
      
      if(empty($files)){
        $queue = array
        (
          'status' => 'error',
          'total' => 0,
          'message' => 'No files found !',
          'percent' => 0,
          'count' => 0,
        );

        variable_set('translation_helper_translation_text_file_queue', serialize($queue));
        
        drupal_set_message('No files found !', 'warning');
        exit();
      }
      
      ob_end_flush();  

      // Total processes
      $total = count($files);

      $queue = array
      (
        'status' => 'warning',
        'total' => $total,
        'message' => ' file(s) processed.',
        'percent' => 0,
        'count' => 0,
      );

      variable_set('translation_helper_translation_text_file_queue', serialize($queue));

      $text = array();
      foreach($files as $count => $file){  

        // Calculate the percentation
        $percent = intval(($count+1)/$total * 100);

        $queue = array
        (
          'status' => 'warning',
          'total' => $total,
          'message' =>  ' file(s) processed of ' . $total . ' file(s) in ' . str_replace($_SERVER['DOCUMENT_ROOT'], '', $file),
          'percent' => $percent,
          'count' => $count+1,
        );

        variable_set('translation_helper_translation_text_file_queue', serialize($queue));

        // get contents
        $handle = fopen($file, "r");
        $contents = fread($handle, filesize($file));
        fclose($handle);
        
        foreach(unserialize($translation_text['platform']) as $platform){
          $text = array_merge($text, translation_helper_get_files_text_platform($platform, $contents));
        }

        // This is for the buffer achieve the minimum size in order to flush data
        echo str_repeat(' ',1024*64); 
        flush();

        // sleep(1);
        time_nanosleep(0, 100000000);
      }

      // Total processes
      $total = count($text);

      $queue = array
      (
        'status' => 'warning',
        'total' => $total,
        'message' => ' line(s) written into translation_text.po',
        'percent' => 0,
        'count' => 0,
      );

      variable_set('translation_helper_translation_text_file_queue', serialize($queue));

      // save text to file
      $file = fopen(file_directory_temp() . '/translation_helper/translation_text.po','w');
      fwrite($file,'msgid ""' . "\r\n");
      fwrite($file,'msgstr ""' . "\r\n");
      /*fwrite($file,'' . "\r\n");
      fwrite($file,'"MIME-Version: 1.0"' . "\r\n");
      fwrite($file,'"Content-Type: text/plain; charset=utf-8"' . "\r\n");
      fwrite($file,'"Content-Transfer-Encoding: 8bit"');
      fwrite($file,'"Plural-Forms: nplurals=2; plural=(n!=1);"' . "\r\n");*/

      fwrite($file,'"Project-Id-Version: CiviCRM"' . "\r\n");
      fwrite($file,'"POT-Creation-Date: 2013-10-08 08:14-0400"' . "\r\n");
      fwrite($file,'"PO-Revision-Date: 2013-11-04 11:51+0000"' . "\r\n");
      fwrite($file,'"Last-Translator: HanV <han.velthuis@home.nl>"' . "\r\n");
      fwrite($file,'"Language-Team: Dutch (http://www.transifex.com/projects/p/civicrm/language/"' . "\r\n");
      fwrite($file,'"nl/)"' . "\r\n");
      fwrite($file,'"MIME-Version: 1.0"' . "\r\n");
      fwrite($file,'"Content-Type: text/plain; charset=UTF-8"' . "\r\n");
      fwrite($file,'"Content-Transfer-Encoding: 8bit"' . "\r\n");
      fwrite($file,'"Language: nl"' . "\r\n");
      fwrite($file,'"Plural-Forms: nplurals=2; plural=(n != 1);"' . "\r\n");
      fwrite($file,'' . "\r\n");
      
      echo str_repeat(' ',1024*64); 
      flush();

      time_nanosleep(0, 100000000);

      foreach($text as $count => $t){
        $percent = intval(($count+1)/$total * 100);

        $queue = array
        (
          'status' => 'warning',
          'total' => $total,
          'message' => ' line(s) written of ' . $total . ' line(s) into translation_text.po',
          'percent' => $percent,
          'count' => $count+1,
        );

        variable_set('translation_helper_translation_text_file_queue', serialize($queue));
        
        fwrite($file,'' . "\r\n");
        fwrite($file,'msgid "' .  $t . '"' . "\r\n");
        fwrite($file,'msgstr ""' . "\r\n");

        echo str_repeat(' ',1024*64); 
        flush();

        time_nanosleep(0, 100000000);
      }

      fclose($file);

      $queue = array
      (
        'status' => 'status',
        'message' => 'writing translation_text.po compleet',
        'percent' => 100,
        'count' => '',
      );

      variable_set('translation_helper_translation_text_file_queue', serialize($queue));
      exit();
      
      break;
    
    case 'status':
      $queue = array
      (
        'status' => 'warning',
        'total' => 100,
        'message' => '',
        'percent' => 0,
        'count' => 0,
      );

      echo(variable_get('translation_helper_translation_text_file_queue', $queue));
      exit();
      
      break;
    
    case 'open':
      header("Content-type: text/plain");
      header("Content-Disposition: attachment; filename=translation_text.po");

      $filename = file_directory_temp() . '/translation_helper/translation_text.po';

      $handle = fopen($filename, "r");
      $contents = fread($handle, filesize($filename));
      fclose($handle);

      echo($contents);
      exit();
      
      break;
  }
}
?>