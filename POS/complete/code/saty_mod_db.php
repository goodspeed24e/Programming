<?php
 //----------�s����Ʈw----------
	include("mysqlcntdb.php");
	//----------�s����Ʈw---------   
	$sql="UPDATE saty SET satyname = '$satyname' WHERE   satyno = '$satyno' LIMIT 1";
    mysql_query($sql);	
?>
<script>
location.href = "../index.php?$Select=65";
</script>   