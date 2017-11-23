<?php
ini_set("display_errors", 0);

$search = $_GET["id"];
$query = "select * from users where id {$search}";

try
{
  $result = $db->query($query)->fetchAll();
  foreach($result as $r)
  {

  }
}
catch (Exception e)
{

}
?>
