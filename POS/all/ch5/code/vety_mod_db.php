<?php
 //----------�s����Ʈw----------
	include("mysqlcntdb.php");
	//----------�s����Ʈw---------   
	$sql="UPDATE vety SET vetyname = '$vetyname' WHERE   vetyno = '$vetyno' LIMIT 1";
    mysql_query($sql);	
?>
<script>
location.href = "../index.php?$Select=65";
</script>   