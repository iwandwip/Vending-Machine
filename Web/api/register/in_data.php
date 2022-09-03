<?php
require_once "../../db_conn.php";
require_once "../../func.php";

if (isset($_GET["rfid"]) and isset($_GET["fingerid"])) {

    $uid_rfid = $_GET["rfid"];
    $finger_id = $_GET["fingerid"];

    if (inData($uid_rfid, $finger_id, "id_pelanggan", $koneksi)) {
        echo '1';
    } else {
        echo '0';
    }
}
