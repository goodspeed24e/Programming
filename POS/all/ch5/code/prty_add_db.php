<?php   
    //----------�s����Ʈw----------
	include("mysqlcntdb.php");
	//----------�s����Ʈw---------	
	$sql="INSERT INTO prty (prtyno, prtyname) VALUES ('$prtyno', '$prtyname')"; 
    mysql_query($sql);	
?>
<script>
location.href = "../index.php?$Select=65";
</script>   