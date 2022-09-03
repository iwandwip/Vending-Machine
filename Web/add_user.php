<?php

require_once "db_conn.php";
require_once "func.php";

$valid = 0;

//$FLAG = 0;
//if (isset($_GET['daftar'])) {
//    $nama = $_GET['nama_form'];
//    $saldo = $_GET['saldo_form'];
//    $uid = $_GET['uid_form'];
//    $fingger = $_GET['fingger_form'];
//
//    $sqlInsert_User = "INSERT INTO `tbl_user`(`id_user`, `nama_user`, `saldo_user`, `uid_user`, `fingger_user`)
//                        VALUES (NULL,'$nama','$saldo','$uid','$fingger')";
//
//    $result = $koneksi->query($sqlInsert_User);
//
//    if ($result) {
//        $FLAG = 1;
//    } else {
//        $FLAG = -1;
//    }
//
//}
//
//$sqlUpdate_UID_Fingger = "UPDATE `tbl_board` SET `mode_board` = '1'  WHERE `tbl_board`.`id_board` = 1";
//$result = $koneksi->query($sqlUpdate_UID_Fingger);
//

if (isset($_GET["submit"]) and $_GET["submit"] == "submit") {

    $IDBoard = $_GET["id_board_form"];

    if (!validationBoardID($IDBoard, "id_user_penjual", $koneksi)) {
        $stmt = $koneksi->prepare("INSERT INTO id_user_penjual(`username`, `password`, `nik`, `nama`, `jk`, `id_board`) VALUES (?, ?, ?, ?, ?, ?)");
        $stmt->bind_param('sssssi', $username, $password, $NIK, $nama, $jenisKelamin, $IDBoard);

        $username = $_GET["username_form"];
        $password = $_GET["password_form"];

        $NIK = $_GET["nik_form"];
        $nama = $_GET["nama_form"];

        $jenisKelamin = $_GET["jenisKelamin"];
        $IDBoard = $_GET["id_board_form"];

        $stmt->execute();

        $stmt_ = $koneksi->prepare("INSERT INTO list_item(`id_board`) VALUES (?)");
        $stmt_->bind_param('i', $IDBoard_);

        $IDBoard_ = $_GET["id_board_form"];
        $stmt_->execute();

        $valid = 1;

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
    <title>Daftarkan Penjual</title>

</head>
<body>

<div class="row" style="height:  100vh">
    <div class="col-2  bg-light">
        <div class="d-flex flex-column  p-3">
            <ul class="nav nav-pills flex-column mb-auto">
                <li class="nav-item">
                    <a href="add_user.php" class="nav-link active" aria-current="page">
                        Daftar Penjual
                    </a>
                </li>
                <li>
                    <a href="admin_page.php" class="nav-link link-dark">
                        List Penjual
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
        <h1>Daftar Penjual</h1>
        <?php if ($valid == 1) { ?>
            <div class="alert alert-success" role="alert">
                Berhasil Daftar
            </div>
        <?php } elseif ($valid == 2) { ?>
            <div class="alert alert-danger" role="alert">
                Gagal Daftar ID Board Telah Terdaftar
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
                <label for="nik_form" class="form-label">NIK</label>
                <input type="nik" class="form-control rounded-left" id="nik_form" name="nik_form"
                       aria-describedby="emailHelp" required>
            </div>

            <div class="mb-3 form-group">
                <label for="nama_form" class="form-label">Nama</label>
                <input type="nama" class="form-control rounded-left" id="nama_form" name="nama_form"
                       aria-describedby="emailHelp" required>
            </div>

            <div>
                <label for="nama_form" class="form-label">Jenis Kelamin</label>
            </div>
            <div class="form-check form-group">
                <input class="form-check-input" type="radio" name="jenisKelamin" id="flexRadioDefault1" checked
                       value="laki">
                <label class="form-check-label" for="flexRadioDefault1">
                    Laki - laki
                </label>
            </div>
            <div class="form-check mb-3 form-group">
                <input class="form-check-input" type="radio" name="jenisKelamin" id="flexRadioDefault2"
                       value="perempuan">
                <label class="form-check-label" for="flexRadioDefault2">
                    Perempuan
                </label>
            </div>

            <div class="mb-3 form-group">
                <label for="id_board_form" class="form-label">ID Board</label>
                <input type="number" class="form-control rounded-left" id="id_board_form" name="id_board_form"
                       aria-describedby="emailHelp" min="0" max="500" required placeholder="1 - 500">
            </div>

            <div class="mb-3 form-group">
                <label for="username_form" class="form-label">Username</label>
                <input type="username" class="form-control rounded-left" id="username_form" name="username_form"
                       aria-describedby="emailHelp" required>
            </div>

            <div class="mb-3 form-group">
                <label for="password_form" class="form-label">Password</label>
                <input type="password" class="form-control rounded-left" id="password_form" name="password_form"
                       aria-describedby="emailHelp" required>
            </div>

            <button type="submit" class="btn btn-primary" name="submit" value="submit">Submit</button>
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
