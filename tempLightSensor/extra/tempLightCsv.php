<?php 
$json = file_get_contents('http://arduino/');

$data = json_decode($json);
$temp = $data->{"sensors"}->{"temp"};
echo time().",";
echo $temp->{"raw"}.",".$temp->{"volts"}.",".$temp->{"celsius"}.",";
echo $data->{"sensors"}->{"light"}."\n";
