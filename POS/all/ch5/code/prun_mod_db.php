<?php
 //----------�s����Ʈw----------
	include("mysqlcntdb.php");
	//----------�s����Ʈw---------   
	$sql="UPDATE prun SET prunname = '$prunname' WHERE   prunno = '$prunno' LIMIT 1";
    mysql_query($sql);	
?>
<script>
location.href = "../index.php?$Select=65";
</script>   