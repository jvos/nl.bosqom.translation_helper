<?php
function translation_helper_translate_po_file($form, &$form_state)
{
  $translate_po_file = array
  (
    'provider' => 'bing',
    'from' => 'en',
    'to' => 'nl',
    'google' => array('api_key' => 'AIzaSyAkHGAjQIkpRfkEosTRAXYD8v2kHlxmC80'),
    'bing' => array('client_id' => '3f0225c2-05ea-48ae-b092-b69bf9dba920', 'client_secret' => 'M/jjQ6jWX2+p8pUd8G6B7TMsQlNaATTVG5/CySFzXH0=')
  );
  
  $translate_po_file = unserialize(variable_get('translation_helper_translate_po_file', serialize($translate_po_file)));
  
  $form['#attributes']['class'][] = 'translation_helper';

  $form['#validate'][] = 'translation_helper_translate_po_file_validate';
  $form['#submit'][] = 'translation_helper_translate_po_file_submit';

  $options = array('google' => t('Google'), 'bing' => t('Bing'));
  
  $form['help'] = array(
    '#type' => 'fieldset', 
    '#title' => t('Help'), 
    '#collapsible' => TRUE, 
    '#collapsed' => FALSE,
  );
  
  $form['help']['help']['#markup'] = t('Don not use files bigger than 500 translation text ! Or you have to change the memory_limit to a higher value, in the php.ini.');
  
  $form['file'] = array(
    '#type' => 'fieldset', 
    '#title' => t('File'), 
    '#collapsible' => TRUE, 
    '#collapsed' => FALSE,
  );
  
  $form['file']['file'] = array(
    '#name' => 'file',
    '#type' => 'file',
    '#title' => t('File'),
    '#title_display' => 'invisible',
    '#size' => 22,
  );
  
  $form['provider'] = array(
    '#type' => 'fieldset', 
    '#title' => t('Provider'), 
    '#collapsible' => TRUE, 
    '#collapsed' => FALSE,
  );
  
  $form['provider']['provider'] = array(
    '#type' => 'radios', 
    '#title' => t('Provider'), 
    '#description' => t('Which translation provider to use.'),
    '#required' => TRUE,
    '#options' => $options,
    '#default_value' => $translate_po_file['provider'], 
  );
  
  $language = array(
    'aa' => t('Afar'),
    'ab' => t('Abkhaz'),
    'ae' => t('Avestan'),
    'af' => t('Afrikaans'),
    'ak' => t('Akan'),
    'am' => t('Amharic'),
    'an' => t('Aragonese'),
    'ar' => t('Arabic'),
    'as' => t('Assamese'),
    'av' => t('Avaric'),
    'ay' => t('Aymara'),
    'az' => t('Azerbaijani'),
    'ba' => t('Bashkir'),
    'be' => t('Belarusian'),
    'bg' => t('Bulgarian'),
    'bh' => t('Bihari'),
    'bi' => t('Bislama'),
    'bm' => t('Bambara'),
    'bn' => t('Bengali'),
    'bo' => t('Tibetan Standard, Tibetan, Central'),
    'br' => t('Breton'),
    'bs' => t('Bosnian'),
    'ca' => t('Catalan; Valencian'),
    'ce' => t('Chechen'),
    'ch' => t('Chamorro'),
    'co' => t('Corsican'),
    'cr' => t('Cree'),
    'cs' => t('Czech'),
    'cu' => t('Old Church Slavonic, Church Slavic, Church Slavonic, Old Bulgarian, Old Slavonic'),
    'cv' => t('Chuvash'),
    'cy' => t('Welsh'),
    'da' => t('Danish'),
    'de' => t('German'),
    'dv' => t('Divehi; Dhivehi; Maldivian;'),
    'dz' => t('Dzongkha'),
    'ee' => t('Ewe'),
    'el' => t('Greek, Modern'),
    'en' => t('English'),
    'eo' => t('Esperanto'),
    'es' => t('Spanish; Castilian'),
    'et' => t('Estonian'),
    'eu' => t('Basque'),
    'fa' => t('Persian'),
    'ff' => t('Fula; Fulah; Pulaar; Pular'),
    'fi' => t('Finnish'),
    'fj' => t('Fijian'),
    'fo' => t('Faroese'),
    'fr' => t('French'),
    'fy' => t('Western Frisian'),
    'ga' => t('Irish'),
    'gd' => t('Scottish Gaelic; Gaelic'),
    'gl' => t('Galician'),
    'gn' => t('GuaranÃ­'),
    'gu' => t('Gujarati'),
    'gv' => t('Manx'),
    'ha' => t('Hausa'),
    'he' => t('Hebrew (modern)'),
    'hi' => t('Hindi'),
    'ho' => t('Hiri Motu'),
    'hr' => t('Croatian'),
    'ht' => t('Haitian; Haitian Creole'),
    'hu' => t('Hungarian'),
    'hy' => t('Armenian'),
    'hz' => t('Herero'),
    'ia' => t('Interlingua'),
    'id' => t('Indonesian'),
    'ie' => t('Interlingue'),
    'ig' => t('Igbo'),
    'ii' => t('Nuosu'),
    'ik' => t('Inupiaq'),
    'io' => t('Ido'),
    'is' => t('Icelandic'),
    'it' => t('Italian'),
    'iu' => t('Inuktitut'),
    'ja' => t('Japanese (ja)'),
    'jv' => t('Javanese (jv)'),
    'ka' => t('Georgian'),
    'kg' => t('Kongo'),
    'ki' => t('Kikuyu, Gikuyu'),
    'kj' => t('Kwanyama, Kuanyama'),
    'kk' => t('Kazakh'),
    'kl' => t('Kalaallisut, Greenlandic'),
    'km' => t('Khmer'),
    'kn' => t('Kannada'),
    'ko' => t('Korean'),
    'kr' => t('Kanuri'),
    'ks' => t('Kashmiri'),
    'ku' => t('Kurdish'),
    'kv' => t('Komi'),
    'kw' => t('Cornish'),
    'ky' => t('Kirghiz, Kyrgyz'),
    'la' => t('Latin'),
    'lb' => t('Luxembourgish, Letzeburgesch'),
    'lg' => t('Luganda'),
    'li' => t('Limburgish, Limburgan, Limburger'),
    'ln' => t('Lingala'),
    'lo' => t('Lao'),
    'lt' => t('Lithuanian'),
    'lu' => t('Luba-Katanga'),
    'lv' => t('Latvian'),
    'mg' => t('Malagasy'),
    'mh' => t('Marshallese'),
    'mi' => t('Maori'),
    'mk' => t('Macedonian'),
    'ml' => t('Malayalam'),
    'mn' => t('Mongolian'),
    'mr' => t('Marathi (Mara?hi)'),
    'ms' => t('Malay'),
    'mt' => t('Maltese'),
    'my' => t('Burmese'),
    'na' => t('Nauru'),
    'nb' => t('Norwegian BokmÃ¥l'),
    'nd' => t('North Ndebele'),
    'ne' => t('Nepali'),
    'ng' => t('Ndonga'),
    'nl' => t('Dutch'),
    'nn' => t('Norwegian Nynorsk'),
    'no' => t('Norwegian'),
    'nr' => t('South Ndebele'),
    'nv' => t('Navajo, Navaho'),
    'ny' => t('Chichewa; Chewa; Nyanja'),
    'oc' => t('Occitan'),
    'oj' => t('Ojibwe, Ojibwa'),
    'om' => t('Oromo'),
    'or' => t('Oriya'),
    'os' => t('Ossetian, Ossetic'),
    'pa' => t('Panjabi, Punjabi'),
    'pi' => t('Pali'),
    'pl' => t('Polish'),
    'ps' => t('Pashto, Pushto'),
    'pt' => t('Portuguese'),
    'qu' => t('Quechua'),
    'rm' => t('Romansh'),
    'rn' => t('Kirundi'),
    'ro' => t('Romanian, Moldavian, Moldovan'),
    'ru' => t('Russian'),
    'rw' => t('Kinyarwanda'),
    'sa' => t('Sanskrit (Sa?sk?ta)'),
    'sc' => t('Sardinian'),
    'sd' => t('Sindhi'),
    'se' => t('Northern Sami'),
    'sg' => t('Sango'),
    'si' => t('Sinhala, Sinhalese'),
    'sk' => t('Slovak'),
    'sl' => t('Slovene'),
    'sm' => t('Samoan'),
    'sn' => t('Shona'),
    'so' => t('Somali'),
    'sq' => t('Albanian'),
    'sr' => t('Serbian'),
    'ss' => t('Swati'),
    'st' => t('Southern Sotho'),
    'su' => t('Sundanese'),
    'sv' => t('Swedish'),
    'sw' => t('Swahili'),
    'ta' => t('Tamil'),
    'te' => t('Telugu'),
    'tg' => t('Tajik'),
    'th' => t('Thai'),
    'ti' => t('Tigrinya'),
    'tk' => t('Turkmen'),
    'tl' => t('Tagalog'),
    'tn' => t('Tswana'),
    'to' => t('Tonga (Tonga Islands)'),
    'tr' => t('Turkish'),
    'ts' => t('Tsonga'),
    'tt' => t('Tatar'),
    'tw' => t('Twi'),
    'ty' => t('Tahitian'),
    'ug' => t('Uighur, Uyghur'),
    'uk' => t('Ukrainian'),
    'ur' => t('Urdu'),
    'uz' => t('Uzbek'),
    've' => t('Venda'),
    'vi' => t('Vietnamese'),
    'vo' => t('VolapÃ¼k'),
    'wa' => t('Walloon'),
    'wo' => t('Wolof'),
    'xh' => t('Xhosa'),
    'yi' => t('Yiddish'),
    'yo' => t('Yoruba'),
    'za' => t('Zhuang, Chuang'),
    'zh' => t('Chinese'),
    'zu' => t('Zulu'),
  );
  
  $form['language'] = array(
    '#type' => 'fieldset', 
    '#title' => t('Langugae'), 
    '#collapsible' => TRUE, 
    '#collapsed' => FALSE,
  );
  
  $form['language']['from'] = array(
    '#type' => 'select', 
    '#title' => t('From langugae'), 
    '#description' => t('From witch language.'),
    '#required' => TRUE,
    '#options' => $language,
    '#default_value' => $translate_po_file['from'], 
  );
  
  $form['language']['to'] = array(
    '#type' => 'select', 
    '#title' => t('To langugae'), 
    '#description' => t('To witch language.'),
    '#required' => TRUE,
    '#options' => $language,
    '#default_value' => $translate_po_file['to'], 
  );
  
  // google
  $form['google'] = array(
    '#type' => 'fieldset', 
    '#title' => t('Google'), 
    '#collapsible' => TRUE, 
    '#collapsed' => FALSE,
  );
  
  $form['google']['help']['#markup'] = t('If you don’t already have one, you’ll need a google account. You can get one by visiting ') . l('Google', 'https://accounts.google.com/signup?hl=nl') . t('.') . '<br/><br/>';
  $form['google']['help']['#markup'] .= t('To get your API key, go to ') . l('Google console', 'https://code.google.com/apis/console/') . t(' and login.') . '<br/><br/>';
  $form['google']['help']['#markup'] .= t('Click on Services on the left.') . '<br/>';
  $form['google']['help']['#markup'] .= t('Scroll down and turn on Google Translate on, and agree the terms.') . '<br/><br/>';
  $form['google']['help']['#markup'] .= t('Click on API Access.') . '<br/>';
  $form['google']['help']['#markup'] .= t('Under the section Simple API Access, click on Create new Server key.') . '<br/>';
  $form['google']['help']['#markup'] .= t('Fill in the ip address of your server.') . '<br/><br/>';
  $form['google']['help']['#markup'] .= t('Copy the API key, and past the key below in the API key field.') . '<br/>';
  
  
  // 'min']['#value'] = isset($_REQUEST['price']['min']) ? $_REQUEST['price']['min'] : $my_default_value;
  
  $form['google']['api_key'] = array(
    '#type' => 'textfield', 
    '#title' => t('API key'), 
    '#description' => t('API key of google translate. If empty the API key will be deleted.'),
    '#size' => 100, 
    '#maxlength' => 255, 
    '#required' => FALSE,
    '#default_value' => $translate_po_file['google']['api_key'], 
  );
  
  // bing
  $form['bing'] = array(
    '#type' => 'fieldset', 
    '#title' => t('Bing'), 
    '#collapsible' => TRUE, 
    '#collapsed' => FALSE,
  );
  
  // help windows live id
  $form['bing']['help']['#markup'] = t('If you don’t already have one, you’ll need a Windows Live ID. You can get one by visiting ') . l('Windows Live ID', 'https://signup.live.com/signup.aspx') . t('.') . '<br/><br/>';
  // help microsoft translator
  $form['bing']['help']['#markup'] .= t('To sign up for microsoft translator, go to ') . l('Bing developers', 'http://www.bing.com/developers/appids.aspx') . t(' and login.') . '<br/>';
  $form['bing']['help']['#markup'] .= t('Click on ') . l('Data', 'https://datamarket.azure.com/browse/data') . '<br/>';
  $form['bing']['help']['#markup'] .= t('Click on ') . l('Microsoft Translator', 'https://datamarket.azure.com/dataset/bing/microsofttranslator') . '<br/>';
  $form['bing']['help']['#markup'] .= t('Click on sign up, on the right column, under active subscription') . '<br/>';
  $form['bing']['help']['#markup'] .= t('You can choose for a free subscription of 2.000.000 characters per month. Or a payed subscription.') . '<br/>';
  $form['bing']['help']['#markup'] .= t('Click on sign up, on the right column, under active subscription') . '<br/><br/>';
  // help client id
  $form['bing']['help']['#markup'] .= t('To get your client Id goto ') . l('My account', 'https://datamarket.azure.com/account') . '<br/>';
  $form['bing']['help']['#markup'] .= t('And below under account information there is your client id. Copy this client id and past it below.') . '<br/><br/>';
  // help client secret
  $form['bing']['help']['#markup'] .= t('To get your client secret, you must first copy your client id, and goto ') . l('Register your application', 'https://datamarket.azure.com/developer/applications/register') . '<br/>';
  $form['bing']['help']['#markup'] .= t('Past the client id, an fill out the rest of the form, and hit create.') . '<br/>';
  $form['bing']['help']['#markup'] .= t('Go to ') . l('developers', 'https://datamarket.azure.com/developer/applications')  . t(' under ') . l('My account', 'https://datamarket.azure.com/account') . '.<br/>';
  $form['bing']['help']['#markup'] .= t('Click on change at the right end under registered applications in the table.') . '<br/>';
  $form['bing']['help']['#markup'] .= t('Copy the client secret and past it down below.') . '<br/>';
  
  $form['bing']['client_id'] = array(
    '#type' => 'textfield', 
    '#title' => t('Client Id'), 
    '#description' => t('Client Id of bing translate. If empty the Client Id will be deleted.'),
    '#size' => 100, 
    '#maxlength' => 255, 
    '#required' => FALSE,
    '#default_value' => $translate_po_file['bing']['client_id'], 
  );
  
  $form['bing']['client_secret'] = array(
    '#type' => 'textfield', 
    '#title' => t('Client Secret'), 
    '#description' => t('Client Secret of bing translate. If empty the Client Secret will be deleted.'),
    '#size' => 100, 
    '#maxlength' => 255, 
    '#required' => FALSE,
    '#default_value' => 'M/jjQ6jWX2+p8pUd8G6B7TMsQlNaATTVG5/CySFzXH0=', 
    '#default_value' => $translate_po_file['bing']['client_secret'], 
  );
  
  $form['submit'] = array
  (
    '#type' => 'submit',
    '#value' => t('Save')
  );
  
  $form['translate_po_file'] = array
  (
    '#type' => 'submit',
    '#value' => t('Save & Translate po file')
  );
  
  if(file_exists(file_directory_temp() . '/translation_helper/translate_po_file.po')){
    $form['translation_text_po'] = array
    (
      '#type' => 'submit',
      '#value' => t('Save & Open translate_po_file'),
    );
  }
  
  return $form;
}

