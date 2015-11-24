<?php
// get files with translation text
function translation_helper_get_files($path, $extensions, &$files = array())
{
  $dir = opendir($path."/.");
  while($item = readdir($dir)){
      if(is_file($sub = $path."/".$item)){
          
          $file_parts = pathinfo($path."/".$item);
          if(isset($file_parts['extension']) and in_array($file_parts['extension'], $extensions)){
            $files[] = $path."/".$item;
          }
          
      }else{
        if($item != "." and $item != ".."){
          $files = translation_helper_get_files($sub, $extensions, $files);
        }
      }
  }

  return($files);
}

// get translation text form files by platform
function translation_helper_get_files_text_platform($platform, $contents)
{
  $return = array();
  
  if('drupal' == $platform){    
    $return = translation_helper_get_files_text("t('", "')", $contents, $return, 0, 1);
    $return = translation_helper_get_files_text('t("', '")', $contents, $return, 0, 1);

  }else if('civicrm' == $platform) {
    $return = translation_helper_get_files_text("ts('", "')", $contents, $return, 0, 1);
    $return = translation_helper_get_files_text('ts("', '")', $contents, $return, 0, 1);
  }
  
  return $return;
}

// get translation text form files
function translation_helper_get_files_text($begin, $end, $contents, $return, $pos, $last)
{
  $pos = strpos($contents, $begin, $pos);
  $before_pos = substr($contents, $pos-1, 1); // get one caracter befor pos

  if(false === $pos){
    unset($contents);
    unset($pos);
    unset($last);
    unset($begin);
    unset($end);
    unset($before_pos);
    
    return $return;
  }
  
  if(false !== $before_pos){ // if there is a caracter
    if (preg_match('/[A-Za-z0-9_-]+/', $before_pos)) { // if it is one of the caracters, it must be another function then t or ts
      
        $return = translation_helper_get_files_text($begin, $end, $contents, $return, ($pos + strlen($begin)), ($pos + strlen($begin) + strlen($end)));
        unset($contents);
        unset($pos);
        unset($last);
        unset($begin);
        unset($end);
        unset($before_pos);
        
        return $return;
    }
  }

  $pos2 = strpos($contents, $end, $pos);

  if($pos2 < $last){ // only run next if psoition 2 is bigger or equal as last
    unset($contents);
    unset($pos);
    unset($last);
    unset($begin);
    unset($end);
    unset($before_pos);
    unset($pos2);
    
    return $return;
  }

  $text = substr($contents, ($pos + strlen($begin)), ($pos2-$pos) - strlen($begin));
  if(!in_array($text, $return)){
    $return[] = substr($contents, ($pos + strlen($begin)), ($pos2-$pos) - strlen($begin));
  }

  unset($pos);
  unset($last);
  unset($before_pos);

  $return = translation_helper_get_files_text($begin, $end, $contents, $return, $pos2, ($pos2 + strlen($end)));
  
  unset($contents);
  unset($begin);
  unset($end);
  unset($pos2);
  
  return $return;
}

function translation_helper_get_po_files_text($contents, $id_return, $str_return, $pos, $last)
{
  $id_begin = 'msgid "';
  $str_begin = 'msgstr "';
    
  $id = '';
  $str = '';
  
  $id_pos = strpos($contents, $id_begin, $pos);

  if(false === $id_pos){
    unset($contents);
    unset($pos);
    unset($last);
    unset($id_begin);
    unset($str_begin);
    unset($id);
    unset($str);
    unset($id_pos);
    
    return array($id_return, $str_return);
  }
  
  $id_pos2 = strpos($contents, '"', $id_pos + strlen($id_begin));
  
  if($id_pos2 < $last){ // only run next if position 2 is bigger or equal as last
    unset($contents);
    unset($pos);
    unset($last);
    unset($id_begin);
    unset($str_begin);
    unset($id);
    unset($str);
    unset($id_pos);
    unset($id_pos2);
    return array($id_return, $str_return);
  }
  
  $id = substr($contents, ($id_pos + strlen($id_begin)), ($id_pos2-$id_pos) - strlen($id_begin));

  if('' == $id){ // if id is empty
    list($id_return, $str_return) = translation_helper_get_po_files_text($contents, $id_return, $str_return, ($id_pos2 + 1), ($id_pos2 + 2));
    unset($contents);
    unset($pos);
    unset($last);
    unset($id_begin);
    unset($str_begin);
    unset($id);
    unset($str);
    unset($id_pos);
    unset($id_pos2);
    return array($id_return, $str_return);
  }

  $str_pos = strpos($contents, $str_begin, $id_pos2);

  if(false === $str_pos){ // if " not exists
    unset($contents);
    unset($pos);
    unset($last);
    unset($id_begin);
    unset($str_begin);
    unset($id);
    unset($str);
    unset($id_pos);
    unset($id_pos2);
    unset($str_pos);
    return array($id_return, $str_return);
  }
    
  $str_pos2 = strpos($contents, '"', $str_pos + strlen($str_begin));
  
  if($str_pos2 < $last){ // only run next if position 2 is bigger or equal as last
    unset($contents);
    unset($pos);
    unset($last);
    unset($id_begin);
    unset($str_begin);
    unset($id);
    unset($str);
    unset($id_pos);
    unset($id_pos2);
    unset($str_pos);
    unset($str_pos2);
    return array($id_return, $str_return);
  }
  
  $str = substr($contents, ($str_pos + strlen($str_begin)), ($str_pos2-$str_pos) - strlen($str_begin));
  
  if(!in_array($id, $id_return)){ // if id is not in list
    $id_return[] = $id;
    $str_return[] = $str; 
  }
  
  
  
  /*echo('<pre>');
  print_r($id_return);
  echo('</pre>') . '<br/>' . PHP_EOL; 
  */
  
  echo('count: ' . count($id_return)) . '<br/>' . PHP_EOL; 
  echo('id: ' . $id) . '<br/>' . PHP_EOL;   
  echo('str: ' . $str) . '<br/><br/>' . PHP_EOL;

  echo str_repeat(' ',1024*64); 
  flush();

  unset($pos);
  unset($last);
  unset($id_begin);
  unset($str_begin);
  unset($id);
  unset($str);
  unset($id_pos);
  unset($id_pos2);
  unset($str_pos);
  
  //time_nanosleep(0, 100000000);
  
  list($id_return, $str_return) = translation_helper_get_po_files_text($contents, $id_return, $str_return, $str_pos2, ($str_pos2 + 1));
  unset($contents);
  unset($str_pos2);
  
  return array($id_return, $str_return);
}

