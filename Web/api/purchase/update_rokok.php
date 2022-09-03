<?php
require_once "../../db_conn.php";
require_once "../../func.php";

$rokok = 0;
$harga_rokok = 0;

if (isset($_GET["idboard"])) {

    $idboard = $_GET["idboard"];
    $merk = $_GET["merk"];
    $uid_rfid = $_GET["rfid"];

    if ($merk == "surya") $harga_rokok = 21000;
    else if ($merk == "camel") $harga_rokok = 26000;
    else if ($merk == "marlboro") $harga_rokok = 24000;

    if (!getItemRokok($idboard, $merk, "list_item", $koneksi) == 0) {

        $total_rokok = getItemRokok($idboard, $merk, "list_item", $koneksi) - 1;

        $saldo = getSaldo($uid_rfid, "id_pelanggan", $koneksi);
        $total_saldo = $saldo - $harga_rokok;

        updateItemRokok($total_rokok, $idboard, $merk, "list_item", $koneksi);
        updateSaldo($total_saldo, $uid_rfid, "id_pelanggan", $koneksi);
    }
}