function translation_helper_translate_po_file_validate($form, &$form_state)
{
  $form_state['values']['api_key'] = trim($form_state['values']['api_key']);
  $form_state['values']['client_id'] = trim($form_state['values']['client_id']);
  $form_state['values']['client_secret'] = trim($form_state['values']['client_secret']);
  
  if(t('Save & Open translate_po_file') != $form_state['values']['op']){
    // check file
    if (!isset($_FILES['file']['name']) or empty($_FILES['file']['name'])) {
      @unlink($_FILES['file']['tmp_name']);
      unset($form_state['values']['file']);

      form_set_error('file', t('No file !'));

    }else {
      switch ($_FILES['file']['error']) {
        case UPLOAD_ERR_INI_SIZE:
        case UPLOAD_ERR_FORM_SIZE:
          @unlink($_FILES['file']['tmp_name']);
          unset($form_state['values']['file']);

          form_set_error('file', t('The file ') . $_FILES['file']['name'] . (' could not be saved, because it exceeds ') . format_size(file_upload_max_size()) . t(', the maximum allowed size for uploads.'));

        case UPLOAD_ERR_PARTIAL:
        case UPLOAD_ERR_NO_FILE:
          @unlink($_FILES['file']['tmp_name']);
          unset($form_state['values']['file']);

          form_set_error('file', t('The file ') . $_FILES['file']['name'] . (' could not be saved, because the upload did not complete.'));

        case UPLOAD_ERR_OK:
          // Final check that this is a valid upload, if it isn't, use the
          // default error handler.
          if (is_uploaded_file($_FILES['file']['tmp_name'])) {
            break;
          }

          // Unknown error
        default:
          @unlink($_FILES['file']['tmp_name']);
          unset($form_state['values']['file']);

          form_set_error('file', t('The file ') . $_FILES['file']['name'] . (' could not be saved. An unknown error has occurred.'));
      }

      // check if it is a po file
      $file_parts = pathinfo($_FILES['file']['name']);
      if(!isset($file_parts['extension']) or !in_array($file_parts['extension'], array('po'))){
        @unlink($_FILES['file']['tmp_name']);
        unset($form_state['values']['file']);

        form_set_error('file', t('The file ') . $_FILES['file']['name'] . (' is not a po file !')); 
      }
    }
  }
  
  if('google' == $form_state['values']['provider']){
    if('' == $form_state['values']['api_key']){
      form_set_error('api_key', t('Google API key is empty !'));
    }
  }
  
  if('bing' == $form_state['values']['provider']){
    if('' == $form_state['values']['client_id']){
      form_set_error('api_key', t('Bing client id is empty !'));
    }
    if('' == $form_state['values']['client_secret']){
      form_set_error('api_key', t('Bing client secret is empty !'));
    }
  }
}

