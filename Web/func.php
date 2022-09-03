<?php

ob_start();
require_once "db_conn.php";

//$response = get_web_page("http://".$HOST_ADDR."/api/getBoardMode.php?board_id=1");

//$resArr = array();
//$resArr = json_decode($response);
//echo "<pre>"; print_r($response); echo "</pre>";

function get_web_page($url)
{

    $options = array(
        CURLOPT_RETURNTRANSFER => true,   // return web page
        CURLOPT_HEADER => false,  // don't return headers
        CURLOPT_FOLLOWLOCATION => true,   // follow redirects
        CURLOPT_MAXREDIRS => 10,     // stop after 10 redirects
        CURLOPT_ENCODING => "",     // handle compressed
        CURLOPT_USERAGENT => "test", // name of client
        CURLOPT_AUTOREFERER => true,   // set referrer on redirect
        CURLOPT_CONNECTTIMEOUT => 120,    // time-out on connect
        CURLOPT_TIMEOUT => 120,    // time-out on response
    );

    $ch = curl_init($url);
    curl_setopt_array($ch, $options);

    $content = curl_exec($ch);

    curl_close($ch);

    return $content;
}

function userNamePassVerify($usrname = NULL, $passwd = NULL, $tbl = NULL, $dbconn = NULL)
{
    $sql = "SELECT username, password  FROM $tbl WHERE username = ?";
    $valid = false;

    if (isset($usrname) and isset($passwd)) {
        if ($stmt = $dbconn->prepare($sql)) {
            /* Bind variables to the prepared statement as parameters */
            $stmt->bind_param("s", $usrname);
            if ($stmt->execute()) {

                // Store result
                $stmt->store_result();
                if ($stmt->num_rows == 1) {
                    /* Bind result variables */
                    // $stmt->bind_result($usrname, $passwd);
                    $valid = true;
                }
            }
            $stmt->close();
        }
    }
    return $valid;
}

function validationBoardID($boardID = NULL, $tbl = NULL, $dbConn = NULL)
{
    $sql = "SELECT id_board  FROM $tbl WHERE id_board = ?";
    $valid_ = false;

    if (isset($boardID)) {
        if ($stmt = $dbConn->prepare($sql)) {
            /* Bind variables to the prepared statement as parameters */
            $stmt->bind_param("i", $boardID);
            if ($stmt->execute()) {
                // Store result
                $stmt->store_result();
                if ($stmt->num_rows == 1) {
                    /* Bind result variables */
                    // $stmt->bind_result($usrname, $passwd);
                    $valid_ = true;
                }
            }
            $stmt->close();
        }
    }
    return $valid_;
}

function RFIDFingerValidation($_IDFinger = NULL, $_IDRfid = NULL, $tbl = NULL, $dbConn = NULL)
{
    $sql = "SELECT id_fingger, id_rfid  FROM $tbl WHERE (id_fingger = ? AND id_rfid = ?)";
    $valid = false;

    if (isset($_IDFinger) and isset($_IDRfid)) {

        if ($stmt = $dbConn->prepare($sql)) {

            $stmt->bind_param("ii", $_IDFinger, $_IDRfid);
            if ($stmt->execute()) {

                // Store result
                $stmt->store_result();
                if ($stmt->num_rows == 1) {

                    /* Bind result variables */
                    $stmt->bind_result($_IDFinger, $_IDRfid);
                    $valid = true;
                }
            }
            $stmt->close();
        }
    }
    return $valid;
}

function getSaldoUser($_IDFinger = NULL, $_IDRfid = NULL, $tbl = NULL, $dbConn = NULL)
{
    $sql = "SELECT saldo  FROM $tbl WHERE (id_fingger = $_IDFinger AND id_rfid = $_IDRfid)";
    $saldo = 0;
    $saldoItem = 0;

    if ($stmt = $dbConn->prepare($sql)) {

        if ($stmt->execute()) {

            $stmt->bind_result($saldo);
            while ($stmt->fetch()) {

                $saldoItem = $saldo;
            }
        }
    }

    return $saldoItem;
}

function getUserID($ID = NULL, $tbl = NULL, $dbConn = NULL, $myId = NULL)
{
    $sql = "SELECT $myId  FROM $tbl WHERE $myId = $ID";
    $_ID = 0;
    $_IDItem = 0;

    if ($stmt = $dbConn->prepare($sql)) {

        if ($stmt->execute()) {

            $stmt->bind_result($_ID);
            while ($stmt->fetch()) {

                $_IDItem = $_ID;
            }
        }
    }

    return $_IDItem;
}

function getSaldo($_ID_rfid = NULL, $tbl = NULL, $dbConn = NULL)
{
    $sql = "SELECT saldo  FROM $tbl WHERE id_rfid = $_ID_rfid";
    $saldo = 0;
    $saldoItem = 0;

    if ($stmt = $dbConn->prepare($sql)) {

        if ($stmt->execute()) {

            $stmt->bind_result($saldo);
            while ($stmt->fetch()) {

                $saldoItem = $saldo;
            }
        }
    }

    return $saldoItem;
}

function getItemRokok($idboard = NULL, $merk = NULL, $tbl = NULL, $dbConn = NULL)
{
    $sql = "SELECT $merk  FROM $tbl WHERE id_board = $idboard";
    $rokok = 0;
    $rokokItem = 0;

    if ($stmt = $dbConn->prepare($sql)) {

        if ($stmt->execute()) {

            $stmt->bind_result($rokok);
            while ($stmt->fetch()) {

                $rokokItem = $rokok;
            }
        }
    }

    return $rokokItem;
}

function updateItemRokok($total_rokok = NULL, $idboard = NULL, $merk = NULL, $tbl = NULL, $dbConn = NULL)
{
    $sql = "UPDATE $tbl SET $merk=? WHERE id_board=?";

    if ($stmt = $dbConn->prepare($sql)) {

        $stmt->bind_param('ii', $total_rokok, $idboard);
        $stmt->execute();
    }
}

function updateSaldo($saldo = NULL, $_ID_rfid = NULL, $tbl = NULL, $dbConn = NULL)
{
    $sql = "UPDATE $tbl SET saldo=? WHERE id_rfid=?";

    if ($stmt = $dbConn->prepare($sql)) {

        $stmt->bind_param('ii', $saldo, $_ID_rfid);
        $stmt->execute();
    }
}

function getNewUserID($dbConn = NULL)
{
    $sql = "SELECT id_fingger FROM id_pelanggan WHERE id_fingger = ( SELECT MAX(id_fingger) FROM id_pelanggan )";
    $_ID = 0;
    $_IDItem = 0;

    if ($stmt = $dbConn->prepare($sql)) {

        if ($stmt->execute()) {

            $stmt->bind_result($_ID);
            while ($stmt->fetch()) {

                $_IDItem = $_ID;
            }
        }
    }

    return $_IDItem + 1;
}

function inData($uid_rfid = NULL, $finger_id = NULL, $tbl = NULL, $dbConn = NULL)
{
    $sql = "INSERT INTO $tbl (id_fingger, id_rfid, saldo) VALUES (?, ?, ?)";
    $saldo_awal = 0;
    $state = 0;

    if ($stmt = $dbConn->prepare($sql)) {

        $stmt->bind_param('iii', $finger_id, $uid_rfid, $saldo_awal);

        if ($stmt->execute()) {
            $state = 1;
        }
    }
    return $state;
}
