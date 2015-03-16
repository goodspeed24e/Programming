<?php   
    //----------連接資料庫----------
	include("mysqlcntdb.php");
	//----------連接資料庫---------	
	$sql="INSERT INTO vety (vetyno, vetyname) VALUES ('$vetyno', '$vetyname')"; 
    mysql_query($sql);	
?>
<script>
location.href = "../index.php?$Select=65";
</script>   