<!--// 執行完成回 index.php 主目錄頁面, 並顯示訊息 //-->
<script>
alert("<?php echo $message; ?>");
location.href = "../index.php?Select=10";
</script>