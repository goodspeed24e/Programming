<?php
    include("swmcntdb.php");	
	$sql="DELETE FROM vety WHERE vetyno = '$vetyno' LIMIT 1 ";
    mysql_query($sql);	
?>
<script>
location.href = "index.php?$Act=10";
</script>   