function translation_helper_translate_po_file_submit($form, &$form_state)
{  
  $translate_po_file = array
  ( 
    'provider' => $form_state['values']['provider'],
    'from' => $form_state['values']['from'],
    'to' => $form_state['values']['to'],
    'google' => array('api_key' => $form_state['values']['api_key']),
    'bing' => array('client_id' => $form_state['values']['client_id'], 'client_secret' => $form_state['values']['client_secret'])
  );
  
  variable_set('translation_helper_translate_po_file', serialize($translate_po_file));
  
  if(t('Save & Open translate_po_file') != $form_state['values']['op']){
    if(!move_uploaded_file($_FILES['file']['tmp_name'], file_directory_temp() . '/translation_helper/translate_po_file_temp.po')){
      @unlink($_FILES['file']['tmp_name']);
      
      form_set_error('file', t('Can not move uploaded file !'));
    }
  }
  
  unset($form_state['values']['file']);
  
  if(t('Save & Translate po file') == $form_state['values']['op']){
    $form_state['redirect'] = array
    (
      'admin/config/regional/translate/translation_helper/translate_po_file/progress', 
    );
  }
  
  if(t('Save & Open translate_po_file') == $form_state['values']['op']){
    $form_state['redirect'] = array
    (
      'admin/config/regional/translate/translation_helper/translate_po_file/open', 
    );
  }
}


