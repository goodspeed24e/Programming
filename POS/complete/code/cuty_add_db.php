<?php   
    //----------�s����Ʈw----------
	include("mysqlcntdb.php");
	//----------�s����Ʈw---------	
	$sql="INSERT INTO cuty (cutyno, cutyname) VALUES ('$cutyno', '$cutyname')"; 
    mysql_query($sql);	
?>
<script>
location.href = "../index.php?$Select=65";
</script>   