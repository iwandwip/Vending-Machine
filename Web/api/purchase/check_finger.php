<?php
require_once "../../db_conn.php";
require_once "../../func.php";

$finger_id = 0;

if (isset($_GET["fingerid"])){

    $finger_id = $_GET["fingerid"];

    if ($finger_id == getUserID($finger_id, "id_pelanggan", $koneksi, "id_fingger")){

        echo '1';
    }
}
