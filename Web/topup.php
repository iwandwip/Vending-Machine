<?php

require_once "db_conn.php";
require_once "func.php";

$valid = 0;
$total_saldo = 0;

if (isset($_GET["submit"]) and $_GET["submit"] == "submit_topup") {

    $IDFinger = $_GET["id_finger_form"];
    $IDRfid = $_GET["uid_rfid_form"];
    $saldo = $_GET["saldo_form"];

    if (RFIDFingerValidation($IDFinger, $IDRfid, "id_pelanggan", $koneksi)) {

        if ($total_saldo = $saldo + getSaldoUser($IDFinger, $IDRfid, "id_pelanggan", $koneksi)) {

            $sql = "UPDATE id_pelanggan SET saldo=? WHERE (id_fingger = ? AND id_rfid = ?)";
            if ($stmt = $koneksi->prepare($sql)) {

                $stmt->bind_param("iii", $total_saldo, $IDFinger, $IDRfid);
                if ($stmt->execute()) {
                    $valid = 1;
                }
                $stmt->close();
            }
        }

    } else {
        $valid = 2;
    }
}
?>

<!doctype html>
<html lang="en">
<head>
    <!-- Required meta tags -->
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, height=device-height, initial-scale=1.0, minimum-scale=1.0">

    <!-- Bootstrap CSS -->
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/css/bootstrap.min.css" rel="stylesheet"
          integrity="sha384-EVSTQN3/azprG1Anm3QDgpJLIm9Nao0Yz1ztcQTwFspd3yD65VohhpuuCOmLASjC" crossorigin="anonymous">
    <title>Hello, world!</title>

</head>
<body>

<div class="row" style="height:  100vh">
    <div class="col-2  bg-light">
        <div class="d-flex flex-column  p-3">
            <ul class="nav nav-pills flex-column mb-auto">
                <li class="nav-item">
                    <a href="topup.php" class="nav-link active" aria-current="page">
                        TopUp
                    </a>
                </li>
                <li>
                    <a href="user_page.php" class="nav-link link-dark">
                        List Item
                    </a>
                </li>
                <li>
                    <a href="logout.php" class="nav-link link-dark">
                        Logout
                    </a>
                </li>
                <!--                <li class="position-absolute bottom-50 translate-middle-y bg-light">-->
                <!--                    <a href="#" class="nav-link">-->
                <!--                        Logout-->
                <!--                    </a>-->
                <!--                </li>-->
            </ul>
        </div>
    </div>
    <div class="col-8 p-5   ">
        <h1>TopUp</h1>
        <?php if ($valid == 1) { ?>
            <div class="alert alert-success" role="alert">
                Top Up Berhasil
            </div>
        <?php } elseif ($valid == 2) { ?>
            <div class="alert alert-danger" role="alert">
                Top Up Gagal ID Finger dan UID RFID Salah
            </div>
        <?php } ?>

        <hr>
        <span class="voters"></span>

        <form>
            <!--            <div class="mb-3">-->
            <!--                <label for="nama_form" class="form-label">Nama</label>-->
            <!--                <input type="nama" class="form-control" id="nama_form" name="nama_form" aria-describedby="emailHelp">-->
            <!--            </div>-->

            <!--            <div class="mb-3">-->
            <!--                <label for="saldo_form" class="form-label">Saldo (Rp)</label>-->
            <!--                <input type="number" class="form-control" name="saldo_form" id="Saldo" aria-describedby="emailHelp"-->
            <!--                       step="100">-->
            <!--            </div>-->

            <!--            <div class="mb-3">-->
            <!--                <label for="uid" class="form-label">UID RFID</label>-->
            <!--                <input class="uid_val form-control" name="uid_form" id="uid" type="text"-->
            <!--                       placeholder="Disabled input here...">-->
            <!--            </div>-->
            <!--            <div class="mb-3">-->
            <!--                <label for="id_fingger" class="form-label">ID FINGGER</label>-->
            <!--                <input class="id_fingger form-control" name="fingger_form" id="id_fingger" type="text"-->
            <!--                       placeholder="Disabled input here...">-->
            <!--                <input type="hidden" name="daftar" value="1">-->
            <!--            </div>-->

            <div class="mb-3 form-group">
                <label for="id_finger_form" class="form-label">ID Finger</label>
                <input type="text" class="form-control rounded-left" id="id_finger_form" name="id_finger_form"
                       aria-describedby="emailHelp" required>
            </div>

            <div class="mb-3 form-group">
                <label for="uid_rfid_form" class="form-label">UID RFID</label>
                <input type="text" class="form-control rounded-left" id="uid_rfid_form" name="uid_rfid_form"
                       aria-describedby="emailHelp" required>
            </div>

            <div class="mb-3 form-group">
                <label for="saldo_form" class="form-label">(Rp) Nominal</label>
                <input type="number" class="form-control rounded-left" id="saldo_form" name="saldo_form"
                       aria-describedby="emailHelp" required step="10000">
            </div>

            <button type="submit" class="btn btn-primary" name="submit" value="submit_topup">Submit</button>
        </form>
    </div>
</div>

<!-- Option 1: Bootstrap Bundle with Popper -->
<script src="https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/js/bootstrap.bundle.min.js"
        integrity="sha384-MrcW6ZMFYlzcLA8Nl+NtUVF0sA7MsXsP1UyJoMp4YLEuNSfAP+JcXn/tWtIaxVXM"
        crossorigin="anonymous"></script>
<script src="https://ajax.googleapis.com/ajax/libs/jquery/3.6.0/jquery.min.js"></script>

<script>

    var refInterval = window.setInterval('update()', 1000); // 30 seconds

    var update = function () {
        $.ajax({
            type: 'GET',
            url: 'api/daftar/getDataDaftar.php',
            success: function (data) {
                var dataJson = jQuery.parseJSON(data);
                // var json = $.parseJSON(j);
                $(dataJson["data_daftar"]).each(function (i, val) {
                    $.each(val, function (k, v) {
                        console.log(k + " : " + v);
                        if (k == "uid") $('.uid_val').val(v);
                        //if (k == "fingger") $('.id_fingger').val(v);
                    });
                });
            },
        });
    };
    update();
</script>

</body>
</html>
