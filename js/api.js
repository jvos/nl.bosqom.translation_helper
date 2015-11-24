function translation_helper_goto(base_url, url)
{
  if(-1 != document.location.href.indexOf('render=overlay')){ // ?render=overlay or &render=overlay
    document.location.href = base_url + url + '?render=overlay';
  }else {
    document.location.href = base_url + url;
  }
}