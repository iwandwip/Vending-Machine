<?php
// Initialize the session
session_start();

$valid = 0;

// Check if the user is logged in, if not then redirect him to login page
if (!isset($_SESSION["loggedin"]) || $_SESSION["loggedin"] !== true) {
    header("location: index.php");
    exit;
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
                    <a href="topup.php" class="nav-link link-dark" aria-current="page">
                        TopUp
                    </a>
                </li>
                <li>
                    <a href="user_page.php" class="nav-link active">
                        List Item
                    </a>
                </li>
                <li>
                    <a href="logout.php" class="nav-link link-dark">
                        Logout
                    </a>
                </li>
            </ul>

        </div>
    </div>
    <div class="col-8 p-5   ">
        <h1>Item Vending</h1>


        <hr>
        <span class="voters"></span>

        <?php
        require_once "db_conn.php";
        require_once "func.php";

        $marlboroItem = 0;
        $camelItem = 0;
        $suryaItem = 0;

        $IDBoard = getBoardID($_SESSION["username"], "id_user_penjual", $koneksi);

        $mySql = "SELECT marlboro, sampoerna, surya, camel  FROM list_item WHERE id_board = $IDBoard";

        if ($stmt = $koneksi->prepare($mySql)) {

            if ($stmt->execute()) {

                $stmt->bind_result($marlboro, $sampoerna, $surya, $camel);
                while ($stmt->fetch()) {

                    $marlboroItem = $marlboro;
                    $camelItem = $camel;
                    $suryaItem = $surya;

                }
            }
        }

        function getBoardID($usrname = NULL, $tbl = NULL, $dbConn = NULL)
        {
            $sql = "SELECT id_board  FROM $tbl WHERE username = ?";
            $_myBoardID = 0;
            $boardID = 0;
            if (isset($usrname)) {

                if ($stmt = $dbConn->prepare($sql)) {
                    /* Bind variables to the prepared statement as parameters */
                    $stmt->bind_param("s", $usrname);

                    if ($stmt->execute()) {
                        // Store result
                        $stmt->store_result();

                        if ($stmt->num_rows == 1) {
                            /* Bind result variables */
                            $stmt->bind_result($_myBoardID);

                            while ($stmt->fetch()) {
                                $boardID = $_myBoardID;
                            }
                        }
                    }
                    $stmt->close();
                }
            }
            return $boardID;
        }

        ?>

        <?php
        require_once "db_conn.php";
        require_once "func.php";

        if (isset($_GET["submit"]) and $_GET["submit"] == "submit") {

            $marlboro_insert = $_GET["marlboro_form"];
            $total_marlboro = 0;

            $total_marlboro = $marlboro_insert + getStock("marlboro", $IDBoard, "list_item", $koneksi);
            if ($total_marlboro > 4) {
                $valid = 2;
            } else {

                $sql = "UPDATE list_item  SET marlboro=? WHERE id_board = ?";
                if ($stmt = $koneksi->prepare($sql)) {

                    $stmt->bind_param("ii", $total_marlboro, $IDBoard);
                    if ($stmt->execute()) {

                        $valid = 1;
                        header("location: user_page.php");

                    }
                    $stmt->close();
                }
            }

        }

        function getStock($rokokType = NULL, $boardID = NULL, $tbl = NULL, $dbConn = NULL)
        {
            $sql = "SELECT $rokokType  FROM $tbl WHERE id_board = $boardID";
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

        ?>
        <div class="row">
            <div class="col-3">
                <div class="card">
                    <div class="card-body text-center">
                        <h5 class="card-title">Item Vending</h5>
                        <div class="card-text">
                            <ul class="list-group p-4">
                                <?php if ($suryaItem == 4) { ?>
                                    <li class="list-group-item list-group-item-success">&nbsp;</li>
                                    <li class="list-group-item list-group-item-success">&nbsp;</li>
                                    <li class="list-group-item list-group-item-success">&nbsp;</li>
                                    <li class="list-group-item list-group-item-success">&nbsp;</li>
                                <?php } elseif ($suryaItem == 3) { ?>
                                    <li class="list-group-item list-group-item-dark">&nbsp;</li>
                                    <li class="list-group-item list-group-item-success">&nbsp;</li>
                                    <li class="list-group-item list-group-item-success">&nbsp;</li>
                                    <li class="list-group-item list-group-item-success">&nbsp;</li>
                                <?php } elseif ($suryaItem == 2) { ?>
                                    <li class="list-group-item list-group-item-dark">&nbsp;</li>
                                    <li class="list-group-item list-group-item-dark">&nbsp;</li>
                                    <li class="list-group-item list-group-item-success">&nbsp;</li>
                                    <li class="list-group-item list-group-item-success">&nbsp;</li>
                                <?php } elseif ($suryaItem == 1) { ?>
                                    <li class="list-group-item list-group-item-dark">&nbsp;</li>
                                    <li class="list-group-item list-group-item-dark">&nbsp;</li>
                                    <li class="list-group-item list-group-item-dark">&nbsp;</li>
                                    <li class="list-group-item list-group-item-success">&nbsp;</li>
                                <?php } elseif ($suryaItem == 0) { ?>
                                    <li class="list-group-item list-group-item-dark">&nbsp;</li>
                                    <li class="list-group-item list-group-item-dark">&nbsp;</li>
                                    <li class="list-group-item list-group-item-dark">&nbsp;</li>
                                    <li class="list-group-item list-group-item-dark">&nbsp;</li>
                                <?php } ?>
                            </ul>
                        </div>
                        <div class="card-text">
                            <p>Produk : <b>Surya</b></p>
                        </div>
                        <a href="edit_item_surya.php" class="btn btn-primary">Edit List Vending</a>
                    </div>
                </div>
            </div>
            <div class="col-3">
                <div class="card">
                    <div class="card-body text-center">
                        <h5 class="card-title">Item Vending</h5>
                        <div class="card-text">
                            <ul class="list-group p-4">
                                <?php if ($camelItem == 4) { ?>
                                    <li class="list-group-item list-group-item-success">&nbsp;</li>
                                    <li class="list-group-item list-group-item-success">&nbsp;</li>
                                    <li class="list-group-item list-group-item-success">&nbsp;</li>
                                    <li class="list-group-item list-group-item-success">&nbsp;</li>
                                <?php } elseif ($camelItem == 3) { ?>
                                    <li class="list-group-item list-group-item-dark">&nbsp;</li>
                                    <li class="list-group-item list-group-item-success">&nbsp;</li>
                                    <li class="list-group-item list-group-item-success">&nbsp;</li>
                                    <li class="list-group-item list-group-item-success">&nbsp;</li>
                                <?php } elseif ($camelItem == 2) { ?>
                                    <li class="list-group-item list-group-item-dark">&nbsp;</li>
                                    <li class="list-group-item list-group-item-dark">&nbsp;</li>
                                    <li class="list-group-item list-group-item-success">&nbsp;</li>
                                    <li class="list-group-item list-group-item-success">&nbsp;</li>
                                <?php } elseif ($camelItem == 1) { ?>
                                    <li class="list-group-item list-group-item-dark">&nbsp;</li>
                                    <li class="list-group-item list-group-item-dark">&nbsp;</li>
                                    <li class="list-group-item list-group-item-dark">&nbsp;</li>
                                    <li class="list-group-item list-group-item-success">&nbsp;</li>
                                <?php } elseif ($camelItem == 0) { ?>
                                    <li class="list-group-item list-group-item-dark">&nbsp;</li>
                                    <li class="list-group-item list-group-item-dark">&nbsp;</li>
                                    <li class="list-group-item list-group-item-dark">&nbsp;</li>
                                    <li class="list-group-item list-group-item-dark">&nbsp;</li>
                                <?php } ?>
                            </ul>
                        </div>
                        <div class="card-text">
                            <p>Produk : <b> Camel</b></p>
                        </div>
                        <a href="edit_item_camel.php" class="btn btn-primary">Edit List Vending</a>
                    </div>
                </div>
            </div>
            <div class="col-3">
                <div class="card">
                    <div class="card-body text-center">
                        <h5 class="card-title">Item Vending</h5>
                        <div class="card-text">
                            <ul class="list-group p-4">
                                <?php if ($marlboroItem == 4) { ?>
                                    <li class="list-group-item list-group-item-success">&nbsp;</li>
                                    <li class="list-group-item list-group-item-success">&nbsp;</li>
                                    <li class="list-group-item list-group-item-success">&nbsp;</li>
                                    <li class="list-group-item list-group-item-success">&nbsp;</li>
                                <?php } elseif ($marlboroItem == 3) { ?>
                                    <li class="list-group-item list-group-item-dark">&nbsp;</li>
                                    <li class="list-group-item list-group-item-success">&nbsp;</li>
                                    <li class="list-group-item list-group-item-success">&nbsp;</li>
                                    <li class="list-group-item list-group-item-success">&nbsp;</li>
                                <?php } elseif ($marlboroItem == 2) { ?>
                                    <li class="list-group-item list-group-item-dark">&nbsp;</li>
                                    <li class="list-group-item list-group-item-dark">&nbsp;</li>
                                    <li class="list-group-item list-group-item-success">&nbsp;</li>
                                    <li class="list-group-item list-group-item-success">&nbsp;</li>
                                <?php } elseif ($marlboroItem == 1) { ?>
                                    <li class="list-group-item list-group-item-dark">&nbsp;</li>
                                    <li class="list-group-item list-group-item-dark">&nbsp;</li>
                                    <li class="list-group-item list-group-item-dark">&nbsp;</li>
                                    <li class="list-group-item list-group-item-success">&nbsp;</li>
                                <?php } elseif ($marlboroItem == 0) { ?>
                                    <li class="list-group-item list-group-item-dark">&nbsp;</li>
                                    <li class="list-group-item list-group-item-dark">&nbsp;</li>
                                    <li class="list-group-item list-group-item-dark">&nbsp;</li>
                                    <li class="list-group-item list-group-item-dark">&nbsp;</li>
                                <?php } ?>
                            </ul>
                        </div>
                        <form>
                            <div class="mb-3 form-group">
                                <input type="number" class="form-control rounded-left" id="marlboro_form"
                                       name="marlboro_form"
                                       aria-describedby="emailHelp" required max="4" min="1" step="1">
                            </div>
                            <button type="submit" class="btn btn-primary" name="submit" value="submit">Tambah</button>

                            <br/><br/>

                            <?php if ($valid == 1) { ?>
                                <div class="alert alert-success" role="alert">
                                    Berhasil Menambahkan Item
                                </div>
                            <?php } elseif ($valid == 2) { ?>
                                <div class="alert alert-danger" role="alert">
                                    Gagal !! Item Telah Penuh
                                </div>
                            <?php } ?>
                        </form>
                    </div>
                </div>
            </div>


            <!--            <div class="col-3">-->
            <!--                <div class="card">-->
            <!--                    <div class="card-body text-center">-->
            <!--                        <h5 class="card-title">Item Vending</h5>-->
            <!--                        <div class="card-text">-->
            <!--                            <ul class="list-group p-4">-->
            <!--                                <li class="list-group-item list-group-item-success">&nbsp;</li>-->
            <!--                                <li class="list-group-item list-group-item-success">&nbsp;</li>-->
            <!--                                <li class="list-group-item list-group-item-success">&nbsp;</li>-->
            <!--                                <li class="list-group-item list-group-item-success">&nbsp;</li>-->
            <!--                            </ul>-->
            <!--                        </div>-->
            <!--                        <div class="card-text">-->
            <!--                            <p>Produk : <b> 	Sampoerna</b></p>-->
            <!--                        </div>-->
            <!--                        <a href="#" class="btn btn-primary">Edit List Vending</a>-->
            <!--                    </div>-->
            <!--                </div>-->
            <!--            </div>-->


        </div>
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
                        if (k == "fingger") $('.id_fingger').val(v);
                    });
                });
            },
        });
    };
    update();
</script>

</body>
</html>