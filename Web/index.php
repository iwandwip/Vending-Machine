<?php
// Initialize the session
session_start();

// Check if the user is already logged in, if yes then redirect him to welcome page
if (isset($_SESSION["loggedin"]) && $_SESSION["loggedin"] === true) {
    header("location: user_page.php");
    exit;
}

?>

<!DOCTYPE html>
<html lang="en">

<head>
    <title>Vending Machine</title>
    <meta charset="utf-8"/>
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no"/>

    <link href="https://fonts.googleapis.com/css?family=Lato:300,400,700&display=swap" rel="stylesheet"/>

    <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/font-awesome/4.7.0/css/font-awesome.min.css"/>

    <link rel="stylesheet" href="css/style.css"/>
</head>

<body>

<section class="ftco-section">
    <div class="container" style="background: #007bff; padding: 50px; border-radius: 10px;">
        <div class="row justify-content-center">
            <div class="col-md-6 text-center mb-5">
                <!-- <h2 class="heading-section">Login #01</h2> -->
            </div>
        </div>
        <div class="row justify-content-center">
            <div class="col-md-7 col-lg-5">
                <div class="login-wrap p-4 p-md-5">
                    <div class="icon d-flex align-items-center justify-content-center">
                        <span class="fa fa-user-o"></span>
                    </div>
                    <h3 class="text-center mb-4">Sign In</h3>
                    <form action="" class="login-form">
                        <div class="text-md-right">
                            <!-- Login as -->
                            <div class="text-center">
                                <p>Login Sebagai <a href="admin_login.php">Admin</a></p>
                            </div>
                            <!-- Login as end -->
                        </div>
                        <div class="form-group">
                            <input type="text" name="username" class="form-control rounded-left" placeholder="Username"
                                   required/>
                        </div>

                        <div class="form-group d-flex">
                            <input type="password" name="password" class="form-control rounded-left"
                                   placeholder="Password" required/>
                        </div>

                        <?php
                        require_once "db_conn.php";
                        require_once "func.php";

                        if ($_SERVER["REQUEST_METHOD"] == "GET") {

                            if (isset($_GET["username"]) and isset($_GET["password"])) {

                                if (!userNamePassVerify(
                                    $_GET["username"],
                                    $_GET["password"],
                                    "id_user_penjual",
                                    $koneksi)) {
                                    echo '   <div class="alert alert-warning alert-dismissible fade show" role="alert">
                                                <strong>Username atau Password Salah!</strong> Check kembali Username dan Password anda.
                                                <button type="button" class="close" data-dismiss="alert" aria-label="Close">
                                                    <span aria-hidden="true">&times;</span>
                                                </button>
                                             </div>';
                                } else {
                                    session_start();

                                    $username = $_GET["username"];
                                    // Store data in session variables

                                    $_SESSION["loggedin"] = true;
                                    $_SESSION["username"] = $username;

                                    header("location: user_page.php");
                                }
                            }
                        }
                        ?>

                        <!-- Username Password Alert -->
                        <!-- <div class="alert alert-warning alert-dismissible fade show" role="alert">
                            <strong>Username atau Password Salah!</strong> Check kembali Username dan Password anda.
                            <button type="button" class="close" data-dismiss="alert" aria-label="Close">
                                <span aria-hidden="true">&times;</span>
                            </button>
                        </div> -->
                        <!-- Username Password Alert End -->

                        <div class="form-group">
                            <button type="submit" value="login" name="login"
                                    class="form-control btn btn-primary rounded submit px-3">
                                Login
                            </button>
                        </div>
                        <!-- Register buttons -->
                        <!--                        <div class="text-center">-->
                        <!--                            <p>Tidak punya akun? <a href="register.php">Register</a></p>-->
                        <!--                        </div>-->

                        <!--                        <div class="alert alert-warning" role="alert">-->
                        <!--                            This is a warning alert—check it out!-->
                        <!--                        </div>-->

                        <!-- <div class="form-group d-md-flex">
                            <div class="w-50">
                              <label class="checkbox-wrap checkbox-primary"
                                >Remember Me
                                <input type="checkbox" checked />
                                <span class="checkmark"></span>
                              </label>
                            </div>
                            <div class="w-50 text-md-right">
                              <a href="#">Forgot Password</a>
                            </div>
                          </div> -->
                    </form>
                </div>
            </div>
        </div>
    </div>
</section>

<script src="js/jquery.min.js"></script>
<script src="js/popper.js"></script>
<script src="js/bootstrap.min.js"></script>
<script src="js/main.js"></script>
</body>

</html>