<?php
 //----------�s����Ʈw----------
	include("mysqlcntdb.php");
	//----------�s����Ʈw---------   
	$sql="UPDATE cuty SET cutyname = '$cutyname' WHERE   cutyno = '$cutyno' LIMIT 1";
    mysql_query($sql);	
?>
<script>
location.href = "../index.php?$Select=65";
</script>   