function translation_helper_translate_po_file_actions($form, &$form_state, $action = 'progress')
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
        'message' => ' line(s) processed.',
        'percent' => 0,
        'count' => 0,
      );

      variable_set('translate_po_file_line_queue', serialize($queue)); // reset queu
      
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
          'data' => drupal_get_path('module', 'translation_helper') . '/js/translate_po_file.js',
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
      
      ob_end_flush(); 
      
      $translate_po_file = unserialize(variable_get('translation_helper_translate_po_file'));
      
      // get contents
      $file = file_directory_temp() . '/translation_helper/translate_po_file_temp.po';
      $handle = fopen($file, "r");
      $contents = fread($handle, filesize($file));
      fclose($handle);
      
      // get text
      list($text_id, $text_str) = translation_helper_get_po_files_text($contents, array(), array(), 0, 1);
    
      if(empty($text_id)){
        $queue = array
        (
          'status' => 'error',
          'total' => 0,
          'message' => 'No translation text found in translate_po_file.po !',
          'percent' => 0,
          'count' => 0,
        );

        variable_set('translation_helper_translation_text_file_queue', serialize($queue));
        
        drupal_set_message('No translation text found in translate_po_file.po !', 'warning');
        exit();
      }

      // Total processes
      $total = count($text_id);

      $queue = array
      (
        'status' => 'warning',
        'total' => $total,
        'message' => ' line(s) processed.',
        'percent' => 0,
        'count' => 0,
      );

      variable_set('translate_po_file_line_queue', serialize($queue));
      
      if('bing' == $translate_po_file['provider']){
        $access_token = translation_helper_translate_text_bing_token();
        if(!$access_token){
          drupal_set_message(t('A error occured. Bing request access token'), 'warning');
          
          $queue = array
          (
            'status' => 'error',
            'message' => 'Bing request access token error',
            'percent' => 100,
            'count' => '',
          );

          variable_set('translate_po_file_line_queue', serialize($queue));
          
          exit();
        }
      }
      
      /*// This is for the buffer achieve the minimum size in order to flush data
      echo str_repeat(' ',1024*64); 
      flush();*/

      sleep(5);
      //time_nanosleep(0, 100000000);
      
      foreach($text_id as $count => $text){
        // Calculate the percentation
        $percent = intval(($count+1)/$total * 100);

        $queue = array
        (
          'status' => 'warning',
          'total' => $total,
          'message' =>  ' line(s) processed of ' . $total . ' line(s) in translate_po_file.po',
          'percent' => $percent,
          'count' => $count+1,
        );

        variable_set('translate_po_file_line_queue', serialize($queue));
        
        $str = $text_str[$count];
        
        if('' != $text){
          if('' == $str){ // if str is empty
            switch($translate_po_file['provider'])
            {
              case 'bing':
                $str = translation_helper_translate_text_bing($access_token, $text, $translate_po_file['from'], $translate_po_file['to']);
              break;

              case 'google':
                $str = translation_helper_translate_text_google($text, $translate_po_file['from'], $translate_po_file['to']);
                break;
            }
            
            sleep(1);
          }
        }
        
        $text_str[$count] = $str;
        
        /*// This is for the buffer achieve the minimum size in order to flush data
        echo str_repeat(' ',1024*64); 
        flush();*/

        
        time_nanosleep(0, 100000000);
      }
      
      fclose($file);

      // Total processes
      $total = count($text_id);

      $queue = array
      (
        'status' => 'warning',
        'total' => $total,
        'message' => ' line(s) written into translate_po_file.po',
        'percent' => 0,
        'count' => 0,
      );

      variable_set('translate_po_file_line_queue', serialize($queue));
      
      // save text to file
      $file = fopen(file_directory_temp() . '/translation_helper/translate_po_file.po','w');
      fwrite($file,'msgid ""' . "\r\n");
      fwrite($file,'msgstr ""' . "\r\n");
      /*fwrite($file,'' . "\r\n");
      fwrite($file,'"MIME-Version: 1.0"' . "\r\n");
      fwrite($file,'"Content-Type: text/plain; charset=utf-8"' . "\r\n");
      fwrite($file,'"Content-Transfer-Encoding: 8bit"');
      fwrite($file,'"Plural-Forms: nplurals=2; plural=(n!=1);"' . "\r\n");*/

      /*echo str_repeat(' ',1024*64); 
      flush();*/
      
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
      
      time_nanosleep(0, 100000000);

      foreach($text_id as $count => $text){
        $percent = intval(($count+1)/$total * 100);

        $queue = array
        (
          'status' => 'warning',
          'total' => $total,
          'message' => ' line(s) written of ' . $total . ' line(s) into translate_po_file.po',
          'percent' => $percent,
          'count' => $count+1,
        );

        variable_set('translate_po_file_line_queue', serialize($queue));
        
        $str = '';
        $str = $text_str[$count];
        
        fwrite($file,'' . "\r\n");
        fwrite($file,'msgid "' .  $text . '"' . "\r\n");
        fwrite($file,'msgstr "' . $str . '"' . "\r\n");

        /*echo str_repeat(' ',1024*64); 
        flush();*/

        time_nanosleep(0, 100000000);
      }

      fclose($file);

      $queue = array
      (
        'status' => 'status',
        'message' => 'writing translate_po_file.po compleet',
        'percent' => 100,
        'count' => '',
      );

      variable_set('translate_po_file_line_queue', serialize($queue));
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

      echo(variable_get('translate_po_file_line_queue', $queue));
      exit();
      
      break;
    
    case 'open':
      header("Content-type: text/plain");
      header("Content-Disposition: attachment; filename=translate_po_file.po");

      $filename = file_directory_temp() . '/translation_helper/translate_po_file.po';

      $handle = fopen($filename, "r");
      $contents = fread($handle, filesize($filename));
      fclose($handle);

      echo($contents);
      exit();
      
      break;
  }
}