<?php   
    //----------�s����Ʈw----------
	include("mysqlcntdb.php");
	//----------�s����Ʈw---------	
	$sql="INSERT INTO vety (vetyno, vetyname) VALUES ('$vetyno', '$vetyname')"; 
    mysql_query($sql);	
?>
<script>
location.href = "../index.php?$Select=65";
</script>   