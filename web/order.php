<?php
$quantity = escapeshellarg($_POST['quantity']);
$special_request = escapeshellarg($_POST['special_request']);

$cmd = "./backend/order $quantity $special_request";
$output = shell_exec($cmd);

echo "<pre>$output</pre>";
?>
