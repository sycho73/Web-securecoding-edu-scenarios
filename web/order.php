<?php
header("Content-Type: text/html; charset=UTF-8");

$quantity_raw = $_POST['quantity'];
$special_count_raw = $_POST['special_count'];
$special_request_raw = $_POST['special_request'];

$quantity = escapeshellarg($quantity_raw);
$special_count = escapeshellarg($special_count_raw);
$special_request = escapeshellarg($special_request_raw);

$cmd = "../backend/order $quantity $special_count $special_request";
$output = shell_exec($cmd);
?>
<!DOCTYPE html>
<html lang="ko">
<head>
    <meta charset="UTF-8">
    <title>주문 결과</title>
</head>
<body>
    <h2>주문 결과</h2>

    <p><strong>주문 수량:</strong> <?php echo htmlspecialchars($quantity_raw); ?></p>
    <p><strong>특별상품 수량:</strong> <?php echo htmlspecialchars($special_count_raw); ?></p>
    <p><strong>추가 요구 사항:</strong> <?php echo htmlspecialchars($special_request_raw); ?></p>

    <?php if ($output === null): ?>
        <p style="color: red;"><strong>⚠️ 오류 발생: 프로그램이 비정상적으로 종료되었습니다 (버퍼 오버플로우 가능성)</strong></p>
    <?php else: ?>
        <pre><?php echo htmlspecialchars($output); ?></pre>
    <?php endif; ?>
</body>
</html>
