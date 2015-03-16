<?php
 //----------連接資料庫----------
	include("mysqlcntdb.php");
	//----------連接資料庫---------   
	$sql="UPDATE saty SET satyname = '$satyname' WHERE   satyno = '$satyno' LIMIT 1";
    mysql_query($sql);	
?>
<script>
location.href = "../index.php?$Select=65";
</script>   