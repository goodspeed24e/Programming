<?php   
    //----------�s����Ʈw----------
	include("mysqlcntdb.php");
	//----------�s����Ʈw---------	
	$sql="INSERT INTO prun (prunno, prunname) VALUES ('$prunno', '$prunname')"; 
    mysql_query($sql);	
?>
<script>
location.href = "../index.php?$Select=65";
</script>   