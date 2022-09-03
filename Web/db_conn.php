<?php
//$DB_HOST = "localhost";
//$DB_USER = "adminkastara_22_vending";
//$DB_PASS = "adminkastara_22_vending";
//$DB_DATABASE = "adminkastara_22_vending";
//$HOST_ADDR = "www.imakeofficial.com/project/22_Vending/";

$DB_HOST = "localhost";
$DB_USER = "root";
$DB_PASS = "";
$DB_DATABASE = "test";
$HOST_ADDR = "www.imakeofficial.com/project/22_Vending/";

$koneksi = new mysqli($DB_HOST, $DB_USER, $DB_PASS, $DB_DATABASE);
if (!$koneksi) die("Koneksi Problem : " . $koneksi->connect_errno);
