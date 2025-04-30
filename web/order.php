<?php
$quantity = escapeshellarg($_POST['quantity']);
$special_request = escapeshellarg($_POST['special_request']);

// C 실행 파일 경로 수정 (order_processor는 /var/www/html/에 복사되어 있어야 함)
$cmd = "../backend/order $quantity $special_request";
$output = shell_exec($cmd);

if ($output === null) {
    echo "⚠️ 명령 실행 실패: $cmd";
} else {
    echo "<pre>$output</pre>";
}
?>
