<?php
 //----------�s����Ʈw----------
	include("mysqlcntdb.php");
	//----------�s����Ʈw---------   
	$sql="UPDATE prty SET prtyname = '$prtyname' WHERE   prtyno = '$prtyno' LIMIT 1";
    mysql_query($sql);	
?>
<script>
location.href = "../index.php?$Select=65";
</script>   