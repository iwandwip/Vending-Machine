<?php
require_once "../../db_conn.php";
require_once "../../func.php";

if (isset($_GET["rfid"])){
    $uid_rfid = $_GET["rfid"];

    if ($uid_rfid == getUserID($uid_rfid, "id_pelanggan", $koneksi, "id_rfid")){

        $saldo = getSaldo($uid_rfid, "id_pelanggan", $koneksi);
        echo '1'.'#'.$saldo;
    }
}
