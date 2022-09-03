<?php
// Initialize the session
//session_start();

?>

<!DOCTYPE html>
<html lang="en">

<head>
    <title>List Penjual</title>
    <meta charset="utf-8"/>
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no"/>

    <link href="https://fonts.googleapis.com/css?family=Lato:300,400,700&display=swap" rel="stylesheet"/>

    <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/font-awesome/4.7.0/css/font-awesome.min.css"/>

    <link rel="stylesheet" href="css/style.css"/>
    <!-- Bootstrap CSS -->
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/css/bootstrap.min.css" rel="stylesheet"
          integrity="sha384-EVSTQN3/azprG1Anm3QDgpJLIm9Nao0Yz1ztcQTwFspd3yD65VohhpuuCOmLASjC" crossorigin="anonymous">
</head>

<body>
<div class="row" style="height: 100vh">
    <div class="col-2  bg-light">
        <div class="d-flex flex-column  p-3">
            <ul class="nav nav-pills flex-column mb-auto">
                <li class="nav-item">
                    <a href="add_user.php" class="nav-link link-dark" aria-current="page">
                        Daftar Penjual
                    </a>
                </li>
                <li>
                    <a href="admin_page.php" class="nav-link active ">
                        List Penjual
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

    <div class="col-8 p-5 ">
        <h1>List Penjual</h1>
        <span class="voters"></span>
        <table class="table">
            <thead>
            <tr>
                <th scope="col">#</th>
                <th scope="col">NIK KTP</th>
                <th scope="col">Nama User</th>
                <th scope="col">Jenis Kelamin</th>
                <th scope="col">ID Board</th>
            </tr>
            </thead>
            <tbody>
            <?php
            require_once "db_conn.php";
            require_once "func.php";

            $x = 1;

            $sql = "SELECT username, password, nik, nama, jk, id_board FROM id_user_penjual";
            if ($stmt = $koneksi->prepare($sql)) {

                if ($stmt->execute()) {

                    $jenisKelamin = "";

                    $stmt->bind_result($username, $password, $nik, $nama, $jk, $id_board);
                    while ($stmt->fetch()) {

                        if ($jk == "laki") $jenisKelamin = "Laki - laki";
                        else $jenisKelamin = "Perempuan";

                        echo '

                        <tr>
                            <td>' . $x++ . '</td>
                            <td>' . $nik . '</td>
                            <td>' . $nama . '</td>
                            <td>' . $jenisKelamin . '</td>
                            <td>' . $id_board . '</td>
                        </tr>
                    
                    ';
                    }
                }
            }
            ?>
            </tbody>
    </div>

</div>
<!-- Option 1: Bootstrap Bundle with Popper -->
<script src="https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/js/bootstrap.bundle.min.js"
        integrity="sha384-MrcW6ZMFYlzcLA8Nl+NtUVF0sA7MsXsP1UyJoMp4YLEuNSfAP+JcXn/tWtIaxVXM" crossorigin="anonymous">
</script>
<script src="https://ajax.googleapis.com/ajax/libs/jquery/3.6.0/jquery.min.js"></script>

<script src="js/jquery.min.js"></script>
<script src="js/popper.js"></script>
<script src="js/bootstrap.min.js"></script>
<script src="js/main.js"></script>
</body>

</html>