<?php
require_once "../../db_conn.php";
require_once "../../func.php";

if (isset($_GET["fingerid"]) and isset($_GET["rfid"])){

    $finger_id = $_GET["fingerid"];
    $uid_rfid = $_GET["rfid"];

    echo getSaldoUser(1, 1, "id_pelanggan", $koneksi);
}

