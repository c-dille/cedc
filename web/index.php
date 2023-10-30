<?php

$page_path = "404.php";

$uri = urldecode($_SERVER["REQUEST_URI"]);

switch($uri) :
	case "/paquets":
		$page_path = "./packages.php";
		break;
	case "/paquet":
		$page_path = "./package.php";
		break;
	case "/tarifs":
		$page_path = "./prices.php";
		break;
	case "/documentation":
		$page_path =  "./documentation.php";
		break;
	case "/téléchargements":
		$page_path =  "./downloads.php";
		break;
	case "/contact":
		$page_path = "./contact.php";
		break;
	case "/":
		$page_path = "./home.php";
		break;
endswitch;

$page = include ($page_path);

?>


<!DOCTYPE html>
<html lang="fr">
<?php include "./components/head.php"; ?>
	<body class="bg-gray-100 font-sans leading-normal tracking-normal" style="position: relative;
min-height: calc(100vh - 80px);
margin-top: -20px !important;">
<?php include "./components/nav.php";?>
	<?php $page["render"]() ?>
<?php include "./components/footer.php"; ?>
	</body>
</html>
