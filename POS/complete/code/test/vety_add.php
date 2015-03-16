<?php
    include("swmcntdb.php");	
	$sql="INSERT INTO vety (vetyno, vetyname) VALUES ('$vetyno', '$vetyname')"; 
    mysql_query($sql);	
?>
<script>
location.href = "index.php?$Act=10";
</script>   