function translation_helper_translate_text_google($text, $source, $target)
{
  $translate_po_file = unserialize(variable_get('translation_helper_translate_po_file'));
  
  if(!isset($translate_po_file['google']['api_key']) or '' == $translate_po_file['google']['api_key']){
    drupal_set_message(t('A error occured. Google no API key !'), 'warning');
    return false;
  }
  
  $key = $translate_po_file['google']['api_key'];
  
  /// this is the form data to be included with the request
  $url = 'https://www.googleapis.com/language/translate/v2';
  
  $values = array(
    'q' => rawurlencode($text),
    'key' => $key,
    'source' => $source,
    'target' => $target,
  );
  
  // turn the form data array into raw format so it can be used with cURL
  $post = http_build_query($values);

  // create a connection to the API endpoint
  $ch = curl_init($url);

  // tell cURL to return the response rather than outputting it
  curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);

  // write the form data to the request in the post body
  curl_setopt($ch, CURLOPT_POSTFIELDS, $post);

  // include the header to make Google treat this post request as a get request
  curl_setopt($ch, CURLOPT_HTTPHEADER, array('X-HTTP-Method-Override: GET'));

  // set curl not to verify the ssl peer
  curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, false);
  
  // execute the HTTP request
  $json = curl_exec($ch);
  
  //Get the Error Code returned by Curl.
  $errno = curl_errno($ch);
  
  curl_close($ch);
  
  if($errno){
    var_dump($errno);
    drupal_set_message(t('A error occured. Google curl errno, message: ') . $errno, 'warning');
    return '';
  }
 
  if(!$json){
    var_dump($json);
    drupal_set_message(t('A error occured. Google response, message: ') . $json, 'warning');
    return '';
  }
  
  $data = json_decode($json, true);
  if(isset($data['error']) and '' != $data['error']['code']){
    print_r($data);
    drupal_set_message(t('A error occured. Google response, code: ') . $data['error']['code'] . t(', message: ') . $data['error']['message'], 'warning');
    return '';
  }
  
  /*print_r($data);
  exit();*/
  
  return $data;
}

