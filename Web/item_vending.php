<?php

require_once "db_conn.php";
require_once "func.php";


?>


<!doctype html>
<html lang="en">
<head>
    <!-- Required meta tags -->
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, height=device-height, initial-scale=1.0, minimum-scale=1.0">

    <!-- Bootstrap CSS -->
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-EVSTQN3/azprG1Anm3QDgpJLIm9Nao0Yz1ztcQTwFspd3yD65VohhpuuCOmLASjC" crossorigin="anonymous">
    <title>List Item</title>

</head>
<body>

<div class="row" style="height:  100vh">
    <div class="col-2  bg-light">
        <div class="d-flex flex-column  p-3">
            <ul class="nav nav-pills flex-column mb-auto">
                <li class="nav-item">
                    <a href="tambah_user.php" class="nav-link link-dark" aria-current="page">
                        Daftar
                    </a>
                </li>
                <li>
                    <a href="index.php" class="nav-link link-dark  ">
                        List User
                    </a>
                </li>
                <li>
                    <a href="stock.php" class="nav-link link-dark  ">
                        Sisa Stock Produk
                    </a>
                </li>
                <li>
                    <a href="item_vending.php" class="nav-link active ">
                        Item Vending
                    </a>
                </li>
            </ul>

        </div>
    </div>
    <div class="col-8 p-5   ">
        <h1>Item Vending</h1>


        <hr> <span class="voters"></span>
        <div class="row">
            <div class="col-3">
                <div class="card">
                    <div class="card-body text-center">
                        <h5 class="card-title">Item Vending</h5>
                        <div class="card-text">
                            <ul class="list-group p-4">
                                <li class="list-group-item list-group-item-success">&nbsp;</li>
                                <li class="list-group-item list-group-item-success">&nbsp;</li>
                                <li class="list-group-item list-group-item-success">&nbsp;</li>
                                <li class="list-group-item list-group-item-success">&nbsp;</li>
                            </ul>
                        </div>
                        <div class="card-text">
                            <p>Produk : <b>Sampoerna</b></p>
                        </div>
                        <a href="#" class="btn btn-primary">Edit List Vending</a>
                    </div>
                </div>
            </div>
            <div class="col-3">
                <div class="card">
                    <div class="card-body text-center">
                        <h5 class="card-title">Item Vending</h5>
                        <div class="card-text">
                            <ul class="list-group p-4">
                                <li class="list-group-item list-group-item-dark">&nbsp;</li>
                                <li class="list-group-item list-group-item-success">&nbsp;</li>
                                <li class="list-group-item list-group-item-success">&nbsp;</li>
                                <li class="list-group-item list-group-item-success">&nbsp;</li>
                            </ul>
                        </div>
                        <div class="card-text">
                            <p>Produk : <b> 	 	Camel</b></p>
                        </div>
                        <a href="#" class="btn btn-primary">Edit List Vending</a>
                    </div>
                </div>
            </div>
            <div class="col-3">
                <div class="card" >
                    <div class="card-body text-center">
                        <h5 class="card-title">Item Vending</h5>
                        <div class="card-text">
                            <ul class="list-group p-4">
                                <li class="list-group-item list-group-item-dark">&nbsp;</li>
                                <li class="list-group-item list-group-item-success">&nbsp;</li>
                                <li class="list-group-item list-group-item-success">&nbsp;</li>
                                <li class="list-group-item list-group-item-success">&nbsp;</li>
                            </ul>
                        </div>
                        <div class="card-text">
                            <p>Produk : <b> 	 	Marlboro</b></p>
                        </div>
                        <a href="#" class="btn btn-primary">Edit List Vending</a>
                    </div>
                </div>
            </div>
            <div class="col-3">
                <div class="card">
                    <div class="card-body text-center">
                        <h5 class="card-title">Item Vending</h5>
                        <div class="card-text">
                            <ul class="list-group p-4">
                                <li class="list-group-item list-group-item-success">&nbsp;</li>
                                <li class="list-group-item list-group-item-success">&nbsp;</li>
                                <li class="list-group-item list-group-item-success">&nbsp;</li>
                                <li class="list-group-item list-group-item-success">&nbsp;</li>
                            </ul>
                        </div>
                        <div class="card-text">
                            <p>Produk : <b> 	Surya</b></p>
                        </div>
                        <a href="#" class="btn btn-primary">Edit List Vending</a>
                    </div>
                </div>
            </div>
        </div>
    </div>
</div>

<!-- Option 1: Bootstrap Bundle with Popper -->
<script src="https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/js/bootstrap.bundle.min.js" integrity="sha384-MrcW6ZMFYlzcLA8Nl+NtUVF0sA7MsXsP1UyJoMp4YLEuNSfAP+JcXn/tWtIaxVXM" crossorigin="anonymous"></script>
<script src="https://ajax.googleapis.com/ajax/libs/jquery/3.6.0/jquery.min.js"></script>

<script>

    var refInterval = window.setInterval('update()', 1000); // 30 seconds

    var update = function() {
        $.ajax({
            type : 'GET',
            url : 'api/daftar/getDataDaftar.php',
            success : function(data){
                var dataJson = jQuery.parseJSON(data);
                // var json = $.parseJSON(j);
                $(dataJson["data_daftar"]).each(function(i,val){
                    $.each(val,function(k,v){
                        console.log(k+" : "+ v);
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


