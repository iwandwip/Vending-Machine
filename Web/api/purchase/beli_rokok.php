<?php
require_once "../../db_conn.php";
require_once "../../func.php";

$rokok = 0;

if (isset($_GET["idboard"])) {
    $idboard = $_GET["idboard"];
    $merk = $_GET["merk"];

    if (!getItemRokok($idboard, $merk, "list_item", $koneksi) == 0) {
        echo '1';
    } else {
        echo '-1';
    }
}