function translation_helper_translate_text_bing_token()
{
  $translate_po_file = unserialize(variable_get('translation_helper_translate_po_file'));
  
  if(!isset($translate_po_file['bing']['client_id']) or '' == $translate_po_file['bing']['client_id']){
    drupal_set_message(t('A error occured. Bing token no client id !'), 'warning');
    return false;
  }
  
  if(!isset($translate_po_file['bing']['client_secret']) or '' == $translate_po_file['bing']['client_secret']){
    drupal_set_message(t('A error occured. Bing token no client secret!'), 'warning');
    return false;
  }

  //Initialize the Curl Session.
  $ch = curl_init();
  
  //Create the request Array.
  $values = array (
      'grant_type'    => "client_credentials",
      'scope'         => "http://api.microsofttranslator.com",
      'client_id'     => $translate_po_file['bing']['client_id'],
      'client_secret' => $translate_po_file['bing']['client_secret']
  );
  
  //Create an Http Query.//
  $values = http_build_query($values);

  //Set the Curl URL.
  curl_setopt($ch, CURLOPT_URL, "https://datamarket.accesscontrol.windows.net/v2/OAuth2-13/");
  //Set HTTP POST Request.
  curl_setopt($ch, CURLOPT_POST, TRUE);
  //Set data to POST in HTTP "POST" Operation.
  curl_setopt($ch, CURLOPT_POSTFIELDS, $values);
  //CURLOPT_RETURNTRANSFER- TRUE to return the transfer as a string of the return value of curl_exec().
  curl_setopt ($ch, CURLOPT_RETURNTRANSFER, TRUE);
  //CURLOPT_SSL_VERIFYPEER- Set FALSE to stop cURL from verifying the peer's certificate.
  curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, false);
  
  //Execute the  cURL session.
  $json = curl_exec($ch);
  
  //Get the Error Code returned by Curl.
  $errno = curl_errno($ch);
  
  //Close the Curl Session.
  curl_close($ch);
  
  if($errno){
    /*echo('') . '<br/>' . PHP_EOL;
    echo('') . '<br/>' . PHP_EOL;
    echo('bing token errno: ') . '<br/>' . PHP_EOL;
    var_dump($errno);*/
    drupal_set_message(t('A error occured. Bing token curl errno, message: ') . $errno, 'warning');
    return false;
  }
  
  $data = json_decode($json, true);
  
  if(isset($data['error']) and '' != $data['error']){
    /*echo('') . '<br/>' . PHP_EOL;
    echo('') . '<br/>' . PHP_EOL;
    echo('bing token respones: ') . '<br/>' . PHP_EOL;
    print_r($data);*/
    drupal_set_message(t('A error occured. Bing token , error: ') . $data['error'] . t(', description: ') . $data['error_description'], 'warning');
    return false;    
  }
  
  /*echo('') . '<br/>' . PHP_EOL;
  echo('') . '<br/>' . PHP_EOL;
  echo('bing token json decode respones data: ') . '<br/>' . PHP_EOL;
  print_r($data);*/
  
  /*echo('') . '<br/>' . PHP_EOL;
  echo('') . '<br/>' . PHP_EOL;
  print_r(explode('&', $data['access_token']));
  
  $access_tokens = explode('&', $data['access_token']);
  list($key, $access_token) = explode('=', $access_tokens[5]);
  
  return $access_token;*/
  
  //exit();
  /*if(!isset($data['access_token'])){
    $data = rawurldecode($data)
  }*/
  return $data['access_token'];
}

function translation_helper_translate_text_bing($access_token, $text, $source, $target)
{
  //echo('bing token json decode respones access token: ') . '<br/>' . PHP_EOL;
  //var_dump($access_token);
  //print_r($access_token);
  
  $params = "appId=&text=" . urlencode($text) . "&to=" . $target . "&from=" . $source;
  $header = "Authorization: Bearer ". $access_token;
  
  //Initialize the Curl Session.
  $ch = curl_init();
  //Set the Curl url.
  curl_setopt ($ch, CURLOPT_URL, "http://api.microsofttranslator.com/v2/Http.svc/Translate?" . $params);
  //Set the HTTP HEADER Fields.
  curl_setopt ($ch, CURLOPT_HTTPHEADER, array($header, "Content-Type: text/xml"));
  //CURLOPT_RETURNTRANSFER- TRUE to return the transfer as a string of the return value of curl_exec().
  curl_setopt ($ch, CURLOPT_RETURNTRANSFER, TRUE);
  //CURLOPT_SSL_VERIFYPEER- Set FALSE to stop cURL from verifying the peer's certificate.
  curl_setopt ($ch, CURLOPT_SSL_VERIFYPEER, False);
  
  //Execute the  cURL session.
  $response = curl_exec($ch);
  
  //Get the Error Code returned by Curl.
  $errno = curl_errno($ch);
    
  //Close a cURL session.
  curl_close($ch);
  
  if ($errno) {
    /*echo('') . '<br/>' . PHP_EOL;
    echo('') . '<br/>' . PHP_EOL;
    echo('bing errno: ') . '<br/>' . PHP_EOL;
    var_dump($errno);*/
    drupal_set_message(t('A error occured. Bing curl errno, message: ') . $errno, 'warning');
    return '';
  }
  
  /*echo('') . '<br/>' . PHP_EOL;
  echo('') . '<br/>' . PHP_EOL;
  echo('bing response: ') . '<br/>' . PHP_EOL;
  var_dump($response);*/

  //Interprets a string of XML into an object.
  $xml = simplexml_load_string($response);   

  /*echo('') . '<br/>' . PHP_EOL;
  echo('') . '<br/>' . PHP_EOL;
  echo('bing xml: ') . '<br/>' . PHP_EOL;
  var_dump($xml);*/
  
  return $xml->{0};
}
?>