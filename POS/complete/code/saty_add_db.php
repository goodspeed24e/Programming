<?php   
    //----------連接資料庫----------
	include("mysqlcntdb.php");
	//----------連接資料庫---------	
	$sql="INSERT INTO saty (satyno, satyname) VALUES ('$satyno', '$satyname')"; 
    mysql_query($sql);	
?>
<script>
location.href = "../index.php?$Select=65";
</script>   